#include <iostream>
#include <vector>
#include <queue>
#include <utility>

/*
This is the solution for the problem "Number of Islands", classed "Medium" on LeetCode. It is found under:
https://leetcode.com/problems/number-of-islands/description/

It uses a Breadth-First Search (BFS) approach to identify and count islands in a grid.
Time Complexity: O(m*n), where m is the number of rows and n is the number of columns in the grid.
Space Complexity: O(min(m,n)), as the queue in BFS could hold at most min(m,n) nodes.
*/

class Solution {
public:
    int numIslands(std::vector<std::vector<char>>& grid) {
        int m = grid.size(), n = m ? grid[0].size() : 0, islands = 0, offsets[] = {0, 1, 0, -1, 0};
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == '1') {
                    islands++;
                    grid[i][j] = '0';
                    std::queue<std::pair<int, int>> todo;
                    todo.push({i, j});
                    while (!todo.empty()) {
                        std::pair<int, int> p = todo.front();
                        todo.pop();
                        for (int k = 0; k < 4; k++) {
                            int r = p.first + offsets[k], c = p.second + offsets[k + 1];
                            if (r >= 0 && r < m && c >= 0 && c < n && grid[r][c] == '1') {
                                grid[r][c] = '0';
                                todo.push({r, c});
                            }
                        }
                    }
                }
            }
        }
        return islands;
    }
};

int main() {
    // Create an instance of the Solution class
    Solution solution;
    
    // Test cases
    std::vector<std::vector<std::vector<char>>> testCases = {
        {
            {'1', '1', '1', '1', '0'},
            {'1', '1', '0', '1', '0'},
            {'1', '1', '0', '0', '0'},
            {'0', '0', '0', '0', '0'}
        }, // Expected output: 1
        {
            {'1', '1', '0', '0', '0'},
            {'1', '1', '0', '0', '0'},
            {'0', '0', '1', '0', '0'},
            {'0', '0', '0', '1', '1'}
        }, // Expected output: 3
        {
            {'1', '0', '1', '0', '1'},
            {'0', '1', '0', '1', '0'},
            {'1', '0', '1', '0', '1'},
            {'0', '1', '0', '1', '0'}
        }, // Expected output: 10
        {
            {'0', '0', '0'},
            {'0', '0', '0'},
            {'0', '0', '0'}
        }, // Expected output: 0
        {} // Expected output: 0 (empty grid)
    };
    
    // Iterate through test cases
    int testNum = 1;
    for (auto grid : testCases) {
        // Print the input
        std::cout << "Test Case " << testNum++ << ":\n";
        std::cout << "Grid:\n";
        for (const auto& row : grid) {
            for (char cell : row) {
                std::cout << cell << " ";
            }
            std::cout << "\n";
        }
        
        // Call the numIslands function and print the output
        int result = solution.numIslands(grid);
        std::cout << "Number of Islands: " << result << "\n\n";
    }
    
    return 0;
}

