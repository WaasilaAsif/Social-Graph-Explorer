import { X } from 'lucide-react';

export default function SettingsModal({ isOpen, onClose }) {
  if (!isOpen) return null;

  return (
    <div className="fixed inset-0 bg-black/50 flex items-center justify-center z-50">
      <div className="bg-[#1e1e1e] border border-[#2b2b2b] rounded-lg w-full max-w-2xl max-h-[80vh] overflow-auto">
        <div className="flex items-center justify-between p-6 border-b border-[#2b2b2b]">
          <h2 className="text-xl font-semibold text-gray-200">Settings</h2>
          <button
            onClick={onClose}
            className="p-2 hover:bg-[#2b2b2b] rounded transition-colors"
          >
            <X size={20} className="text-gray-400" />
          </button>
        </div>

        <div className="p-6 space-y-6">
          <div>
            <h3 className="text-sm font-semibold text-gray-300 mb-3">Appearance</h3>
            <div className="space-y-3">
              <div className="flex items-center justify-between">
                <span className="text-sm text-gray-400">Theme</span>
                <select className="bg-[#2b2b2b] text-gray-200 text-sm px-3 py-1.5 rounded border border-[#3a3a3a]">
                  <option>Dark</option>
                  <option>Light</option>
                </select>
              </div>
            </div>
          </div>

          <div>
            <h3 className="text-sm font-semibold text-gray-300 mb-3">Graph Settings</h3>
            <div className="space-y-3">
              <div className="flex items-center justify-between">
                <span className="text-sm text-gray-400">Default Layout</span>
                <select className="bg-[#2b2b2b] text-gray-200 text-sm px-3 py-1.5 rounded border border-[#3a3a3a]">
                  <option>Force-Directed</option>
                  <option>Circular</option>
                  <option>Hierarchical</option>
                </select>
              </div>
            </div>
          </div>

          <div>
            <h3 className="text-sm font-semibold text-gray-300 mb-3">About</h3>
            <p className="text-sm text-gray-400">
              SocialGraphExplorer v1.0.0
            </p>
            <p className="text-xs text-gray-500 mt-2">
              A learning-oriented social network engine focused on data structures and algorithms.
            </p>
          </div>
        </div>

        <div className="flex justify-end gap-3 p-6 border-t border-[#2b2b2b]">
          <button
            onClick={onClose}
            className="px-4 py-2 bg-[#2b2b2b] hover:bg-[#3a3a3a] text-gray-200 text-sm rounded transition-colors"
          >
            Close
          </button>
        </div>
      </div>
    </div>
  );
}
