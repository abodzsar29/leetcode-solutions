#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

/*
This is the solution for the problem "Maximum Average Subarray I", classed "Easy" on LeetCode. It can be found at:
https://leetcode.com/problems/maximum-average-subarray-i/

It uses the **Sliding Window** technique to efficiently compute the maximum average of any contiguous subarray of length `k`.

Time Complexity: O(n), where n is the size of the input array. Each element is visited at most twice.
Space Complexity: O(1), as no additional data structures are used beyond basic variables.
*/

// Define the Solution class
class Solution {
public:
    double findMaxAverage(std::vector<int>& nums, int k) {
        if (nums.size() == 1) return nums[0];

        double maxAverage = INT_MIN;
        double sum = 0;
        int left = 0;
        int right = k - 1;

        // Compute the sum of the first 'k' elements
        for (int i = 0; i < k; ++i) {
            sum += nums[i];
        }

        maxAverage = sum / k;

        // Slide the window across the array
        while (right + 1 < nums.size()) {
            sum += nums[++right];
            sum -= nums[left++];
            maxAverage = std::max(maxAverage, sum / k);
        }

        return maxAverage;
    }
};

int main() {
    // Create an instance of the Solution class
    Solution solution;

    // Define test cases
    std::vector<std::pair<std::vector<int>, int>> testCases = {
        {{1, 12, -5, -6, 50, 3}, 4},   // Expected: 12.75
        {{5}, 1},                     // Expected: 5.0
        {{0, 4, 0, 3, 2}, 1},         // Expected: 4.0
        {{0, 4, 0, 3, 2}, 2},         // Expected: 3.5
        {{-1, -12, -5, -6, -50, -3}, 2} // Expected: -4.0
    };

    // Iterate through test cases
    for (const auto& [nums, k] : testCases) {
        // Print the input array
        std::cout << "Array: [";
        for (size_t i = 0; i < nums.size(); ++i) {
            std::cout << nums[i];
            if (i != nums.size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << "], k = " << k << "\n";

        // Call the findMaxAverage function and print the result
        double result = solution.findMaxAverage(const_cast<std::vector<int>&>(nums), k);
        std::cout << "Maximum Average Subarray: " << result << "\n\n";
    }

    return 0;
}
