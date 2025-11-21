export default function Pane({ children, className = '' }) {
  return (
    <div className={`h-full bg-[#1e1e1e] overflow-auto ${className}`}>
      {children}
    </div>
  );
}
