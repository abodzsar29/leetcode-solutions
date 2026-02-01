from typing import List
from functools import cache

"""
This is the solution for the problem:
"Check if There Is a Valid Parentheses String Path in a Grid"
(LeetCode #2267, Hard)

Link:
https://leetcode.com/problems/check-if-there-is-a-valid-parentheses-string-path/

Problem summary:
- Given an m x n grid containing '(' and ')'
- Start at (0, 0), end at (m-1, n-1)
- You may only move right or down
- The sequence of parentheses along the path must form a valid string

Core idea:
- DFS with memoization
- Track current balance of parentheses
- Prune invalid states early:
  - balance < 0
  - balance > remaining steps
  - odd path length
"""

class Solution:
    def hasValidPath(self, grid: List[List[str]]) -> bool:
        m, n = len(grid), len(grid[0])

        # Path length must be even
        if (m + n - 1) % 2 != 0:
            return False

        # Start and end checks
        if grid[0][0] == ')' or grid[m - 1][n - 1] == '(':
            return False

        @cache
        def dfs(r: int, c: int, bal: int) -> bool:
            # Update balance for current cell
            bal += 1 if grid[r][c] == '(' else -1

            # Invalid prefix
            if bal < 0:
                return False

            # Too many opens to be closed
            remaining = (m - 1 - r) + (n - 1 - c)
            if bal > remaining:
                return False

            # Reached destination
            if r == m - 1 and c == n - 1:
                return bal == 0

            # Move down
            if r + 1 < m and dfs(r + 1, c, bal):
                return True

            # Move right
            if c + 1 < n and dfs(r, c + 1, bal):
                return True

            return False

        return dfs(0, 0, 0)


# -------------------------------
# Driver code & test harness
# -------------------------------

def run_test(grid, expected):
    solution = Solution()
    result = solution.hasValidPath(grid)

    print("Grid:")
    for row in grid:
        print(" ", row)
    print(f"Expected: {expected}")
    print(f"Result:   {result}")
    print("✓ PASS" if result == expected else "✗ FAIL")
    print("-" * 50)


if __name__ == "__main__":
    print("=== Testing Valid Parentheses Path in Grid ===\n")

    # Test Case 1: Example from LeetCode
    run_test(
        grid=[
            ["(", "(", "("],
            [")", "(", ")"],
            ["(", "(", ")"],
            ["(", "(", ")"]
        ],
        expected=True
    )

    # Test Case 2: Invalid due to imbalance
    run_test(
        grid=[
            ["(", ")"],
            ["(", ")"]
        ],
        expected=False
    )

    # Test Case 3: Single invalid path
    run_test(
        grid=[
            [")"]
        ],
        expected=False
    )

    # Test Case 4: Minimal valid path
    run_test(
        grid=[
            ["(", ")"]
        ],
        expected=True
    )

    # Test Case 5: Impossible due to end '('
    run_test(
        grid=[
            ["(", "("],
            [")", "("]
        ],
        expected=False
    )

    print("\n=== Algorithm Analysis ===\n")
    print("Time Complexity:")
    print("  - O(m · n · (m + n)) due to DFS states with memoization")
    print("\nSpace Complexity:")
    print("  - O(m · n · (m + n)) for recursion + cache")
    print("\nKey Insights:")
    print("  - Prefix balance must never be negative")
    print("  - Remaining steps cap the maximum possible balance")
    print("  - Early pruning is essential for performance")
