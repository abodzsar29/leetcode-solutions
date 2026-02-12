from typing import List, Optional
from collections import defaultdict, deque

"""
Driver + solution for:

LeetCode #2458
Height of Binary Tree After Subtree Removal Queries

Problem summary:
- Given a binary tree and a list of queries.
- Each query removes the subtree rooted at a node.
- For every query, return the height of the remaining tree.

Core idea:
- Precompute:
    depth[node]
    subtree height[node]
- For each depth level, store the two largest subtree heights.
- Each query can then be answered in O(1).
"""


# -------------------------------
# Tree utilities
# -------------------------------

class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


def build_tree(level_list: List[Optional[int]]) -> Optional[TreeNode]:
    """Build binary tree from level-order list."""
    if not level_list:
        return None

    root = TreeNode(level_list[0])
    q = deque([root])
    i = 1

    while q and i < len(level_list):
        node = q.popleft()

        if i < len(level_list) and level_list[i] is not None:
            node.left = TreeNode(level_list[i])
            q.append(node.left)
        i += 1

        if i < len(level_list) and level_list[i] is not None:
            node.right = TreeNode(level_list[i])
            q.append(node.right)
        i += 1

    return root


# -------------------------------
# Solution
# -------------------------------

class Solution:
    def treeQueries(self, root: TreeNode, queries: List[int]) -> List[int]:
        depth = {}
        subh = {}
        best = defaultdict(lambda: [-1, -1])  # [largest, second largest]

        def dfs(node, d):
            if not node:
                return -1

            depth[node.val] = d
            lh = dfs(node.left, d + 1)
            rh = dfs(node.right, d + 1)
            h = max(lh, rh) + 1
            subh[node.val] = h

            m1, m2 = best[d]
            if h > m1:
                best[d] = [h, m1]
            elif h > m2:
                best[d][1] = h

            return h

        dfs(root, 0)

        ans = []
        for q in queries:
            d = depth[q]
            h = subh[q]
            m1, m2 = best[d]
            use = m2 if h == m1 else m1
            ans.append(d + use)

        return ans


# -------------------------------
# Driver code & test harness
# -------------------------------

def run_test(tree_list, queries, expected):
    root = build_tree(tree_list)
    solution = Solution()
    result = solution.treeQueries(root, queries)

    print(f"Tree (level-order) = {tree_list}")
    print(f"Queries = {queries}")
    print(f"Expected: {expected}")
    print(f"Result:   {result}")
    print("✓ PASS" if result == expected else "✗ FAIL")
    print("-" * 50)


if __name__ == "__main__":
    print("=== Testing Height of Binary Tree After Subtree Removal Queries ===\n")

    # Test Case 1 (LeetCode example)
    run_test(
        tree_list=[1, 3, 4, 2, None, 6, 5, None, None, None, None, None, 7],
        queries=[4],
        expected=[2]
    )

    # Test Case 2
    run_test(
        tree_list=[5, 8, 9, 2, 1, 3, 7, 4, 6],
        queries=[3, 2, 4, 8],
        expected=[3, 2, 3, 2]
    )

    # Test Case 3: Single node tree
    run_test(
        tree_list=[1],
        queries=[1],
        expected=[-1]
    )

    print("\n=== Algorithm Analysis ===\n")
    print("Time Complexity:")
    print("  - DFS preprocessing: O(n)")
    print("  - Each query: O(1)")
    print("  - Total: O(n + q)")
    print("\nSpace Complexity:")
    print("  - O(n) for depth, subtree heights, and per-level maxima")

