#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>

/*
This is the solution for the problem "Intersection of Two Arrays II", classed "Easy" on LeetCode. It is found under:
https://leetcode.com/problems/intersection-of-two-arrays-ii/description/

Time Complexity:
Solution 1: O(n + m)
Solution 2: O(n + m)

Space Complexity:
Solution 1: O(n + min(n,m))
Solution 2: O(n + min(n,m))

where n and m are lengths of input arrays.

Both solutions beat 100% on runtime as of 24/1/2025.
*/

// Solution 1: Using unordered_multiset
class Solution1 {
public:
    std::vector<int> intersect(std::vector<int>& nums1, std::vector<int>& nums2) {
        std::unordered_multiset<int> multiSet(nums1.begin(), nums1.end());
        std::vector<int> result;
        for(auto j : nums2) {
            auto it = multiSet.find(j);
            if (it != multiSet.end()) {
                multiSet.erase(it);
                result.push_back(j);
            }
        }
        return result;
    }
};

// Solution 2: Using unordered_map
class Solution2 {
public:
    std::vector<int> intersect(std::vector<int>& a, std::vector<int>& b) {
        std::unordered_map<int, int> ctr;
        for (int i : a)
            ctr[i]++;
        std::vector<int> out;
        for (int i : b)
            if (ctr[i]-- > 0)
                out.push_back(i);
        return out;
    }
};

void printVector(const std::vector<int>& vec) {
    for (int num : vec) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

int main() {
    // Test Case 1: Regular intersection
    std::vector<int> nums1 = {1, 2, 2, 1};
    std::vector<int> nums2 = {2, 2};
    
    Solution1 sol1;
    Solution2 sol2;
    
    std::cout << "Test Case 1:\n";
    std::cout << "Solution 1 output: ";
    printVector(sol1.intersect(nums1, nums2));
    std::cout << "Solution 2 output: ";
    printVector(sol2.intersect(nums1, nums2));
    
    // Test Case 2: No intersection
    std::vector<int> nums3 = {1, 2, 3};
    std::vector<int> nums4 = {4, 5, 6};
    
    std::cout << "\nTest Case 2:\n";
    std::cout << "Solution 1 output: ";
    printVector(sol1.intersect(nums3, nums4));
    std::cout << "Solution 2 output: ";
    printVector(sol2.intersect(nums3, nums4));
    
    // Test Case 3: Multiple occurrences
    std::vector<int> nums5 = {1, 1, 1, 2};
    std::vector<int> nums6 = {1, 1, 2, 2};
    
    std::cout << "\nTest Case 3:\n";
    std::cout << "Solution 1 output: ";
    printVector(sol1.intersect(nums5, nums6));
    std::cout << "Solution 2 output: ";
    printVector(sol2.intersect(nums5, nums6));
    
    return 0;
}
