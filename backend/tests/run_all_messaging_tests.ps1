# Run all messaging system tests
Write-Host "=== Running All Messaging System Tests ===" -ForegroundColor Cyan

Write-Host "`n[1/5] MessageQueue Tests..." -ForegroundColor Yellow
.\backend\tests\MessageQueue.exe

Write-Host "`n[2/5] TopKConversations Tests..." -ForegroundColor Yellow
.\backend\tests\TopKConversations.exe

Write-Host "`n[3/5] MessageAnalytics Tests..." -ForegroundColor Yellow
.\backend\tests\MessageAnalytics.exe

Write-Host "`n[4/5] MessagingSystem Tests..." -ForegroundColor Yellow
.\backend\tests\MessagingSystem.exe

Write-Host "`n[5/5] ScheduledMessages Tests..." -ForegroundColor Yellow
.\backend\tests\ScheduledMessages.exe

Write-Host "`n=== ALL TESTS COMPLETED ===" -ForegroundColor Green
