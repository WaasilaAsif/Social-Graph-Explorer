# Run all Msg algorithm tests
Write-Host "=== Running All Msg Algorithm Tests ===" -ForegroundColor Cyan

Write-Host "`n[1/4] MsgMutualInteraction Tests..." -ForegroundColor Yellow
.\backend\tests\MsgMutualInteraction.exe

Write-Host "`n[2/4] MsgFriendSuggestion Tests..." -ForegroundColor Yellow
.\backend\tests\MsgFriendSuggestion.exe

Write-Host "`n[3/4] MsgShortestPath Tests..." -ForegroundColor Yellow
.\backend\tests\MsgShortestPath.exe

Write-Host "`n[4/4] MsgTopKMessages Tests..." -ForegroundColor Yellow
.\backend\tests\MsgTopKMessages.exe

Write-Host "`n=== ALL MSG ALGORITHM TESTS COMPLETED ===" -ForegroundColor Green
