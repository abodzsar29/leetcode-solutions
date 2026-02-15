from typing import List
from collections import Counter
from itertools import chain, product
from itertools import accumulate

"""
LeetCode #1782 — Count Pairs of Nodes

Problem summary:
- We have an undirected multigraph with n nodes.
- deg[i] = degree of node i (counting multiplicities).
- For each query q, count the number of unordered node pairs (u, v), u < v,
  such that:
        deg[u] + deg[v] > q
- If nodes share multiple edges, we must correct for overcounting:
  if deg[u] + deg[v] > q but (deg[u] + deg[v] - shared_edges) <= q,
  then the pair should NOT be counted.
"""


# ----------------------------------------------------------------------
# Solution 1 — Two-pointer per query
#
# Idea:
# 1. Compute degree of each node and multiplicity of each node pair.
# 2. Sort the degree array once.
# 3. For every query:
#      - Use two pointers on sorted degrees to count pairs whose sum > q
#      - Correct overcounted pairs using the edge multiplicity table
#
# Complexity:
#   O(n log n + Q*n + m)
# ----------------------------------------------------------------------
class SolutionTwoPointer:
    def countPairs(self, n: int, edges: List[List[int]], queries: List[int]) -> List[int]:
        deg = [0] * (n + 1)
        pair_cnt = Counter()

        for u, v in edges:
            if u > v:
                u, v = v, u
            deg[u] += 1
            deg[v] += 1
            pair_cnt[(u, v)] += 1

        sorted_deg = sorted(deg[1:])
        ans = []

        for q in queries:
            total = 0
            l, r = 0, n - 1

            # count pairs by two-pointer
            while l < r:
                if sorted_deg[l] + sorted_deg[r] <= q:
                    l += 1
                else:
                    total += r - l
                    r -= 1

            # remove overcounted pairs
            for (u, v), c in pair_cnt.items():
                if deg[u] + deg[v] > q and deg[u] + deg[v] - c <= q:
                    total -= 1

            ans.append(total)

        return ans


# ----------------------------------------------------------------------
# Solution 2 — Degree-frequency histogram (precompute all sums once)
#
# Idea:
# 1. Count how many nodes have each degree.
# 2. Build a histogram:
#        count_pairs[s] = number of node pairs with degree sum == s
# 3. Fix histogram for multi-edge corrections.
# 4. Convert histogram to suffix sums so:
#        ans[k] = number of pairs with degree sum >= k
# 5. Each query is answered in O(1).
#
# Complexity:
#   Preprocessing: O(D^2 + m), D = distinct degree count
#   Query: O(1)
# ----------------------------------------------------------------------
class SolutionHistogram:
    def countPairs(self, n: int, edges: List[List[int]], queries: List[int]) -> List[int]:

        nodes = Counter(chain(*edges))
        nodes = {i: nodes[i] if i in nodes else 0 for i in range(1, n + 1)}

        edges_cnt = Counter(map(lambda x: (min(x), max(x)), edges))

        size = 2 + 2 * max(nodes.values())
        ans = [0] * size
        ctr = Counter(nodes.values())

        # build histogram of degree sums
        for c1, c2 in product(ctr, ctr):
            if c1 > c2:
                continue
            if c1 != c2:
                ans[c1 + c2] += ctr[c1] * ctr[c2]
            else:
                ans[c1 + c2] += ctr[c1] * (ctr[c2] - 1) // 2

        # correct pairs sharing edges
        for (i, j), c in edges_cnt.items():
            sm = nodes[i] + nodes[j]
            ans[sm] -= 1
            ans[sm - c] += 1

        # suffix accumulation
        ans = list(accumulate(ans[::-1]))[::-1]

        return [ans[min(q + 1, size - 1)] for q in queries]


# ----------------------------------------------------------------------
# Driver code & test harness
# ----------------------------------------------------------------------
def run_test(n, edges, queries):
    print(f"n = {n}")
    print(f"edges = {edges}")
    print(f"queries = {queries}")

    sol1 = SolutionTwoPointer()
    sol2 = SolutionHistogram()

    r1 = sol1.countPairs(n, edges, queries)
    r2 = sol2.countPairs(n, edges, queries)

    print("TwoPointer:", r1)
    print("Histogram: ", r2)
    print("✓ SAME" if r1 == r2 else "✗ DIFFER")
    print("-" * 60)


if __name__ == "__main__":
    print("=== Testing Count Pairs of Nodes ===\n")

    run_test(
        n=4,
        edges=[[1, 2], [2, 3], [2, 3], [2, 4]],
        queries=[1, 2, 3]
    )

    run_test(
        n=5,
        edges=[[1, 2], [1, 3], [2, 3], [2, 4], [2, 5]],
        queries=[1, 2, 3, 4]
    )

