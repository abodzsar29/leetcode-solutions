#include <iostream>
#include <vector>

/*
This is the solution for the problem "Best Time to Buy and Sell Stock", classed "Medium" on LeetCode. It is found under:
https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/description/?envType=study-plan-v2&envId=top-interview-150

It is included in the "Top Interview 150" problem set, which covers comprehensive interview A&DS topics.

Time Complexity: O(n), where n is the length of the input array. The algorithm iterates through the array once.
Space Complexity: O(1), as the modification is done in-place without using any additional data structures.
*/

// Approach 1: 
class Solution {
public:
    int maxProfit(std::vector<int>& prices) {
        int min_price = INT_MAX;
        int profit = 0;
        for (int daily_price : prices) {
            min_price = std::min(daily_price, min_price);
            int pot_profit = daily_price - min_price;
            if (pot_profit > 0) {
                profit += pot_profit;
                min_price = daily_price;
            }
        }
        return profit;
    }
};


int main() {
    std::vector<int> setOne = { 7,1,5,3,6,4 };
    std::vector<int> setTwo = { 1,2,3,4,5 };
    std::vector<int> setThree = { 7,6,4,3,1 };
    Solution sol1;
    std::cout << sol1.maxProfit(setOne) << std::endl;
    std::cout << sol1.maxProfit(setTwo) << std::endl;
    std::cout << sol1.maxProfit(setThree) << std::endl;
}

