#include <iostream>
#include <vector>
#include <queue>
#include <stack>

struct TreeNode {
public:
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(): val(0), left(nullptr), right(nullptr) {};
    TreeNode(int x): val(x), left(nullptr), right(nullptr) {};
    TreeNode(int x, TreeNode* left, TreeNode* right): val(x), left(left), right(right) {};
};

class BinaryTree {
private:
    TreeNode* root;

    void deleteNodes(TreeNode* node) {
        if (node == nullptr) {
            return;
        }
        deleteNodes(node->left);
        deleteNodes(node->right);
        delete node;
    }

public:
    BinaryTree() : root(nullptr) {};
    ~BinaryTree() {
        deleteNodes(root);
    };

    TreeNode* getRoot() { return root;};

/* In-order Depth-First Search Traversal - Recursive solution*/
    void inorderHelper(TreeNode* node, std::vector<int>& result) {
        if (!node) return;
        inorderHelper(node->left, result);
        result.push_back(node->val);
        inorderHelper(node->right, result);
    }

    std::vector<int> inorder() {
        std::vector<int> result;
        inorderHelper(root, result);
        return result;
    }

/* In-order Depth-First Search Traversal - Iterative solution using a Stack*/
    
    std::vector<int> inorderTraversal(TreeNode* root) {
        std::vector<int> result;
        std::stack<TreeNode*> myStack;
        TreeNode* currentNode = root;
    
        while (currentNode || !myStack.empty()) {
            // Go as far left as possible
            while (currentNode) {
                myStack.push(currentNode);
                currentNode = currentNode->left;
            };
        
        // Process current node and go right
            currentNode = myStack.top();
            myStack.pop();
            result.push_back(currentNode->val);
            currentNode = currentNode->right;
        }
    
    return result;
    }
};




int main() {



  return 0;
} 

