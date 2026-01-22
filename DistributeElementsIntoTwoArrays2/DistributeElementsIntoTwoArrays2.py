from typing import List
from sortedcontainers import SortedList

"""
This is the solution for the problem:
"Distribute Elements Into Two Arrays II" (LeetCode #3072, Medium)

Link:
https://leetcode.com/problems/distribute-elements-into-two-arrays-ii/

Problem summary:
- You are given an integer array nums.
- You must distribute elements into two arrays arr1 and arr2.
- Rules:
    1. arr1 starts with nums[0], arr2 starts with nums[1]
    2. For each subsequent element nums[i]:
        - Let gc1 = number of elements in arr1 greater than nums[i]
        - Let gc2 = number of elements in arr2 greater than nums[i]
        - If gc1 > gc2 → append to arr1
        - If gc1 < gc2 → append to arr2
        - If equal → append to the shorter array
- Return arr1 followed by arr2.

Core idea:
- Maintain two dynamically sorted structures
- Use binary search to count how many elements are greater than a value
- Make a greedy decision at each step

Time Complexity:
- O(N log N) due to sorted insertions and rank queries
Space Complexity:
- O(N)
"""


class Solution:
    def resultArray(self, nums: List[int]) -> List[int]:
        # Initialize result arrays
        arr1 = [nums[0]]
        arr2 = [nums[1]]

        # Length trackers
        l1 = l2 = 1

        # Sorted structures for efficient rank queries
        sort_arr1 = SortedList([nums[0]])
        sort_arr2 = SortedList([nums[1]])

        # Process remaining elements
        for num in nums[2:]:
            # Count elements greater than num
            gc1 = l1 - sort_arr1.bisect_right(num)
            gc2 = l2 - sort_arr2.bisect_right(num)

            if gc1 > gc2:
                arr1.append(num)
                sort_arr1.add(num)
                l1 += 1
            elif gc1 < gc2:
                arr2.append(num)
                sort_arr2.add(num)
                l2 += 1
            else:
                # Tie-breaking by size
                if l1 <= l2:
                    arr1.append(num)
                    sort_arr1.add(num)
                    l1 += 1
                else:
                    arr2.append(num)
                    sort_arr2.add(num)
                    l2 += 1

        return arr1 + arr2


# -------------------------------
# Driver code & test harness
# -------------------------------

def run_test(nums, expected):
    solution = Solution()
    result = solution.resultArray(nums)

    print(f"nums = {nums}")
    print(f"Expected: {expected}")
    print(f"Result:   {result}")
    print("✓ PASS" if result == expected else "✗ FAIL")
    print("-" * 50)


if __name__ == "__main__":
    print("=== Testing Distribute Elements Into Two Arrays II ===\n")

    # Test Case 1: Example
    run_test(
        nums=[2, 1, 3, 3],
        expected=[2, 3, 1, 3]
    )

    # Test Case 2: Increasing order
    run_test(
        nums=[1, 2, 3, 4, 5],
        expected=[1, 3, 5, 2, 4]
    )

    # Test Case 3: All equal values
    run_test(
        nums=[7, 7, 7, 7],
        expected=[7, 7, 7, 7]
    )

    # Test Case 4: Minimum length
    run_test(
        nums=[10, 20],
        expected=[10, 20]
    )

    print("\n=== Algorithm Analysis ===\n")
    print("Time Complexity:")
    print("  - Each insertion and rank query is O(log N)")
    print("  - Total time: O(N log N)")
    print("\nSpace Complexity:")
    print("  - O(N) for arrays and sorted lists")
    print("\nKey Insights:")
    print("  - SortedList enables fast order statistics")
    print("  - Greedy local decisions lead to a valid global result")
    print("  - Backward counting (greater-than) avoids scanning arrays")
