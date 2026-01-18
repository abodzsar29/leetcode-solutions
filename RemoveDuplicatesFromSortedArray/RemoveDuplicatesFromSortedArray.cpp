#include <iostream>
#include <vector>
using namespace std;

/*
This is the solution for the problem "Remove Duplicates from Sorted Array", classed "Easy" on LeetCode. It is found under:
https://leetcode.com/problems/remove-duplicates-from-sorted-array/?envType=study-plan-v2&envId=top-interview-150

It is included in the "Top Interview 150" problem set, which covers comprehensive interview topics.
*/

// Time Complexity: O(n^2) with nested loops
/*
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        for (int i = 0; i < nums.size(); ++i) {
            for (int j = i + 1; j < nums.size() - 1;) {
                if (nums[j] == nums[i]) {
                    nums.erase(nums.begin() + j);
                }
                else {
                    ++j;
                }
            }
        }
        return nums.size();
    }
};
*/

// Time Complexity: O(n)
class Solution {
public:
    int removeDuplicates(std::vector<int>& nums) {
        if (nums.empty()) return 0;

        int uniqueIndex = 1; // Index to place the next unique element

        for (int i = 1; i < nums.size(); ++i) {
            if (nums[i] != nums[i - 1]) {
                nums[uniqueIndex] = nums[i];
                ++uniqueIndex;
            }
        }
        // Resize the vector to remove the extra elements
        nums.resize(uniqueIndex);

        return uniqueIndex;
    }
};


int main() {
    Solution solution;
    vector<int> nums = { 1,1,2,3,3,3,4,5,5,5,6 };
    solution.removeDuplicates(nums);
    for (int i : nums) {
        cout << i << " ";
    }
    return 0;
}

