#include <iostream>
#include <vector>
using namespace std;

/*
This is the solution for the problem "Rotate Array", classed "Medium" on LeetCode. It is found under:
https://leetcode.com/problems/rotate-array/description/?envType=study-plan-v2&envId=top-interview-150

It is included in the "Top Interview 150" problem set, which covers comprehensive interview topics.
*/

// Approach 1: 
/*
The provided solution first reduces the rotation steps k by taking k % nums.size(), which optimizes the operation by handling cases where
k exceeds the array length. It then iterates through the array and places each element at its new position in a temporary array, ensuring 
proper wrapping using the modulus operator. Finally, it copies the temporary array back to the original array.
Time Complexity: O(n) due to iterating through each element
Space Complexity: O(n) due to the temporary array
*/
/*
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        k = k % n; // Ensure k is within the bounds of the array size
        vector<int> tempNum = nums;
        for (int i = 0; i < n; i++) {
            tempNum[(i + k) % n] = nums[i];
        }
        nums = tempNum;
    }
};
*/

// Approach 2:
/*
- It defines an extra fucntion that reverses a given array between given boundaries.
- Then it follows 3 steps which invole calling the reversing function
    - 1. Reverse entire array
    - 2. Reverse the first k items
    - 3. Reverse the remaining the array.size() - k number of items at the end of array
This basically disects the array into two, with the first array being the first k items
and the second array being the array.size() - k items. It reverses both arrays inwards.
Time Complexity: O(n) - constants are ignored so O(3n) becomes O(n)
Space Complexity: O(1) as no additional data structures were used which grow with the size of input
*/
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        k %= nums.size();  // Prevents overflow, calculates how much array needs to wrap around by
        reverse(nums, 0, nums.size() - 1);  // If k = 4, it results in 7 6 5 4 3 2 1
        reverse(nums, 0, k - 1);  // Results in 4 5 6 7 3 2 1
        reverse(nums, k, nums.size() - 1);  // Results in 4 5 6 7 1 2 3
    };

    void reverse(vector<int>& nums, int start, int end) {
        while (start < end) {
            int temp = nums[start];
            nums[start] = nums[end];
            nums[end] = temp;
            start++;
            end--;
        }
    }
};

int main() {
    Solution solution;
    int k = 4;
    vector<int> nums = { 1,2,3,4,5,6,7 };
    solution.rotate(nums, k);
    for (int i : nums) {
        cout << i << " ";
    }
    return 0;
}

