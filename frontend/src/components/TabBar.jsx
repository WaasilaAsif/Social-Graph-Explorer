import { X } from 'lucide-react';

export default function TabBar({ tabs, activeTab, onTabChange, onTabClose }) {
  return (
    <div className="flex items-center bg-[#1e1e1e] border-b border-[#2b2b2b] overflow-x-auto">
      {tabs.map((tab) => (
        <div
          key={tab.id}
          className={`flex items-center gap-2 px-4 py-2 border-r border-[#2b2b2b] cursor-pointer transition-colors min-w-fit ${
            activeTab === tab.id
              ? 'bg-[#2b2b2b] text-gray-200'
              : 'text-gray-400 hover:bg-[#252525] hover:text-gray-300'
          }`}
          onClick={() => onTabChange(tab.id)}
        >
          {tab.icon && <span className="text-sm">{tab.icon}</span>}
          <span className="text-sm whitespace-nowrap">{tab.title}</span>
          <button
            onClick={(e) => {
              e.stopPropagation();
              onTabClose(tab.id);
            }}
            className="ml-2 p-0.5 hover:bg-[#3a3a3a] rounded transition-colors"
          >
            <X size={14} />
          </button>
        </div>
      ))}
    </div>
  );
}
