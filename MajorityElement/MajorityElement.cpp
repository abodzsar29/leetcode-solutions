#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

/*
This is the solution for the problem "Majority Element", classed "Easy" on LeetCode. It is found under:
https://leetcode.com/problems/majority-element/description/?envType=study-plan-v2&envId=top-interview-150

It is included in the "Top Interview 150" problem set, which covers comprehensive interview topics.

Description:
Given an array nums of size n, return the majority element.
The majority element is the element that appears more than n / 2 times. You may assume that the majority element always exists in the array.

Example 1:
Input: nums = [3,2,3]
Output: 3

Example 2:
Input: nums = [2,2,1,1,1,2,2]
Output: 2
*/
/*
Approach 1: 
- If an element occurs more than n/2 times, it will always occupy the middle position when the array is sorted.
- Hence, we can sort the array and return the element at index n/2.
- It would be possible to use a sorting algorithm instead of the built-in sort function.
Time Complexity: O(n logn)
*/
/*
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        sort(nums.begin(), nums.end());  // Algorithm library needed
        int n = nums.size();
        return nums[n / 2];
    } // 
};
*/

// Approach 2: Hash Maps
/* 
- By using the unordered_map function of the Standard Library Template, we can iterate over each element inside the vector and
create key-value pairs, where each key would correspond to each different integer inside the vector, and the values would be the number
of the times they occur. 
- Then, the size of the vector would be stored inside an integer and divided by 2
- Following this, each value would be iterated over inside the unordered_map, and compared against the integer of the vector size (halved) stored previously
- The key of the value larger than this integer would be returned as the majority element
Time Complexity: O(n)
*/
/*
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        unordered_map<int, int> m;
        for (int i = 0; i < nums.size(); ++i) {
            m[nums[i]]++;
        }
        int vecSize = nums.size() / 2;
        for (auto x : m) {
            if (x.second > vecSize) {
                return x.first;
            }
        }
    }
};
*/

/*
Approach 3: Using Boyer-Moore Voting Algorithm
- If there is a majority element in the vector, it will always have the highest count if iterated through the vector and given 1 point per occurence for that integer.
- Initialize two variables: count and candidate. Set both variables to 0
- Iterate through the array nums:
a. Set the logic so if count is 0, assign the current element as the new candidate and increment count by 1. 
In the first iteration this will set candidate to the first element in the vector.
b. If the current element is the same as the candidate, increment count by 1
c. If the current element is different from the candidate, decrement count by 1
- After the iteration, return the candidate variable as it will hold the majority element
This method is more efficient than Approach 1 as it only requires one pass through and does not change the original order of the elements
Time Complexity: O(n)
*/

class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int count = 0;
        int candidate = 0;

        for (int num : nums) {
            if (count == 0) {
                candidate = num;
            }

            if (num == candidate) {
                count++;
            }
            else {
                count--;
            }
        }

        return candidate;
    }
};

int main() {
    Solution solution;
    vector<int> nums = { 2,2,1,1,3,2,2,2 };
    cout << solution.majorityElement(nums);
    /*for (int i : nums) {
        cout << i << " ";
    }*/
    return 0;
}

