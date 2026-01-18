"""
LeetCode 1631 — Path With Minimum Effort
https://leetcode.com/problems/path-with-minimum-effort/

The problem:
Given a grid of heights, find a path from the top-left to the bottom-right
such that the maximum absolute difference in heights between consecutive
cells along the path is minimised.

This file implements two optimal solutions:

1. Dijkstra (Min–Max Path) — Primary Solution - Runtime: 213ms, Beats 98.23%
   - Treats the grid as a graph
   - Path cost = maximum edge weight along the path
   - Uses a modified Dijkstra relaxation: min(max(edge))
   - Time:  O(mn log(mn))
   - Space: O(mn)

2. Prim-style MST Expansion — Alternative Solution - Runtime: 187ms, Beats 99.60%
   - Grows a minimum spanning tree from (0,0)
   - Stops when target is reached
   - The largest edge used on that path is the answer
   - Time:  O(mn log(mn))
   - Space: O(mn)

Both solutions are optimal and accepted.
"""

import heapq
from typing import List, Tuple


# ============================================================
# Solution 1: Dijkstra (Min–Max Path)
# ============================================================

class SolutionDijkstra:
    """
    Primary solution.

    Uses a modified Dijkstra algorithm where:
      - dist[r][c] = minimum possible maximum edge difference
        to reach cell (r, c)
    """

    def minimumEffortPath(self, heights: List[List[int]]) -> int:
        rows, cols = len(heights), len(heights[0])
        INF = float("inf")

        # Distance matrix: best known effort to each cell
        dist = [[INF] * cols for _ in range(rows)]
        dist[0][0] = 0

        # Min-heap of (current effort, row, col)
        heap = [(0, 0, 0)]

        # 4-directional movement
        directions = [(1, 0), (-1, 0), (0, 1), (0, -1)]

        while heap:
            effort, r, c = heapq.heappop(heap)

            # Early exit: first time we pop the target is optimal
            if (r, c) == (rows - 1, cols - 1):
                return effort

            # Skip stale entries
            if effort > dist[r][c]:
                continue

            for dr, dc in directions:
                nr, nc = r + dr, c + dc
                if 0 <= nr < rows and 0 <= nc < cols:
                    edge_cost = abs(heights[nr][nc] - heights[r][c])
                    new_effort = max(effort, edge_cost)

                    if new_effort < dist[nr][nc]:
                        dist[nr][nc] = new_effort
                        heapq.heappush(heap, (new_effort, nr, nc))

        return 0  # Grid is always connected


# ============================================================
# Solution 2: Prim-style Minimum Spanning Tree Expansion
# ============================================================

class SolutionPrimMST:
    """
    Alternative optimal solution.

    Grows a minimum spanning tree starting from (0,0).
    The moment the target is reached, the maximum edge
    used so far is the answer.
    """

    def minimumEffortPath(self, heights: List[List[int]]) -> int:
        rows, cols = len(heights), len(heights[0])

        visited = [[False] * cols for _ in range(rows)]
        heap = [(0, 0, 0)]  # (edge weight, row, col)

        max_edge_used = 0
        directions = [(1, 0), (-1, 0), (0, 1), (0, -1)]

        while heap:
            edge_weight, r, c = heapq.heappop(heap)

            if visited[r][c]:
                continue

            visited[r][c] = True
            max_edge_used = max(max_edge_used, edge_weight)

            if (r, c) == (rows - 1, cols - 1):
                return max_edge_used

            for dr, dc in directions:
                nr, nc = r + dr, c + dc
                if 0 <= nr < rows and 0 <= nc < cols and not visited[nr][nc]:
                    next_edge = abs(heights[nr][nc] - heights[r][c])
                    heapq.heappush(heap, (next_edge, nr, nc))

        return 0


# ============================================================
# Helper Functions
# ============================================================

def print_grid(grid: List[List[int]], label: str) -> None:
    print(f"{label}:")
    for row in grid:
        print(" ", row)


def run_test_case(
    grid: List[List[int]],
    sol1: SolutionDijkstra,
    sol2: SolutionPrimMST,
    test_id: int
) -> None:
    print(f"\nTest Case {test_id}")
    print_grid(grid, "Input Grid")

    result_dijkstra = sol1.minimumEffortPath(grid)
    result_prim = sol2.minimumEffortPath(grid)

    print(f"Dijkstra (min–max path): {result_dijkstra}")
    print(f"Prim-style MST expansion: {result_prim}")
    print("Status:", "✓ PASS" if result_dijkstra == result_prim else "✗ FAIL")


# ============================================================
# Driver Code
# ============================================================

def main() -> None:
    solution_dijkstra = SolutionDijkstra()
    solution_prim = SolutionPrimMST()

    test_cases = [
        # Example from LeetCode
        [[1, 2, 2],
         [3, 8, 2],
         [5, 3, 5]],

        # Flat grid
        [[1, 1, 1],
         [1, 1, 1],
         [1, 1, 1]],

        # Increasing heights
        [[1, 2, 3],
         [2, 3, 4],
         [3, 4, 5]],

        # Large jump in middle
        [[1, 10, 6],
         [7,  5, 2],
         [3,  8, 4]],

        # Single row
        [[1, 100, 1, 1, 1]],

        # Single column
        [[1], [3], [6], [10]]
    ]

    print("=== Path With Minimum Effort — Algorithm Comparison ===")

    for i, grid in enumerate(test_cases, 1):
        run_test_case(grid, solution_dijkstra, solution_prim, i)

    print("\n=== Complexity Summary ===")
    print("Dijkstra (min–max path):")
    print("  Time  : O(mn log(mn))")
    print("  Space : O(mn)")
    print("  Best for: Interviews, production, clarity\n")

    print("Prim-style MST Expansion:")
    print("  Time  : O(mn log(mn))")
    print("  Space : O(mn)")
    print("  Best for: Graph-theory perspective\n")

    print("Key Insight:")
    print("  The problem is a minimum bottleneck path problem.")
    print("  Both algorithms correctly minimise the maximum edge")
    print("  weight encountered along the path.")


if __name__ == "__main__":
    main()
