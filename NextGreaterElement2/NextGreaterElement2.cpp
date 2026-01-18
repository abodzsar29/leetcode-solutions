#include <iostream>
#include <vector>
#include <stack>
#include <unordered_map>
using namespace std;



/*
This is the solution for the problem "Next Greater Element 2", classed "Medium" on LeetCode. It is found under:
https://leetcode.com/problems/next-greater-element-ii/

Time Complexity: O(n) as the main loop runs 2n times and each element is pushed and popped at most once from stack
Space Complexity: O(n) as stack can store at most n elements and result vector stores n elements
*/

class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        int n = nums.size();
        stack<int> st;
        vector<int> result(n, -1);
        
        // Process array twice to handle circular nature
        for(int i = 0; i < n * 2; i++) {
            while(!st.empty() && nums[st.top()] < nums[i % n]) {
                result[st.top()] = nums[i % n];
                st.pop();
            }
            if(i < n) st.push(i);
        }
        
        return result;
    }
};

int main() {
   Solution solution;
   
   vector<int> nums = {1,2,1};
   vector<int> result = solution.nextGreaterElements(nums);
   
   cout << "Output of {1, 2, 1}: ";
   for(int num : result) {
       cout << num << " ";  // Expected output: 2 -1 2
   }
   cout << endl << endl;
   
   vector<int> nums2 = {1,2,3,4,3};
   cout << "Output of {1, 2, 3, 4, 3}: ";
   result = solution.nextGreaterElements(nums2);
   
   for(int num : result) {
       cout << num << " ";  // Expected output: 2 3 4 -1 4
   }
   cout << endl;   
   return 0;
}
