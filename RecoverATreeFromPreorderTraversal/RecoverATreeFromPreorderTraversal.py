from typing import Optional, List
from collections import deque

"""
This is the solution for the problem:
"Recover a Tree From Preorder Traversal" (LeetCode #1028, Hard)

Link:
https://leetcode.com/problems/recover-a-tree-from-preorder-traversal/

Problem summary:
- A preorder traversal string encodes depth using '-' characters.
- The number of dashes before a value equals the node depth.
- Reconstruct and return the binary tree.
"""

# Definition for a binary tree node (used for local testing / driver).
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:
    def recoverFromPreorder(self, traversal: str) -> Optional[TreeNode]:
        stack = []
        i = 0
        n = len(traversal)

        while i < n:
            depth = 0
            while i < n and traversal[i] == '-':
                depth += 1
                i += 1

            value = 0
            while i < n and traversal[i].isdigit():
                value = value * 10 + int(traversal[i])
                i += 1

            node = TreeNode(value)

            while len(stack) > depth:
                stack.pop()

            if stack:
                parent = stack[-1]
                if parent.left is None:
                    parent.left = node
                else:
                    parent.right = node

            stack.append(node)

        return stack[0] if stack else None


# -------------------------------
# Helper: serialize tree (level-order)
# -------------------------------
def serialize(root: Optional[TreeNode]) -> List[Optional[int]]:
    if not root:
        return []

    result = []
    q = deque([root])

    while q:
        node = q.popleft()
        if node:
            result.append(node.val)
            q.append(node.left)
            q.append(node.right)
        else:
            result.append(None)

    while result and result[-1] is None:
        result.pop()

    return result


# -------------------------------
# Driver code & test harness
# -------------------------------
def run_test(traversal, expected_level_order):
    solution = Solution()
    root = solution.recoverFromPreorder(traversal)
    result = serialize(root)

    print(f"traversal = {traversal}")
    print(f"Expected: {expected_level_order}")
    print(f"Result:   {result}")
    print("✓ PASS" if result == expected_level_order else "✗ FAIL")
    print("-" * 50)


if __name__ == "__main__":
    print("=== Testing Recover a Tree From Preorder Traversal ===\n")

    # Test Case 1
    run_test(
        "1-2--3--4-5--6--7",
        [1, 2, 5, 3, 4, 6, 7]
    )

    # Test Case 2
    run_test(
        "1-2--3---4-5--6---7",
        [1, 2, 5, 3, None, 6, None, 4, None, 7]
    )

    # Test Case 3: Single node
    run_test(
        "1",
        [1]
    )

    print("\n=== Algorithm Analysis ===\n")
    print("Time Complexity:")
    print("  - Each character processed once: O(n)")
    print("\nSpace Complexity:")
    print("  - Stack stores at most tree height: O(h)")
    print("\nKey Insights:")
    print("  - Dash count directly gives node depth")
    print("  - Stack depth always equals current traversal depth")
    print("  - Attach left child first, then right child")



