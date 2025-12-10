# Restart script for Social Graph Explorer
Write-Host "=== Social Graph Explorer - Restart Script ===" -ForegroundColor Cyan

# Stop existing processes
Write-Host "`nStopping existing processes..." -ForegroundColor Yellow
Get-Process server -ErrorAction SilentlyContinue | Stop-Process -Force
Get-Process node -ErrorAction SilentlyContinue | Where-Object { $_.Path -like '*SocialGraphExplorer*' } | Stop-Process -Force
Start-Sleep -Seconds 1

# Start backend server in new window
Write-Host "Starting backend server..." -ForegroundColor Green
Start-Process powershell -ArgumentList "-NoExit", "-Command", "cd D:\SocialGraphExplorer\backend; Write-Host 'Backend Server Starting...' -ForegroundColor Cyan; ./server.exe"
Start-Sleep -Seconds 3

# Start CORS proxy
Write-Host "Starting CORS proxy..." -ForegroundColor Green
Start-Process powershell -ArgumentList "-NoExit", "-Command", "cd D:\SocialGraphExplorer\backend; Write-Host 'CORS Proxy Starting...' -ForegroundColor Cyan; node cors-proxy.js"
Start-Sleep -Seconds 2

# Check if both are running
Write-Host "`nChecking services..." -ForegroundColor Yellow
$backend = Test-NetConnection localhost -Port 8081 -InformationLevel Quiet -WarningAction SilentlyContinue
$proxy = Test-NetConnection localhost -Port 8082 -InformationLevel Quiet -WarningAction SilentlyContinue

if ($backend) {
    Write-Host "✓ Backend server running on port 8081" -ForegroundColor Green
} else {
    Write-Host "✗ Backend server NOT running" -ForegroundColor Red
}

if ($proxy) {
    Write-Host "✓ CORS proxy running on port 8082" -ForegroundColor Green
} else {
    Write-Host "✗ CORS proxy NOT running" -ForegroundColor Red
}

Write-Host "`nFrontend should be at: http://localhost:5174/" -ForegroundColor Cyan
Write-Host "Start frontend with: cd frontend; npm run dev" -ForegroundColor Gray
