#include <iostream>
#include <vector>
#include <queue>

/*
This is the solution for "Course Schedule" (LeetCode 207):
https://leetcode.com/problems/course-schedule/description/

Approach: Use topological sort with BFS (Kahn's algorithm) to detect cycles in the directed graph.
Time: O(V + E) where V = courses, E = prerequisites
Space: O(V + E) for adjacency list and in-degree array
*/

class Solution {
public:   
    bool canFinish(int n, std::vector<std::vector<int>>& pre) {
        std::vector<std::vector<int>> adj(n, std::vector<int>());  // The integers inside each inner vector represent the nodes that are depending on the position integer at which the vector containing them is. For: [1,0], 1 will be pushed to position 0, hence node 1 depends on node 0.
        std::vector<int> degree(n, 0);  // Each position shows the number of dependencies for each node
        for (auto &p: pre) {
            adj[p[1]].push_back(p[0]);
            degree[p[0]]++;
        }
        std::queue<int> q;  // Contains indexes of nodes with 0 dependencies
        for (int i = 0; i < n; i++)  // Check which nodes have 0 dependencies and start with them
            if (degree[i] == 0) q.push(i);
        while (!q.empty()) {
            int curr = q.front(); q.pop(); n--;
            for (auto next: adj[curr])
                if (--degree[next] == 0) q.push(next);  // If dependencies are 0 at the index, push to queue
        }
        return n == 0;
    }
};

int main() {
    Solution solution;
    
    // Test cases: {numCourses, prerequisites, expectedOutput}
    std::vector<std::tuple<int, std::vector<std::vector<int>>, bool>> testCases = {
        {2, {{1, 0}}, true},
        {2, {{1, 0}, {0, 1}}, false},
        {3, {{1, 0}, {2, 1}}, true},
        {4, {{1, 0}, {2, 1}, {3, 2}}, true},
        {4, {{1, 0}, {2, 1}, {3, 2}, {1, 3}}, false},
        {5, {{1, 0}, {2, 1}, {3, 1}, {4, 3}}, true},
        {3, {}, true},
        {1, {}, true}
    };
    
    // Run tests
    int testCaseNum = 1;
    for (const auto& testCase : testCases) {
        int numCourses = std::get<0>(testCase);
        std::vector<std::vector<int>> prerequisites = std::get<1>(testCase);
        bool expectedOutput = std::get<2>(testCase);
        
        std::cout << "Test Case " << testCaseNum++ << ":\n";
        std::cout << "Number of courses: " << numCourses << "\n";
        std::cout << "Prerequisites: [";
        for (size_t i = 0; i < prerequisites.size(); ++i) {
            std::cout << "[" << prerequisites[i][0] << "," << prerequisites[i][1] << "]";
            if (i != prerequisites.size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << "]\n";
        
        bool result = solution.canFinish(numCourses, prerequisites);
        std::cout << "Output: " << (result ? "true" : "false") << "\n";
        std::cout << "Expected: " << (expectedOutput ? "true" : "false") << "\n";
        std::cout << "Result: " << (result == expectedOutput ? "PASS" : "FAIL") << "\n\n";
    }
    
    return 0;
}

