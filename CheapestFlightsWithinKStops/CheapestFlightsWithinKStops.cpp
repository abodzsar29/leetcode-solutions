#include <bits/stdc++.h>
using namespace std;

/*
LeetCode 787 — Cheapest Flights Within K Stops

Dijkstra + (node, stops) state
--------------------------------
Time Complexity:
    O(E * log(V * K))
Space Complexity:
    O(V * K)
*/

class Solution {
public:
    int findCheapestPrice(int n,
                          vector<vector<int>>& flights,
                          int src,
                          int dst,
                          int k) {

        // Build adjacency list
        vector<vector<pair<int,int>>> adj(n);
        for (auto &f : flights) {
            adj[f[0]].push_back({f[1], f[2]});
        }

        const int INF = 1e9;

        // dist[node][edges_used]
        vector<vector<int>> dist(n, vector<int>(k + 2, INF));
        dist[src][0] = 0;

        // (cost, node, edges_used)
        using T = tuple<int,int,int>;
        priority_queue<T, vector<T>, greater<T>> pq;
        pq.push({0, src, 0});

        while (!pq.empty()) {
            auto [cost, node, edges] = pq.top();
            pq.pop();

            // Cheapest valid arrival
            if (node == dst)
                return cost;

            // At most k stops => k+1 edges
            if (edges == k + 1)
                continue;

            // Ignore outdated state
            if (cost > dist[node][edges])
                continue;

            for (auto &[next, price] : adj[node]) {
                int newCost = cost + price;

                if (newCost < dist[next][edges + 1]) {
                    dist[next][edges + 1] = newCost;
                    pq.push({newCost, next, edges + 1});
                }
            }
        }

        return -1;
    }
};


/* --------------------------------------------------
   Driver code & test harness
-------------------------------------------------- */

void run_test(int n,
              vector<vector<int>> flights,
              int src,
              int dst,
              int k,
              int expected)
{
    Solution sol;
    int result = sol.findCheapestPrice(n, flights, src, dst, k);

    cout << "n = " << n << "\n";
    cout << "flights = [";
    for (auto &f : flights) {
        cout << "[" << f[0] << "," << f[1] << "," << f[2] << "]";
    }
    cout << "]\n";

    cout << "src = " << src
         << ", dst = " << dst
         << ", k = " << k << "\n";

    cout << "Expected: " << expected << "\n";
    cout << "Result:   " << result << "\n";
    cout << (result == expected ? "✓ PASS" : "✗ FAIL") << "\n";
    cout << string(60, '-') << "\n";
}


int main() {

    cout << "=== Testing Cheapest Flights Within K Stops ===\n\n";

    // Test Case 1 — LeetCode example
    run_test(
        4,
        {{0,1,100},{1,2,100},{2,3,100},{0,3,500}},
        0, 3, 1,
        500
    );

    // Test Case 2 — cheaper with one stop
    run_test(
        3,
        {{0,1,100},{1,2,100},{0,2,500}},
        0, 2, 1,
        200
    );

    // Test Case 3 — direct only (k = 0)
    run_test(
        3,
        {{0,1,100},{1,2,100},{0,2,500}},
        0, 2, 0,
        500
    );

    // Test Case 4 — unreachable
    run_test(
        3,
        {{0,1,100}},
        0, 2, 2,
        -1
    );

    cout << "\n=== Algorithm Analysis ===\n\n";
    cout << "Time Complexity: O(E * log(V * K))\n";
    cout << "Space Complexity: O(V * K)\n\n";

    cout << "Key Insights:\n";
    cout << " - Stops must be part of the state.\n";
    cout << " - Priority queue guarantees cheapest expansion first.\n";
    cout << " - Early return works because heap is cost-ordered.\n";

    return 0;
}
