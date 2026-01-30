from typing import List

"""
This is the solution for the problem:
"Minimum Cost to Make Array Equal" (LeetCode #2448, Hard)

Link:
https://leetcode.com/problems/minimum-cost-to-make-array-equal/

Problem summary:
- Given two arrays:
    nums[i]  → values
    cost[i]  → cost per unit change for nums[i]
- You can change nums[i] to any integer x with cost:
    |nums[i] - x| * cost[i]
- Find the minimum total cost to make all elements equal.

Core idea:
- The objective function is a weighted sum of absolute deviations
- The minimum occurs at the weighted median of nums
- Sort (nums, cost), find weighted median, compute total cost
"""


class Solution:
    def minCost(self, nums: List[int], cost: List[int]) -> int:
        pairs = sorted(zip(nums, cost))

        total_weight = sum(cost)
        half_weight = (total_weight + 1) // 2

        cumulative = 0
        target = 0

        for value, weight in pairs:
            cumulative += weight
            if cumulative >= half_weight:
                target = value
                break

        return sum(abs(value - target) * weight for value, weight in pairs)


# -------------------------------
# Driver code & test harness
# -------------------------------

def run_test(nums, cost, expected):
    solution = Solution()
    result = solution.minCost(nums, cost)

    print(f"nums = {nums}")
    print(f"cost = {cost}")
    print(f"Expected: {expected}")
    print(f"Result:   {result}")
    print("✓ PASS" if result == expected else "✗ FAIL")
    print("-" * 50)


if __name__ == "__main__":
    print("=== Testing Minimum Cost to Make Array Equal ===\n")

    # Test Case 1: Example from LeetCode
    run_test(
        nums=[1, 3, 5, 2],
        cost=[2, 3, 1, 14],
        expected=8
    )

    # Test Case 2: All elements already equal
    run_test(
        nums=[2, 2, 2],
        cost=[1, 2, 3],
        expected=0
    )

    # Test Case 3: Single element
    run_test(
        nums=[10],
        cost=[100],
        expected=0
    )

    # Test Case 4: Large imbalance in cost
    run_test(
        nums=[1, 100],
        cost=[1000, 1],
        expected=99
    )

    # Test Case 5: Increasing sequence, uniform cost
    run_test(
        nums=[1, 2, 3, 4, 5],
        cost=[1, 1, 1, 1, 1],
        expected=6
    )

    print("\n=== Algorithm Analysis ===\n")
    print("Time Complexity:")
    print("  - Sorting: O(n log n)")
    print("  - One pass for median + one pass for cost")
    print("  - Total: O(n log n)")
    print("\nSpace Complexity:")
    print("  - O(n) for sorted (value, cost) pairs")
    print("\nKey Insights:")
    print("  - Weighted median minimizes weighted absolute deviation")
    print("  - Convex cost function guarantees a single global minimum")
    print("  - Avoids binary search or brute-force approaches")
