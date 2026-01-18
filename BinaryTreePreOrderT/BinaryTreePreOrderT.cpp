#include <iostream>
#include <vector>
using namespace std;

// Definition for a binary tree node as provided
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// The Solution class containing the preorder traversal function
class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> result;
        preOrderHelper(root, result);
        return result;
    };

    void preOrderHelper(TreeNode* root, vector<int>& result) {
        if (!root) return;
        result.push_back(root->val);
        preOrderHelper(root->left, result);
        preOrderHelper(root->right, result);
    }

    vector<int> iterativePreOrderTraversal(TreeNode* root) {
        vector<int> result;
        stack<TreeNode*> myStack;
        while (root || !myStack.empty()) {
            if (root) {
                result.push_back(root -> val);
                if (root -> right) {
                    myStack.push(root -> right);
                }
                root = root -> left;
            } else {
                root = myStack.top();
                myStack.pop();
            }
        }
        return result;
    }


};

// Function to create a sample binary tree
TreeNode* createSampleTree() {
    /* Creating a tree that looks like:
            1
           / \
          2   3
         / \   \
        4   5   6
    */
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->right = new TreeNode(6);
    
    return root;
}

// Function to delete the tree to prevent memory leaks
void deleteTree(TreeNode* root) {
    if (root == nullptr) return;
    
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

// Main function to demonstrate the preorder traversal
int main() {
    // Create a sample binary tree
    TreeNode* root = createSampleTree();
    
    // Create a Solution object
    Solution solution;
    
    // Perform preorder traversal
    vector<int> result = solution.preorderTraversal(root);
    
    // Print the result
    cout << "Preorder Traversal: ";
    for (int val : result) {
        cout << val << " ";
    }
    cout << endl;
    
    // Expected output: 1 2 4 5 3 6
    cout << "Expected output: 1 2 4 5 3 6" << endl;
    
    // Clean up memory
    deleteTree(root);
    
    return 0;
}
