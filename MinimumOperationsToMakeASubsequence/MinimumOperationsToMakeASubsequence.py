from typing import List
from bisect import bisect_left

"""
This is the solution for the problem:
"Minimum Operations to Make a Subsequence" (LeetCode #1713, Hard)

Link:
https://leetcode.com/problems/minimum-operations-to-make-a-subsequence/

Problem summary:
- Given arrays target (distinct values) and arr
- You may insert any integer anywhere into arr
- Return the minimum number of insert operations required so that
  target becomes a subsequence of arr

Core idea:
- Map each value in target to its index
- Convert arr into a sequence of indices that appear in target
- Find the Longest Increasing Subsequence (LIS) of this index sequence
- Result = len(target) - LIS_length
"""

class Solution:
    def minOperations(self, p: List[int], l: List[int]) -> int:
        mp = {v: i for i, v in enumerate(p)}
        lis = [-1]

        for v in l:
            i = mp.get(v)
            if i is None:
                continue
            if lis[-1] < i:
                lis.append(i)
            else:
                lis[bisect_left(lis, i)] = i

        return len(p) - len(lis) + 1


# -------------------------------
# Driver code & test harness
# -------------------------------

def run_test(target, arr, expected):
    solution = Solution()
    result = solution.minOperations(target, arr)

    print(f"target = {target}")
    print(f"arr    = {arr}")
    print(f"Expected: {expected}")
    print(f"Result:   {result}")
    print("✓ PASS" if result == expected else "✗ FAIL")
    print("-" * 50)


if __name__ == "__main__":
    print("=== Testing Minimum Operations to Make a Subsequence ===\n")

    # Test Case 1: Example
    run_test(
        target=[5, 1, 3],
        arr=[9, 4, 2, 3, 4],
        expected=2
    )

    # Test Case 2: Already subsequence
    run_test(
        target=[1, 2, 3],
        arr=[1, 2, 3],
        expected=0
    )

    # Test Case 3: Partial match
    run_test(
        target=[6, 4, 8, 1, 3, 2],
        arr=[4, 7, 6, 2, 3, 8, 6, 1],
        expected=3
    )

    # Test Case 4: No matches
    run_test(
        target=[1, 2, 3],
        arr=[4, 5, 6],
        expected=3
    )

    print("\n=== Algorithm Analysis ===\n")
    print("Time Complexity:")
    print("  - Mapping: O(n)")
    print("  - LIS via binary search: O(m log n)")
    print("  - Total: O((n + m) log n)")
    print("\nSpace Complexity:")
    print("  - O(n) for mapping and LIS structure")
    print("\nKey Insights:")
    print("  - Distinct values in target allow mapping to indices")
    print("  - Problem reduces to LIS on mapped index sequence")
    print("  - Minimum operations = target length - LIS length")

