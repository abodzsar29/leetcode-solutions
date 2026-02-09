from typing import List
from itertools import accumulate

"""
This file contains two dynamic-programming solutions for the problem:

"Maximum Value of K Coins From Piles" (LeetCode #2218, Hard)

Link:
https://leetcode.com/problems/maximum-value-of-k-coins-from-piles/

Problem summary:
- You are given several piles of coins; each pile is stacked vertically.
- You may take coins only from the top of each pile.
- You must take exactly k coins total.
- Return the maximum possible sum of values.

Core idea:
- This is a grouped / multiple-choice knapsack problem.
- Each pile forms a group, and choosing x coins from a pile has:
      weight = x
      value  = prefix_sum[x]
- Dynamic programming is applied pile by pile.
"""


# -------------------------------------------------------
# Solution 1: Capacity-first grouped knapsack transition
# -------------------------------------------------------
class SolutionDP1:
    def maxValueOfCoins(self, piles: List[List[int]], k: int) -> int:
        dp = [0] * (k + 1)

        for pile in piles:
            prefix = [0]
            for coin in pile:
                prefix.append(prefix[-1] + coin)

            new_dp = dp[:]

            for used in range(1, k + 1):
                for x in range(1, min(len(pile), used) + 1):
                    new_dp[used] = max(new_dp[used],
                                       dp[used - x] + prefix[x])

            dp = new_dp

        return dp[k]


# -------------------------------------------------------
# Solution 2: Convolution-style grouped knapsack merging
# -------------------------------------------------------
class SolutionDP2:
    def maxValueOfCoins(self, a: List[List[int]], k: int) -> int:
        dp = [0]
        pre_cnt = 0

        for pile in a:
            cur_cnt = pre_cnt + len(pile)
            DP = [0] * (min(cur_cnt, k) + 1)

            presum = list(accumulate(pile, initial=0))

            for i, x in enumerate(presum[:k + 1]):        # take i coins
                for j, y in enumerate(dp[:k - i + 1]):    # previous coins
                    DP[i + j] = max(DP[i + j], x + y)

            pre_cnt = cur_cnt
            dp = DP

        return dp[k] if len(dp) > k else 0


# -------------------------------
# Driver code & test harness
# -------------------------------
def run_test(piles, k, expected):
    sol1 = SolutionDP1()
    sol2 = SolutionDP2()

    r1 = sol1.maxValueOfCoins(piles, k)
    r2 = sol2.maxValueOfCoins(piles, k)

    print(f"piles = {piles}")
    print(f"k = {k}")
    print(f"Expected: {expected}")
    print(f"DP1 Result: {r1}")
    print(f"DP2 Result: {r2}")
    ok = (r1 == expected) and (r2 == expected)
    print("✓ PASS" if ok else "✗ FAIL")
    print("-" * 50)


if __name__ == "__main__":
    print("=== Testing Maximum Value of K Coins From Piles ===\n")

    # Test Case 1
    run_test(
        piles=[[1, 100, 3], [7, 8, 9]],
        k=2,
        expected=101
    )

    # Test Case 2
    run_test(
        piles=[[100], [100], [100], [100], [100], [100], [1,1,1,1,1,1,700]],
        k=7,
        expected=706
    )

    # Test Case 3
    run_test(
        piles=[[1, 2, 3], [4, 5, 6]],
        k=3,
        expected=15
    )

    print("\n=== Algorithm Analysis ===\n")
    print("Time Complexity:")
    print("  - O(number_of_piles × k × average_pile_size)")
    print("\nSpace Complexity:")
    print("  - O(k)")
    print("\nKey Insights:")
    print("  - Each pile represents a group in grouped knapsack")
    print("  - Prefix sums allow O(1) value lookup for taking x coins")
    print("  - Both implementations perform the same DP transition")

