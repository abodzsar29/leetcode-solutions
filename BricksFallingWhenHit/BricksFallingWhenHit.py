from typing import List

"""
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
- Removing bricks dynamically is expensive.
- Instead:
    1) Apply all hits first.
    2) Flood-fill from the roof to mark stable bricks.
    3) Add bricks back in reverse order.
    4) When a brick reconnects to stability, flood-fill its component.
- Each brick is marked stable at most once → linear complexity.
"""


class Solution:
    def hitBricks(self, grid: List[List[int]], hits: List[List[int]]) -> List[int]:
        m, n = len(grid), len(grid[0])

        # -------------------------------------------------------
        # Flood fill: marks stable bricks with value 2
        # Returns size of connected stable component
        # -------------------------------------------------------
        def flood_fill(r: int, c: int) -> int:
            if r < 0 or r >= m or c < 0 or c >= n or grid[r][c] != 1:
                return 0

            grid[r][c] = 2  # mark as stable

            return (
                1
                + flood_fill(r + 1, c)
                + flood_fill(r - 1, c)
                + flood_fill(r, c + 1)
                + flood_fill(r, c - 1)
            )

        # -------------------------------------------------------
        # Check if a brick connects to already stable structure
        # -------------------------------------------------------
        def is_connected(r: int, c: int) -> bool:
            if r == 0:
                return True

            directions = [(1, 0), (-1, 0), (0, 1), (0, -1)]

            for dr, dc in directions:
                nr, nc = r + dr, c + dc
                if 0 <= nr < m and 0 <= nc < n and grid[nr][nc] == 2:
                    return True

            return False

        # -------------------------------------------------------
        # Step 1: Remove all hits
        # -------------------------------------------------------
        for r, c in hits:
            grid[r][c] -= 1

        # -------------------------------------------------------
        # Step 2: Mark initially stable bricks (roof-connected)
        # -------------------------------------------------------
        for c in range(n):
            flood_fill(0, c)

        # -------------------------------------------------------
        # Step 3: Process hits in reverse
        # -------------------------------------------------------
        result = [0] * len(hits)

        for k in range(len(hits) - 1, -1, -1):
            r, c = hits[k]

            # restore brick
            grid[r][c] += 1

            # if brick exists and connects to stable area
            if grid[r][c] == 1 and is_connected(r, c):
                # minus 1 excludes the restored brick itself
                result[k] = flood_fill(r, c) - 1

        return result


# -------------------------------
# Driver code & test harness
# -------------------------------

def run_test(grid, hits, expected):
    solution = Solution()
    result = solution.hitBricks([row[:] for row in grid], hits)

    print(f"grid = {grid}")
    print(f"hits = {hits}")
    print(f"Expected: {expected}")
    print(f"Result:   {result}")
    print("✓ PASS" if result == expected else "✗ FAIL")
    print("-" * 60)


if __name__ == "__main__":
    print("=== Testing Bricks Falling When Hit (Reverse Flood Fill) ===\n")

    # Test Case 1: LeetCode example
    run_test(
        grid=[[1, 0, 0, 0], [1, 1, 1, 0]],
        hits=[[1, 0]],
        expected=[2]
    )

    # Test Case 2: Multiple hits
    run_test(
        grid=[[1,0,0,0],[1,1,0,0]],
        hits=[[1,1],[1,0]],
        expected=[0,0]
    )

    # Test Case 3: Top-row stability
    run_test(
        grid=[[1]],
        hits=[[0,0]],
        expected=[0]
    )

    # Test Case 4: Complex structure
    run_test(
        grid=[[1,1,1],[0,1,0],[0,0,0]],
        hits=[[0,2],[2,0],[0,1],[1,2]],
        expected=[0,0,1,0]
    )

    print("\n=== Algorithm Analysis ===\n")
    print("Time Complexity:")
    print("  - Each brick is flood-filled at most once")
    print("  - Total: O(m * n + k)")
    print("\nSpace Complexity:")
    print("  - O(m * n) worst-case recursion stack")
    print("\nKey Insights:")
    print("  - Reverse processing avoids repeated recomputation")
    print("  - Stable bricks are explicitly marked (value = 2)")
    print("  - Flood-fill acts as incremental connectivity expansion")
