import '../styles/LoadingSpinner.css';

interface LoadingSpinnerProps {
  message?: string;
  size?: 'small' | 'medium' | 'large';
}

const LoadingSpinner = ({ message = 'Loading...', size = 'medium' }: LoadingSpinnerProps) => {
  return (
    <div className="loading-spinner-container">
      <div className={`loading-spinner ${size}`}></div>
      {message && <p className="loading-message">{message}</p>}
    </div>
  );
};

export default LoadingSpinner;
