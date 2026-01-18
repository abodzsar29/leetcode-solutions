#include <iostream>
#include <string>

/*
This is the solution for the problem "Reverse Words in a String III", classed "Easy" on LeetCode. It is found under:
https://leetcode.com/problems/reverse-words-in-a-string-iii/description/

It uses the Two Pointer approach for strings for its solution.

Time Complexity: O(n), where n is the length of the input array. The algorithm iterates through the array once.
Space Complexity: O(1), as the modification is done in-place without using any additional data structures.
*/

class Solution {
public:
    std::string reverseWords(std::string s) {
        int start = 0; // Start index of a word
        int n = s.length();

        for (int i = 0; i <= n; ++i) {
            // When a space or the end of the string is found, reverse the current word
            if (i == n || s[i] == ' ') {
                int end = i - 1; // End index of a word
                while (start < end) {
                    // Swap characters using two-pointer technique
                    std::swap(s[start], s[end]);
                    start++;
                    end--;
                }
                start = i + 1; // Move to the start of the next word
            }
        }

        return s;
    }
};

int main()
{
    Solution solution;
    std::string str = "Let's take LeetCode contest";
    std::cout << "Original string: \"" << str << "\"\n";
    std::string reversed = solution.reverseWords(str);
    std::cout << "Reversed string: \"" << reversed << "\"\n";
    return 0;
}
