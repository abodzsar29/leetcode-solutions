#include <iostream>
#include <vector>
#include <array>

using namespace std;

/*
This is the solution for the problem:
"Bricks Falling When Hit" (LeetCode #803, Hard)

Link:
https://leetcode.com/problems/bricks-falling-when-hit/

Problem summary:
- Given a grid of bricks (1 = brick, 0 = empty).
- A brick is stable if:
    - it is in the top row, OR
    - connected (4-directionally) to another stable brick.
- Each hit removes one brick.
- After each removal, unstable bricks fall.
- Return how many bricks fall after each hit.

Core idea (Reverse Flood Fill):
- Apply all hits first.
- Flood-fill from the top row and mark stable bricks as value 2.
- Process hits in reverse order:
    - restore brick
    - if connected to stability, flood-fill and count new stable bricks.
- Each brick becomes stable at most once → O(m*n + k).
*/

class Solution {
private:
    array<pair<int,int>,4> dir{{{-1,0},{1,0},{0,1},{0,-1}}};
    int m, n;

    bool valid(int x, int y) const noexcept {
        return x >= 0 && x < m && y >= 0 && y < n;
    }

    // Flood-fill stable bricks and return component size
    int dfs(vector<vector<int>>& grid, int x, int y) {
        if (grid[x][y] == 2) return 0;

        grid[x][y] = 2;
        int cnt = 1;

        for (const auto& [dx, dy] : dir) {
            int nx = x + dx;
            int ny = y + dy;
            if (valid(nx, ny) && grid[nx][ny] == 1) {
                cnt += dfs(grid, nx, ny);
            }
        }
        return cnt;
    }

    // Check whether this brick connects to stable structure
    bool is_connected(vector<vector<int>>& grid, int x, int y) noexcept {
        if (x == 0) return true;

        for (const auto& [dx, dy] : dir) {
            int nx = x + dx;
            int ny = y + dy;
            if (valid(nx, ny) && grid[nx][ny] == 2) {
                return true;
            }
        }
        return false;
    }

public:
    vector<int> hitBricks(vector<vector<int>>& grid,
                          vector<vector<int>>& hits) {

        m = grid.size();
        n = grid[0].size();

        // Step 1: Remove all hits
        for (const auto& h : hits) {
            grid[h[0]][h[1]] -= 1;
        }

        // Step 2: Mark stable bricks from the top row
        for (int j = 0; j < n; ++j) {
            if (grid[0][j] == 1) {
                dfs(grid, 0, j);
            }
        }

        // Step 3: Process hits in reverse
        vector<int> res(hits.size(), 0);

        for (int i = (int)hits.size() - 1; i >= 0; --i) {
            int x = hits[i][0];
            int y = hits[i][1];

            // restore brick
            grid[x][y] += 1;

            if (grid[x][y] == 1 && is_connected(grid, x, y)) {
                // minus restored brick itself
                res[i] = dfs(grid, x, y) - 1;
            }
        }

        return res;
    }
};


// ------------------------------------------------
// Driver code & test harness
// ------------------------------------------------

void run_test(vector<vector<int>> grid,
              vector<vector<int>> hits,
              vector<int> expected) {

    Solution solution;
    vector<int> result = solution.hitBricks(grid, hits);

    cout << "grid = [";
    for (const auto& row : grid) {
        cout << "[";
        for (int v : row) cout << v << " ";
        cout << "]";
    }
    cout << "]\n";

    cout << "hits = [";
    for (const auto& h : hits) {
        cout << "[" << h[0] << "," << h[1] << "]";
    }
    cout << "]\n";

    cout << "Expected: ";
    for (int x : expected) cout << x << " ";
    cout << "\nResult:   ";
    for (int x : result) cout << x << " ";

    bool pass = (result == expected);
    cout << "\n" << (pass ? "✓ PASS" : "✗ FAIL") << "\n";
    cout << "--------------------------------------------------\n";
}


int main() {
    cout << "=== Testing Bricks Falling When Hit (Reverse Flood Fill) ===\n\n";

    // Test Case 1: LeetCode example
    run_test(
        {{1,0,0,0},{1,1,1,0}},
        {{1,0}},
        {2}
    );

    // Test Case 2
    run_test(
        {{1,0,0,0},{1,1,0,0}},
        {{1,1},{1,0}},
        {0,0}
    );

    // Test Case 3: single brick
    run_test(
        {{1}},
        {{0,0}},
        {0}
    );

    // Test Case 4
    run_test(
        {{1,1,1},{0,1,0},{0,0,0}},
        {{0,2},{2,0},{0,1},{1,2}},
        {0,0,1,0}
    );

    cout << "\n=== Algorithm Analysis ===\n\n";
    cout << "Time Complexity:\n";
    cout << "  - Each brick is flood-filled at most once\n";
    cout << "  - Total: O(m * n + k)\n\n";
    cout << "Space Complexity:\n";
    cout << "  - O(m * n) recursion stack (worst case)\n\n";
    cout << "Key Insights:\n";
    cout << "  - Reverse processing avoids repeated recomputation\n";
    cout << "  - Stable bricks are explicitly marked (value = 2)\n";
    cout << "  - Flood-fill acts as incremental connectivity expansion\n";

    return 0;
}
