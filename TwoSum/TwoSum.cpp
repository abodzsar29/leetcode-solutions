#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

/*
This is the solution for the problem "Two Sum", classed "Easy" on LeetCode. It is found under:
https://leetcode.com/problems/two-sum/description/

Two approaches are implemented:
1. Hash Map Approach - O(n) time complexity
2. Brute Force Approach - O(n²) time complexity

The problem asks to find indices of two numbers in an array that add up to a specific target.
*/

// Hash Map Solution
// Time Complexity: O(n), where n is the length of the input array.
//   The algorithm iterates through the array once.
// Space Complexity: O(n), as we store up to n elements in the hash map.
class HashMapSolution {
public:
    std::vector<int> twoSum(std::vector<int>& nums, int target) {
        std::unordered_map<int, int> numMap;
        int n = nums.size();

        for (int i = 0; i < n; i++) {
            int complement = target - nums[i];
            // Check if the complement exists in our map
            if (numMap.count(complement)) {
                return {numMap[complement], i};
            }
            // Store current number and its index
            numMap[nums[i]] = i;
        }

        return {}; // No solution found
    }
};

// Brute Force Solution
// Time Complexity: O(n²), where n is the length of the input array.
//   We check each pair of elements in the array.
// Space Complexity: O(1), as we only use a constant amount of space.
class BruteForceSolution {
public:
    std::vector<int> twoSum(std::vector<int>& nums, int target) {
        int n = nums.size();
        for (int i = 0; i < n - 1; i++) {
            for (int j = i + 1; j < n; j++) {
                // Check if current pair sums to target
                if (nums[i] + nums[j] == target) {
                    return {i, j};
                }
            }
        }
        return {}; // No solution found
    }
};

int main() {
    // Create instances of both solution classes
    HashMapSolution hashMapSolution;
    BruteForceSolution bruteForceSolution;
    
    // Test cases: {array, target}
    std::vector<std::pair<std::vector<int>, int>> testCases = {
        {{2, 7, 11, 15}, 9},             // Expected output: [0, 1]
        {{3, 2, 4}, 6},                  // Expected output: [1, 2]
        {{3, 3}, 6},                     // Expected output: [0, 1]
        {{1, 2, 3, 4, 5}, 9},            // Expected output: [3, 4]
        {{-1, -2, -3, -4, -5}, -8},      // Expected output: [2, 4]
        {{0, 4, 3, 0}, 0}                // Expected output: [0, 3]
    };
    
    // Iterate through test cases
    for (const auto& test : testCases) {
        std::vector<int> nums = test.first;
        int target = test.second;
        
        // Print the input
        std::cout << "Input Array: [";
        for (size_t i = 0; i < nums.size(); ++i) {
            std::cout << nums[i];
            if (i != nums.size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << "], Target: " << target << "\n";
        
        // Test Hash Map Solution
        auto hashMapResult = hashMapSolution.twoSum(nums, target);
        std::cout << "Hash Map Solution: [";
        for (size_t i = 0; i < hashMapResult.size(); ++i) {
            std::cout << hashMapResult[i];
            if (i != hashMapResult.size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << "]\n";
        
        // Test Brute Force Solution
        auto bruteForceResult = bruteForceSolution.twoSum(nums, target);
        std::cout << "Brute Force Solution: [";
        for (size_t i = 0; i < bruteForceResult.size(); ++i) {
            std::cout << bruteForceResult[i];
            if (i != bruteForceResult.size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << "]\n\n";
    }
    
    return 0;
}

