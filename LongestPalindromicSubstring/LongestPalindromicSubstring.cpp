
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

/*
This is the solution for the problem "Longest Palindromic Substring", classed "Medium" on LeetCode. It is found under:
https://leetcode.com/problems/longest-palindromic-substring/description/

Two implementations are provided:

1. Mancher's Algorithm:
   Time Complexity: O(n), where n is the length of the string. The algorithm processes each character once.
   Space Complexity: O(n), for the transformed string and the palindrome radius array.

2. Expand Around Centers:
   Time Complexity: O(n^2), where n is the length of the string. For each center, we expand outward.
   Space Complexity: O(1), as no additional data structures are used.
*/

// Solution using Manacher's Algorithm - O(n) time, O(n) space
class SolutionManacher {
public:
    std::string longestPalindrome(std::string s) {
        int n = s.size();
        if (n == 0) return "";
        
        // Step 1: Transform the string with separators
        // Insert '#' between characters and at both ends to handle even/odd length palindromes uniformly
        std::string t;
        t.reserve(2 * n + 1);
        for (char c : s) {
            t.push_back('#');
            t.push_back(c);
        }
        t.push_back('#');
        
        int m = t.size();
        std::vector<int> P(m, 0); // P[i] = max arm length around center i
        int center = 0, right = 0; // Track the rightmost palindrome boundary
        
        // Step 2: Manacher's algorithm main loop
        for (int i = 0; i < m; ++i) {
            int mirror = 2 * center - i; // Mirror position of i around current center
            
            // If i is within the right boundary, use previously computed values
            if (i < right) {
                P[i] = std::min(P[mirror], right - i);
            }
            
            // Attempt to expand palindrome centered at i
            while (i - P[i] - 1 >= 0 && i + P[i] + 1 < m && 
                   t[i - P[i] - 1] == t[i + P[i] + 1]) {
                ++P[i];
            }
            
            // Update center and right boundary if palindrome extends beyond current right
            if (i + P[i] > right) {
                center = i;
                right = i + P[i];
            }
        }
        
        // Step 3: Find the longest palindromic substring
        int maxLen = 0, centerIndex = 0;
        for (int i = 0; i < m; ++i) {
            if (P[i] > maxLen) {
                maxLen = P[i];
                centerIndex = i;
            }
        }
        
        // Convert back to original string coordinates
        int start = (centerIndex - maxLen) / 2;
        return s.substr(start, maxLen);
    }
};

// Solution using Expand Around Centers - O(n^2) time, O(1) space
class SolutionExpandCenter {
public:
    std::string longestPalindrome(const std::string& s) {
        int n = s.size();
        if (n == 0) return "";
        
        int start = 0, maxLen = 1;
        
        // Lambda function to expand around a given center
        auto expandAroundCenter = [&](int left, int right) {
            // Expand outward while characters match
            while (left >= 0 && right < n && s[left] == s[right]) {
                int currentLen = right - left + 1;
                // Update longest palindrome if current is longer
                if (currentLen > maxLen) {
                    start = left;
                    maxLen = currentLen;
                }
                --left;
                ++right;
            }
        };
        
        // Check all possible centers
        for (int i = 0; i < n; ++i) {
            expandAroundCenter(i, i);     // Odd-length palindrome (center at i)
            expandAroundCenter(i, i + 1); // Even-length palindrome (center between i and i+1)
        }
        
        return s.substr(start, maxLen);
    }
};

int main() {
    // Create instances of both solution classes
    SolutionManacher solutionManacher;
    SolutionExpandCenter solutionExpandCenter;
    
    // Test cases with expected outputs
    std::vector<std::pair<std::string, std::string>> testCases = {
        {"babad", "bab or aba"},     // Expected output: "bab" or "aba"
        {"cbbd", "bb"},              // Expected output: "bb"
        {"a", "a"},                  // Expected output: "a"
        {"ac", "a or c"},            // Expected output: "a" or "c"
        {"racecar", "racecar"},      // Expected output: "racecar"
        {"abcdef", "any single char"}, // Expected output: any single character
        {"", ""},                    // Expected output: ""
        {"noon", "noon"},            // Expected output: "noon"
        {"abacabad", "abacaba"},     // Expected output: "abacaba"
        {"forgeeksskeegfor", "geeksskeeg"} // Expected output: "geeksskeeg"
    };
    
    std::cout << "=== Testing Manacher's Algorithm (O(n) time, O(n) space) ===\n\n";
    
    // Test Manacher's algorithm
    for (const auto& testCase : testCases) {
        const std::string& input = testCase.first;
        const std::string& expected = testCase.second;
        
        std::cout << "Input: \"" << input << "\"\n";
        std::cout << "Expected: " << expected << "\n";
        
        std::string result = solutionManacher.longestPalindrome(input);
        std::cout << "Manacher Result: \"" << result << "\"\n\n";
    }
    
    std::cout << "=== Testing Expand Around Centers (O(n^2) time, O(1) space) ===\n\n";
    
    // Test expand around centers algorithm
    for (const auto& testCase : testCases) {
        const std::string& input = testCase.first;
        const std::string& expected = testCase.second;
        
        std::cout << "Input: \"" << input << "\"\n";
        std::cout << "Expected: " << expected << "\n";
        
        std::string result = solutionExpandCenter.longestPalindrome(input);
        std::cout << "Expand Centers Result: \"" << result << "\"\n\n";
    }
    
    // Performance comparison demonstration
    std::cout << "=== Algorithm Comparison ===\n";
    std::cout << "Manacher's Algorithm:\n";
    std::cout << "  - Time Complexity: O(n)\n";
    std::cout << "  - Space Complexity: O(n)\n";
    std::cout << "  - Best for: Large inputs where performance is critical\n\n";
    
    std::cout << "Expand Around Centers:\n";
    std::cout << "  - Time Complexity: O(n^2)\n";
    std::cout << "  - Space Complexity: O(1)\n";
    std::cout << "  - Best for: Small to medium inputs where memory is limited\n\n";
    
    return 0;
}
