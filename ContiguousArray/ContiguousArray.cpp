#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

/*
This is the solution for the problem "Contiguous Array", classed "Medium" on LeetCode. It is found under:
https://leetcode.com/problems/contiguous-array/description/

For both solutions:
Time Complexity: O(n), where n is the length of the input array. The algorithm iterates through the array once.
Space Complexity: O(n), as the modification is done in-place without using any additional data structures.
*/

// Fixed-size Array Solution
class SolutionArray {
public:
    int findMaxLength(std::vector<int>& nums) {
        std::vector<int> arr(2 * nums.size() + 1, INT_MIN);
        arr[nums.size()] = -1;
        int maxLen = 0, sum = 0;
        for (int i = 0; i < nums.size(); i++) {
            sum += (nums[i] == 0 ? -1 : 1);
            if (arr[sum + nums.size()] >= -1)  maxLen = std::max(maxLen, i - arr[sum + nums.size()]);
            else  arr[sum + nums.size()] = i;
        }
        return maxLen;
    }
};

// Prefix Sum + Hash Map Solution
class SolutionHash {
public:
    int findMaxLength(std::vector<int>& nums) {
        // Map to store the first occurrence of a prefix sum
        std::unordered_map<int, int> prefixMap;
        // Initialize prefix sum and max length
        int prefixSum = 0, maxLength = 0;
        // Insert an initial value into the map to handle cases where the subarray starts from index 0
        prefixMap[0] = -1;

        // Iterate through the array
        for (int i = 0; i < nums.size(); ++i) {
            // Update prefix sum: treat 0 as -1
            prefixSum += (nums[i] == 1 ? 1 : -1);

            // Check if this prefix sum has been seen before
            if (prefixMap.find(prefixSum) != prefixMap.end()) {
                // Calculate the length of the subarray
                maxLength = std::max(maxLength, i - prefixMap[prefixSum]);
            }
            else {
                // Store the first occurrence of this prefix sum
                prefixMap[prefixSum] = i;
            }
        }

        return maxLength;
    }
};

int main() {
    // Test cases
    std::vector<std::vector<int>> testCases = {
        {0, 1},
        {0, 1, 0},
        {0, 0, 1, 0, 0, 1, 1},
        {0, 1, 1, 0, 1, 1, 0, 0},
        {1, 1, 1, 0, 0, 0, 1, 0}
    };

    SolutionArray solArray;
    SolutionHash solHash;

    // Execute test cases for both solutions
    for (const auto& testCase : testCases) {
        std::cout << "Testing array: ";
        for (int num : testCase) std::cout << num << " ";
        std::cout << "\n";

        int resultArray = solArray.findMaxLength(const_cast<std::vector<int>&>(testCase));
        int resultHash = solHash.findMaxLength(const_cast<std::vector<int>&>(testCase));

        std::cout << "SolutionArray Result: " << resultArray << "\n";
        std::cout << "SolutionHash Result: " << resultHash << "\n";
        std::cout << "---------------------------\n";
    }

    return 0;
}