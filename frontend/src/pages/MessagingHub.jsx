import { useState, useEffect } from 'react';
import { messagingAPI, userAPI, algoAPI } from '../services/api';
import { MessageSquare, Send, Search, Users, Clock, TrendingUp, Users2, Route } from 'lucide-react';
import '../styles/MessagingHub.css';

export default function MessagingHub() {
  const [currentUserId, setCurrentUserId] = useState(1); // Default logged-in user
  const [selectedContact, setSelectedContact] = useState(null);
  const [contacts, setContacts] = useState([]);
  const [allMessages, setAllMessages] = useState([]);
  const [messageText, setMessageText] = useState('');
  const [searchQuery, setSearchQuery] = useState('');
  const [loading, setLoading] = useState(false);
  const [error, setError] = useState(null);
  const [userCache, setUserCache] = useState(new Map());
  const [activeTab, setActiveTab] = useState('chat'); // chat, search, analytics, suggestions
  const [searchResults, setSearchResults] = useState(null);
  const [topConversations, setTopConversations] = useState([]);
  const [suggestions, setSuggestions] = useState([]);
  const [popularUsers, setPopularUsers] = useState([]);
  const [mutualInteractions, setMutualInteractions] = useState([]);
  const [searchMessagesDetails, setSearchMessagesDetails] = useState([]);
  const [pathResult, setPathResult] = useState(null);
  const [pathDestId, setPathDestId] = useState('');

  // Load analytics data on mount and when user changes
  useEffect(() => {
    loadAllData();
    loadMessages();
  }, [currentUserId]);

  const getUserDetails = async (userId) => {
    if (userCache.has(userId)) {
      return userCache.get(userId);
    }
    try {
      const response = await userAPI.getUser(userId);
      const username = response.user?.username || response.username || `User ${userId}`;
      setUserCache(prev => new Map(prev).set(userId, username));
      return username;
    } catch (err) {
      console.error(`Failed to fetch user ${userId}:`, err);
      const fallback = `User ${userId}`;
      setUserCache(prev => new Map(prev).set(userId, fallback));
      return fallback;
    }
  };

  const loadMessages = async () => {
    try {
      // Fetch all messages from backend
      const response = await fetch('http://localhost:8081/api/messages');
      if (response.ok) {
        const data = await response.json();
        setAllMessages(data.messages || []);
      }
    } catch (err) {
      console.error('Failed to load messages:', err);
    }
  };

  const loadAllData = async () => {
    setLoading(true);
    try {
      // Load top conversations
      const topKData = await messagingAPI.getTopK(currentUserId, 10);
      const topConvos = await Promise.all(
        (topKData.messages || []).map(async (msg) => ({
          ...msg,
          username: await getUserDetails(msg.userId)
        }))
      );
      setTopConversations(topConvos);
      
      // Create contacts from top conversations
      setContacts(topConvos);
      
      // Auto-select first contact
      if (topConvos.length > 0 && !selectedContact) {
        setSelectedContact(topConvos[0]);
      }

      // Load friend suggestions
      const suggestionsData = await messagingAPI.getSuggestions(currentUserId, 5);
      const suggestionsList = await Promise.all(
        (suggestionsData.friends || []).map(async (userId) => ({
          id: userId,
          username: await getUserDetails(userId)
        }))
      );
      setSuggestions(suggestionsList);

      // Load popular users - use messaging rank API
      const popularResponse = await fetch(`http://localhost:8082/msg/rank/10`);
      if (popularResponse.ok) {
        const popularData = await popularResponse.json();
        const popularList = await Promise.all(
          (popularData.rank || []).map(async (user) => {
            const username = await getUserDetails(user.userId);
            return {
              userId: user.userId,
              username: username,
              popularity: user.popularity
            };
          })
        );
        setPopularUsers(popularList);
      }

      // Load mutual interactions
      const mutualData = await messagingAPI.getMutualInteractions(currentUserId);
      const mutualList = await Promise.all(
        (mutualData.mutual || []).map(async (pair) => ({
          ...pair,
          u1Name: await getUserDetails(pair.u1),
          u2Name: await getUserDetails(pair.u2)
        }))
      );
      setMutualInteractions(mutualList);

    } catch (err) {
      setError('Failed to load data');
      console.error(err);
    } finally {
      setLoading(false);
    }
  };

  const handleSendMessage = async () => {
    if (!selectedContact || !messageText.trim()) {
      return;
    }

    setLoading(true);
    setError(null);
    
    try {
      const response = await messagingAPI.sendMessage(
        currentUserId,
        selectedContact.userId,
        messageText.trim()
      );

      if (response.status === 'success') {
        // Add message to local state optimistically
        const newMsg = {
          id: response.messageId,
          senderId: currentUserId,
          receiverId: selectedContact.userId,
          text: messageText.trim(),
          timestamp: Date.now() / 1000
        };
        setAllMessages(prev => [...prev, newMsg]);
        setMessageText('');
        
        // Reload messages and conversations
        await loadMessages();
        await loadAllData();
        
        // Scroll to bottom
        setTimeout(() => {
          const messagesContainer = document.querySelector('.messages-container');
          if (messagesContainer) {
            messagesContainer.scrollTop = messagesContainer.scrollHeight;
          }
        }, 100);
      }
    } catch (err) {
      setError('Failed to send message: ' + err.message);
      console.error(err);
    } finally {
      setLoading(false);
    }
  };

  const handleSearch = async (isPrefix = false) => {
    if (!searchQuery.trim()) {
      setError('Please enter a search term');
      return;
    }
    
    setLoading(true);
    setError(null);
    
    try {
      const data = isPrefix 
        ? await messagingAPI.searchPrefix(searchQuery)
        : await messagingAPI.searchWord(searchQuery);
      
      setSearchResults({
        query: searchQuery,
        type: isPrefix ? 'prefix' : 'word',
        results: data.results || [],
        count: (data.results || []).length
      });
      
      // Fetch full message details for each message ID
      if (data.results && data.results.length > 0) {
        const messageDetailsPromises = data.results.map(async (msgId) => {
          try {
            const response = await fetch(`http://localhost:8081/api/messages/${msgId}`);
            if (response.ok) {
              const msgData = await response.json();
              // Enrich with usernames
              const senderName = await getUserDetails(parseInt(msgData.senderId));
              const receiverName = await getUserDetails(parseInt(msgData.receiverId));
              return {
                ...msgData,
                senderName,
                receiverName
              };
            }
            return null;
          } catch (err) {
            console.error(`Failed to fetch message ${msgId}:`, err);
            return null;
          }
        });
        
        const messagesDetails = await Promise.all(messageDetailsPromises);
        setSearchMessagesDetails(messagesDetails.filter(m => m !== null));
      } else {
        setSearchMessagesDetails([]);
      }
    } catch (err) {
      setError('Search failed: ' + err.message);
      console.error(err);
    } finally {
      setLoading(false);
    }
  };

  const findShortestPath = async (destUserId) => {
    if (!destUserId || destUserId === currentUserId) {
      setPathResult(null);
      return null;
    }
    
    setLoading(true);
    setError(null);
    
    try {
      const data = await messagingAPI.getShortestPath(currentUserId, destUserId);
      
      if (data.path && data.path.length > 0) {
        const pathWithNames = await Promise.all(
          data.path.map(async (userId) => ({
            id: userId,
            username: await getUserDetails(userId)
          }))
        );
        setPathResult(pathWithNames);
        return pathWithNames;
      } else {
        setPathResult([]);
        return [];
      }
    } catch (err) {
      setError('Failed to find path: ' + err.message);
      console.error(err);
      setPathResult(null);
      return null;
    } finally {
      setLoading(false);
    }
  };

  const getConversationMessages = () => {
    if (!selectedContact) return [];
    return allMessages.filter(msg => 
      (msg.senderId === currentUserId && msg.receiverId === selectedContact.userId) ||
      (msg.senderId === selectedContact.userId && msg.receiverId === currentUserId)
    ).sort((a, b) => a.timestamp - b.timestamp);
  };

  const handleKeyPress = (e) => {
    if (e.key === 'Enter' && !e.shiftKey) {
      e.preventDefault();
      handleSendMessage();
    }
  };

  const formatTime = (timestamp) => {
    const date = new Date(timestamp * 1000);
    return date.toLocaleTimeString('en-US', { hour: '2-digit', minute: '2-digit' });
  };

  return (
    <div className="messaging-hub-modern">
      {/* Header with tabs */}
      <div className="messaging-header-tabs">
        <button 
          className={`tab-btn ${activeTab === 'chat' ? 'active' : ''}`}
          onClick={() => setActiveTab('chat')}
        >
          <MessageSquare size={18} />
          Chat
        </button>
        <button 
          className={`tab-btn ${activeTab === 'search' ? 'active' : ''}`}
          onClick={() => setActiveTab('search')}
        >
          <Search size={18} />
          Search
        </button>
        <button 
          className={`tab-btn ${activeTab === 'analytics' ? 'active' : ''}`}
          onClick={() => setActiveTab('analytics')}
        >
          <TrendingUp size={18} />
          Analytics
        </button>
        <button 
          className={`tab-btn ${activeTab === 'suggestions' ? 'active' : ''}`}
          onClick={() => setActiveTab('suggestions')}
        >
          <Users2 size={18} />
          Network
        </button>
      </div>

      {/* Chat Tab */}
      {activeTab === 'chat' && (
        <div className="chat-container">
          <div className="contacts-sidebar">
            <div className="sidebar-header">
              <div className="header-content">
                <MessageSquare size={24} />
                <h2>Top Conversations</h2>
              </div>
              <div className="current-user-badge">
                {userCache.get(currentUserId) || `User ${currentUserId}`}
              </div>
            </div>

            <div className="contacts-list">
              {loading && contacts.length === 0 ? (
                <div className="loading-state">
                  <div className="spinner"></div>
                  <p>Loading...</p>
                </div>
              ) : contacts.length === 0 ? (
                <div className="empty-state">
                  <Users size={48} />
                  <p>No conversations yet</p>
                </div>
              ) : (
                contacts.map((contact) => (
                  <div
                    key={contact.userId}
                    className={`contact-item ${selectedContact?.userId === contact.userId ? 'active' : ''}`}
                    onClick={() => setSelectedContact(contact)}
                  >
                    <div className="contact-avatar">
                      {contact.username.charAt(0).toUpperCase()}
                    </div>
                    <div className="contact-info">
                      <div className="contact-header">
                        <span className="contact-name">{contact.username}</span>
                        <span className="contact-weight">({contact.weight} msgs)</span>
                      </div>
                    </div>
                  </div>
                ))
              )}
            </div>
          </div>

          <div className="chat-main">
            {selectedContact ? (
              <>
                <div className="chat-header">
                  <div className="chat-header-info">
                    <div className="chat-avatar">
                      {selectedContact.username.charAt(0).toUpperCase()}
                    </div>
                    <div>
                      <h3>{selectedContact.username}</h3>
                      <span className="status-indicator">{selectedContact.weight} messages exchanged</span>
                    </div>
                  </div>
                </div>

                <div className="messages-container">
                  {getConversationMessages().length === 0 ? (
                    <div className="empty-conversation">
                      <MessageSquare size={64} />
                      <p>No messages yet</p>
                      <span>Start the conversation!</span>
                    </div>
                  ) : (
                    getConversationMessages().map((msg) => (
                      <div
                        key={msg.id}
                        className={`message ${msg.senderId === currentUserId ? 'sent' : 'received'}`}
                      >
                        <div className="message-bubble">
                          <p>{msg.text}</p>
                          <span className="message-time">
                            <Clock size={12} />
                            {formatTime(msg.timestamp)}
                          </span>
                        </div>
                      </div>
                    ))
                  )}
                </div>

                <div className="chat-input-container">
                  {error && (
                    <div className="error-banner">{error}</div>
                  )}
                  <div className="chat-input">
                    <textarea
                      value={messageText}
                      onChange={(e) => setMessageText(e.target.value)}
                      onKeyPress={handleKeyPress}
                      placeholder="Type a message..."
                      rows={1}
                      disabled={loading}
                    />
                    <button
                      className="send-button"
                      onClick={handleSendMessage}
                      disabled={loading || !messageText.trim()}
                    >
                      <Send size={20} />
                    </button>
                  </div>
                </div>
              </>
            ) : (
              <div className="no-contact-selected">
                <MessageSquare size={80} />
                <h3>Select a conversation</h3>
                <p>Choose from your top conversations</p>
              </div>
            )}
          </div>
        </div>
      )}

      {/* Search Tab */}
      {activeTab === 'search' && (
        <div className="search-tab-content">
          <div className="search-section">
            <h2>Search Messages</h2>
            <div className="search-input-group">
              <input
                type="text"
                placeholder="Enter word or prefix..."
                value={searchQuery}
                onChange={(e) => setSearchQuery(e.target.value)}
              />
              <div className="search-buttons">
                <button className="action-btn" onClick={() => handleSearch(false)}>
                  Search Exact Word
                </button>
                <button className="action-btn" onClick={() => handleSearch(true)}>
                  Search Prefix
                </button>
              </div>
            </div>

            {searchResults && (
              <div className="search-results">
                <h3>Results for "{searchResults.query}" ({searchResults.type})</h3>
                <p className="results-count">{searchResults.count} message(s) found</p>
                <div className="results-list">
                  {searchMessagesDetails.length > 0 ? (
                    searchMessagesDetails.map((msg) => (
                      <div key={msg.id} className="result-item">
                        <div className="result-header">
                          <span className="result-sender">{msg.senderName}</span>
                          <span className="result-arrow">→</span>
                          <span className="result-receiver">{msg.receiverName}</span>
                        </div>
                        <div className="result-text">{msg.text}</div>
                        <div className="result-meta">
                          <span className="result-id">ID: {msg.id}</span>
                          <span className="result-time">{new Date(msg.timestamp * 1000).toLocaleString()}</span>
                        </div>
                      </div>
                    ))
                  ) : searchResults.results.length === 0 ? (
                    <p className="no-results">No messages found</p>
                  ) : (
                    <div className="loading-state">
                      <div className="spinner"></div>
                      <p>Loading message details...</p>
                    </div>
                  )}
                </div>
              </div>
            )}
          </div>
        </div>
      )}

      {/* Analytics Tab */}
      {activeTab === 'analytics' && (
        <div className="analytics-tab-content">
          <h2>Messaging Analytics</h2>
          
          <div className="analytics-grid">
            <div className="analytics-card">
              <h3>
                <TrendingUp size={20} />
                Most Popular Users
              </h3>
              <div className="user-list">
                {popularUsers.length === 0 ? (
                  <p className="no-data">No popular users found</p>
                ) : (
                  popularUsers.map((user, idx) => (
                    <div key={user.userId} className="user-item">
                      <span className="rank">#{idx + 1}</span>
                      <span className="user-name">{user.username}</span>
                      <span className="popularity-score">{user.popularity} interactions</span>
                    </div>
                  ))
                )}
              </div>
            </div>

            <div className="analytics-card">
              <h3>
                <Users2 size={20} />
                Mutual Interactions
              </h3>
              <p className="card-description">People in your network who message each other</p>
              <div className="mutual-list">
                {mutualInteractions.length > 0 ? (
                  mutualInteractions.map((pair, idx) => (
                    <div key={idx} className="mutual-item">
                      {pair.u1Name} ↔️ {pair.u2Name}
                    </div>
                  ))
                ) : (
                  <p className="no-data">No mutual interactions found</p>
                )}
              </div>
            </div>
          </div>
        </div>
      )}

      {/* Network/Suggestions Tab */}
      {activeTab === 'suggestions' && (
        <div className="suggestions-tab-content">
          <h2>Network Insights</h2>
          
          <div className="suggestions-grid">
            <div className="suggestions-card">
              <h3>
                <Users size={20} />
                Friend Suggestions
              </h3>
              <p className="card-description">People you might want to connect with</p>
              <div className="suggestions-list">
                {suggestions.length > 0 ? (
                  suggestions.map((user) => (
                    <div key={user.id} className="suggestion-item">
                      <div className="suggestion-avatar">
                        {user.username.charAt(0).toUpperCase()}
                      </div>
                      <div className="suggestion-info">
                        <span className="suggestion-name">{user.username}</span>
                        <button 
                          className="start-chat-btn"
                          onClick={() => {
                            setSelectedContact({ userId: user.id, username: user.username, weight: 0 });
                            setActiveTab('chat');
                          }}
                        >
                          Start Chat
                        </button>
                      </div>
                    </div>
                  ))
                ) : (
                  <p className="no-data">No suggestions available</p>
                )}
              </div>
            </div>

            <div className="path-finder-card">
              <h3>
                <Route size={20} />
                Message Path Finder
              </h3>
              <p className="card-description">Find shortest messaging chain to any user</p>
              <div className="path-input">
                <input
                  type="number"
                  placeholder="Enter User ID"
                  min="1"
                  onChange={(e) => {
                    const destId = parseInt(e.target.value);
                    if (destId && destId !== currentUserId) {
                      findShortestPath(destId);
                    }
                  }}
                />
              </div>
            </div>
          </div>
        </div>
      )}

      {loading && (
        <div className="loading-overlay">
          <div className="spinner"></div>
        </div>
      )}
    </div>
  );
}
