from typing import List

"""
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
"""

class Solution:
    def minDays(self, grid: List[List[int]]) -> int:
        m, n = len(grid), len(grid[0])
        dirs = [(1,0), (-1,0), (0,1), (0,-1)]

        def neighbors(r, c):
            for dr, dc in dirs:
                nr, nc = r + dr, c + dc
                if 0 <= nr < m and 0 <= nc < n and grid[nr][nc] == 1:
                    yield nr, nc

        # Count islands + land cells
        def count_islands():
            seen = set()
            islands = 0
            land = 0

            def dfs(r, c):
                stack = [(r, c)]
                seen.add((r, c))
                while stack:
                    x, y = stack.pop()
                    for nx, ny in neighbors(x, y):
                        if (nx, ny) not in seen:
                            seen.add((nx, ny))
                            stack.append((nx, ny))

            for i in range(m):
                for j in range(n):
                    if grid[i][j] == 1:
                        land += 1
                        if (i, j) not in seen:
                            islands += 1
                            dfs(i, j)

            return islands, land

        islands, land = count_islands()

        if islands != 1:
            return 0

        # critical edge case
        if land == 1:
            return 1

        disc = {}
        low = {}
        time = 0
        found_cut = False

        start = None
        for i in range(m):
            for j in range(n):
                if grid[i][j] == 1:
                    start = (i, j)
                    break
            if start:
                break

        def tarjan(r, c, parent):
            nonlocal time, found_cut
            disc[(r, c)] = low[(r, c)] = time
            time += 1

            children = 0

            for nr, nc in neighbors(r, c):
                if (nr, nc) == parent:
                    continue

                if (nr, nc) not in disc:
                    children += 1
                    tarjan(nr, nc, (r, c))
                    low[(r, c)] = min(low[(r, c)], low[(nr, nc)])

                    if parent is not None and low[(nr, nc)] >= disc[(r, c)]:
                        found_cut = True
                else:
                    low[(r, c)] = min(low[(r, c)], disc[(nr, nc)])

            if parent is None and children > 1:
                found_cut = True

        tarjan(start[0], start[1], None)

        return 1 if found_cut else 2


# -------------------------------
# Driver code & test harness
# -------------------------------

def run_test(grid, expected):
    solution = Solution()
    result = solution.minDays(grid)

    print("grid =")
    for row in grid:
        print(row)
    print(f"Expected: {expected}")
    print(f"Result:   {result}")
    print("✓ PASS" if result == expected else "✗ FAIL")
    print("-" * 50)


if __name__ == "__main__":
    print("=== Testing Minimum Number of Days to Disconnect Island ===\n")

    # Test Case 1: Already disconnected
    run_test(
        grid=[
            [1,0],
            [0,1]
        ],
        expected=0
    )

    # Test Case 2: Single land cell
    run_test(
        grid=[
            [1]
        ],
        expected=1
    )

    # Test Case 3: Articulation point exists
    run_test(
        grid=[
            [1,1,0],
            [1,1,0],
            [0,1,0]
        ],
        expected=1
    )

    # Test Case 4: Requires 2 removals
    run_test(
        grid=[
            [1,1],
            [1,1]
        ],
        expected=2
    )

    print("\n=== Algorithm Analysis ===\n")
    print("Time Complexity:")
    print("  - Island counting DFS: O(m*n)")
    print("  - Tarjan DFS: O(m*n)")
    print("  - Total: O(m*n)")
    print("\nSpace Complexity:")
    print("  - O(m*n) for visited + Tarjan maps")
    print("\nKey Insights:")
    print("  - Always check island count first")
    print("  - Any island can be disconnected in at most 2 days")
    print("  - Articulation points determine if answer is 1")
