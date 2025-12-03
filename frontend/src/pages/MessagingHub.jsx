import { useState } from 'react';
import { messagingAPI } from '../services/api';
import { MessageSquare, Send, Search, Users, TrendingUp, Navigation } from 'lucide-react';
import '../styles/MessagingHub.css';

export default function MessagingHub() {
  const [activeSection, setActiveSection] = useState('send');
  const [senderId, setSenderId] = useState('1');
  const [receiverId, setReceiverId] = useState('');
  const [messageText, setMessageText] = useState('');
  const [searchQuery, setSearchQuery] = useState('');
  const [userId, setUserId] = useState('1');
  const [kValue, setKValue] = useState('5');
  const [topN, setTopN] = useState('10');
  const [srcUserId, setSrcUserId] = useState('');
  const [destUserId, setDestUserId] = useState('');
  const [result, setResult] = useState(null);
  const [loading, setLoading] = useState(false);
  const [error, setError] = useState(null);

  const handleSendMessage = async () => {
    if (!receiverId || !messageText) {
      setError('Please enter receiver ID and message text');
      return;
    }
    setLoading(true);
    setError(null);
    try {
      const data = await messagingAPI.sendMessage(
        parseInt(senderId),
        parseInt(receiverId),
        messageText
      );
      setResult(data);
      setMessageText('');
    } catch (err) {
      setError(err.message);
    } finally {
      setLoading(false);
    }
  };

  const handleSearchWord = async () => {
    if (!searchQuery) {
      setError('Please enter a search word');
      return;
    }
    setLoading(true);
    setError(null);
    try {
      const data = await messagingAPI.searchWord(searchQuery);
      setResult(data);
    } catch (err) {
      setError(err.message);
    } finally {
      setLoading(false);
    }
  };

  const handleSearchPrefix = async () => {
    if (!searchQuery) {
      setError('Please enter a search prefix');
      return;
    }
    setLoading(true);
    setError(null);
    try {
      const data = await messagingAPI.searchPrefix(searchQuery);
      setResult(data);
    } catch (err) {
      setError(err.message);
    } finally {
      setLoading(false);
    }
  };

  const handleTopK = async () => {
    setLoading(true);
    setError(null);
    try {
      const data = await messagingAPI.getTopK(parseInt(userId), parseInt(kValue));
      setResult(data);
    } catch (err) {
      setError(err.message);
    } finally {
      setLoading(false);
    }
  };

  const handleSuggestions = async () => {
    setLoading(true);
    setError(null);
    try {
      const data = await messagingAPI.getSuggestions(parseInt(userId), parseInt(kValue));
      setResult(data);
    } catch (err) {
      setError(err.message);
    } finally {
      setLoading(false);
    }
  };

  const handleMutual = async () => {
    setLoading(true);
    setError(null);
    try {
      const data = await messagingAPI.getMutualInteractions(parseInt(userId));
      setResult(data);
    } catch (err) {
      setError(err.message);
    } finally {
      setLoading(false);
    }
  };

  const handlePopularity = async () => {
    setLoading(true);
    setError(null);
    try {
      const data = await messagingAPI.getPopularityRank(parseInt(topN));
      setResult(data);
    } catch (err) {
      setError(err.message);
    } finally {
      setLoading(false);
    }
  };

  const handleShortestPath = async () => {
    if (!srcUserId || !destUserId) {
      setError('Please enter both source and destination user IDs');
      return;
    }
    setLoading(true);
    setError(null);
    try {
      const data = await messagingAPI.getShortestPath(parseInt(srcUserId), parseInt(destUserId));
      setResult(data);
    } catch (err) {
      setError(err.message);
    } finally {
      setLoading(false);
    }
  };

  return (
    <div className="messaging-hub">
      <div className="messaging-header">
        <MessageSquare size={24} />
        <h1>Messaging Hub</h1>
        <p>Send messages and explore messaging analytics</p>
      </div>

      <div className="messaging-sections">
        <button
          className={`section-btn ${activeSection === 'send' ? 'active' : ''}`}
          onClick={() => setActiveSection('send')}
        >
          <Send size={16} />
          Send Message
        </button>
        <button
          className={`section-btn ${activeSection === 'search' ? 'active' : ''}`}
          onClick={() => setActiveSection('search')}
        >
          <Search size={16} />
          Search Messages
        </button>
        <button
          className={`section-btn ${activeSection === 'analytics' ? 'active' : ''}`}
          onClick={() => setActiveSection('analytics')}
        >
          <TrendingUp size={16} />
          Analytics
        </button>
        <button
          className={`section-btn ${activeSection === 'path' ? 'active' : ''}`}
          onClick={() => setActiveSection('path')}
        >
          <Navigation size={16} />
          Message Path
        </button>
      </div>

      <div className="messaging-content">
        {activeSection === 'send' && (
          <div className="section-content">
            <h2>Send New Message</h2>
            
            <div className="input-group">
              <label>Sender ID</label>
              <input
                type="number"
                value={senderId}
                onChange={(e) => setSenderId(e.target.value)}
                placeholder="Your user ID"
              />
            </div>

            <div className="input-group">
              <label>Receiver ID</label>
              <input
                type="number"
                value={receiverId}
                onChange={(e) => setReceiverId(e.target.value)}
                placeholder="Recipient user ID"
              />
            </div>

            <div className="input-group">
              <label>Message</label>
              <textarea
                value={messageText}
                onChange={(e) => setMessageText(e.target.value)}
                placeholder="Type your message here..."
                rows={4}
              />
            </div>

            <button className="action-btn primary" onClick={handleSendMessage}>
              <Send size={16} />
              Send Message
            </button>
          </div>
        )}

        {activeSection === 'search' && (
          <div className="section-content">
            <h2>Search Messages</h2>
            
            <div className="input-group">
              <label>Search Query</label>
              <input
                type="text"
                value={searchQuery}
                onChange={(e) => setSearchQuery(e.target.value)}
                placeholder="Enter word or prefix to search"
              />
            </div>

            <div className="button-row">
              <button className="action-btn primary" onClick={handleSearchWord}>
                Search Exact Word
              </button>
              <button className="action-btn primary" onClick={handleSearchPrefix}>
                Search by Prefix
              </button>
            </div>

            <div className="info-box">
              <p><strong>Exact Word:</strong> Find messages containing the exact word.</p>
              <p><strong>Prefix:</strong> Find messages with words starting with the prefix.</p>
            </div>
          </div>
        )}

        {activeSection === 'analytics' && (
          <div className="section-content">
            <h2>Messaging Analytics</h2>
            
            <div className="input-group">
              <label>User ID</label>
              <input
                type="number"
                value={userId}
                onChange={(e) => setUserId(e.target.value)}
                placeholder="Enter user ID"
              />
            </div>

            <div className="input-group">
              <label>K Value (for Top-K and Suggestions)</label>
              <input
                type="number"
                value={kValue}
                onChange={(e) => setKValue(e.target.value)}
                placeholder="Enter K value"
              />
            </div>

            <div className="button-grid">
              <button className="action-btn primary" onClick={handleTopK}>
                Top K Conversations
              </button>
              <button className="action-btn primary" onClick={handleSuggestions}>
                Friend Suggestions
              </button>
              <button className="action-btn primary" onClick={handleMutual}>
                Mutual Interactions
              </button>
            </div>

            <div className="divider"></div>

            <div className="input-group">
              <label>Top N (for Popularity Ranking)</label>
              <input
                type="number"
                value={topN}
                onChange={(e) => setTopN(e.target.value)}
                placeholder="Enter N value"
              />
            </div>

            <button className="action-btn primary" onClick={handlePopularity}>
              Get Popularity Ranking
            </button>
          </div>
        )}

        {activeSection === 'path' && (
          <div className="section-content">
            <h2>Shortest Messaging Path</h2>
            
            <div className="input-group">
              <label>Source User ID</label>
              <input
                type="number"
                value={srcUserId}
                onChange={(e) => setSrcUserId(e.target.value)}
                placeholder="Enter source user ID"
              />
            </div>

            <div className="input-group">
              <label>Destination User ID</label>
              <input
                type="number"
                value={destUserId}
                onChange={(e) => setDestUserId(e.target.value)}
                placeholder="Enter destination user ID"
              />
            </div>

            <button className="action-btn primary" onClick={handleShortestPath}>
              Find Messaging Path
            </button>

            <div className="info-box">
              <p>Finds the shortest chain of message interactions between two users.</p>
            </div>
          </div>
        )}

        {loading && (
          <div className="result-box loading">
            <div className="spinner"></div>
            <p>Loading...</p>
          </div>
        )}

        {error && (
          <div className="result-box error">
            <h3>Error</h3>
            <p>{error}</p>
          </div>
        )}

        {result && !loading && (
          <div className="result-box success">
            <h3>Result</h3>
            <pre>{JSON.stringify(result, null, 2)}</pre>
          </div>
        )}
      </div>
    </div>
  );
}
