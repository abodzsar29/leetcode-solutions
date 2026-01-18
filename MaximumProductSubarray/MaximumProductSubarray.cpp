#include <iostream>
#include <vector>
#include <algorithm>

/*
This is the solution for the problem "Maximum Product Subarray", classed "Medium" on LeetCode. It is found under:
https://leetcode.com/problems/maximum-product-subarray/description/

It uses Kadane's Algorithm for its solution.

Time Complexity: O(n), where n is the length of the input array. The algorithm iterates through the array once.
Space Complexity: O(1), as the modification is done in-place without using any additional data structures.
*/

class Solution {
public:
    int maxProductSubarray(std::vector<int>& nums) {
        int maxProduct = nums[0];
        int minProduct = nums[0];
        int result = nums[0];

        for (size_t i = 1; i < nums.size(); ++i) {
            if (nums[i] < 0) {
                std::swap(maxProduct, minProduct);
            }

            maxProduct = std::max(nums[i], maxProduct * nums[i]);
            minProduct = std::min(nums[i], minProduct * nums[i]);

            result = std::max(result, maxProduct);
        }

        return result;
    }
};

int main() {
    std::vector<int> nums = { -2, 3, -2, 4, 6, 3, 2, 1, -4 }; // Example input

    try {
        Solution solution;
        int result = solution.maxProductSubarray(nums);
        std::cout << "Maximum Product Subarray: " << result << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}