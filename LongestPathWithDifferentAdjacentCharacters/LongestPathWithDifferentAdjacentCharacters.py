from typing import List
from collections import defaultdict

"""
This is the solution for the problem:
"Longest Path With Different Adjacent Characters" (LeetCode #2246, Hard)

Link:
https://leetcode.com/problems/longest-path-with-different-adjacent-characters/

Problem summary:
- Given a rooted tree represented by `parent` and a string `s`
- Each node has a character s[i]
- Find the length of the longest path where adjacent nodes have different characters

Core idea:
- DFS tree DP
- For each node, compute the longest valid downward chain starting at that node
- Combine the two best child chains (whose characters differ from the node)
- Update a global answer
"""


# ---------------------------------------------------------
# Solution 1 — Explicitly track top two child chains
# ---------------------------------------------------------
class Solution1:
    def longestPath(self, parent: List[int], s: str) -> int:
        n = len(parent)

        children = defaultdict(list)
        for i in range(1, n):
            children[parent[i]].append(i)

        self.ans = 1

        def dfs(node: int) -> int:
            longest1 = 0
            longest2 = 0

            for child in children[node]:
                child_len = dfs(child)

                if s[child] == s[node]:
                    continue

                if child_len > longest1:
                    longest2 = longest1
                    longest1 = child_len
                elif child_len > longest2:
                    longest2 = child_len

            self.ans = max(self.ans, 1 + longest1 + longest2)
            return 1 + longest1

        dfs(0)
        return self.ans


# ---------------------------------------------------------
# Solution 2 — Compact formulation (implicit second-best)
# ---------------------------------------------------------
class Solution2:
    def longestPath(self, parent: List[int], s: str) -> int:
        n = len(s)
        g = [[] for _ in range(n)]
        for i in range(1, n):
            g[parent[i]].append(i)

        ans = 0

        def dfs(x: int) -> int:
            nonlocal ans
            x_len = 0

            for y in g[x]:
                y_len = dfs(y) + 1

                if s[y] != s[x]:
                    ans = max(ans, x_len + y_len)
                    x_len = max(x_len, y_len)

            return x_len

        dfs(0)
        return ans + 1


# -------------------------------
# Driver code & test harness
# -------------------------------

def run_test(parent, s, expected):
    result1 = Solution1().longestPath(parent, s)
    result2 = Solution2().longestPath(parent, s)

    print(f"parent = {parent}")
    print(f"s = '{s}'")
    print(f"Expected: {expected}")
    print(f"Solution1: {result1}")
    print(f"Solution2: {result2}")

    ok = (result1 == expected) and (result2 == expected)
    print("✓ PASS" if ok else "✗ FAIL")
    print("-" * 60)


if __name__ == "__main__":
    print("=== Testing Longest Path With Different Adjacent Characters ===\n")

    # Test Case 1 (LeetCode example)
    run_test(
        parent=[-1, 0, 0, 1, 1, 2],
        s="abacbe",
        expected=3
    )

    # Test Case 2
    run_test(
        parent=[-1, 0, 0, 0],
        s="aabc",
        expected=3
    )

    # Test Case 3: single node
    run_test(
        parent=[-1],
        s="a",
        expected=1
    )

    # Test Case 4: chain alternating
    run_test(
        parent=[-1, 0, 1, 2, 3],
        s="ababa",
        expected=5
    )

    print("\n=== Algorithm Analysis ===\n")
    print("Time Complexity:")
    print("  - O(n) DFS over the tree")
    print("\nSpace Complexity:")
    print("  - O(n) adjacency list + recursion stack")
    print("\nKey Insights:")
    print("  - At each node only the two longest valid child chains matter")
    print("  - Solution2 computes the same logic but tracks the second-best chain implicitly")

