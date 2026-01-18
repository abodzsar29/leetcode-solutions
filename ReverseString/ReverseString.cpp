#include<iostream>
#include<vector>

/*
This is the solution for the problem "Reverse String", classed "Easy" on LeetCode. It is found under:
https://leetcode.com/problems/reverse-string/

It uses the Two Pointer Approach.

Time Complexity: O(n), where n is the length of the input array. The algorithm processes n/2 elements, but we simplify it to O(n).
Space Complexity: O(1), as the modification is done in-place without using any additional data structures.
*/


class Solution {
public:
    void reverseString(std::vector<char>& s) {
        int left = 0;
        int right = s.size() - 1;
        char container;
        while (left < right) {
            container = s[left];
            s[left] = s[right];
            s[right] = container;
            left++;
            right--;
        }
    }
};

int main() {
Solution solution;

// Create a vector of characters
std::vector<char> str = {'h', 'e', 'l', 'l', 'o'};

// Print original string
std::cout << "Original string: ";
for(char c : str) {
    std::cout << c;
}
std::cout << std::endl;

// Reverse the string
solution.reverseString(str);

// Print reversed string
std::cout << "Reversed string: ";
for(char c : str) {
    std::cout << c;
}
std::cout << std::endl;
  

return 0;
}
