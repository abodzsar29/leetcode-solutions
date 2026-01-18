#include <vector>
#include <queue>
#include <iostream>

// Breadth First Search method:
class BFS {
public:
    std::vector<std::vector<int>> permute(std::vector<int>& nums) {
        std::vector<std::vector<int>> result;
        std::queue<std::vector<int>> permutations;
        permutations.push({});

        for (int num : nums) {
            int size = permutations.size();
            for (int i = 0; i < size; ++i) {
                std::vector<int> current = permutations.front();
                permutations.pop();

                // Insert the current number into every possible position
                for (int j = 0; j <= current.size(); ++j) {
                    std::vector<int> newPermutation = current;
                    newPermutation.insert(newPermutation.begin() + j, num);
                    if (newPermutation.size() == nums.size()) {
                        result.push_back(newPermutation);
                    }
                    else {
                        permutations.push(newPermutation);
                    }
                }
            }
        }

        return result;
    }
};


// Backtracking / Depth First Search method:
class Backtracking{
public:
    std::vector<std::vector<int>> permute(std::vector<int>& nums) {
        std::vector<std::vector<int>> result;
        backtrack(nums, 0, result);
        return result;
    }

private:
    void backtrack(std::vector<int>& nums, int start, std::vector<std::vector<int>>& result) {
        if (start == nums.size()) {
            result.push_back(nums);
            return;
        }

        for (int i = start; i < nums.size(); ++i) {
            std::swap(nums[start], nums[i]);
            backtrack(nums, start + 1, result);
            std::swap(nums[start], nums[i]); // backtrack
        }
    }
};


int main() {
    std::vector<int> nums = { 1,2,3 };
    BFS bfs;
    std::vector<std::vector<int>> bfsResult = bfs.permute(nums);
    std::cout << "BFS Results: " << std::endl;
    for (const std::vector<int>& container : bfsResult) {
        for (int num : container) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    Backtracking bcktrck;
    std::vector<std::vector<int>> bcktrckResults = bcktrck.permute(nums);
    std::cout << "Backtracked results: " << std::endl;
    for (int i = 0; i < bcktrckResults.size(); i++) {
        std::cout << "[ ";
        for (int num : bcktrckResults[i]) {
            std::cout << num << ", ";
        }
        std::cout << "]" << std::endl;
    }


    return 0;
}