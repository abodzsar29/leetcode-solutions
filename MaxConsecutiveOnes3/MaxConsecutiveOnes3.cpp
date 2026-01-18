#include <iostream>
#include <vector>
#include <algorithm>

/*
This is the solution for the problem "Max Consecutive Ones III", classed "Medium" on LeetCode.
It is found under:
https://leetcode.com/problems/max-consecutive-ones-iii/

It uses the Sliding Window approach to keep track of the maximum window where at most K zeros can be flipped to ones.

Time Complexity: O(n), where n is the length of the input array. Each element is visited at most twice.
Space Complexity: O(1), as it uses a constant amount of extra space.
*/

// Define the Solution class
class Solution {
public:
    int longestOnes(std::vector<int>& nums, int k) {
        int left = 0;      // Left boundary of the sliding window
        int right = 0;     // Right boundary of the sliding window
        int count = 0;     // Count of zeros in the current window
        int maxi = 0;      // Maximum length of valid window found

        while (right < nums.size()) {
            // If current element is 0, increase the zero count
            if (nums[right] == 0) count++;

            // If the number of zeros exceeds k, shrink the window from the left
            if (count > k) {
                if (nums[left] == 0) count--;
                left++;
            }

            // Update the maximum window size
            maxi = std::max(maxi, right - left + 1);

            // Move the right pointer to expand the window
            right++;
        }

        return maxi;
    }
};

int main() {
    // Create an instance of the Solution class
    Solution solution;

    // Test cases
    std::vector<std::pair<std::vector<int>, int>> testCases = {
        {{1,1,1,0,0,0,1,1,1,1,0}, 2},    // Expected output: 6
        {{0,0,1,1,1,0,0}, 0},            // Expected output: 3
        {{1,1,1,1,1}, 2},                // Expected output: 5
        {{0,0,0,0}, 2},                  // Expected output: 2
        {{1,0,1,0,1}, 1},                // Expected output: 3
        {{1,0,1,0,1}, 2},                // Expected output: 5
        {{}, 1}                          // Expected output: 0
    };

    // Iterate through test cases
    for (const auto& [nums, k] : testCases) {
        // Print the input
        std::cout << "Input Array: [";
        for (size_t i = 0; i < nums.size(); ++i) {
            std::cout << nums[i];
            if (i != nums.size() - 1) std::cout << ", ";
        }
        std::cout << "], K = " << k << "\n";

        // Call the longestOnes function and print the output
        int result = solution.longestOnes(const_cast<std::vector<int>&>(nums), k);
        std::cout << "Max Consecutive Ones (with at most " << k << " zero flips): " << result << "\n\n";
    }

    return 0;
}
