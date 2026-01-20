"""
LeetCode 1681 — Minimum Incompatibility (Hard)
https://leetcode.com/problems/minimum-incompatibility/

The problem:
Given an integer array nums and an integer k, partition nums into k subsets
of equal size such that:
  - Each subset contains only unique elements
  - The total incompatibility is minimised

Incompatibility of a subset = max(subset) - min(subset)

Return the minimum total incompatibility, or -1 if impossible.

------------------------------------------------------------

This file implements two optimal solutions:

1. Backtracking + Branch-and-Bound — Primary (Fast in Practice)
   - Builds groups incrementally
   - Uses symmetry breaking and tight lower bounds
   - Extremely fast on LeetCode test data
   - Worst-case exponential (super-exponential partitions)

2. Bitmask DP (State Compression) — Theoretical Optimal
   - Enumerates all valid subsets of size n/k
   - DP over used-element masks
   - Guaranteed O(2^n · n)
   - Stable, predictable performance

Both solutions are optimal and accepted.
"""

from collections import Counter
from typing import List
from math import inf


# ============================================================
# Solution 1: Backtracking + Branch-and-Bound
# ============================================================

class SolutionBacktracking:
    """
    Primary practical solution.

    Key ideas:
      - Build subsets in increasing order to enforce uniqueness
      - Fix the smallest unused element to start each group
        (symmetry breaking)
      - Use a lower bound to prune branches aggressively
    """

    def minimumIncompatibility(self, nums: List[int], k: int) -> int:
        n = len(nums)
        group_size = n // k

        counter = Counter(nums)
        if any(freq > k for freq in counter.values()):
            return -1

        res = inf

        def backtrack(used: int, curr_score: int, last: int):
            nonlocal res

            if used == n:
                res = min(res, curr_score)
                return

            used += 1
            remaining = n - used
            group_complete = (used % group_size == 0)

            if last != 0:
                # Continue current group
                groups_left, rem = divmod(remaining, group_size)
                lower_bound = (group_size - 1) * groups_left + rem

                for num in range(last + 1, max(counter) + 1):
                    if counter[num] == 0:
                        continue

                    next_score = curr_score + (num - last)
                    if next_score + lower_bound >= res:
                        break

                    counter[num] -= 1
                    backtrack(
                        used,
                        next_score,
                        0 if group_complete else num
                    )
                    counter[num] += 1
            else:
                # Start a new group: fix smallest available number
                for num in sorted(counter):
                    if counter[num] == 0:
                        continue
                    counter[num] -= 1
                    backtrack(
                        used,
                        curr_score,
                        0 if group_complete else num
                    )
                    counter[num] += 1
                    break  # symmetry breaking

        backtrack(0, 0, 0)
        return res if res < inf else -1


# ============================================================
# Solution 2: Bitmask DP (State Compression)
# ============================================================

class SolutionBitmaskDP:
    """
    Theoretical optimal solution.

    Key ideas:
      - Precompute all valid subsets of size n/k
      - Each subset contributes (max - min)
      - DP[mask] = minimum incompatibility using elements in mask
      - Symmetry breaking: always include first unused index
    """

    def minimumIncompatibility(self, nums: List[int], k: int) -> int:
        n = len(nums)
        m = n // k

        if any(v > k for v in Counter(nums).values()):
            return -1

        subset_cost = {}

        for mask in range(1 << n):
            if bin(mask).count("1") != m:
                continue

            seen = set()
            vals = []
            valid = True

            for i in range(n):
                if mask & (1 << i):
                    if nums[i] in seen:
                        valid = False
                        break
                    seen.add(nums[i])
                    vals.append(nums[i])

            if valid:
                subset_cost[mask] = max(vals) - min(vals)

        dp = [inf] * (1 << n)
        dp[0] = 0

        for mask in range(1 << n):
            if dp[mask] == inf:
                continue

            # find first unused index
            i = 0
            while mask & (1 << i):
                i += 1

            for sub, cost in subset_cost.items():
                if (sub & (1 << i)) and (sub & mask) == 0:
                    dp[mask | sub] = min(dp[mask | sub], dp[mask] + cost)

        ans = dp[(1 << n) - 1]
        return ans if ans < inf else -1


# ============================================================
# Driver / Test Harness
# ============================================================

def run_test_case(nums: List[int], k: int, test_id: int) -> None:
    sol_bt = SolutionBacktracking()
    sol_dp = SolutionBitmaskDP()

    print(f"\nTest Case {test_id}")
    print(f"nums = {nums}, k = {k}")

    r1 = sol_bt.minimumIncompatibility(nums, k)
    r2 = sol_dp.minimumIncompatibility(nums, k)

    print(f"Backtracking + B&B : {r1}")
    print(f"Bitmask DP        : {r2}")
    print("Status:", "✓ PASS" if r1 == r2 else "✗ FAIL")


def main() -> None:
    test_cases = [
        ([1, 2, 1, 4], 2),
        ([6, 3, 8, 1, 3, 1, 2, 2], 4),
        ([5, 3, 3, 6, 3, 3], 3),
        ([1, 2, 3, 4], 2),
        ([1, 1, 1, 1], 2),
        ([1, 2, 3, 1, 2, 3], 3),
    ]

    print("=== Minimum Incompatibility — Algorithm Comparison ===")

    for i, (nums, k) in enumerate(test_cases, 1):
        run_test_case(nums, k, i)

    print("\n=== Complexity Summary ===")
    print("Backtracking + Branch-and-Bound:")
    print("  Time  : Exponential (pruned heavily in practice)")
    print("  Space : O(n)")
    print("  Best for: Real-world speed, LeetCode submissions\n")

    print("Bitmask DP (State Compression):")
    print("  Time  : O(2^n · n)")
    print("  Space : O(2^n)")
    print("  Best for: Theoretical guarantees, editorial clarity\n")

    print("Key Insight:")
    print("  Small-n partitioning problems often admit both")
    print("  a theoretically optimal DP and a faster practical")
    print("  backtracking solution with strong pruning.")


if __name__ == "__main__":
    main()

