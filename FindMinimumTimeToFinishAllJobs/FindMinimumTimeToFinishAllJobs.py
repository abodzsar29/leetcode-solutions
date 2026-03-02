from typing import List

"""
This is the solution for the problem:
"Minimum Time to Finish All Jobs" (LeetCode #1723, Hard)

Link:
https://leetcode.com/problems/minimum-time-to-finish-all-jobs/

Problem summary:
- You are given an array jobs where jobs[i] is the time required for the ith job.
- There are k workers.
- Each job must be assigned to exactly one worker.
- The time required is the maximum working time among all workers.
- Return the minimum possible maximum working time.

Core idea:
- Binary search the answer (maximum allowed workload).
- Use backtracking (DFS) to check feasibility.
- Sort jobs in descending order for strong pruning.
- Prune symmetric states aggressively.
"""


class Solution:
    def minimumTimeRequired(self, jobs: List[int], k: int) -> int:
        jobs.sort(reverse=True)

        left, right = max(jobs), sum(jobs)

        def can_finish(limit: int) -> bool:
            workloads = [0] * k

            def dfs(index: int) -> bool:
                if index == len(jobs):
                    return True

                for worker in range(k):
                    if workloads[worker] + jobs[index] <= limit:
                        workloads[worker] += jobs[index]
                        if dfs(index + 1):
                            return True
                        workloads[worker] -= jobs[index]

                    # Pruning 1: avoid symmetric states
                    if workloads[worker] == 0:
                        break

                return False

            return dfs(0)

        while left < right:
            mid = (left + right) // 2
            if can_finish(mid):
                right = mid
            else:
                left = mid + 1

        return left


# -------------------------------
# Driver code & test harness
# -------------------------------

def run_test(jobs, k, expected):
    solution = Solution()
    result = solution.minimumTimeRequired(jobs, k)

    print(f"jobs = {jobs}")
    print(f"k = {k}")
    print(f"Expected: {expected}")
    print(f"Result:   {result}")
    print("✓ PASS" if result == expected else "✗ FAIL")
    print("-" * 50)


if __name__ == "__main__":
    print("=== Testing Minimum Time to Finish All Jobs ===\n")

    # Test Case 1: Example from LeetCode
    run_test(
        jobs=[3, 2, 3],
        k=3,
        expected=3
    )

    # Test Case 2: Example from LeetCode
    run_test(
        jobs=[1, 2, 4, 7, 8],
        k=2,
        expected=11
    )

    # Test Case 3: Single worker
    run_test(
        jobs=[5, 3, 8, 2],
        k=1,
        expected=18
    )

    # Test Case 4: More workers than jobs
    run_test(
        jobs=[5, 3],
        k=5,
        expected=5
    )

    print("\n=== Algorithm Analysis ===\n")
    print("Time Complexity:")
    print("  - Binary search over answer: O(log(sum(jobs)))")
    print("  - Backtracking worst case: O(k^n), heavily pruned")
    print("  - Practical performance acceptable since n ≤ 12")
    print("\nSpace Complexity:")
    print("  - O(k) for workloads array")
    print("  - O(n) recursion depth")
    print("\nKey Insights:")
    print("  - Sort jobs descending to fail early")
    print("  - Binary search reduces search space dramatically")
    print("  - Symmetry pruning is critical for passing constraints")
