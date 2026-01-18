#include <iostream>
#include <vector>
#include <iterator>
#include <cmath>
using namespace std;

/*
This is the solution for the problem "Remove Element", classed "Easy" on LeetCode. It is found under:
https://leetcode.com/problems/remove-element/?envType=study-plan-v2&envId=top-interview-150

It is included in the "Top Interview 150" problem set, which covers comprehensive interview topics.
*/

class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] == val) {
                nums.erase(nums.begin() + i);
                i--;
            }
        }
        return nums.size();
    }
}; 

int main() {
    Solution solution;
    int val = 2;
    vector<int> nums = {0,1,2,2,3,0,4,2};
    cout << solution.removeElement(nums, val) << endl;
    for (int i : nums) {
        cout << i << " ";
    }
    return 0;
}

