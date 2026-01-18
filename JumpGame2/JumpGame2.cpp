#include <iostream>
#include <vector>

/*
This is the solution for the problem "Jump Game 2", classed "Medium" on LeetCode. It is found under:
https://leetcode.com/problems/jump-game-ii/?envType=study-plan-v2&envId=top-interview-150

It is included in the "Top Interview 150" problem set, which covers comprehensive interview A&DS topics.

Time Complexity: O(n), where n is the length of the input array. The algorithm iterates through the array once.
Space Complexity: O(1), as the modification is done in-place without using any additional data structures.
*/

// Approach 1: 
class Solution {
public:
    int jump(std::vector<int>& nums) {
        int jumps = 0, current_end = 0, farthest = 0;

        for (int i = 0; i < nums.size() - 1; ++i) {
            farthest = std::max(farthest, i + nums[i]);

            if (i == current_end) {
                jumps++;
                current_end = farthest;

                // If we have already reached or surpassed the last index, break early
                if (current_end >= nums.size() - 1) {
                    break;
                }
            }
        }

        return jumps;
    }
};

int main() {
    // Test cases for Jump Game II problem
    std::vector<std::vector<int>> testCases = {
        {2, 3, 1, 1, 4},           // Expected output: 2
        {2, 3, 0, 1, 4},           // Expected output: 2
        {0},                       // Expected output: 0
        {1, 1, 1, 1},              // Expected output: 3
        {5, 4, 3, 2, 1, 0},        // Expected output: 1
        {2, 0, 2, 0, 1},           // Expected output: 2
        {1, 2, 1, 1, 1},           // Expected output: 3
        {10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0}  // Expected output: 1
    };

    Solution solution;

    for (int i = 0; i < testCases.size(); ++i) {
        int result = solution.jump(testCases[i]);

        // Output the result for each test case
        std::cout << "Minimum jumps for test case " << i + 1 << ": " << result << std::endl;
    }

    return 0;
}

