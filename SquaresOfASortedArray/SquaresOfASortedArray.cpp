#include <iostream>
#include <vector>
#include <cstdlib> // for abs()
using namespace std;


/*
This is the solution for the problem "Squares of a Sorted Array", classed "Easy" on LeetCode. It is found under:
https://leetcode.com/problems/squares-of-a-sorted-array/description/

The code uses two-pointer technique to handle negative and positive numbers efficiently while maintaining sorted order of squares

Time Complexity: O(n), where n is the length of input array. The algorithm makes a single pass through the array

Space Complexity: O(n) to store the result array. No additional space is used besides the output array
*/




class Solution {
public:
   vector<int> sortedSquares(vector<int>& a) {
       int i = 0;
       int j = a.size() - 1;
       int k = j;
       vector<int> ret(k + 1, 0);
       
       while (k >= 0) {
           if (abs(a[i]) > abs(a[j])) {
               ret[k--] = a[i] * a[i++];
           } else {
               ret[k--] = a[j] * a[j--];
           }
       }
       return ret;
   }
};

int main() {
   Solution sol;
   vector<int> nums = {-4, -1, 0, 3, 10};
   
   vector<int> result = sol.sortedSquares(nums);
   
   cout << "Squared and sorted array: ";
   for (int num : result) {
       cout << num << " ";
   }
   cout << endl;
   
   return 0;
}
