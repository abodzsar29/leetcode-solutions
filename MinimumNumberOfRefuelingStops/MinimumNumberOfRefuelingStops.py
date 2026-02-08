from typing import List
import heapq

"""
This is the solution for the problem:
"Minimum Number of Refueling Stops" (LeetCode #871, Hard)

Link:
https://leetcode.com/problems/minimum-number-of-refueling-stops/

Problem summary:
- You start at position 0 with startFuel liters of fuel.
- There are gas stations along the way: stations[i] = [position, fuel].
- Each time you stop at a station, you may take all its fuel.
- Return the minimum number of refueling stops needed to reach target.
- If the target cannot be reached, return -1.

Core idea:
- Greedy + Max Heap
- While traveling forward, push all reachable stations' fuel into a max heap.
- Whenever fuel is insufficient to proceed, refuel using the largest fuel available.
"""

class Solution:
    def minRefuelStops(self, target: int, startFuel: int, stations: List[List[int]]) -> int:
        max_heap = []  # store negative fuel values to simulate max heap
        fuel = startFuel
        i = 0
        stops = 0
        n = len(stations)

        while fuel < target:
            # Add all stations reachable with current fuel
            while i < n and stations[i][0] <= fuel:
                heapq.heappush(max_heap, -stations[i][1])
                i += 1

            # No station available to refuel
            if not max_heap:
                return -1

            # Refuel with the largest available fuel
            fuel += -heapq.heappop(max_heap)
            stops += 1

        return stops


# -------------------------------
# Driver code & test harness
# -------------------------------

def run_test(target, startFuel, stations, expected):
    solution = Solution()
    result = solution.minRefuelStops(target, startFuel, stations)

    print(f"target = {target}")
    print(f"startFuel = {startFuel}")
    print(f"stations = {stations}")
    print(f"Expected: {expected}")
    print(f"Result:   {result}")
    print("✓ PASS" if result == expected else "✗ FAIL")
    print("-" * 50)


if __name__ == "__main__":
    print("=== Testing Minimum Number of Refueling Stops ===\n")

    # Test Case 1: Example from LeetCode
    run_test(
        target=100,
        startFuel=10,
        stations=[[10, 60], [20, 30], [30, 30], [60, 40]],
        expected=2
    )

    # Test Case 2: No stops needed
    run_test(
        target=50,
        startFuel=60,
        stations=[],
        expected=0
    )

    # Test Case 3: Impossible case
    run_test(
        target=100,
        startFuel=1,
        stations=[[10, 100]],
        expected=-1
    )

    # Test Case 4: Single station enough
    run_test(
        target=100,
        startFuel=50,
        stations=[[50, 60]],
        expected=1
    )

    print("\n=== Algorithm Analysis ===\n")
    print("Time Complexity:")
    print("  - Each station is pushed/popped once from heap")
    print("  - Total time: O(n log n)")
    print("\nSpace Complexity:")
    print("  - O(n) for heap storage")
    print("\nKey Insights:")
    print("  - Delay refueling decisions until necessary")
    print("  - Always choose the largest fuel among reachable stations")
    print("  - A max heap enables optimal greedy decisions efficiently")
