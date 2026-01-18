#include <iostream>
#include <vector>
using namespace std;

/*
This is the solution for the problem "Binary Search", classed "Easy" on LeetCode. It is found under:
https://leetcode.com/problems/binary-search/description/
      //
This problem uses the Binary Search technique.

Time Complexity: O(log n) where n is the number of elements in the array.
                 In each iteration, we halve the search space, so the time complexity is logarithmic.
                 
Space Complexity: O(1) as we only use a constant amount of extra space regardless of the input size.
*/

class Solution {
public:
    int search(vector<int>& nums, int target) {
        // Iterative solution
        int low = 0;
        int high = nums.size() - 1;
        while (low <= high) {
            int mid = low + ((high - low) / 2);
            if (nums[mid] == target) { 
                return mid; 
            }

            if (target < nums[mid]) {
                high = mid - 1;
            } else if (target > nums[mid]) {
                low = mid + 1;
            }
        }

        return -1;  // If target is not found
    }
};

int main() {
    Solution sol;

    // Test case 1: Target exists in the array
    vector<int> nums1 = {-1, 0, 3, 5, 9, 12};
    int target1 = 9;
    cout << "Index of " << target1 << ": " << sol.search(nums1, target1) << endl;  // Expected: 4

    // Test case 2: Target does not exist in the array
    vector<int> nums2 = {-1, 0, 3, 5, 9, 12};
    int target2 = 2;
    cout << "Index of " << target2 << ": " << sol.search(nums2, target2) << endl;  // Expected: -1

    // Test case 3: Target is the first element
    vector<int> nums3 = {-5, 0, 3, 5, 9, 12};
    int target3 = -5;
    cout << "Index of " << target3 << ": " << sol.search(nums3, target3) << endl;  // Expected: 0

    // Test case 4: Target is the last element
    vector<int> nums4 = {1, 3, 5, 7, 9, 11};
    int target4 = 11;
    cout << "Index of " << target4 << ": " << sol.search(nums4, target4) << endl;  // Expected: 5

    // Test case 5: Array has only one element (target exists)
    vector<int> nums5 = {5};
    int target5 = 5;
    cout << "Index of " << target5 << ": " << sol.search(nums5, target5) << endl;  // Expected: 0

    // Test case 6: Array has only one element (target does not exist)
    vector<int> nums6 = {5};
    int target6 = 3;
    cout << "Index of " << target6 << ": " << sol.search(nums6, target6) << endl;  // Expected: -1

    return 0;
}
