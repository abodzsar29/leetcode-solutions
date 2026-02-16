from typing import List

"""
LeetCode 1483 — Kth Ancestor of a Tree Node

Two implementations:

1. Binary Lifting (standard optimal interview solution)
2. Leaf-path caching (path compression style approach)

Driver harness tests both implementations on identical queries.
"""

# ---------------------------------------------------
# Solution 1 — Binary Lifting
# ---------------------------------------------------
class TreeAncestorBinary:
    def __init__(self, n: int, parent: List[int]):
        LOG = (n).bit_length()
        self.LOG = LOG
        self.up = [[-1] * n for _ in range(LOG)]

        for i in range(n):
            self.up[0][i] = parent[i]

        for j in range(1, LOG):
            for i in range(n):
                prev = self.up[j - 1][i]
                if prev != -1:
                    self.up[j][i] = self.up[j - 1][prev]

    def getKthAncestor(self, node: int, k: int) -> int:
        j = 0
        while k and node != -1:
            if k & 1:
                node = self.up[j][node]
            k >>= 1
            j += 1
        return node


# ---------------------------------------------------
# Solution 2 — Leaf-path caching (your approach)
# ---------------------------------------------------
class TreeAncestorLeaf:
    def __init__(self, n: int, parent: List[int]):
        existing = set(parent)
        self.cache = {}

        for node in range(n):
            if node not in existing:
                key = node
                self.cache[key] = []
                level = 0
                cur = node
                while cur != -1:
                    self.cache[key].append(parent[cur])
                    self.cache[parent[cur]] = (key, level + 1)
                    cur = parent[cur]
                    level += 1

    def getKthAncestor(self, node: int, k: int) -> int:
        if k == 0:
            return node

        result = self.cache[node]
        if not isinstance(result, list):
            node, level = result
            k += level

        return self.cache[node][k - 1] if k <= len(self.cache[node]) else -1


# ---------------------------------------------------
# Driver code & test harness
# ---------------------------------------------------
def run_test(n, parent, queries, expected):
    sol1 = TreeAncestorBinary(n, parent)
    sol2 = TreeAncestorLeaf(n, parent)

    print(f"n = {n}")
    print(f"parent = {parent}")

    for i, (node, k) in enumerate(queries):
        r1 = sol1.getKthAncestor(node, k)
        r2 = sol2.getKthAncestor(node, k)

        print(f"Query {i+1}: node={node}, k={k}")
        print(f"Binary: {r1}, LeafCache: {r2}, Expected: {expected[i]}")
        ok = (r1 == expected[i]) and (r2 == expected[i])
        print("✓ PASS" if ok else "✗ FAIL")
        print("-" * 40)


if __name__ == "__main__":
    print("=== Testing Kth Ancestor of a Tree Node ===\n")

    # Example tree:
    #        0
    #      /   \
    #     1     2
    #    / \
    #   3   4
    # parent = [-1,0,0,1,1]

    run_test(
        n=5,
        parent=[-1, 0, 0, 1, 1],
        queries=[
            (3, 1),
            (3, 2),
            (4, 2),
            (2, 1),
            (2, 2)
        ],
        expected=[1, 0, 0, 0, -1]
    )

    print("\n=== Complexity Summary ===\n")
    print("Binary Lifting:")
    print("  Preprocess: O(n log n)")
    print("  Query:      O(log n)")
    print("  Space:      O(n log n)")
    print()
    print("Leaf-path caching:")
    print("  Preprocess: ~O(n) average")
    print("  Query:      O(1)")
    print("  Space:      up to O(n^2) worst-case")

