#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
This is the solution for the problem "Array Partition", classed "Easy" on LeetCode. It is found under:
https://leetcode.com/problems/array-partition/description/

Time Complexity: O(n log n) where n is the lengths of nums
Space Complexity: O(log n) as we are modifying values in place
*/



class Solution {
public:
    int arrayPairSum(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        int maxsum = 0;
        for(int i = 0 ; i<nums.size(); i= i +2){
            maxsum = maxsum+nums[i];
        }
        return maxsum;
    }
};

// Driver code
int main() {
    // Test case 1: [1,4,3,2]
    vector<int> nums1 = {1, 4, 3, 2};
    Solution sol;
    int result1 = sol.arrayPairSum(nums1);
    cout << "Test case 1: [1,4,3,2] => " << result1 << endl;  // Expected output: 4

    // Test case 2: [6,2,6,5,1,2]
    vector<int> nums2 = {6, 2, 6, 5, 1, 2};
    int result2 = sol.arrayPairSum(nums2);
    cout << "Test case 2: [6,2,6,5,1,2] => " << result2 << endl;  // Expected output: 9

    // Test case 3: Empty array
    vector<int> nums3 = {};
    int result3 = sol.arrayPairSum(nums3);
    cout << "Test case 3: [] => " << result3 << endl;  // Expected output: 0

    // Test case 4: Negative numbers
    vector<int> nums4 = {-1, -4, -3, -2};
    int result4 = sol.arrayPairSum(nums4);
    cout << "Test case 4: [-1,-4,-3,-2] => " << result4 << endl;  // Expected output: -6

    return 0;
}
