#include <iostream>
#include <vector>

/*
This is the solution for the problem "Sort Array by Parity", classed "Easy" on LeetCode. It is found under:
https://leetcode.com/problems/sort-array-by-parity/description/

This problem uses a form of the Two Pointer algorithm.

Time Complexity: O(n) where n is the lengths of nums
Space Complexity: O(1) as we are modifying values in place
*/


using namespace std;

class Solution {
public:
    vector<int> sortArrayByParity(vector<int>& nums) {
        int evenIndex = 0;
        
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] % 2 == 0) {
                swap(nums[i], nums[evenIndex]);
                evenIndex++;
            }
        }
        
        return nums;
    }
};

// Utility function to print a vector
void printVector(const vector<int>& nums) {
    cout << "[";
    for (size_t i = 0; i < nums.size(); i++) {
        cout << nums[i];
        if (i < nums.size() - 1) {
            cout << ", ";
        }
    }
    cout << "]" << endl;
}

int main() {
    // Test cases
    vector<vector<int>> testCases = {
        {3, 1, 2, 4},
        {0, 1, 2},
        {0},
        {1, 3, 5, 7, 2, 4, 6, 8},
        {2, 4, 6, 8, 1, 3, 5, 7}
    };
    
    Solution solution;
    
    // Process each test case
    for (size_t i = 0; i < testCases.size(); i++) {
        vector<int> nums = testCases[i];
        
        cout << "Test Case " << (i + 1) << ":" << endl;
        cout << "Input: ";
        printVector(nums);
        
        vector<int> result = solution.sortArrayByParity(nums);
        
        cout << "Output: ";
        printVector(result);
        
        // Verify the result: all even numbers should come before odd numbers
        bool isValid = true;
        int firstOddIndex = -1;
        
        for (size_t j = 0; j < result.size(); j++) {
            if (result[j] % 2 == 1) { // Found an odd number
                firstOddIndex = j;
                break;
            }
        }
        
        if (firstOddIndex != -1) {
            for (size_t j = firstOddIndex; j < result.size(); j++) {
                if (result[j] % 2 == 0) { // Found an even number after odd numbers started
                    isValid = false;
                    break;
                }
            }
        }
        
        cout << "Valid result: " << (isValid ? "Yes" : "No") << endl;
        cout << "------------------------" << endl;
    }
    
    return 0;
}
