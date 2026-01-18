#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
using namespace std;

/*
 * This is the solution for the problem "Clone Graph", classed "Medium" on LeetCode.
 * It is found under: https://leetcode.com/problems/clone-graph/
 *
 * Problem description:
 * Given a reference of a node in a connected undirected graph, return a deep copy (clone) of the graph.
 * Each node in the graph contains a value (int) and a list (vector) of its neighbors.
 *
 * Time Complexity: O(V + E), where V is the number of vertices and E is the number of edges.
 * We explore each vertex and edge once in the worst case.
 *
 * Space Complexity: O(V), where V is the number of vertices, for storing the visited nodes array
 * and the recursion stack.
 */

// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;
    
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};

class Solution {
public:
    Node* cloneGraph(Node* originalGraph) {
        if (originalGraph == nullptr) {
            return nullptr;
        }

        vector<Node*> visitedNodes(101, nullptr);
        Node* clonedRoot = new Node(originalGraph->val);
        cloneNodesRecursively(clonedRoot, originalGraph, visitedNodes);

        return clonedRoot;
    }

private:
    void cloneNodesRecursively(Node* clonedNode, Node* originalNode, vector<Node*>& visitedNodes) {
        visitedNodes[clonedNode->val] = clonedNode;

        for (Node* neighbor : originalNode->neighbors) {
            if (visitedNodes[neighbor->val] == nullptr) {
                Node* clonedNeighbor = new Node(neighbor->val);
                clonedNode->neighbors.push_back(clonedNeighbor);
                cloneNodesRecursively(clonedNeighbor, neighbor, visitedNodes);
            } else {
                clonedNode->neighbors.push_back(visitedNodes[neighbor->val]);
            }
        }
    }
};

// Helper function to create a graph from an adjacency list
Node* createGraph(const vector<vector<int>>& adjList) {
    if (adjList.empty()) {
        return nullptr;
    }
    
    // Create all nodes first
    vector<Node*> nodes(adjList.size() + 1, nullptr);
    for (int i = 1; i <= adjList.size(); i++) {
        nodes[i] = new Node(i);
    }
    
    // Add neighbors
    for (int i = 0; i < adjList.size(); i++) {
        int nodeVal = i + 1;
        for (int neighborVal : adjList[i]) {
            nodes[nodeVal]->neighbors.push_back(nodes[neighborVal]);
        }
    }
    
    return nodes[1]; // Return the node with value 1 as the entry point
}

// Helper function to convert a graph to an adjacency list
vector<vector<int>> graphToAdjList(Node* node) {
    if (node == nullptr) {
        return {};
    }
    
    // Find the maximum node value to determine adjacency list size
    int maxVal = 0;
    std::queue<Node*> q;
    std::unordered_set<int> visited;
    
    q.push(node);
    visited.insert(node->val);
    maxVal = std::max(maxVal, node->val);
    
    while (!q.empty()) {
        Node* current = q.front();
        q.pop();
        
        for (Node* neighbor : current->neighbors) {
            maxVal = std::max(maxVal, neighbor->val);
            if (visited.find(neighbor->val) == visited.end()) {
                visited.insert(neighbor->val);
                q.push(neighbor);
            }
        }
    }
    
    // Create adjacency list
    vector<vector<int>> adjList(maxVal);
    visited.clear();
    q.push(node);
    visited.insert(node->val);
    
    while (!q.empty()) {
        Node* current = q.front();
        q.pop();
        
        // Sort neighbors for consistent output
        vector<int> neighborVals;
        for (Node* neighbor : current->neighbors) {
            neighborVals.push_back(neighbor->val);
        }
        sort(neighborVals.begin(), neighborVals.end());
        
        adjList[current->val - 1] = neighborVals;
        
        for (Node* neighbor : current->neighbors) {
            if (visited.find(neighbor->val) == visited.end()) {
                visited.insert(neighbor->val);
                q.push(neighbor);
            }
        }
    }
    
    return adjList;
}

// Helper function to check if two graphs are equal
bool areGraphsEqual(Node* graph1, Node* graph2) {
    if (graph1 == nullptr && graph2 == nullptr) {
        return true;
    }
    if (graph1 == nullptr || graph2 == nullptr) {
        return false;
    }
    
    // Convert both graphs to adjacency lists and compare
    auto adjList1 = graphToAdjList(graph1);
    auto adjList2 = graphToAdjList(graph2);
    
    if (adjList1.size() != adjList2.size()) {
        return false;
    }
    
    for (size_t i = 0; i < adjList1.size(); i++) {
        if (adjList1[i] != adjList2[i]) {
            return false;
        }
    }
    
    return true;
}

// Helper function to clean up memory
void cleanupGraph(Node* node) {
    if (node == nullptr) {
        return;
    }
    
    std::unordered_set<int> visited;
    std::queue<Node*> q;
    
    q.push(node);
    visited.insert(node->val);
    
    while (!q.empty()) {
        Node* current = q.front();
        q.pop();
        
        for (Node* neighbor : current->neighbors) {
            if (visited.find(neighbor->val) == visited.end()) {
                visited.insert(neighbor->val);
                q.push(neighbor);
            }
        }
    }
    
    // Delete all nodes
    for (auto it = visited.begin(); it != visited.end(); ++it) {
        // This is inefficient in a real scenario as we don't have a mapping from values to nodes
        // For a simple driver program, we'll leave it as is
    }
}

// Print adjacency list representation of a graph
void printGraph(Node* node) {
    if (node == nullptr) {
        std::cout << "Empty graph" << std::endl;
        return;
    }
    
    auto adjList = graphToAdjList(node);
    std::cout << "Graph representation:" << std::endl;
    
    for (int i = 0; i < adjList.size(); i++) {
        std::cout << "Node " << (i + 1) << " -> [";
        for (size_t j = 0; j < adjList[i].size(); j++) {
            std::cout << adjList[i][j];
            if (j < adjList[i].size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << "]" << std::endl;
    }
}

int main() {
    // Create an instance of the Solution class
    Solution solution;
    
    // Test cases
    std::vector<std::vector<std::vector<int>>> testCases = {
        // Test case 1: Simple graph with 4 nodes
        // Node 1 connects to 2, 4
        // Node 2 connects to 1, 3
        // Node 3 connects to 2, 4
        // Node 4 connects to 1, 3
        {
            {2, 4},    // Neighbors of node 1
            {1, 3},    // Neighbors of node 2
            {2, 4},    // Neighbors of node 3
            {1, 3}     // Neighbors of node 4
        },
        
        // Test case 2: Single node graph
        {
            {}         // Node 1 with no neighbors
        },
        
        // Test case 3: Linear graph
        {
            {2},       // Node 1 connects to 2
            {1, 3},    // Node 2 connects to 1, 3
            {2}        // Node 3 connects to 2
        }
    };
    
    int testCaseNumber = 1;
    for (const auto& adjList : testCases) {
        std::cout << "==== Test Case " << testCaseNumber++ << " ====" << std::endl;
        
        // Create the original graph
        Node* originalGraph = createGraph(adjList);
        
        std::cout << "Original Graph:" << std::endl;
        printGraph(originalGraph);
        
        // Clone the graph
        Node* clonedGraph = solution.cloneGraph(originalGraph);
        
        std::cout << "Cloned Graph:" << std::endl;
        printGraph(clonedGraph);
        
        // Check if the cloned graph is equal to the original graph
        bool areEqual = areGraphsEqual(originalGraph, clonedGraph);
        std::cout << "Are graphs equal? " << (areEqual ? "Yes" : "No") << std::endl;
        
        // Check if they are different objects in memory
        bool areDifferentObjects = (originalGraph != clonedGraph);
        std::cout << "Are they different objects? " << (areDifferentObjects ? "Yes" : "No") << std::endl;
        
        // Check deep clone (neighbors are also different objects)
        bool isDeepClone = true;
        if (originalGraph != nullptr && clonedGraph != nullptr) {
            std::queue<std::pair<Node*, Node*>> q;
            std::unordered_map<int, bool> visited;
            
            q.push({originalGraph, clonedGraph});
            visited[originalGraph->val] = true;
            
            while (!q.empty() && isDeepClone) {
                Node* origNode = q.front().first;
                Node* cloneNode = q.front().second;
                q.pop();
                
                if (origNode->neighbors.size() != cloneNode->neighbors.size()) {
                    isDeepClone = false;
                    break;
                }
                
                // Create mappings from node values to node objects for easier comparison
                std::unordered_map<int, Node*> origNeighbors, cloneNeighbors;
                for (Node* n : origNode->neighbors) origNeighbors[n->val] = n;
                for (Node* n : cloneNode->neighbors) cloneNeighbors[n->val] = n;
                
                for (const auto& entry : origNeighbors) {
                    int nodeVal = entry.first;
                    Node* origNeighbor = entry.second;
                    Node* cloneNeighbor = cloneNeighbors[nodeVal];
                    
                    if (origNeighbor == cloneNeighbor) {
                        isDeepClone = false;
                        break;
                    }
                    
                    if (!visited[nodeVal]) {
                        visited[nodeVal] = true;
                        q.push({origNeighbor, cloneNeighbor});
                    }
                }
            }
        }
        std::cout << "Is it a deep clone? " << (isDeepClone ? "Yes" : "No") << std::endl;
        
        // Clean up memory (in a real application, we would need better memory management)
        // This is simplified for the driver code
        std::cout << std::endl;
    }
    
    return 0;
}
