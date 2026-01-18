#include <iostream>
#include <vector>
#include <queue>
#include <numeric>
using namespace std;

/*
This is the solution for the problem "Average of Levels in Binary Tree", classed "Easy" on LeetCode. It is found under:

https://leetcode.com/problems/average-of-levels-in-binary-tree/description/

This problem uses a level-order traversal (BFS) to calculate the average value of nodes at each level.
Time Complexity: O(n) where n is the number of nodes in the tree
Space Complexity: O(w) where w is the maximum width of the tree (could be up to n/2 in a worst case)
*/

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    vector<double> averageOfLevels(TreeNode* root) {
        // vector<vector<double>> tempResult;
        vector<double> result;
        if(!root) return result;
        queue<TreeNode*> q;
        q.push(root);

        while(!q.empty()) {
            vector<int> currentLevel = {};
            int levelSize = q.size();

            for(int i = 0; i < levelSize; i++) {
                TreeNode* node = q.front();
                currentLevel.push_back(node->val);
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
                q.pop();
            }
            double sum = (accumulate(currentLevel.begin(), currentLevel.end(), 0.0)) / levelSize;
            result.push_back(sum);
        }
        return result;
    }
  
};

int main() {
  return 0;
}
