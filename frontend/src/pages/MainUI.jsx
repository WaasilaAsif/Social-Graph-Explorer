import { useState, useEffect } from 'react';
import Sidebar from '../components/Sidebar';
import TabBar from '../components/TabBar';
import Pane from '../components/Pane';
import Splitter from '../components/Splitter';
import GraphView from '../components/GraphView';
import UserProfileView from '../components/UserProfileView';
import PostView from '../components/PostView';
import RightInfoPane from '../components/RightInfoPane';
import { getRecentPosts } from '../data/dummyPosts';
import { Network, User, FileText, Home } from 'lucide-react';

export default function MainUI() {
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
      case 'post':
        title = 'Post';
        icon = <FileText size={14} />;
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
        return <HomeView onPostClick={handlePostClick} onUserClick={handleUserClick} />;
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
      case 'post':
        return (
          <PostView
            post={currentTab.data.post}
            onUserClick={handleUserClick}
          />
        );
      default:
        return <div className="p-6 text-gray-400">Unknown view type</div>;
    }
  };

  return (
    <div className="h-screen flex bg-[#1e1e1e] text-gray-200">
      <div style={{ width: leftWidth, minWidth: 200 }}>
        <Sidebar onUserClick={handleUserClick} onNavigate={handleNavigate} />
      </div>

      <Splitter onDrag={handleLeftDrag} />

      <div className="flex-1 flex flex-col min-w-0">
        <TabBar
          tabs={tabs}
          activeTab={activeTab}
          onTabChange={setActiveTab}
          onTabClose={closeTab}
        />
        <Pane className="flex-1">
          {renderTabContent()}
        </Pane>
      </div>

      {showRightPane && (
        <>
          <Splitter onDrag={handleRightDrag} />
          <div style={{ width: rightWidth, minWidth: 250 }}>
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
    <div className="h-full overflow-auto">
      <div className="max-w-4xl mx-auto p-8">
        <div className="mb-8">
          <h1 className="text-3xl font-bold text-gray-200 mb-2">Social Graph Explorer</h1>
          <p className="text-gray-400">
            Explore social networks through data structures and algorithms
          </p>
        </div>

        <div className="grid grid-cols-3 gap-4 mb-8">
          <div className="bg-[#2b2b2b] rounded-lg p-6">
            <div className="flex items-center gap-3 mb-2">
              <Network size={20} className="text-blue-400" />
              <h3 className="text-sm font-semibold text-gray-300">Network</h3>
            </div>
            <p className="text-2xl font-bold text-gray-200">10</p>
            <p className="text-xs text-gray-500 mt-1">Active nodes</p>
          </div>

          <div className="bg-[#2b2b2b] rounded-lg p-6">
            <div className="flex items-center gap-3 mb-2">
              <User size={20} className="text-purple-400" />
              <h3 className="text-sm font-semibold text-gray-300">Users</h3>
            </div>
            <p className="text-2xl font-bold text-gray-200">10</p>
            <p className="text-xs text-gray-500 mt-1">Total users</p>
          </div>

          <div className="bg-[#2b2b2b] rounded-lg p-6">
            <div className="flex items-center gap-3 mb-2">
              <FileText size={20} className="text-emerald-400" />
              <h3 className="text-sm font-semibold text-gray-300">Posts</h3>
            </div>
            <p className="text-2xl font-bold text-gray-200">15</p>
            <p className="text-xs text-gray-500 mt-1">Total posts</p>
          </div>
        </div>

        <h2 className="text-xl font-semibold text-gray-200 mb-4">Recent Activity</h2>
        <div className="space-y-4">
          {recentPosts.map((post) => {
            const author = { id: post.userId, name: `User ${post.userId}`, avatar: `U${post.userId}` };
            return (
              <button
                key={post.id}
                onClick={() => onPostClick(post)}
                className="w-full text-left bg-[#2b2b2b] hover:bg-[#3a3a3a] rounded-lg p-4 transition-colors"
              >
                <div className="flex items-center gap-3 mb-3">
                  <div
                    onClick={(e) => {
                      e.stopPropagation();
                      onUserClick(author);
                    }}
                    className="w-10 h-10 rounded-full bg-gradient-to-br from-blue-500 to-purple-600 flex items-center justify-center text-sm font-semibold text-white cursor-pointer"
                  >
                    {author.avatar}
                  </div>
                  <div>
                    <p className="text-sm font-medium text-gray-200">{author.name}</p>
                    <p className="text-xs text-gray-500">
                      {new Date(post.timestamp).toLocaleString()}
                    </p>
                  </div>
                </div>
                <p className="text-sm text-gray-300 line-clamp-2">{post.content}</p>
                <div className="flex items-center gap-4 mt-3 text-xs text-gray-500">
                  <span>{post.likes} likes</span>
                  <span>{post.comments} comments</span>
                </div>
              </button>
            );
          })}
        </div>
      </div>
    </div>
  );
}
