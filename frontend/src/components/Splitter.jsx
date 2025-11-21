import { useState } from 'react';

export default function Splitter({ onDrag, orientation = 'vertical' }) {
  const [isDragging, setIsDragging] = useState(false);

  const handleMouseDown = (e) => {
    setIsDragging(true);
    e.preventDefault();
  };

  const handleMouseMove = (e) => {
    if (isDragging && onDrag) {
      onDrag(orientation === 'vertical' ? e.clientX : e.clientY);
    }
  };

  const handleMouseUp = () => {
    setIsDragging(false);
  };

  if (isDragging) {
    document.addEventListener('mousemove', handleMouseMove);
    document.addEventListener('mouseup', handleMouseUp);
    return () => {
      document.removeEventListener('mousemove', handleMouseMove);
      document.removeEventListener('mouseup', handleMouseUp);
    };
  }

  return (
    <div
      className={`${
        orientation === 'vertical'
          ? 'w-1 cursor-col-resize hover:bg-blue-500/30'
          : 'h-1 cursor-row-resize hover:bg-blue-500/30'
      } bg-[#2b2b2b] transition-colors`}
      onMouseDown={handleMouseDown}
    />
  );
}
