"""
Problem:
"Minimum Cost to Make All Characters Equal" (LeetCode #2712)

Link:
https://leetcode.com/problems/minimum-cost-to-make-all-characters-equal/

------------------------------------------------------------
METHOD OVERVIEW (APPLIES TO BOTH SOLUTIONS)
------------------------------------------------------------
Key observation:
- Only positions where s[i] != s[i+1] matter (transitions)
- Each transition must be resolved exactly once

For a transition at index i:
- Flip prefix [0..i]      → cost = i + 1
- Flip suffix [i+1..n-1] → cost = n - i - 1

Greedy rule:
- Always choose the cheaper side
- Transitions are independent → local minimum is globally optimal

Time complexity (both): O(n)
Space complexity (both): O(1)
"""

# --------------------------------------------------
# METHOD 1: Half-Split Greedy (Optimized)
# --------------------------------------------------
"""
Explanation:
- Pre-applies the greedy decision using index position
- Left half of the string: prefix flips are always cheaper
- Right half of the string: suffix flips are always cheaper
- Avoids min() calls and reduces branching

LeetCode performance:
- Runtime: 43 ms
- Beats: 100% of Python submissions
"""

class SolutionOptimized:
    def minimumCost(self, s: str) -> int:
        n = len(s)
        firsthalf = 0
        secondhalf = 0
        last = s[0]

        # Left half → always flip prefix
        for i in range(n // 2 + 1):
            if s[i] != last:
                firsthalf += i
            last = s[i]

        # Right half → always flip suffix
        for i in range(n // 2 + 1, n):
            if s[i] != last:
                secondhalf += (n - i)
            last = s[i]

        return firsthalf + secondhalf


# --------------------------------------------------
# METHOD 2: Canonical Greedy (Direct)
# --------------------------------------------------
"""
Explanation:
- Explicitly applies the greedy rule at each transition
- Uses min(prefix_cost, suffix_cost) for clarity

LeetCode performance:
- Runtime: 71 ms
- Beats: 77.94% of Python submissions
"""

class SolutionGreedy:
    def minimumCost(self, s: str) -> int:
        ans = 0
        n = len(s)

        for i in range(n - 1):
            if s[i] != s[i + 1]:
                ans += min(i + 1, n - i - 1)

        return ans


# --------------------------------------------------
# DRIVER CODE
# --------------------------------------------------

def run_test(s, expected):
    opt = SolutionOptimized()
    greedy = SolutionGreedy()

    r1 = opt.minimumCost(s)
    r2 = greedy.minimumCost(s)

    print(f"s = {s}")
    print(f"Expected: {expected}")
    print(f"Optimized: {r1}")
    print(f"Greedy:    {r2}")
    print("✓ PASS" if r1 == r2 == expected else "✗ FAIL")
    print("-" * 50)


if __name__ == "__main__":
    print("=== Minimum Cost to Make All Characters Equal ===\n")

    run_test("0011", 2)
    run_test("010101", 9)
    run_test("1111", 0)
    run_test("0000", 0)
    run_test("100", 1)

    print("\nSUMMARY")
    print("- Both solutions use the same greedy strategy")
    print("- Optimized version trades clarity for speed")
    print("- Direct greedy version trades speed for readability")
    print("- Both run in O(n) time and O(1) space")

