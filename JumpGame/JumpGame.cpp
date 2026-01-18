#include <iostream>
#include <vector>

/*
This is the solution for the problem "Jump Game", classed "Medium" on LeetCode. It is found under:
https://leetcode.com/problems/jump-game/?envType=study-plan-v2&envId=top-interview-150

It is included in the "Top Interview 150" problem set, which covers comprehensive interview A&DS topics.

Time Complexity: O(n), where n is the length of the input array. The algorithm iterates through the array once.
Space Complexity: O(1), as the modification is done in-place without using any additional data structures.
*/

// Approach 1: 
class Solution {
public:
    bool canJump(std::vector<int>& nums) {
        int reach = 0;

        for (int i = 0; i < nums.size(); ++i) {
            if (i > reach) {
                return false;  // If the current index is beyond the farthest reachable point, return false.
            }
            reach = std::max(reach, i + nums[i]);  // Update the farthest reachable index.
            if (reach >= nums.size() - 1) {
                return true;  // If reach is at or beyond the last index, return true.
            }
        }

        return false;  // If loop completes without reaching the last index.
    }
};

int main() {
    // Test cases for the Jump Game problem
    std::vector<std::vector<int>> testCases = {
        {2, 3, 1, 1, 4},
        {3, 2, 1, 0, 4},   
        {0},               
        {2, 0, 0},         
        {1, 1, 0, 1},      
        {5, 4, 0, 0, 0, 0}, 
        {1, 2, 3},         
        {0, 2, 3}          
    };

    // Create an instance of the Solution class
    Solution solution;

    // Loop through each test case
    for (int i = 0; i < testCases.size(); ++i) {
        bool result = solution.canJump(testCases[i]);

        // Output the result for each test 
        if (result) {
            std::cout << "Vector " << i + i << " can reach the last index." << std::endl;
        }
        else {
            std::cout << "Vector " << i + i << " cannot reach the last index." << std::endl;
        }
    }

    return 0;
}

