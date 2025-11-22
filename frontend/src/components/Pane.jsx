import '../styles/Pane.css';

export default function Pane({ children, className = '' }) {
  return (
    <div className={`pane ${className}`}>
      <div className="pane-content">
        {children}
      </div>
    </div>
  );
}
