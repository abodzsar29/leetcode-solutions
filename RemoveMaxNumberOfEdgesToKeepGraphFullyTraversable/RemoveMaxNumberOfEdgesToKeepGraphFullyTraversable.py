from typing import List

"""
This is the solution for the problem:
"Remove Max Number of Edges to Keep Graph Fully Traversable" (LeetCode #1579, Hard)

Link:
https://leetcode.com/problems/remove-max-number-of-edges-to-keep-graph-fully-traversable/

Problem summary:
- Given a graph with n nodes and edges of three types:
    type 1: Alice-only
    type 2: Bob-only
    type 3: Shared
- Alice and Bob must each be able to traverse the entire graph.
- Return the maximum number of edges that can be removed while keeping both graphs fully connected.
- If impossible, return -1.

Core idea:
- Use Union-Find (Disjoint Set Union) for Alice and Bob
- Process shared edges first (type 3)
- Then process Alice-only and Bob-only edges
- Count how many edges are actually used
- Result = total edges - used edges
"""

# Union-Find / Disjoint Set implementation
class UnionFind:
    def __init__(self, n: int):
        # Parent of each node (1-indexed)
        self.parent = list(range(n + 1))
        # Number of connected components
        self.node_count = n

    def find(self, x: int) -> int:
        # Path compression
        if self.parent[x] != x:
            self.parent[x] = self.find(self.parent[x])
        return self.parent[x]

    def union(self, x: int, y: int) -> int:
        """
        Union x and y.
        Returns:
            1 if union was successful (edge used)
            0 if x and y were already connected (edge redundant)
        """
        xroot = self.find(x)
        yroot = self.find(y)

        if xroot == yroot:
            return 0

        # Attach yroot to xroot
        self.parent[yroot] = xroot
        self.node_count -= 1
        return 1

    def isConnected(self) -> bool:
        # Graph is fully connected if exactly one component remains
        return self.node_count == 1


class Solution:
    def maxNumEdgesToRemove(self, n: int, edges: List[List[int]]) -> int:
        alice = UnionFind(n)
        bob = UnionFind(n)

        used_edges = 0

        # Step 1: Process shared edges first (type 3)
        for edge_type, u, v in edges:
            if edge_type == 3:
                if alice.union(u, v) == 1:
                    bob.union(u, v)
                    used_edges += 1

        # Early exit: both already fully connected
        if alice.isConnected() and bob.isConnected():
            return len(edges) - used_edges

        # Step 2: Process Alice-only and Bob-only edges
        for edge_type, u, v in edges:
            if edge_type == 1:
                used_edges += alice.union(u, v)
            elif edge_type == 2:
                used_edges += bob.union(u, v)

        # Final connectivity check
        if alice.isConnected() and bob.isConnected():
            return len(edges) - used_edges

        return -1


# -------------------------------
# Driver code & test harness
# -------------------------------

def run_test(n, edges, expected):
    solution = Solution()
    result = solution.maxNumEdgesToRemove(n, edges)

    print(f"n = {n}")
    print(f"edges = {edges}")
    print(f"Expected: {expected}")
    print(f"Result:   {result}")
    print("✓ PASS" if result == expected else "✗ FAIL")
    print("-" * 50)


if __name__ == "__main__":
    print("=== Testing Remove Max Number of Edges to Keep Graph Fully Traversable ===\n")

    # Test Case 1: Example from LeetCode
    run_test(
        n=4,
        edges=[
            [3, 1, 2],
            [3, 2, 3],
            [1, 1, 3],
            [1, 2, 4],
            [1, 1, 2],
            [2, 3, 4]
        ],
        expected=2
    )

    # Test Case 2: Only shared edges
    run_test(
        n=3,
        edges=[
            [3, 1, 2],
            [3, 2, 3],
            [3, 1, 3]
        ],
        expected=1
    )

    # Test Case 3: Impossible for Bob
    run_test(
        n=4,
        edges=[
            [3, 1, 2],
            [1, 2, 3],
            [1, 3, 4]
        ],
        expected=-1
    )

    # Test Case 4: Already minimal
    run_test(
        n=2,
        edges=[
            [3, 1, 2]
        ],
        expected=0
    )

    print("\n=== Algorithm Analysis ===\n")
    print("Time Complexity:")
    print("  - Union-Find operations are amortized O(α(n))")
    print("  - Total time: O(E · α(n))")
    print("\nSpace Complexity:")
    print("  - O(n) for Union-Find structures")
    print("\nKey Insights:")
    print("  - Shared edges must be processed first to maximize reuse")
    print("  - Counting used edges is often clearer than counting removed ones")
    print("  - Separate DSUs cleanly model Alice and Bob’s constraints")
