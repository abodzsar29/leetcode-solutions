#include <iostream>
#include <queue>
#include <vector>


/*
This is the solution for the problem "Cousins in Binary Tree", classified as "Easy" on LeetCode. It is found under:
https://leetcode.com/problems/cousins-in-binary-tree/description/

Problem Description:
Given the root of a binary tree and two nodes x and y, return true if x and y are cousins, otherwise false.
Two nodes are cousins if they have the same depth but have different parents.

Time and Space Complexity Analysis:
1. DFS Solution:
   Time Complexity: O(n) where n is the number of nodes in the tree. In the worst case, we might need to visit all nodes.
   Space Complexity: O(h) where h is the height of the tree, due to the recursion stack. In the worst case, h can be n for a skewed tree.

2. BFS Solution:
   Time Complexity: O(n) where n is the number of nodes in the tree. In the worst case, we might need to visit all nodes.
   Space Complexity: O(w) where w is the maximum width of the tree, which is the maximum number of nodes at any level.
   In the worst case, this can be n/2 for a complete binary tree, which simplifies to O(n).
*/

// Definition for a binary tree node
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

//Recursive DFS
class Solution2 {
private:
    struct NodeInfo {
        int depth = -1;
        int parent = -1;
    };
    
    void findNodeInfo(TreeNode* root, int x, int y, NodeInfo& xInfo, NodeInfo& yInfo, 
                     int currentDepth = 0, int parentVal = -1) {
        if (!root) {
            return;
        }
        
        if (root->val == x) {
            xInfo.depth = currentDepth;
            xInfo.parent = parentVal;
        } else if (root->val == y) {
            yInfo.depth = currentDepth;
            yInfo.parent = parentVal;
        }
        
        // If both nodes are found, we can stop the search
        if (xInfo.depth != -1 && yInfo.depth != -1) {
            return;
        }
        
        findNodeInfo(root->left, x, y, xInfo, yInfo, currentDepth + 1, root->val);
        
        // Only proceed with right subtree if we haven't found both nodes yet
        if (xInfo.depth == -1 || yInfo.depth == -1) {
            findNodeInfo(root->right, x, y, xInfo, yInfo, currentDepth + 1, root->val);
        }
    }
    
public:
    bool isCousins(TreeNode* root, int x, int y) {
        if (!root || x == y) {
            return false;
        }
        
        NodeInfo xInfo, yInfo;
        findNodeInfo(root, x, y, xInfo, yInfo);
        
        // Nodes are cousins if they are at the same depth but have different parents
        return (xInfo.depth == yInfo.depth && xInfo.parent != yInfo.parent);
    }
};

// BFS 
class Solution {
public:
    bool isCousins(TreeNode* root, int x, int y) {
        if (!root) {
            return false;
        }
        
        std::queue<TreeNode*> q;
        q.push(root);
        
        while (!q.empty()) {
            int levelSize = q.size();
            bool foundX = false;
            bool foundY = false;
            
            for (int i = 0; i < levelSize; i++) {
                TreeNode* current = q.front();
                q.pop();
                
                // Check if target values are at current level
                if (current->val == x) foundX = true;
                if (current->val == y) foundY = true;
                
                // Check if both nodes have the same parent
                if (current->left && current->right) {
                    bool leftIsX = current->left->val == x;
                    bool leftIsY = current->left->val == y;
                    bool rightIsX = current->right->val == x;
                    bool rightIsY = current->right->val == y;
                    
                    // If both nodes are children of the same parent, they are siblings, not cousins
                    if ((leftIsX && rightIsY) || (leftIsY && rightIsX)) {
                        return false;
                    }
                }
                
                // Add children to the queue
                if (current->left) {
                    q.push(current->left);
                }
                if (current->right) {
                    q.push(current->right);
                }
            }
            
            // If both values are found at the same level, they are cousins
            if (foundX && foundY) {
                return true;
            }
            
            // If only one value is found at this level, they can't be cousins
            if (foundX || foundY) {
                return false;
            }
        }
        
        return false;
    }
};

// Helper function to create a tree from level order traversal
TreeNode* createTree(std::vector<int>& values) {
    if (values.empty() || values[0] == -1) {
        return nullptr;
    }
    
    TreeNode* root = new TreeNode(values[0]);
    std::queue<TreeNode*> q;
    q.push(root);
    
    int i = 1;
    while (!q.empty() && i < values.size()) {
        TreeNode* current = q.front();
        q.pop();
        
        // Left child
        if (i < values.size() && values[i] != -1) {
            current->left = new TreeNode(values[i]);
            q.push(current->left);
        }
        i++;
        
        // Right child
        if (i < values.size() && values[i] != -1) {
            current->right = new TreeNode(values[i]);
            q.push(current->right);
        }
        i++;
    }
    
    return root;
}

// Helper function to clean up memory
void deleteTree(TreeNode* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

// Driver code
int main() {
    // Test cases
    std::vector<std::vector<int>> testTrees = {
        {1, 2, 3, 4, -1, -1, -1},     // [1,2,3,4], x=4, y=3 -> false (different levels)
        {1, 2, 3, -1, 4, -1, 5},      // [1,2,3,null,4,null,5], x=5, y=4 -> true
        {1, 2, 3, -1, -1, 4, 5}       // [1,2,3,null,null,4,5], x=4, y=5 -> false (same parent)
    };
    
    std::vector<std::pair<int, int>> testPairs = {
        {4, 3},
        {5, 4},
        {4, 5}
    };
    
    std::vector<bool> expectedResults = {false, true, false};
    
    // Run tests
    std::cout << "Testing DFS Solution:" << std::endl;
    Solution2 dfs;
    for (size_t i = 0; i < testTrees.size(); i++) {
        TreeNode* root = createTree(testTrees[i]);
        bool result = dfs.isCousins(root, testPairs[i].first, testPairs[i].second);
        std::cout << "Test " << i+1 << ": ";
        if (result == expectedResults[i]) {
            std::cout << "PASSED" << std::endl;
        } else {
            std::cout << "FAILED (Got " << (result ? "true" : "false") 
                      << ", Expected " << (expectedResults[i] ? "true" : "false") << ")" << std::endl;
        }
        deleteTree(root);
    }
    
    std::cout << "\nTesting BFS Solution:" << std::endl;
    Solution bfs;
    for (size_t i = 0; i < testTrees.size(); i++) {
        TreeNode* root = createTree(testTrees[i]);
        bool result = bfs.isCousins(root, testPairs[i].first, testPairs[i].second);
        std::cout << "Test " << i+1 << ": ";
        if (result == expectedResults[i]) {
            std::cout << "PASSED" << std::endl;
        } else {
            std::cout << "FAILED (Got " << (result ? "true" : "false") 
                      << ", Expected " << (expectedResults[i] ? "true" : "false") << ")" << std::endl;
        }
        deleteTree(root);
    }
    
    return 0;
}


