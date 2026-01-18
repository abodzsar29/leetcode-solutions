#include<iostream>
#include<vector>
using namespace std;

/*
This is the solution for the problem "Sort Colors", classed "Medium" on LeetCode. It is found under:
https://leetcode.com/problems/sort-colors/description/

This problem uses the Dutch National Flag algorithm.

Time Complexity: O(n) where n is the lengths of nums
Space Complexity: O(1) as we are modifying values in place
*/

class Solution {
public:
    void sortColors(vector<int>& nums) {
        int low = 0;        // pointer for 0s (left section)
        int mid = 0;        // pointer for 1s (middle section)
        int high = nums.size() - 1;  // pointer for 2s (right section)
        
        while (mid <= high) {
            if (nums[mid] == 0) {
                swap(nums[low], nums[mid]);
                low++;
                mid++;
            }
            else if (nums[mid] == 1) {
                mid++;
            }
            else {  // nums[mid] == 2
                swap(nums[mid], nums[high]);
                high--;
            }
        }
    }
    
private:
    void swap(int& a, int& b) {
        int temp = a;
        a = b;
        b = temp;
    }
};

// Function to print the array
void printArray(const vector<int>& nums) {
    for (int num : nums) {
        cout << num << " ";
    }
    cout << endl;
}

// Driver Code
int main() {
    Solution obj;
    vector<vector<int>> testCases = {
        {2, 0, 2, 1, 1, 0},
        {0, 1, 2, 0, 1, 2, 1, 0},
        {2, 2, 1, 1, 0, 0},
        {0, 0, 0, 1, 1, 1, 2, 2, 2},
        {1, 2, 0, 1, 2, 0, 1, 0, 2}
    };

    for (auto& testCase : testCases) {
        cout << "Original: ";
        printArray(testCase);

        obj.sortColors(testCase);

        cout << "Sorted  : ";
        printArray(testCase);
        cout << "----------------------" << endl;
    }

    return 0;
}


