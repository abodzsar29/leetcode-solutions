from typing import List
from collections import defaultdict

"""
This file contains two optimal solutions for the problem:

"Count Prefix and Suffix Pairs II" (LeetCode #3045, Hard)

Link:
https://leetcode.com/problems/count-prefix-and-suffix-pairs-ii/

Problem summary:
- Given a list of strings `words`
- Count pairs (i, j) such that:
    * i < j
    * words[i] is BOTH a prefix and a suffix of words[j]

Constraints:
- Large input sizes
- Brute force string comparison will TLE

Solutions included:
1) Double Rolling Hash solution
2) Paired Trie solution (character-level, collision-free)
"""

# -------------------------------------------------
# Solution 1: Double Rolling Hash
# -------------------------------------------------

class SolutionHash:
    def countPrefixSuffixPairs(self, words: List[str]) -> int:
        MOD1 = 10**9 + 7
        MOD2 = 10**9 + 9
        BASE = 91138233

        def compute_hash(s: str):
            h1 = h2 = 0
            for c in s:
                h1 = (h1 * BASE + ord(c)) % MOD1
                h2 = (h2 * BASE + ord(c)) % MOD2
            return (h1, h2)

        seen = defaultdict(int)
        result = 0

        for word in words:
            n = len(word)

            pref1 = [0] * (n + 1)
            pref2 = [0] * (n + 1)
            pow1 = [1] * (n + 1)
            pow2 = [1] * (n + 1)

            for i in range(n):
                pref1[i + 1] = (pref1[i] * BASE + ord(word[i])) % MOD1
                pref2[i + 1] = (pref2[i] * BASE + ord(word[i])) % MOD2
                pow1[i + 1] = (pow1[i] * BASE) % MOD1
                pow2[i + 1] = (pow2[i] * BASE) % MOD2

            # Check all prefix = suffix lengths
            for L in range(1, n + 1):
                ph1, ph2 = pref1[L], pref2[L]
                sh1 = (pref1[n] - pref1[n - L] * pow1[L]) % MOD1
                sh2 = (pref2[n] - pref2[n - L] * pow2[L]) % MOD2

                if ph1 == sh1 and ph2 == sh2:
                    result += seen[(ph1, ph2)]

            seen[compute_hash(word)] += 1

        return result


# -------------------------------------------------
# Solution 2: Paired Trie (Prefix + Suffix)
# -------------------------------------------------

class SolutionTrie:
    def countPrefixSuffixPairs(self, words: List[str]) -> int:
        trie = {}
        result = 0

        for word in words:
            cur = trie
            n = len(word)

            for i in range(n):
                key = (word[i], word[n - i - 1])
                cur = cur.setdefault(key, {})
                result += cur.get('#', 0)

            cur['#'] = cur.get('#', 0) + 1

        return result


# -------------------------------------------------
# Driver Code & Test Harness
# -------------------------------------------------

def run_test(words: List[str], expected: int):
    hash_solution = SolutionHash()
    trie_solution = SolutionTrie()

    result_hash = hash_solution.countPrefixSuffixPairs(words)
    result_trie = trie_solution.countPrefixSuffixPairs(words)

    print(f"words = {words}")
    print(f"Expected: {expected}")
    print(f"Hash Solution Result: {result_hash}")
    print(f"Trie Solution Result: {result_trie}")

    ok = (result_hash == expected) and (result_trie == expected)
    print("✓ PASS" if ok else "✗ FAIL")
    print("-" * 60)


if __name__ == "__main__":
    print("=== Testing Count Prefix and Suffix Pairs II ===\n")

    # Test Case 1
    run_test(
        words=["a", "aba", "ababa", "a"],
        expected=4
    )

    # Test Case 2
    run_test(
        words=["aa", "aa", "aa"],
        expected=3
    )

    # Test Case 3
    run_test(
        words=["abc", "ab", "bc", "abc"],
        expected=1
    )

    # Test Case 4
    run_test(
        words=["x"],
        expected=0
    )

    print("\n=== Algorithm Analysis ===\n")

    print("Solution 1: Double Rolling Hash")
    print("Time Complexity:  O(total characters)")
    print("Space Complexity: O(total characters)")
    print("Notes:")
    print("  - Uses prefix/suffix hashing")
    print("  - Extremely low collision risk with double hash")
    print()

    print("Solution 2: Paired Trie")
    print("Time Complexity:  O(total characters)")
    print("Space Complexity: O(total characters)")
    print("Notes:")
    print("  - Collision-free")
    print("  - Very small constant factors")
    print("  - Encodes prefix & suffix symmetry directly")
