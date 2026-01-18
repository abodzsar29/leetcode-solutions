#include<iostream>
#include<vector>
#include<unordered_map>

class Solution {
public:
    int subarraySum(std::vector<int>& nums, int k) {
        std::unordered_map<int, int> holder = {{0,1}};
        int count = 0;
        int sum = 0;

        for (int num : nums) {
            sum += num;
            if (holder.find(sum - k) != holder.end()) {
                count += holder[sum - k];
            }

            holder[sum]++;
        }

        return count;
    }
};


int main() {
    std::vector<int> nums = {3, 4, 7, -2, 2, 1, 4, 2, 1, -1, 5};
    int k = 7;
    
    Solution sol;
    int result = sol.subarraySum(nums, k);
    
    std::cout << "Number of subarrays with sum " << k << ": " << result << std::endl;
    return 0;
}

