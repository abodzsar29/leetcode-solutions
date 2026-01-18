#include<iostream>
#include<vector>


/*
This is the solution for the problem "Move Zeroes", classed "Easy" on LeetCode. It is found under:
https://leetcode.com/problems/move-zeroes/description/

Time Complexity: O(n) where n is the lengths of nums
Space Complexity: O(1) as we are modifying values in place
*/



class Solution {
public:
    void moveZeroes(std::vector<int>& nums) {
        int i = 0;
        // move all the nonzero elements advance
        for (int j = 0; j < nums.size(); j++) {
            if (nums[j] != 0) {
                nums[i++] = nums[j];
            }
        }
        for (;i < nums.size(); i++) {
            nums[i] = 0;
        }
    }
};

int main() {
    // Test cases
    std::vector<std::vector<int>> testCases = {
        {0, 1, 0, 3, 12},
        {0},
        {1},
        {1, 0},
        {1, 0, 1},
        {0, 1, 0, 3, 12, 5, 0 ,0, 1, 4, 4, 0, 0, 1, 0, 0, 1}  // empty vector
    };

    Solution solution;
    
    // Process each test case
    for (auto& nums : testCases) {
        std::cout << "Original array: ";
        for (int num : nums) {
            std::cout << num << " ";
        }
        std::cout << std::endl;

        solution.moveZeroes(nums);

        std::cout << "After moving zeroes: ";
        for (int num : nums) {
            std::cout << num << " ";
        }
        std::cout << "\n\n";
    }

    return 0;
}
