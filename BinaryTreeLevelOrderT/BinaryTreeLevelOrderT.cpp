#include <iostream>
#include <vector>
#include <queue>

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
    std::vector<std::vector<int>> levelOrder(TreeNode* root) {
        std::vector<std::vector<int>> result;
        if(!root) return result;
        std::queue<TreeNode*> q;
        q.push(root);

        while(!q.empty()) {
            std::vector<int> currentLevel = {};
            int levelSize = q.size();

            for(int i = 0; i < levelSize; i++) {
                TreeNode* node = q.front();
                currentLevel.push_back(node->val);
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
                q.pop();
            }
            result.push_back(currentLevel);
        }
        return result;
    }
};

int main() {
    return 0;
}
