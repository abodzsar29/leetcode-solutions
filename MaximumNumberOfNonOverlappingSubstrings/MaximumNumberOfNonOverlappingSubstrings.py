from typing import List

"""
This is the optimal solution for the problem:
"Maximum Number of Non-Overlapping Substrings" (LeetCode #1520, Hard)

Link:
https://leetcode.com/problems/maximum-number-of-non-overlapping-substrings/

Problem summary:
- Given a string s, return the maximum number of non-overlapping substrings
  such that every character appearing in a substring appears ONLY inside it
  (i.e., the substring must contain all occurrences of its characters).
- If multiple answers exist, return the one with minimum total length.

Core idea (Greedy + interval construction):
1. Record first and last occurrence of every character.
2. For each index that is a first occurrence, try to build the minimal valid
   interval [l, r]:
      - Start with r = last[s[l]]
      - Expand while scanning:
            if a character starts before l -> invalid interval
            else update r = max(r, last[char])
3. Collect valid intervals.
4. Sort by end index and greedily pick non-overlapping intervals.

Why this works:
- Each candidate interval is minimal and self-contained.
- Earliest-ending interval greedy selection maximizes the number of
  non-overlapping substrings (classic interval scheduling).
"""

class Solution:
    def maxNumOfSubstrings(self, s: str) -> List[str]:
        n = len(s)
        A = 26

        # Step 1: first and last occurrence of each character
        first = [n] * A
        last = [-1] * A

        for i, ch in enumerate(s):
            idx = ord(ch) - ord('a')
            first[idx] = min(first[idx], i)
            last[idx] = max(last[idx], i)

        intervals = []

        # Step 2: build minimal valid intervals
        for i, ch in enumerate(s):
            idx = ord(ch) - ord('a')

            # Only try intervals from first occurrences
            if i != first[idx]:
                continue

            l = i
            r = last[idx]
            j = l
            valid = True

            while j <= r:
                c = ord(s[j]) - ord('a')

                # Character begins before l → invalid
                if first[c] < l:
                    valid = False
                    break

                r = max(r, last[c])
                j += 1

            if valid:
                intervals.append((l, r))

        # Step 3: greedy selection by earliest end
        intervals.sort(key=lambda x: (x[1], x[0]))

        result = []
        prev_end = -1

        for l, r in intervals:
            if l > prev_end:
                result.append(s[l:r + 1])
                prev_end = r

        return result


# -------------------------------
# Driver code & test harness
# -------------------------------

def run_test(s, expected):
    solution = Solution()
    result = solution.maxNumOfSubstrings(s)

    print(f's = "{s}"')
    print(f"Expected: {expected}")
    print(f"Result:   {result}")
    print("✓ PASS" if result == expected else "✗ FAIL")
    print("-" * 50)


if __name__ == "__main__":
    print("=== Testing Maximum Number of Non-Overlapping Substrings ===\n")

    # Test Case 1: LeetCode example
    run_test(
        "adefaddaccc",
        ["e", "f", "ccc"]
    )

    # Test Case 2: Multiple minimal intervals
    run_test(
        "abbaccd",
        ["bb", "cc", "d"]
    )

    # Test Case 3: All unique characters
    run_test(
        "abc",
        ["a", "b", "c"]
    )

    # Test Case 4: Entire string required
    run_test(
        "abab",
        ["abab"]
    )

    print("\n=== Algorithm Analysis ===\n")
    print("Time Complexity:")
    print("  - First/last occurrence computation: O(n)")
    print("  - Interval expansion: O(n) overall (alphabet size = 26)")
    print("  - Sorting intervals: O(26 log 26) ≈ O(1)")
    print("  - Total: O(n)")
    print("\nSpace Complexity:")
    print("  - O(1) auxiliary space (excluding output)")
    print("\nKey Insights:")
    print("  - Start intervals only at first occurrences")
    print("  - Expand interval until all included chars are fully covered")
    print("  - Greedy by earliest ending interval maximizes count")
