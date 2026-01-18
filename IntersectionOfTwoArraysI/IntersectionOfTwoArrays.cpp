#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>

/*
This is the solution for the problem "Intersection of Two Arrays", classed "Easy" on LeetCode. It is found under:
https://leetcode.com/problems/intersection-of-two-arrays/

Time Complexity:

Solution 1: O(n*m) - nested loops from count() operations
Solution 2: O(n+m) - single pass using hash set

Space Complexity:

Solution 1: O(min(n,m)) for result vector
Solution 2: O(n) for unordered_set plus O(min(n,m)) for result vector
*/




class Solution1 {
public:
   std::vector<int> intersection(std::vector<int>& nums1, std::vector<int>& nums2) {
       int i = 0;
       std::vector<int> result;
       while (i < nums1.size()) {
           if (std::count(nums2.begin(), nums2.end(), nums1[i]) > 0 && 
               (!std::count(result.begin(), result.end(), nums1[i]))) {
               result.push_back(nums1[i]);
           };
           i++;
       }
       return result;
   }
};

class Solution2 {
public:
   std::vector<int> intersection(std::vector<int>& nums1, std::vector<int>& nums2) {
       std::unordered_set<int> m(nums1.begin(), nums1.end());
       std::vector<int> res;
       for (auto a : nums2)
           if (m.count(a)) {
               res.push_back(a);
               m.erase(a);
           }
       return res;
   }
};

int main() {
   std::vector<int> nums1 = {1,2,2,1};
   std::vector<int> nums2 = {2,2};
   
   Solution1 s1;
   Solution2 s2;
   
   auto result1 = s1.intersection(nums1, nums2);
   auto result2 = s2.intersection(nums1, nums2);
   
   std::cout << "Solution 1 result: ";
   for(int n : result1) std::cout << n << " ";
   std::cout << std::endl;
   
   std::cout << "Solution 2 result: ";
   for(int n : result2) std::cout << n << " ";
   std::cout << std::endl;
   
   return 0;
}

