$ErrorActionPreference = "Stop"

Write-Host "Building Social Graph Explorer Server..." -ForegroundColor Cyan

$compileCommand = @"
g++ api/server.cpp `
    api/routes/MsgRoutes.cpp `
    api/routes/MsgAPI.cpp `
    dsa/user/UserManager.cpp `
    dsa/user/User.cpp `
    dsa/utils/idGenerator.cpp `
    messaging/MessageStore.cpp `
    dsa/messaging_ds/MsgTrie.cpp `
    dsa/messaging_ds/ConversationGraph.cpp `
    algorithms/MsgTopKMessage.cpp `
    algorithms/MsgFriendSuggestion.cpp `
    algorithms/MsgMutualInteractions.cpp `
    algorithms/MsgPopularityRanker.cpp `
    algorithms/MsgShortestPatch.cpp `
    algorithms/MutualFriends.cpp `
    algorithms/ShortestPath.cpp `
    algorithms/FriendSuggestion.cpp `
    analytics/PopularityRanker.cpp `
    storage/JSONLoader.cpp `
    storage/JSONWriter.cpp `
    -I. -Ilibs -I../libs/asio `
    -std=c++17 -DASIO_STANDALONE `
    -lws2_32 -lwsock32 `
    -o server_new.exe
"@

Write-Host "Compiling..." -ForegroundColor Yellow
Invoke-Expression $compileCommand

if ($LASTEXITCODE -eq 0) {
    Write-Host "✓ Compilation successful!" -ForegroundColor Green
    
    # Backup old server
    if (Test-Path "server.exe") {
        Write-Host "Backing up old server.exe to server.exe.bak" -ForegroundColor Yellow
        Move-Item -Path "server.exe" -Destination "server.exe.bak" -Force
    }
    
    # Replace with new server
    Move-Item -Path "server_new.exe" -Destination "server.exe" -Force
    Write-Host "✓ Server updated successfully!" -ForegroundColor Green
    
    # Start the server
    Write-Host ""
    Write-Host "Starting server..." -ForegroundColor Cyan
    ./server.exe
} else {
    Write-Host "✗ Compilation failed!" -ForegroundColor Red
    exit 1
}
