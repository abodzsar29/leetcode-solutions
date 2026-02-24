from typing import List

"""
This is the solution for the problem:
"Find in Mountain Array" (LeetCode #1095, Hard)

Link:
https://leetcode.com/problems/find-in-mountain-array/

Problem summary:
- Mountain array: strictly increasing then strictly decreasing
- Access only via MountainArray API
- Return smallest index of target, otherwise -1

Core idea:
- Binary search peak
- Binary search ascending part
- Binary search descending part
- Cache API calls
"""

# -------------------------------
# Mock MountainArray for testing
# -------------------------------
class MountainArray:
    def __init__(self, arr: List[int]):
        self.arr = arr

    def get(self, index: int) -> int:
        return self.arr[index]

    def length(self) -> int:
        return len(self.arr)


class Solution:
    def findInMountainArray(self, target: int, mountain_arr: 'MountainArray') -> int:
        n = mountain_arr.length()
        cache = {}

        def getv(i):
            if i not in cache:
                cache[i] = mountain_arr.get(i)
            return cache[i]

        # Step 1: Find peak
        lo, hi = 0, n - 1
        while lo < hi:
            mid = (lo + hi) // 2
            if getv(mid) < getv(mid + 1):
                lo = mid + 1
            else:
                hi = mid
        peak = lo

        def bin_search(lo, hi, inc):
            while lo <= hi:
                mid = (lo + hi) // 2
                v = getv(mid)

                if v == target:
                    return mid

                if inc:
                    if v < target:
                        lo = mid + 1
                    else:
                        hi = mid - 1
                else:
                    if v < target:
                        hi = mid - 1
                    else:
                        lo = mid + 1
            return -1

        ans = bin_search(0, peak, True)
        if ans != -1:
            return ans

        return bin_search(peak + 1, n - 1, False)


# -------------------------------
# Driver code & test harness
# -------------------------------

def run_test(arr, target, expected):
    mountain = MountainArray(arr)
    solution = Solution()

    result = solution.findInMountainArray(target, mountain)

    print(f"Array = {arr}")
    print(f"Target:   {target}")
    print(f"Expected: {expected}")
    print(f"Result:   {result}")
    print("PASS" if result == expected else "FAIL")
    print("-" * 50)


if __name__ == "__main__":
    print("=== Testing Find in Mountain Array ===\n")

    run_test([1,2,3,4,5,3,1], 3, 2)
    run_test([0,1,2,4,2,1], 3, -1)
    run_test([1,5,2], 2, 2)
    run_test([0,5,3,1], 1, 3)

    print("\n=== Algorithm Analysis ===\n")
    print("Time Complexity:")
    print("  - Peak search: O(log n)")
    print("  - Two binary searches: O(log n)")
    print("  - Total: O(log n)")
    print("\nSpace Complexity:")
    print("  - O(log n) for cached API calls")
