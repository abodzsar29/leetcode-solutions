#include <iostream>
#include <vector>
#include <iterator>
#include <cmath>
using namespace std;

/*
This is the solution for the problem "Merge Sorted Array", classed "Easy" on LeetCode. It is found under:
https://leetcode.com/problems/merge-sorted-array/description/?envType=study-plan-v2&envId=top-interview-150

It is included in the "Top Interview 150" problem set, which covers comprehensive interview topics.
*/

class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int i = m - 1;
        int j = n - 1;
        int k = m + n - 1;
        
        while (i >= 0 && j >= 0) {
            if (nums1[i] > nums2[j]) {
                nums1[k--] = nums1[i--];
            } else {
                nums1[k--] = nums2[j--];
            }
        }
        
        while (j >= 0) { // Required, due to if i goes below 0, the nums2 vector needs to be fully moved
            nums1[k--] = nums2[j--];
        }
    }
};


int main() {
    vector<int> nums1 = {2,5,6,0,0,0};
    int m = 3;    
    vector<int> nums2 = {1,3,6};
    int n = 3;
    Solution solution;
    solution.merge(nums1, m, nums2, n);
    for(int i : nums1) {
        cout << i << " ";
    }
}

