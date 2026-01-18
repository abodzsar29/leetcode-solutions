#include <iostream>
#include <vector>
#include <algorithm>

/*
This is the solution for the problem "Trapping Rain Water", classed "Hard" on LeetCode. It is found under:
https://leetcode.com/problems/trapping-rain-water/description/

It uses the Two Pointer Approach for its solution.

Time Complexity: O(n), where n is the length of the input array. The algorithm iterates through the array once.
Space Complexity: O(1), as the modification is done in-place without using any additional data structures.
*/

// Define the Solution class
class Solution {
public:
    int trap(std::vector<int>& height) {
        if (height.empty()) {
            return 0; // Handle edge case for empty vector
        }

        int left = 0;
        int right = height.size() - 1;
        int leftMax = height[left];
        int rightMax = height[right];
        int water = 0;

        while (left < right) {
            if (leftMax < rightMax) {
                left++;
                leftMax = std::max(leftMax, height[left]);
                water += leftMax - height[left];
            }
            else {
                right--;
                rightMax = std::max(rightMax, height[right]);
                water += rightMax - height[right];
            }
        }
        return water;
    }
};

int main() {
    // Create an instance of the Solution class
    Solution solution;

    // Test cases
    std::vector<std::vector<int>> testCases = {
        {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1}, // Expected output: 6
        {4, 2, 0, 3, 2, 5},                   // Expected output: 9
        {1, 0, 2},                            // Expected output: 1
        {3, 0, 0, 2, 0, 4},                   // Expected output: 10
        {},                                   // Expected output: 0
        {5},                                  // Expected output: 0
        {5, 5, 5, 5}                          // Expected output: 0
    };

    // Iterate through test cases
    for (const auto& heights : testCases) {
        // Print the input
        std::cout << "Heights: [";
        for (size_t i = 0; i < heights.size(); ++i) {
            std::cout << heights[i];
            if (i != heights.size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << "]\n";

        // Call the trap function and print the output
        int result = solution.trap(const_cast<std::vector<int>&>(heights));
        std::cout << "Trapped Water: " << result << "\n\n";
    }

    return 0;
}