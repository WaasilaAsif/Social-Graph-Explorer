#include <iostream>
#include <cstdlib>

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "  Member 3 - Complete Test Suite" << std::endl;
    std::cout << "========================================\n" << std::endl;
    
    int totalTests = 0;
    int passedTests = 0;
    
    // Test 1: PriorityQueue
    std::cout << "[1/6] Running PriorityQueue tests..." << std::endl;
    int result1 = system("test_pq.exe");
    totalTests++;
    if (result1 == 0) {
        passedTests++;
        std::cout << "PriorityQueue tests PASSED\n" << std::endl;
    } else {
        std::cout << "✗ PriorityQueue tests FAILED\n" << std::endl;
    }
    
    // Test 2: MutualFriends
    std::cout << "[2/6] Running MutualFriends tests..." << std::endl;
    int result2 = system("test_mutual.exe");
    totalTests++;
    if (result2 == 0) {
        passedTests++;
        std::cout << " MutualFriends tests PASSED\n" << std::endl;
    } else {
        std::cout << "✗ MutualFriends tests FAILED\n" << std::endl;
    }
    
    // Test 3: ShortestPath
    std::cout << "[3/6] Running ShortestPath tests..." << std::endl;
    int result3 = system("test_sp.exe");
    totalTests++;
    if (result3 == 0) {
        passedTests++;
        std::cout << " ShortestPath tests PASSED\n" << std::endl;
    } else {
        std::cout << "✗ ShortestPath tests FAILED\n" << std::endl;
    }
    
    // Test 4: GraphStats
    std::cout << "[4/6] Running GraphStats tests..." << std::endl;
    int result4 = system("test_stats.exe");
    totalTests++;
    if (result4 == 0) {
        passedTests++;
        std::cout << " GraphStats tests PASSED\n" << std::endl;
    } else {
        std::cout << "✗ GraphStats tests FAILED\n" << std::endl;
    }
    
    // Test 5: PopularityRanker
    std::cout << "[5/6] Running PopularityRanker tests..." << std::endl;
    int result5 = system("test_ranker.exe");
    totalTests++;
    if (result5 == 0) {
        passedTests++;
        std::cout << " PopularityRanker tests PASSED\n" << std::endl;
    } else {
        std::cout << "✗ PopularityRanker tests FAILED\n" << std::endl;
    }
    
    // Test 6: FriendSuggestion
    std::cout << "[6/6] Running FriendSuggestion tests..." << std::endl;
    int result6 = system("test_suggest.exe");
    totalTests++;
    if (result6 == 0) {
        passedTests++;
        std::cout << " FriendSuggestion tests PASSED\n" << std::endl;
    } else {
        std::cout << "✗ FriendSuggestion tests FAILED\n" << std::endl;
    }
    
    // Summary
    std::cout << "========================================" << std::endl;
    std::cout << "  Test Summary" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "Total Tests: " << totalTests << std::endl;
    std::cout << "Passed: " << passedTests << std::endl;
    std::cout << "Failed: " << (totalTests - passedTests) << std::endl;
    std::cout << "Success Rate: " << (passedTests * 100.0 / totalTests) << "%" << std::endl;
    
    if (passedTests == totalTests) {
        std::cout << "\n ALL TESTS PASSED! " << std::endl;
        return 0;
    } else {
        std::cout << "\n✗ SOME TESTS FAILED" << std::endl;
        return 1;
    }
}