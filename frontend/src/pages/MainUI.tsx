import { useState } from 'react';
import Sidebar from '../components/Sidebar';
import TabBar from '../components/TabBar';
import Pane from '../components/Pane';
import Splitter from '../components/Splitter';
import GraphView from '../components/GraphView';
import NetworkOverview from '../components/NetworkOverview';
import UserProfileView from '../components/UserProfileView';
import PostView from '../components/PostView';
import RightInfoPane from '../components/RightInfoPane';
import GraphExplorer from './GraphExplorer';
import MessagingHub from './MessagingHub';
import GraphStats from './GraphStats';
import PopularUsers from './PopularUsers';
import ShortestPath from '../components/ShortestPath';
import Dashboard from '../components/Dashboard';
import { Network, User, FileText, Home, Activity, MessageSquare, BarChart3, Trophy, Navigation, Globe } from 'lucide-react';
import '../styles/MainUI.css';

interface UserData {
  userId: number;
  username: string;
}

interface MainUIProps {
  user: UserData;
  onLogout: () => void;
}

export default function MainUI({ user, onLogout }: MainUIProps) {
  const [tabs, setTabs] = useState([
    { id: 'home', title: 'Home', type: 'home', icon: <Home size={14} /> }
  ]);
  const [activeTab, setActiveTab] = useState('home');
  const [leftWidth, setLeftWidth] = useState(250);
  const [rightWidth, setRightWidth] = useState(300);
  const [showRightPane, setShowRightPane] = useState(false);
  const [selectedNode, setSelectedNode] = useState(null);

  const openTab = (type, data) => {
    const existingTab = tabs.find(
      tab => tab.type === type && JSON.stringify(tab.data) === JSON.stringify(data)
    );

    if (existingTab) {
      setActiveTab(existingTab.id);
      return;
    }

    let title = '';
    let icon = null;

    switch (type) {
      case 'user':
        title = data.user.name;
        icon = <User size={14} />;
        break;
      case 'graph':
        title = data.graphId === 'main' ? 'Main Network' : 'Communities';
        icon = <Network size={14} />;
        break;
      case 'network-overview':
        title = 'Network Overview';
        icon = <Globe size={14} />;
        break;
      case 'post':
        title = 'Post';
        icon = <FileText size={14} />;
        break;
      case 'graph-explorer':
        title = 'Graph Explorer';
        icon = <Activity size={14} />;
        break;
      case 'messaging-hub':
        title = 'Messaging Hub';
        icon = <MessageSquare size={14} />;
        break;
      case 'graph-stats':
        title = 'Network Analytics';
        icon = <BarChart3 size={14} />;
        break;
      case 'leaderboard':
        title = 'Leaderboard';
        icon = <Trophy size={14} />;
        break;
      case 'shortest-path':
        title = 'Shortest Path';
        icon = <Navigation size={14} />;
        break;
      default:
        title = 'New Tab';
    }

    const newTab = {
      id: `${type}-${Date.now()}`,
      title,
      type,
      data,
      icon
    };

    setTabs([...tabs, newTab]);
    setActiveTab(newTab.id);
  };

  const closeTab = (tabId) => {
    const newTabs = tabs.filter(tab => tab.id !== tabId);
    setTabs(newTabs);

    if (activeTab === tabId && newTabs.length > 0) {
      setActiveTab(newTabs[newTabs.length - 1].id);
    }
  };

  const handleUserClick = (user) => {
    openTab('user', { user });
  };

  const handlePostClick = (post) => {
    openTab('post', { post });
  };

  const handleNavigate = (type, data) => {
    if (type === 'home') {
      setActiveTab('home');
    } else if (type === 'graph') {
      openTab('graph', data);
    } else if (type === 'graph-explorer') {
      openTab('graph-explorer', {});
    } else if (type === 'messaging-hub') {
      openTab('messaging-hub', {});
    }
  };

  const handleNodeClick = (user) => {
    setSelectedNode({ id: user.id, label: user.name, group: 1 });
    setShowRightPane(true);
  };

  const handleLeftDrag = (clientX) => {
    setLeftWidth(Math.max(200, Math.min(400, clientX)));
  };

  const handleRightDrag = (clientX) => {
    setRightWidth(Math.max(250, Math.min(500, window.innerWidth - clientX)));
  };

  const currentTab = tabs.find(tab => tab.id === activeTab);

  const renderTabContent = () => {
    if (!currentTab) return null;

    switch (currentTab.type) {
      case 'home':
        return (
          <Dashboard 
            userId={user.userId} 
            username={user.username}
            onOpenTab={openTab}
          />
        );
      case 'user':
        return (
          <UserProfileView
            user={currentTab.data.user}
            onPostClick={handlePostClick}
            onUserClick={handleUserClick}
          />
        );
      case 'graph':
        return (
          <GraphView
            graphId={currentTab.data.graphId}
            onNodeClick={handleNodeClick}
          />
        );
      case 'network-overview':
        return <NetworkOverview />;
      case 'post':
        return (
          <PostView
            post={currentTab.data.post}
            onUserClick={handleUserClick}
          />
        );
      case 'graph-explorer':
        return <GraphExplorer />;
      case 'messaging-hub':
        return <MessagingHub />;
      case 'graph-stats':
        return <GraphStats />;
      case 'leaderboard':
        return <PopularUsers />;
      case 'shortest-path':
        return <ShortestPath />;
      default:
        return <div style={{ padding: '1.5rem', color: 'var(--text-secondary)' }}>Unknown view type</div>;
    }
  };

  return (
    <div className="main-ui">
      <div className="layout-section" style={{ width: leftWidth, minWidth: 200 }}>
        <Sidebar onUserClick={handleUserClick} onNavigate={handleNavigate} user={user} onLogout={onLogout} />
      </div>

      <Splitter onDrag={handleLeftDrag} />

      <div className="layout-section" style={{ flex: 1, minWidth: 0 }}>
        <TabBar
          tabs={tabs}
          activeTab={activeTab}
          onTabChange={setActiveTab}
          onTabClose={closeTab}
        />
        <Pane>
          {renderTabContent()}
        </Pane>
      </div>

      {showRightPane && (
        <>
          <Splitter onDrag={handleRightDrag} />
          <div className="layout-section" style={{ width: rightWidth, minWidth: 250 }}>
            <RightInfoPane
              selectedNode={selectedNode}
              onClose={() => setShowRightPane(false)}
              onUserClick={handleUserClick}
            />
          </div>
        </>
      )}
    </div>
  );
}

function HomeView({ onPostClick, onUserClick }) {
  const recentPosts = getRecentPosts(10);

  return (
    <div style={{ height: '100%', overflow: 'auto' }}>
      <div style={{ maxWidth: '64rem', margin: '0 auto', padding: '2rem' }}>
        <div style={{ marginBottom: '2rem' }}>
          <h1 style={{ fontSize: '1.875rem', fontWeight: '700', marginBottom: '0.5rem' }}>
            Social Graph Explorer
          </h1>
          <p style={{ color: 'var(--text-secondary)' }}>
            Explore social networks through data structures and algorithms
          </p>
        </div>

        <div style={{ display: 'grid', gridTemplateColumns: 'repeat(3, 1fr)', gap: '1rem', marginBottom: '2rem' }}>
          <div style={{ backgroundColor: 'var(--bg-secondary)', borderRadius: '8px', padding: '1.5rem' }}>
            <div style={{ display: 'flex', alignItems: 'center', gap: '0.75rem', marginBottom: '0.5rem' }}>
              <Network size={20} style={{ color: '#3b82f6' }} />
              <h3 style={{ fontSize: '0.875rem', fontWeight: '600' }}>Network</h3>
            </div>
            <p style={{ fontSize: '1.5rem', fontWeight: '700' }}>10</p>
            <p style={{ fontSize: '0.75rem', color: 'var(--text-muted)', marginTop: '0.25rem' }}>Active nodes</p>
          </div>

          <div style={{ backgroundColor: 'var(--bg-secondary)', borderRadius: '8px', padding: '1.5rem' }}>
            <div style={{ display: 'flex', alignItems: 'center', gap: '0.75rem', marginBottom: '0.5rem' }}>
              <User size={20} style={{ color: '#8b5cf6' }} />
              <h3 style={{ fontSize: '0.875rem', fontWeight: '600' }}>Users</h3>
            </div>
            <p style={{ fontSize: '1.5rem', fontWeight: '700' }}>10</p>
            <p style={{ fontSize: '0.75rem', color: 'var(--text-muted)', marginTop: '0.25rem' }}>Total users</p>
          </div>

          <div style={{ backgroundColor: 'var(--bg-secondary)', borderRadius: '8px', padding: '1.5rem' }}>
            <div style={{ display: 'flex', alignItems: 'center', gap: '0.75rem', marginBottom: '0.5rem' }}>
              <FileText size={20} style={{ color: '#10b981' }} />
              <h3 style={{ fontSize: '0.875rem', fontWeight: '600' }}>Posts</h3>
            </div>
            <p style={{ fontSize: '1.5rem', fontWeight: '700' }}>15</p>
            <p style={{ fontSize: '0.75rem', color: 'var(--text-muted)', marginTop: '0.25rem' }}>Total posts</p>
          </div>
        </div>

        <h2 style={{ fontSize: '1.25rem', fontWeight: '600', marginBottom: '1rem' }}>Recent Activity</h2>
        <div style={{ display: 'flex', flexDirection: 'column', gap: '1rem' }}>
          {recentPosts.map((post) => {
            const author = { id: post.userId, name: `User ${post.userId}`, avatar: `U${post.userId}` };
            return (
              <div
                key={post.id}
                onClick={() => onPostClick(post)}
                style={{
                  backgroundColor: 'var(--bg-secondary)',
                  borderRadius: '8px',
                  padding: '1rem',
                  cursor: 'pointer',
                  transition: 'background-color 0.2s'
                }}
                onMouseOver={(e) => e.currentTarget.style.backgroundColor = 'var(--bg-tertiary)'}
                onMouseOut={(e) => e.currentTarget.style.backgroundColor = 'var(--bg-secondary)'}
              >
                <div style={{ display: 'flex', alignItems: 'center', gap: '0.75rem', marginBottom: '0.75rem' }}>
                  <div
                    onClick={(e) => {
                      e.stopPropagation();
                      onUserClick(author);
                    }}
                    style={{
                      width: '40px',
                      height: '40px',
                      borderRadius: '50%',
                      background: 'linear-gradient(135deg, #3b82f6, #8b5cf6)',
                      display: 'flex',
                      alignItems: 'center',
                      justifyContent: 'center',
                      fontSize: '0.875rem',
                      fontWeight: '600',
                      color: 'white',
                      cursor: 'pointer'
                    }}
                  >
                    {author.avatar}
                  </div>
                  <div>
                    <p style={{ fontSize: '0.875rem', fontWeight: '500' }}>{author.name}</p>
                    <p style={{ fontSize: '0.75rem', color: 'var(--text-muted)' }}>
                      {new Date(post.timestamp).toLocaleString()}
                    </p>
                  </div>
                </div>
                <p style={{
                  fontSize: '0.875rem',
                  color: 'var(--text-secondary)',
                  overflow: 'hidden',
                  textOverflow: 'ellipsis',
                  display: '-webkit-box',
                  WebkitLineClamp: 2,
                  WebkitBoxOrient: 'vertical'
                }}>
                  {post.content}
                </p>
                <div style={{ display: 'flex', gap: '1rem', marginTop: '0.75rem', fontSize: '0.75rem', color: 'var(--text-muted)' }}>
                  <span>{post.likes} likes</span>
                  <span>{post.comments} comments</span>
                </div>
              </div>
            );
          })}
        </div>
      </div>
    </div>
  );
}
