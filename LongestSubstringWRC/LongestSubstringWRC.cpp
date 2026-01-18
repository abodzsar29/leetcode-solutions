#include <iostream>
#include <string>
#include <unordered_set>
#include <algorithm>

/*
This is the solution for the problem "Longest Substring Without Repeating Characters", classed "Medium" on LeetCode. It is found under:
https://leetcode.com/problems/longest-substring-without-repeating-characters/

It uses the Sliding Window approach for its solution.

Time Complexity: O(n), where n is the length of the input array. The algorithm iterates through the array once.
Space Complexity: O(1), as the modification is done in-place without using any additional data structures.
*/

class Solution {
public:
    int lengthOfLongestSubstring(const std::string& s) {
        std::unordered_set<char> charSet; // Set to store unique characters in the window
        int start = 0;                    // Start of the window
        int maxLength = 0;                // Maximum length of substring found

        for (int end = 0; end < s.size(); ++end) {
            while (charSet.find(s[end]) != charSet.end()) {
                charSet.erase(s[start]);
                ++start;
            }
            // Add the current character to the set
            charSet.insert(s[end]);
            // Update the maximum length of the substring
            maxLength = std::max(maxLength, end - start + 1);
        }

        return maxLength;
    }
};

int main() {
    std::string s = "abcabcbb";
    Solution solution;
    std::cout << "Length of Longest Substring Without Repeating Characters: "
        << solution.lengthOfLongestSubstring(s) << std::endl;
    return 0;
}