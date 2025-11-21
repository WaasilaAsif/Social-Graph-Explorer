export default function AppLayout({ children }) {
  return (
    <div className="h-screen w-screen overflow-hidden bg-[#1e1e1e]">
      {children}
    </div>
  );
}
