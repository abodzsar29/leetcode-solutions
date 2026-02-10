from typing import List
from collections import defaultdict
import heapq

"""
This is the solution for the problem:
"Network Delay Time" (LeetCode #743, Medium)

Link:
https://leetcode.com/problems/network-delay-time/

Problem summary:
- You are given a directed weighted graph with n nodes labeled 1..n.
- times[i] = (u, v, w) represents a signal traveling from u to v in w time.
- A signal starts from node k.
- Return the time it takes for all nodes to receive the signal.
- If some nodes cannot be reached, return -1.

Core idea:
- Use Dijkstra's algorithm because:
    - The graph is weighted
    - We need the shortest time from a single source to all nodes
- Use a min-heap to always expand the currently fastest known path
- Maintain a distance array and relax edges
"""


class Solution:
    def networkDelayTime(self, times: List[List[int]], n: int, k: int) -> int:
        # use dijkstras because you have a weighted graph + need shortest time from a single source to all nodes
        adj = defaultdict(list)
        for u, v, w in times:
            adj[u].append((v, w))
        
        # smallest time we currently know to reach node x from k
        # set initial time to reach node k from k = 0
        # set all others as infinity 
        dist = [float('inf')] * (n + 1)
        dist[k] = 0

        # min heap, so we always pop the smallest time so far
        heap = [(0, k)]
        
        while heap:
            # pick the currently fastest candidate from all candidates
            time_so_far, node = heapq.heappop(heap)

            # if this is worse than what we already recorded, skip it
            if time_so_far > dist[node]:
                continue

            # try going to the neighbors 
            for neighbor, w in adj[node]:
                # get new time 
                new_time = time_so_far + w
                # if this new route is faster than the best time we already knew, update it
                # this is called relaxing the edge 
                if new_time < dist[neighbor]:
                    dist[neighbor] = new_time
                    heapq.heappush(heap, (new_time, neighbor))

        # if any node is still inf, it's unreachable
        ans = max(dist[1:])
        return -1 if ans == float('inf') else ans


# -------------------------------
# Driver code & test harness
# -------------------------------

def run_test(times, n, k, expected):
    solution = Solution()
    result = solution.networkDelayTime(times, n, k)

    print(f"times = {times}")
    print(f"n = {n}, k = {k}")
    print(f"Expected: {expected}")
    print(f"Result:   {result}")
    print("✓ PASS" if result == expected else "✗ FAIL")
    print("-" * 50)


if __name__ == "__main__":
    print("=== Testing Network Delay Time ===\n")

    # Test Case 1: Example from LeetCode
    run_test(
        times=[[2, 1, 1], [2, 3, 1], [3, 4, 1]],
        n=4,
        k=2,
        expected=2
    )

    # Test Case 2: Single node
    run_test(
        times=[],
        n=1,
        k=1,
        expected=0
    )

    # Test Case 3: Unreachable node
    run_test(
        times=[[1, 2, 1]],
        n=2,
        k=2,
        expected=-1
    )

    # Test Case 4: Multiple paths
    run_test(
        times=[[1, 2, 5], [1, 3, 2], [3, 2, 1], [2, 4, 1]],
        n=4,
        k=1,
        expected=4
    )

    print("\n=== Algorithm Analysis ===\n")
    print("Time Complexity:")
    print("  - Dijkstra using heap: O(E log V)")
    print("\nSpace Complexity:")
    print("  - O(E + V) for adjacency list, heap, and distance array")
    print("\nKey Insights:")
    print("  - Weighted graph + single source shortest paths ⇒ Dijkstra")
    print("  - Edge relaxation updates the best-known distance")
    print("  - Skipping outdated heap entries preserves optimal complexity")

