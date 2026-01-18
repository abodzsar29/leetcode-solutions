#include <iostream>
#include <vector>
using namespace std;

/*
This is the solution for the problem "Remove Duplicates from Sorted Array II", classed "Medium" on LeetCode. It is found under:
https://leetcode.com/problems/remove-duplicates-from-sorted-array-ii/description/?envType=study-plan-v2&envId=top-interview-150

It is included in the "Top Interview 150" problem set, which covers comprehensive interview topics.

Time complexity: O(n), where n is the length of the input array. The algorithm iterates through the array once.
Space complexity: O(1), as the modification is done in-place without using any additional data structures.
*/

// Approach 1:
// Triple nested loops - not ideal as time complexity is O(n^3).
/*
class Solution {
public:
    int removeDuplicatesII(vector<int>& nums) {
        for (int i = 0; i < nums.size(); ++i) {
            for (int j = i + 1; j < nums.size(); ++j) {
                for (int x = j + 1; x < nums.size();) {
                    if (nums[x] == nums[i]) {
                        nums.erase(nums.begin() + x);
                    }
                    else {
                        ++x;
                    }
                }
            }
        }
        return nums.size();
    }
};
*/

// Approach 2: Beats 67.64% as of 10.12.24
/*
- The variable j is used to keep track of the current position in the modified array where elements are being stored without violating the constraint.
- The loop iterates through the array, and for each element, it checks whether it is the same as the element two positions behind the current j. 
If it is, it means there are already two occurrences of this element in the modified array, and we should skip adding another one to adhere to the constraint. 
Otherwise, the element is added to the modified array at position j, and j is incremented.
*/
class Solution2 {
public:
    int removeDuplicatesII(vector<int>& nums) {
        int j = 1;  // Must have value of 1 as minimum due to constraint: 1 <= nums.length
        for (int i = 1; i < nums.size(); i++) {
            if (j == 1 || nums[i] != nums[j - 2]) {  // Because there is a gap of 2 elements in conditional, 
                nums[j++] = nums[i];                // original order of integers is kept
            }
        }
        return j;
    }
};

//Approach 3:
class Solution3 {
public:
    int removeDuplicatesII(vector<int>& nums) {
        int count = 0;
        for(int i=0; i<nums.size()-1; i++)
        {
            if(nums[i]==nums[i+1])
            {
                if(count>=1) nums.erase(nums.begin()+i--);
                else count++;
            }
            else count = 0;
        }
        return nums.size();
    }
};



int main() {
    Solution solution;
    vector<int> nums = { 1,1,1,2,2,3,4 };
    int j = solution.removeDuplicatesII(nums);
    cout << "The final size is: " << j << endl;
    vector<int> finalSequence(nums.begin(), nums.begin() + j);
    cout << "The final sequence is: " << endl;
    for (int i : finalSequence) {
        cout << i << " ";
    }
    return 0;
}