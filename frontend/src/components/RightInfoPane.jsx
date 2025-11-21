import { X } from 'lucide-react';
import { getUserById } from '../data/dummyUsers';
import { getNodeConnections } from '../data/dummyGraph';

export default function RightInfoPane({ selectedNode, onClose, onUserClick }) {
  if (!selectedNode) {
    return (
      <div className="h-full bg-[#1e1e1e] border-l border-[#2b2b2b] flex items-center justify-center">
        <p className="text-gray-500 text-sm">Select a node to view details</p>
      </div>
    );
  }

  const user = getUserById(selectedNode.id);
  const connections = getNodeConnections(selectedNode.id);

  return (
    <div className="h-full bg-[#1e1e1e] border-l border-[#2b2b2b] flex flex-col">
      <div className="flex items-center justify-between p-4 border-b border-[#2b2b2b]">
        <h3 className="text-sm font-semibold text-gray-200">Node Details</h3>
        <button
          onClick={onClose}
          className="p-1 hover:bg-[#2b2b2b] rounded transition-colors"
        >
          <X size={16} className="text-gray-400" />
        </button>
      </div>

      <div className="flex-1 overflow-auto p-4">
        {user && (
          <>
            <div className="flex flex-col items-center text-center mb-6">
              <div className="w-16 h-16 rounded-full bg-gradient-to-br from-blue-500 to-purple-600 flex items-center justify-center text-xl font-bold text-white mb-3">
                {user.avatar}
              </div>
              <h4 className="text-lg font-semibold text-gray-200">{user.name}</h4>
              <p className="text-xs text-gray-500 mt-1">Node ID: {user.id}</p>
            </div>

            <div className="space-y-4">
              <div>
                <p className="text-xs text-gray-500 uppercase mb-2">Bio</p>
                <p className="text-sm text-gray-300">{user.bio}</p>
              </div>

              <div>
                <p className="text-xs text-gray-500 uppercase mb-2">Statistics</p>
                <div className="space-y-2">
                  <div className="flex justify-between text-sm">
                    <span className="text-gray-400">Followers</span>
                    <span className="text-gray-200 font-medium">{user.followers}</span>
                  </div>
                  <div className="flex justify-between text-sm">
                    <span className="text-gray-400">Following</span>
                    <span className="text-gray-200 font-medium">{user.following}</span>
                  </div>
                  <div className="flex justify-between text-sm">
                    <span className="text-gray-400">Posts</span>
                    <span className="text-gray-200 font-medium">{user.posts}</span>
                  </div>
                  <div className="flex justify-between text-sm">
                    <span className="text-gray-400">Connections</span>
                    <span className="text-gray-200 font-medium">{connections.length}</span>
                  </div>
                </div>
              </div>

              <div>
                <p className="text-xs text-gray-500 uppercase mb-2">Connected Nodes</p>
                <div className="space-y-2">
                  {connections.map((connId) => {
                    const connUser = getUserById(connId);
                    return (
                      <button
                        key={connId}
                        onClick={() => onUserClick(connUser)}
                        className="w-full flex items-center gap-2 p-2 bg-[#2b2b2b] hover:bg-[#3a3a3a] rounded transition-colors"
                      >
                        <div className="w-6 h-6 rounded-full bg-gradient-to-br from-blue-500 to-purple-600 flex items-center justify-center text-xs font-semibold text-white">
                          {connUser?.avatar}
                        </div>
                        <span className="text-sm text-gray-300 truncate">
                          {connUser?.name}
                        </span>
                      </button>
                    );
                  })}
                </div>
              </div>

              <div>
                <p className="text-xs text-gray-500 uppercase mb-2">Graph Properties</p>
                <div className="space-y-2 text-sm">
                  <div className="flex justify-between">
                    <span className="text-gray-400">Degree</span>
                    <span className="text-gray-200">{connections.length}</span>
                  </div>
                  <div className="flex justify-between">
                    <span className="text-gray-400">Group</span>
                    <span className="text-gray-200">{selectedNode.group}</span>
                  </div>
                </div>
              </div>

              <button
                onClick={() => onUserClick(user)}
                className="w-full mt-4 px-4 py-2 bg-blue-600 hover:bg-blue-700 text-white text-sm font-medium rounded transition-colors"
              >
                View Full Profile
              </button>
            </div>
          </>
        )}
      </div>
    </div>
  );
}
