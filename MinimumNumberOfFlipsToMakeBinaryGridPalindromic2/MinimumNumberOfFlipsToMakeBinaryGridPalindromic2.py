from typing import List

"""
This is the solution for the problem:
"Minimum Number of Flips to Make Binary Grid Palindromic II" (LeetCode #3240)

Link:
https://leetcode.com/problems/minimum-number-of-flips-to-make-binary-grid-palindromic-ii/

Problem summary:
- You are given an m x n binary grid.
- You may flip any cell (0 ↔ 1).
- The grid must become:
    1) Palindromic row-wise
    2) Palindromic column-wise
    3) Total number of 1s divisible by 4
- Return the minimum number of flips required.

Core idea:
- Use symmetry to group cells into independent equivalence classes.
- Each symmetry group has constant size (≤ 4).
- Greedily minimize flips per group.
- Handle parity constraints using state reduction.
"""


class Solution:
    def minFlips(self, grid: List[List[int]]) -> int:
        m, n = len(grid), len(grid[0])
        ans = 0

        # --------------------------------------------------
        # Step 1: Process 4-cell symmetry groups (4-cycles)
        # --------------------------------------------------
        for i in range(m // 2):
            ii = m - 1 - i
            for j in range(n // 2):
                jj = n - 1 - j

                ones = (
                    grid[i][j]
                    + grid[i][jj]
                    + grid[ii][j]
                    + grid[ii][jj]
                )

                # Make all 0s or all 1s
                ans += min(ones, 4 - ones)

        # --------------------------------------------------
        # Step 2: Handle center cell (if both dimensions odd)
        # Must be 0 to satisfy ones % 4 == 0
        # --------------------------------------------------
        if m % 2 == 1 and n % 2 == 1:
            ans += grid[m // 2][n // 2]

        # --------------------------------------------------
        # Step 3: Handle middle row / column pairs
        # --------------------------------------------------
        mismatches = 0
        mid_ones = 0

        # Middle row pairs
        if m % 2 == 1:
            r = m // 2
            for j in range(n // 2):
                a = grid[r][j]
                b = grid[r][n - 1 - j]
                if a == b:
                    mid_ones += a * 2
                else:
                    mismatches += 1

        # Middle column pairs
        if n % 2 == 1:
            c = n // 2
            for i in range(m // 2):
                a = grid[i][c]
                b = grid[m - 1 - i][c]
                if a == b:
                    mid_ones += a * 2
                else:
                    mismatches += 1

        # --------------------------------------------------
        # Step 4: Resolve parity constraint optimally
        # --------------------------------------------------
        if mismatches > 0 or mid_ones % 4 == 0:
            ans += mismatches
        else:
            # All pairs matched, but ones % 4 == 2
            ans += 2

        return ans


# --------------------------------
# Driver code & test harness
# --------------------------------

def run_test(grid, expected):
    solution = Solution()
    result = solution.minFlips(grid)

    print("Grid:")
    for row in grid:
        print(row)
    print(f"Expected: {expected}")
    print(f"Result:   {result}")
    print("✓ PASS" if result == expected else "✗ FAIL")
    print("-" * 50)


if __name__ == "__main__":
    print("=== Testing Minimum Number of Flips to Make Binary Grid Palindromic II ===\n")

    # Test Case 1: Example with center and symmetry
    run_test(
        grid=[
            [1, 0, 0],
            [0, 1, 0],
            [0, 0, 1]
        ],
        expected=3
    )

    # Test Case 2: Already valid
    run_test(
        grid=[
            [1, 0],
            [0, 1]
        ],
        expected=2
    )

    # Test Case 3: Single row
    run_test(
        grid=[
            [1, 0, 1, 0]
        ],
        expected=2
    )

    # Test Case 4: Single column
    run_test(
        grid=[
            [1],
            [0],
            [1],
            [0]
        ],
        expected=2
    )

    # Test Case 5: All zeros
    run_test(
        grid=[
            [0, 0],
            [0, 0]
        ],
        expected=0
    )

    print("\n=== Algorithm Analysis ===\n")
    print("Time Complexity:")
    print("  - O(m · n)")
    print("\nSpace Complexity:")
    print("  - O(1) extra space")
    print("\nKey Insights:")
    print("  - Symmetry reduces the grid into constant-size independent groups")
    print("  - Each group is optimized greedily")
    print("  - Parity (mod 4) is handled via state reduction, not DP")
