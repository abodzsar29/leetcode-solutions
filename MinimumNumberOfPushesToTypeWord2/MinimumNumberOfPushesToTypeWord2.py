from collections import Counter

"""
This is the solution for the problem:
"Minimum Number of Pushes to Type Word II" (LeetCode #3016, Medium)

Link:
https://leetcode.com/problems/minimum-number-of-pushes-to-type-word-ii/

Problem summary:
- You are given a string `word`.
- You type letters on a phone keypad.
- Each key can hold at most 8 characters.
- Characters assigned to the same key require increasing pushes:
    - 1st character → 1 push
    - 2nd character → 2 pushes
    - ...
- You may assign letters to keys optimally.
- Return the minimum total number of pushes required to type the word.

Core idea:
- Only letter frequencies matter, not their actual characters.
- To minimize total pushes:
    - Assign the most frequent letters to the lowest push counts.
- Each "push tier" can contain up to 8 letters:
    - First 8 letters → cost ×1
    - Next 8 letters → cost ×2
    - Next 8 letters → cost ×3
    - ...
- Greedy strategy:
    - Sort character frequencies in descending order.
    - Multiply each frequency by its tier cost.
"""

class Solution:
    def minimumPushes(self, word: str) -> int:
        # Count frequency of each character
        freq = Counter(word)

        # Sort frequencies in descending order
        counts = sorted(freq.values(), reverse=True)

        total_pushes = 0

        for i, c in enumerate(counts):
            # Each tier holds 8 characters
            # Tier index determines number of pushes
            pushes_per_char = (i // 8) + 1
            total_pushes += pushes_per_char * c

        return total_pushes


# -------------------------------
# Driver code & test harness
# -------------------------------

def run_test(word, expected):
    solution = Solution()
    result = solution.minimumPushes(word)

    print(f'word = "{word}"')
    print(f"Expected: {expected}")
    print(f"Result:   {result}")
    print("✓ PASS" if result == expected else "✗ FAIL")
    print("-" * 50)


if __name__ == "__main__":
    print("=== Testing Minimum Number of Pushes to Type Word II ===\n")

    # Test Case 1: Example from LeetCode
    run_test(
        word="abcde",
        expected=5
    )

    # Test Case 2: Repeated characters
    run_test(
        word="aabbccdd",
        expected=8
    )

    # Test Case 3: More than 8 unique characters
    run_test(
        word="abcdefgh",
        expected=8
    )

    # Test Case 4: Crossing into second tier
    run_test(
        word="abcdefghi",
        expected=10  # 8 * 1 + 1 * 2
    )

    # Test Case 5: All same character
    run_test(
        word="zzzzzz",
        expected=6
    )

    # Test Case 6: Larger mixed case
    run_test(
        word="leetcode",
        expected=8
    )

    print("\n=== Algorithm Analysis ===\n")
    print("Time Complexity:")
    print("  - Counting characters: O(n)")
    print("  - Sorting frequencies: O(k log k), k ≤ 26")
    print("  - Overall: O(n)")
    print("\nSpace Complexity:")
    print("  - O(k) for character frequency map")
    print("\nKey Insights:")
    print("  - The exact keypad layout does not matter, only frequency ordering")
    print("  - Greedy assignment of highest frequencies to lowest costs is optimal")
    print("  - Fixed bucket size (8) creates clear push tiers")
