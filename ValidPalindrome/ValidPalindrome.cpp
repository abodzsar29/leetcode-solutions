#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>

/*
This is the solution for the problem "Valid Palindrome", classed "Easy" on LeetCode. It is found under:
https://leetcode.com/problems/valid-palindrome/description/

It uses strings, which is a sequential data structure, and uses the Two Pointer approach for its solution.

Time Complexity: O(n), where n is the length of the input array. The algorithm iterates through the array once.
Space Complexity: O(1), as the modification is done in-place without using any additional data structures.
*/

// Solution 1:
class SolutionOne {
public:
    bool isPalindrome(std::string s)  {
        s.erase(std::remove_if(s.begin(), s.end(), [](char c) {
            return !std::isalnum(static_cast<unsigned char>(c));
            }), s.end());  // Uses lambda to remove non-alphanumeric characters
        std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c) {
            return std::tolower(c);
            });  // Uses lambda to turn aphanumeric characters to lowercase
        if (s.length() == 0) {
            return true;
        }  // Handle edge case of empty string
        int left = 0;
        for (int right = s.length() - 1; left < right; right--) {
            if (s[left] == s[right]) {  // If letters are the same, then continue the process
                left++;
                continue;
            }
            else {
                return false;
            }
        }

        return true;
    }
};

// Solution 2:
class SolutionTwo {
public:
    bool isPalindrome(std::string s) {
        int start = 0;
        int end = s.size() - 1;
        while (start <= end) {
            if (!isalnum(s[start])) { start++; continue; };  // When isalnum() fails, condition is true, pointer moves on
            if (!isalnum(s[end])) { end--; continue; }
            if (tolower(s[start]) != tolower(s[end]))return false;
            else {
                start++;
                end--;
            }
        }
        return true;
    }
};

int main()
{
    std::string s = "A man, a plan, a canal : Panama";
    SolutionOne solution;
    std::cout << solution.isPalindrome(s) << std::endl;
}
