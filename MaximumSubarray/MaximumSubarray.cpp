#include <iostream>
#include <vector>
#include <algorithm>

/*
This is the solution for the problem "Maximum Subarray", classed "Medium" on LeetCode. It is found under:
https://leetcode.com/problems/maximum-subarray/description/

It uses Kadane's Algorithm for this solution.

Time Complexity: O(n), where n is the length of the input array. The algorithm iterates through the array once.
Space Complexity: O(1), as the modification is done in-place without using any additional data structures.
*/

class Solution {
public:
    int maxSubArray(std::vector<int>& nums) {
        int currentSum = nums[0];
        int maxSum = nums[0];
        for (int i = 1; i < nums.size(); ++i) {
            currentSum = std::max(nums[i], currentSum + nums[i]);
            maxSum = std::max(maxSum, currentSum);
        }
        return maxSum;
    }
};

int main() {
    Solution solution;
    std::vector<int> nums = { -2, 1, -3, 4, -1, 2, 1, -5, 4 }; // Example input

    try {
        int result = solution.maxSubArray(nums);
        std::cout << "Maximum Subarray Sum: " << result << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
