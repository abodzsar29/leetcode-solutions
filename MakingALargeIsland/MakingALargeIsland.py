from typing import List

"""
LeetCode 827 — Make A Large Island

Key idea:
1. First pass: find and label every existing island with a unique id (> 1)
   and record its area.
2. Second pass: for each 0-cell, pretend we flip it to 1 and merge all
   *distinct* neighboring islands to compute the resulting area.
3. Track the maximum possible area.
"""


class Solution:
    def largestIsland(self, grid: List[List[int]]) -> int:
        n = len(grid)

        # We start island ids from 2:
        # 0 = water
        # 1 = unvisited land
        # 2+ = labeled islands
        island_id = 2

        # Maps island_id -> area of that island
        area = {}

        def dfs(r: int, c: int, island_id: int) -> int:
            """
            Iterative DFS that:
            - Marks all connected 1s with island_id
            - Returns the total number of cells in this island
            """
            stack = [(r, c)]
            grid[r][c] = island_id  # mark starting cell
            size = 1

            while stack:
                x, y = stack.pop()

                # Explore 4-directionally adjacent cells
                for dx, dy in ((1, 0), (-1, 0), (0, 1), (0, -1)):
                    nx, ny = x + dx, y + dy

                    # Only expand into valid, unvisited land cells (value == 1)
                    if 0 <= nx < n and 0 <= ny < n and grid[nx][ny] == 1:
                        grid[nx][ny] = island_id  # mark as part of this island
                        stack.append((nx, ny))
                        size += 1

            return size

        # ----------------------------------------------------
        # Step 1: Label all islands and compute their areas
        # ----------------------------------------------------
        for i in range(n):
            for j in range(n):
                # Found an unvisited land cell -> new island
                if grid[i][j] == 1:
                    area[island_id] = dfs(i, j, island_id)
                    island_id += 1

        # If there are no 0s, the entire grid is already land
        # Flipping is unnecessary; max island is whole grid
        if not any(0 in row for row in grid):
            return n * n

        # Start with the largest existing island (in case flipping doesn't help)
        max_area = max(area.values(), default=0)

        # ----------------------------------------------------
        # Step 2: Try flipping each 0 and merging neighbors
        # ----------------------------------------------------
        for i in range(n):
            for j in range(n):
                if grid[i][j] == 0:
                    # Track which islands we have already counted
                    # to avoid double-counting the same island
                    seen = set()

                    # Area starts at 1 for the flipped cell itself
                    current = 1

                    # Check the four neighbors of the 0-cell
                    for dx, dy in ((1, 0), (-1, 0), (0, 1), (0, -1)):
                        ni, nj = i + dx, j + dy
                        if 0 <= ni < n and 0 <= nj < n:
                            island = grid[ni][nj]

                            # island > 1 ensures it's a labeled island
                            # island not in seen avoids counting it twice
                            if island > 1 and island not in seen:
                                current += area[island]
                                seen.add(island)

                    # Update global maximum
                    max_area = max(max_area, current)

        return max_area


# -------------------------------
# Driver code & test harness
# -------------------------------

def run_test(grid, expected):
    solution = Solution()

    # The algorithm mutates the grid, so pass a deep copy
    result = solution.largestIsland([row[:] for row in grid])

    print("grid =")
    for row in grid:
        print(row)
    print(f"Expected: {expected}")
    print(f"Result:   {result}")
    print("✓ PASS" if result == expected else "✗ FAIL")
    print("-" * 50)


if __name__ == "__main__":
    print("=== Testing Make A Large Island ===\n")

    run_test(
        grid=[
            [1, 0],
            [0, 1]
        ],
        expected=3
    )

    run_test(
        grid=[
            [1, 1],
            [1, 0]
        ],
        expected=4
    )

    run_test(
        grid=[
            [1, 1],
            [1, 1]
        ],
        expected=4
    )

    run_test(
        grid=[
            [0]
        ],
        expected=1
    )

    run_test(
        grid=[
            [1, 1, 0, 0],
            [1, 0, 0, 1],
            [0, 0, 1, 1],
            [0, 1, 1, 0]
        ],
        expected=6
    )
