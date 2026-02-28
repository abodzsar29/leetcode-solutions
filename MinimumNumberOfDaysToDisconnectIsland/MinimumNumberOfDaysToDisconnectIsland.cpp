#include <bits/stdc++.h>
using namespace std;

/*
This is the solution for the problem:
"Minimum Number of Days to Disconnect Island" (LeetCode #1568, Hard)

Link:
https://leetcode.com/problems/minimum-number-of-days-to-disconnect-island/

Problem summary:
- Given a binary grid (0 = water, 1 = land).
- Each day you may remove exactly one land cell.
- Return the minimum number of days required to disconnect the island.
- An island is disconnected if:
    * it has 0 islands, or
    * more than 1 island.

Core idea:
- Count number of islands first.
    * If already disconnected -> answer = 0
- If only one land cell -> answer = 1
- Otherwise:
    * Treat land cells as graph nodes
    * Use Tarjan’s algorithm to detect articulation points
    * If an articulation point exists -> answer = 1
    * Else -> answer = 2
*/

class Solution {
public:
    int m, n;
    vector<vector<int>> grid;
    vector<int> disc, low;
    int timer;
    bool foundCut = false;
    int landCount = 0;

    vector<pair<int,int>> dirs = {{1,0},{-1,0},{0,1},{0,-1}};

    int id(int r, int c) {
        return r * n + c;
    }

    bool valid(int r, int c) {
        return r >= 0 && r < m && c >= 0 && c < n && grid[r][c] == 1;
    }

    void dfsIsland(int r, int c, vector<vector<int>>& vis) {
        vis[r][c] = 1;
        for (auto [dr, dc] : dirs) {
            int nr = r + dr, nc = c + dc;
            if (valid(nr, nc) && !vis[nr][nc])
                dfsIsland(nr, nc, vis);
        }
    }

    int countIslands() {
        landCount = 0; // reset (important)
        vector<vector<int>> vis(m, vector<int>(n, 0));
        int cnt = 0;

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 1) {
                    landCount++;
                    if (!vis[i][j]) {
                        cnt++;
                        dfsIsland(i, j, vis);
                    }
                }
            }
        }
        return cnt;
    }

    void tarjan(int r, int c, int parent) {
        int u = id(r, c);
        disc[u] = low[u] = timer++;
        int children = 0;

        for (auto [dr, dc] : dirs) {
            int nr = r + dr, nc = c + dc;
            if (!valid(nr, nc)) continue;

            int v = id(nr, nc);
            if (v == parent) continue;

            if (disc[v] == -1) {
                children++;
                tarjan(nr, nc, u);

                low[u] = min(low[u], low[v]);

                if (parent != -1 && low[v] >= disc[u])
                    foundCut = true;
            } else {
                low[u] = min(low[u], disc[v]);
            }
        }

        if (parent == -1 && children > 1)
            foundCut = true;
    }

    int minDays(vector<vector<int>>& g) {
        grid = g;
        m = grid.size();
        n = grid[0].size();

        int islands = countIslands();

        if (islands != 1)
            return 0;

        // critical edge case
        if (landCount == 1)
            return 1;

        int total = m * n;
        disc.assign(total, -1);
        low.assign(total, -1);
        timer = 0;
        foundCut = false;

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 1) {
                    tarjan(i, j, -1);
                    return foundCut ? 1 : 2;
                }
            }
        }

        return 2;
    }
};

// -------------------------------
// Driver code & test harness
// -------------------------------

void run_test(vector<vector<int>> grid, int expected) {
    Solution solution;
    int result = solution.minDays(grid);

    cout << "grid =\n";
    for (auto& row : grid) {
        cout << "[ ";
        for (int v : row) cout << v << " ";
        cout << "]\n";
    }

    cout << "Expected: " << expected << "\n";
    cout << "Result:   " << result << "\n";
    cout << (result == expected ? "PASS" : "FAIL") << "\n";
    cout << string(50, '-') << "\n";
}

int main() {
    cout << "=== Testing Minimum Number of Days to Disconnect Island ===\n\n";

    // Test Case 1: Already disconnected
    run_test(
        {
            {1,0},
            {0,1}
        },
        0
    );

    // Test Case 2: Single land cell
    run_test(
        {
            {1}
        },
        1
    );

    // Test Case 3: Articulation point exists
    run_test(
        {
            {1,1,0},
            {1,1,0},
            {0,1,0}
        },
        1
    );

    // Test Case 4: Requires 2 removals
    run_test(
        {
            {1,1},
            {1,1}
        },
        2
    );

    cout << "\n=== Algorithm Analysis ===\n\n";
    cout << "Time Complexity:\n";
    cout << "  - Island counting DFS: O(m*n)\n";
    cout << "  - Tarjan DFS: O(m*n)\n";
    cout << "  - Total: O(m*n)\n\n";

    cout << "Space Complexity:\n";
    cout << "  - O(m*n) for visitation + Tarjan arrays\n\n";

    cout << "Key Insights:\n";
    cout << "  - Always check island count first\n";
    cout << "  - Any island can be disconnected in at most 2 days\n";
    cout << "  - Articulation points determine if answer is 1\n";

    return 0;
}
