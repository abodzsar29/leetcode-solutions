#include<iostream>
#include<vector>
#include <unordered_set>
#include <algorithm>



/*
This is the solution for the problem "Find the Difference of Two Arrays", classed "Easy" on LeetCode. It is found under:
https://leetcode.com/problems/find-the-difference-of-two-arrays/description/

The first solution below uses sets, while the second uses the Two Pointer approach.

For the solution utilising sets:
Time Complexity: O(n + m) where n and m are lengths of nums1 and nums2
Space Complexity: O(n + m) where n and m are lengths of nums1 and nums2

For the solution utilising the two pointer approach:
Time Complexity: O(n log n + m log m) where n and m are lengths of nums1 and nums2
Space Complexity: O(1) excluding the output array

This makes the solution utilising sets have the better time complexity, however:
- For small arrays, the Two Pointer solution might be faster due to better cache locality
- The Set Solution uses more space
- Set operations have higher constant factors due to hash computations

*/


// Beats 88.74% of LeetCode submissions as of 21/1/25
class SolutionSet {
public:
    std::vector<std::vector<int>> findDifference(std::vector<int>& nums1, std::vector<int>& nums2) {
        // Convert to unordered_sets for O(1) lookup - O(n) time
        std::unordered_set<int> set1(nums1.begin(), nums1.end());
        std::unordered_set<int> set2(nums2.begin(), nums2.end());
        
        std::vector<int> diff1, diff2;
        
        // Find elements in set1 that aren't in set2 - O(n) time
        for(int num : set1) {
            if(!set2.count(num)) {
                diff1.push_back(num);
            }
        }
        
        // Find elements in set2 that aren't in set1 - O(n) time
        for(int num : set2) {
            if(!set1.count(num)) {
                diff2.push_back(num);
            }
        }
        
        return {diff1, diff2};
    }
};


class SolutionTwoPointer {
public:
    std::vector<std::vector<int>> findDifference(std::vector<int>& nums1, std::vector<int>& nums2) {
        // Sort both arrays
        std::sort(nums1.begin(), nums1.end());
        std::sort(nums2.begin(), nums2.end());
        
        std::vector<int> diff1, diff2;
        int i = 0, j = 0;
        
        // Remove duplicates from nums1
        nums1.erase(std::unique(nums1.begin(), nums1.end()), nums1.end());
        // Remove duplicates from nums2
        nums2.erase(std::unique(nums2.begin(), nums2.end()), nums2.end());
       
        
        // Use two pointers to compare elements
        while(i < nums1.size() && j < nums2.size()) {
            if(nums1[i] < nums2[j]) {
                diff1.push_back(nums1[i]);
                i++;
            }
            else if(nums1[i] > nums2[j]) {
                diff2.push_back(nums2[j]);
                j++;
            }
            else {  // nums1[i] == nums2[j]
                i++;
                j++;
            }
        }
        
        // Add remaining elements from nums1
        while(i < nums1.size()) {
            diff1.push_back(nums1[i]);
            i++;
        }
        
        // Add remaining elements from nums2
        while(j < nums2.size()) {
            diff2.push_back(nums2[j]);
            j++;
        }
        
        return {diff1, diff2};
    }
};

// Helper function to print vectors

void printResult(const std::vector<std::vector<int>>& result) {
    std::cout << "First array unique elements: ";
    for(int num : result[0]) {
        std::cout << num << " ";
    }
    std::cout << "\nSecond array unique elements: ";
    for(int num : result[1]) {
        std::cout << num << " ";
    }
    std::cout << "\n\n";
}

int main() {
    // Test case 1
    std::vector<int> nums1 = {1, 2, 3, 3};
    std::vector<int> nums2 = {2, 4, 6, 2};
    
    SolutionSet sol1;
    SolutionTwoPointer sol2;
    
    std::cout << "Test Case 1:\n";
    std::cout << "Set Solution:\n";
    auto result1 = sol1.findDifference(nums1, nums2);
    printResult(result1);
    
    // Reset nums1 and nums2 as they were modified by the first solution
    nums1 = {1, 2, 3, 3};
    nums2 = {2, 4, 6, 2};
    
    std::cout << "Two Pointer Solution:\n";
    auto result2 = sol2.findDifference(nums1, nums2);
    printResult(result2);
    
    // Test case 2
    nums1 = {9, 6, 4, 5};
    nums2 = {4, 3, 2, 9};
  
    std::cout << "Test Case 2:\n";
    std::cout << "Set Solution:\n";
    result1 = sol1.findDifference(nums1, nums2);
    printResult(result1);
    
    // Reset arrays
    nums1 = {9, 6, 4, 5};
    nums2 = {4, 3, 2, 9};
  
    std::cout << "Two Pointer Solution:\n";
    result2 = sol2.findDifference(nums1, nums2);
    printResult(result2);
    
    return 0;
}

