#include <iostream>
#include <vector>
#include <algorithm>

/*
This is the solution for the problem "Count Number of Nice Subarrays", classed "Medium" on LeetCode. It is found under:
https://leetcode.com/problems/count-number-of-nice-subarrays/description/
It uses the Sliding Window Approach with the "At Most K" technique for its solution.
Time Complexity: O(n), where n is the length of the input array. The algorithm iterates through the array twice.
Space Complexity: O(1), as only a constant amount of extra space is used.
*/

// Define the Solution class
class Solution {
public:
    int n;
    
    // Helper function to count subarrays with at most k odd numbers
    int niceLessEqualK(std::vector<int>& nums, int k) {
        // Handle edge case where k is negative
        if (k < 0) return 0;

        int odds = 0, cnt = 0;
        for (int l = 0, r = 0; r < n; r++) {
            int x = nums[r];
            odds += (x & 1); // Check if number is odd using bitwise AND
            
            // Shrink window from left if we have more than k odd numbers
            while (odds > k) {
                int y = nums[l];
                odds -= (y & 1);
                l++;
            }
            
            // Count all subarrays ending at r with at most k odd numbers
            cnt += (r - l + 1);
        }
        return cnt;
    }
    
    int numberOfSubarrays(std::vector<int>& nums, int k) {
        n = nums.size();
        // Count subarrays with exactly k odd numbers =
        // Count subarrays with at most k odd numbers - Count subarrays with at most (k-1) odd numbers
        return niceLessEqualK(nums, k) - niceLessEqualK(nums, k - 1);
    }
};

int main() {
    // Create an instance of the Solution class
    Solution solution;
    
    // Test cases with expected outputs
    std::vector<std::pair<std::vector<int>, int>> testCases = {
        {{1, 1, 2, 1, 1}, 3},        // Expected output: 2
        {{2, 4, 6}, 1},              // Expected output: 0
        {{2, 2, 2, 1, 2, 2, 1, 2, 2, 2}, 2}, // Expected output: 16
        {{1, 3, 5}, 1},              // Expected output: 3
        {{1, 2, 3, 4, 5}, 2},        // Expected output: 6
        {{2, 4, 6, 8}, 0},           // Expected output: 0
        {{1}, 1},                    // Expected output: 1
        {{1, 1, 1, 1, 1}, 5}         // Expected output: 1
    };
    
    // Iterate through test cases
    for (const auto& testCase : testCases) {
        const std::vector<int>& nums = testCase.first;
        int k = testCase.second;
        
        // Print the input
        std::cout << "Array: [";
        for (size_t i = 0; i < nums.size(); ++i) {
            std::cout << nums[i];
            if (i != nums.size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << "], k = " << k << "\n";
        
        // Call the numberOfSubarrays function and print the output
        std::vector<int> numsCopy = nums; // Create a copy since the function takes non-const reference
        int result = solution.numberOfSubarrays(numsCopy, k);
        std::cout << "Number of Nice Subarrays: " << result << "\n\n";
    }
    
    return 0;
}
