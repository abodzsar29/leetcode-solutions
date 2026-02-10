"""
This is the solution for the problem:
"Longest Happy Prefix" (LeetCode #1392, Hard)

Link:
https://leetcode.com/problems/longest-happy-prefix/

Problem summary:
- A happy prefix is a non-empty prefix of a string that is also a suffix,
  excluding the entire string itself.
- Return the longest happy prefix of the given string.
- If none exists, return an empty string.

Core idea:
- Use the KMP prefix-function (LPS array).
- lps[i] stores the length of the longest prefix which is also a suffix
  for substring s[:i+1].
- The final value lps[n-1] gives the length of the longest happy prefix.
"""


class Solution:
    def longestPrefix(self, s: str) -> str:
        n = len(s)
        lps = [0] * n   # lps[i] = length of longest prefix == suffix for s[:i+1]

        j = 0  # length of current matching prefix

        for i in range(1, n):
            # fallback until characters match or j becomes 0
            while j > 0 and s[i] != s[j]:
                j = lps[j - 1]

            if s[i] == s[j]:
                j += 1
                lps[i] = j

        # lps[n-1] gives length of longest happy prefix
        return s[:lps[-1]]


# -------------------------------
# Driver code & test harness
# -------------------------------

def run_test(s, expected):
    solution = Solution()
    result = solution.longestPrefix(s)

    print(f"s = '{s}'")
    print(f"Expected: '{expected}'")
    print(f"Result:   '{result}'")
    print("✓ PASS" if result == expected else "✗ FAIL")
    print("-" * 50)


if __name__ == "__main__":
    print("=== Testing Longest Happy Prefix ===\n")

    # Test Case 1: Example
    run_test(
        s="level",
        expected="l"
    )

    # Test Case 2: Example
    run_test(
        s="ababab",
        expected="abab"
    )

    # Test Case 3: No happy prefix
    run_test(
        s="abcd",
        expected=""
    )

    # Test Case 4: Entire repeated string
    run_test(
        s="aaaaa",
        expected="aaaa"
    )

    print("\n=== Algorithm Analysis ===\n")
    print("Time Complexity:")
    print("  - Building LPS array takes O(n)")
    print("\nSpace Complexity:")
    print("  - O(n) for the LPS array")
    print("\nKey Insights:")
    print("  - Longest happy prefix equals the final LPS value")
    print("  - KMP preprocessing computes prefix/suffix matches in one pass")
    print("  - This achieves the optimal linear-time solution")

