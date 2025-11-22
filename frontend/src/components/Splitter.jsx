import { useState, useEffect } from 'react';
import '../styles/Splitter.css';

export default function Splitter({ onDrag, orientation = 'vertical' }) {
  const [isDragging, setIsDragging] = useState(false);

  useEffect(() => {
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
  }, [isDragging, onDrag, orientation]);

  const handleMouseDown = (e) => {
    setIsDragging(true);
    e.preventDefault();
  };

  return (
    <div
      className={`splitter ${isDragging ? 'splitter-active' : ''}`}
      style={{
        width: orientation === 'vertical' ? '4px' : '100%',
        height: orientation === 'horizontal' ? '4px' : '100%',
        cursor: orientation === 'vertical' ? 'col-resize' : 'row-resize'
      }}
      onMouseDown={handleMouseDown}
    />
  );
}
