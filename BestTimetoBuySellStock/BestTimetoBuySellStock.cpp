#include <iostream>
#include <vector>
using namespace std;

/*
This is the solution for the problem "Best Time to Buy and Sell Stock", classed "Easy" on LeetCode. It is found under:
https://leetcode.com/problems/best-time-to-buy-and-sell-stock/description/?envType=study-plan-v2&envId=top-interview-150

It is included in the "Top Interview 150" problem set, which covers comprehensive interview A&DS topics.

Time Complexity: O(n), where n is the length of the input array. The algorithm iterates through the array once.
Space Complexity: O(1), as the modification is done in-place without using any additional data structures.
*/

// Approach 1: 
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int smallest = INT_MAX;
        int profit = 0;
        for (int dailyPrice : prices) {
            smallest = min(smallest, dailyPrice);  // Set 
            int potential_profit = dailyPrice - smallest;
            profit = max(profit, potential_profit);
        }
        return profit;
    }
};


int main() {
    vector<int> setOne = { 2, 4, 1};
    Solution sol1;
    cout << sol1.maxProfit(setOne);
}

