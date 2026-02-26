from typing import List
from collections import deque

"""
This file contains TWO solutions for:

LeetCode 787 — Cheapest Flights Within K Stops (Medium)

Link:
https://leetcode.com/problems/cheapest-flights-within-k-stops/

Problem summary:
- There are n cities numbered 0..n-1.
- flights[i] = [u, v, price] represents a directed flight.
- Find the cheapest price from src to dst with at most k stops.
- If no such route exists, return -1.

------------------------------------------------------------
Algorithms included:
1) Bellman–Ford (official / safest approach)
2) BFS-level traversal with pruning (common alternative)

Core idea (Bellman–Ford):
- Relax all edges exactly (k+1) times.
- Each iteration allows paths using one more edge.
- Use a temporary array so updates do not leak within the same round.

Core idea (BFS version):
- Process graph level-by-level (each level = one more stop).
- Store (node, cost) in queue.
- Prune using min cost seen so far.
- Often fast, but Bellman–Ford is easier to prove correct.
"""

# ------------------------------------------------------------
# Solution 1 — Bellman–Ford (Recommended / Optimal)
# ------------------------------------------------------------

class SolutionBellmanFord:
    def findCheapestPrice(
        self,
        n: int,
        flights: List[List[int]],
        src: int,
        dst: int,
        k: int
    ) -> int:

        INF = float("inf")
        dist = [INF] * n
        dist[src] = 0

        # k stops => at most k+1 edges
        for _ in range(k + 1):
            ndist = dist[:]  # freeze previous layer

            for u, v, w in flights:
                if dist[u] != INF and dist[u] + w < ndist[v]:
                    ndist[v] = dist[u] + w

            dist = ndist

        return -1 if dist[dst] == INF else dist[dst]


# ------------------------------------------------------------
# Solution 2 — BFS Level Traversal + Pruning
# ------------------------------------------------------------

class SolutionBFS:
    def findCheapestPrice(
        self,
        n: int,
        flights: List[List[int]],
        src: int,
        dst: int,
        k: int
    ) -> int:

        adj = [[] for _ in range(n)]
        for u, v, c in flights:
            adj[u].append((v, c))

        minCost = [float("inf")] * n
        minCost[src] = 0

        q = deque([(src, 0)])
        stops = 0

        while q and stops <= k:
            level_size = len(q)

            for _ in range(level_size):
                node, cost = q.popleft()

                for nxt, price in adj[node]:
                    newCost = cost + price

                    if newCost >= minCost[nxt]:
                        continue

                    minCost[nxt] = newCost
                    q.append((nxt, newCost))

            stops += 1

        return -1 if minCost[dst] == float("inf") else minCost[dst]


# ------------------------------------------------------------
# Driver code & test harness
# ------------------------------------------------------------

def run_test(n, flights, src, dst, k, expected):
    bellman = SolutionBellmanFord()
    bfs = SolutionBFS()

    result_bellman = bellman.findCheapestPrice(n, flights, src, dst, k)
    result_bfs = bfs.findCheapestPrice(n, flights, src, dst, k)

    print(f"n = {n}")
    print(f"flights = {flights}")
    print(f"src = {src}, dst = {dst}, k = {k}")
    print(f"Expected:           {expected}")
    print(f"Bellman-Ford result {result_bellman}")
    print(f"BFS result          {result_bfs}")

    ok1 = result_bellman == expected
    ok2 = result_bfs == expected

    print("Bellman-Ford:", "✓ PASS" if ok1 else "✗ FAIL")
    print("BFS:", "✓ PASS" if ok2 else "✗ FAIL")
    print("-" * 60)


if __name__ == "__main__":
    print("=== Testing Cheapest Flights Within K Stops ===\n")

    # Test Case 1 — LeetCode example
    run_test(
        n=4,
        flights=[[0,1,100],[1,2,100],[2,3,100],[0,3,500]],
        src=0,
        dst=3,
        k=1,
        expected=500
    )

    # Test Case 2 — cheaper with one stop
    run_test(
        n=3,
        flights=[[0,1,100],[1,2,100],[0,2,500]],
        src=0,
        dst=2,
        k=1,
        expected=200
    )

    # Test Case 3 — direct only (k=0)
    run_test(
        n=3,
        flights=[[0,1,100],[1,2,100],[0,2,500]],
        src=0,
        dst=2,
        k=0,
        expected=500
    )

    # Test Case 4 — unreachable
    run_test(
        n=3,
        flights=[[0,1,100]],
        src=0,
        dst=2,
        k=2,
        expected=-1
    )

    print("\n=== Algorithm Analysis ===\n")

    print("Bellman–Ford:")
    print("  Time Complexity: O(E * (k+1))")
    print("  Space Complexity: O(n)")
    print("  Key Insight: Each round allows one more edge,")
    print("               making correctness easy to prove.")

    print("\nBFS + Pruning:")
    print("  Average Performance: Often fast in practice")
    print("  Space Complexity: O(n + E)")
    print("  Caveat: Uses cost pruning; Bellman–Ford is safer")
    print("          for strict correctness guarantees.")
