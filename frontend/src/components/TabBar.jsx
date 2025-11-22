import { X } from 'lucide-react';
import '../styles/TabBar.css';

export default function TabBar({ tabs, activeTab, onTabChange, onTabClose }) {
  return (
    <div className="tab-bar">
      {tabs.map((tab) => (
        <div
          key={tab.id}
          className={`tab ${activeTab === tab.id ? 'tab-active' : ''}`}
          onClick={() => onTabChange(tab.id)}
        >
          {tab.icon && <span>{tab.icon}</span>}
          <span className="tab-title">{tab.title}</span>
          <button
            onClick={(e) => {
              e.stopPropagation();
              onTabClose(tab.id);
            }}
            className="tab-close"
          >
            <X size={14} />
          </button>
        </div>
      ))}
    </div>
  );
}
