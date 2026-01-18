#include <iostream>
#include <string>

/*
This is the solution for problem number 28 "Find the Index of the First Occurrence in a String", classed "Easy" on LeetCode. It is found under:
https://leetcode.com/problems/find-the-index-of-the-first-occurrence-in-a-string/

It uses the Fast and Slow Pointers approach for its solution.

Time Complexity: O(n), where n is the length of the input array. The algorithm iterates through the array once.
Space Complexity: O(1), as the modification is done in-place without using any additional data structures.
*/


//Solution 1: Solution using string::substr()
class Solution {
public:
    int strStr(std::string haystack, std::string needle) {
        if (haystack.length() < needle.length()) {
            return -1;
        }
        for (int i = 0; i <= haystack.length() - needle.length(); i++) {
            if (haystack.substr(i, needle.length()) == needle) {
                return i;
            }
        }

        return -1;
    }
};

//Solution 2: Sliding Window Solution
class Solution2 {
public:
    int strStr(std::string haystack, std::string needle) {
        int haySize = haystack.size();
        int needleSize = needle.size();

        // Edge case: if needle is empty, return 0
        if (needleSize == 0) return 0;

        // Slide a window of size m over the haystack
        for (int i = 0; i <= haySize - needleSize; ++i) {
            int j = 0;
            // Check character by character within the window
            while (j < needleSize && haystack[i + j] == needle[j]) {
                ++j;
            }
            // If we matched the entire needle, return starting index
            if (j == needleSize) return i;
        }

        // If no match is found, return -1
        return -1;
    }
};

//Solution 3: Recursive Solution
class Solution {
public:
    int strStr(std::string haystack, std::string needle) {
        // Helper function to perform recursive search
        return findSubstring(haystack, needle, 0);
    }

private:
    int findSubstring(const string& haystack, const string& needle, int index) {
        int n = haystack.size();
        int m = needle.size();

        // Base case: If the remaining haystack is smaller than the needle
        if (index > n - m) return -1;

        // Check if the needle matches at the current index
        if (haystack.substr(index, m) == needle) {
            return index;
        }

        // Recursive call: move to the next index
        return findSubstring(haystack, needle, index + 1);
    }
};


int main()
{
    std::cout << "Hello World!\n";
}
