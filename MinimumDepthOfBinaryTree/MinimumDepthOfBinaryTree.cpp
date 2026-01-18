#include <iostream>
#include <queue>
#include <vector>
using namespace std;

/*
This is the solution for the problem "Minimum Depth of Binary Tree", classed "Easy" on LeetCode. It is found under:
https://leetcode.com/problems/minimum-depth-of-binary-tree/description/

This problem uses a level-order traversal (BFS) to find the minimum depth of the tree (shortest path from root to a leaf).

Time Complexity: O(n) where n is the number of nodes in the tree, as in worst case we might need to visit all nodes
Space Complexity: O(w) where w is the maximum width of the tree (could be up to n/2 in a worst case)
*/

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


// Beats 100% of LeetCode submissions as of 28.2.25
class Solution2 {
public:
    int minDepth(TreeNode* root) {
        if (!root) return 0;
        
        queue<TreeNode*> q;
        q.push(root);
        int depth = 0;
        
        while (!q.empty()) {
            depth++; // Increment depth for this level
            int levelSize = q.size();
            
            for (int i = 0; i < levelSize; i++) {
                TreeNode* node = q.front();
                q.pop();
                
                // If we found a leaf node, return current depth
                if (!node->left && !node->right) {
                    return depth;
                }
                
                // Add children to queue
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
        }
        
        return depth;
    }
};

// Solution 2, modified version of the BFS solution, beats 53.51% of LeetCode submissions as of 28.2.25
class Solution {
public:
    int minDepth(TreeNode* root) {
        vector<vector<int>> result;
        if (!root) { return 0; };
        queue<TreeNode*> q;
        q.push(root);

        while(!q.empty()) {
            int levelSize = q.size();
            vector<int> currentLevel = {};

            for (int i = 0; i < levelSize; i++) {
                TreeNode* tempNode = q.front();
                currentLevel.push_back(tempNode->val);
                if (!(tempNode->left) && !(tempNode->right)) {
                    result.push_back(currentLevel);
                    return result.size();
                }
                if (tempNode->left) { q.push(tempNode->left);};
                if (tempNode->right) { q.push(tempNode->right);};
                q.pop();
            }
            result.push_back(currentLevel);
        }   
        return result.size();
    }
};

// Driver code
int main() {
    // Test case 1: [3,9,20,null,null,15,7]
    //        3
    //       / \
    //      9  20
    //        /  \
    //       15   7
    TreeNode* root1 = new TreeNode(3);
    root1->left = new TreeNode(9);
    root1->right = new TreeNode(20);
    root1->right->left = new TreeNode(15);
    root1->right->right = new TreeNode(7);
    
    // Test case 2: [2,null,3,null,4,null,5,null,6]
    //        2
    //         \
    //          3
    //           \
    //            4
    //             \
    //              5
    //               \
    //                6
    TreeNode* root2 = new TreeNode(2);
    root2->right = new TreeNode(3);
    root2->right->right = new TreeNode(4);
    root2->right->right->right = new TreeNode(5);
    root2->right->right->right->right = new TreeNode(6);
    
    // Test case 3: Empty tree
    TreeNode* root3 = nullptr;
    
    Solution solution;
    
    std::cout << "Minimum depth of tree 1: " << solution.minDepth(root1) << std::endl; // Expected: 2
    std::cout << "Minimum depth of tree 2: " << solution.minDepth(root2) << std::endl; // Expected: 5
    std::cout << "Minimum depth of tree 3: " << solution.minDepth(root3) << std::endl; // Expected: 0
    
    // Clean up memory
    // (In a real implementation, you would want a proper cleanup function)
    
    return 0;
}
