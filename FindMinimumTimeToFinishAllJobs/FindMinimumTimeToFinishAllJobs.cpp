#include <bits/stdc++.h>
using namespace std;

/*
This is the solution for the problem:
"Minimum Time to Finish All Jobs" (LeetCode #1723, Hard)

Link:
https://leetcode.com/problems/minimum-time-to-finish-all-jobs/

Problem summary:
- You are given an array jobs where jobs[i] is the time required for the ith job.
- There are k workers.
- Each job must be assigned to exactly one worker.
- The total time is the maximum working time among all workers.
- Return the minimum possible maximum working time.

Core idea:
- Binary search the answer (maximum allowed workload).
- Use DFS/backtracking to test feasibility.
- Sort jobs descending for stronger pruning.
- Skip symmetric worker states to reduce branching.
*/


class Solution {
public:
    bool canFinish(vector<int>& jobs, vector<int>& workload,
                   int idx, int limit) {
        if (idx == jobs.size()) return true;

        int cur = jobs[idx];

        for (int i = 0; i < workload.size(); ++i) {
            if (workload[i] + cur <= limit) {
                workload[i] += cur;

                if (canFinish(jobs, workload, idx + 1, limit))
                    return true;

                workload[i] -= cur;
            }

            // Pruning: avoid symmetric states
            if (workload[i] == 0)
                break;
        }

        return false;
    }

    int minimumTimeRequired(vector<int>& jobs, int k) {
        sort(jobs.rbegin(), jobs.rend());

        int left = jobs[0];
        int right = accumulate(jobs.begin(), jobs.end(), 0);

        while (left < right) {
            int mid = left + (right - left) / 2;
            vector<int> workload(k, 0);

            if (canFinish(jobs, workload, 0, mid))
                right = mid;
            else
                left = mid + 1;
        }

        return left;
    }
};


// -------------------------------
// Driver code & test harness
// -------------------------------

void run_test(vector<int> jobs, int k, int expected) {
    Solution solution;
    int result = solution.minimumTimeRequired(jobs, k);

    cout << "jobs = [";
    for (int i = 0; i < jobs.size(); ++i) {
        cout << jobs[i];
        if (i + 1 < jobs.size()) cout << ", ";
    }
    cout << "]\n";

    cout << "k = " << k << "\n";
    cout << "Expected: " << expected << "\n";
    cout << "Result:   " << result << "\n";
    cout << (result == expected ? "✓ PASS" : "✗ FAIL") << "\n";
    cout << string(50, '-') << "\n";
}


int main() {
    cout << "=== Testing Minimum Time to Finish All Jobs ===\n\n";

    // Test Case 1: Example from LeetCode
    run_test({3, 2, 3}, 3, 3);

    // Test Case 2: Example from LeetCode
    run_test({1, 2, 4, 7, 8}, 2, 11);

    // Test Case 3: Single worker
    run_test({5, 3, 8, 2}, 1, 18);

    // Test Case 4: More workers than jobs
    run_test({5, 3}, 5, 5);

    cout << "\n=== Algorithm Analysis ===\n\n";
    cout << "Time Complexity:\n";
    cout << "  - Binary search: O(log(sum(jobs)))\n";
    cout << "  - DFS worst case: O(k^n), heavily pruned\n";
    cout << "  - Practical performance good since n <= 12\n\n";

    cout << "Space Complexity:\n";
    cout << "  - O(k) for workloads array\n";
    cout << "  - O(n) recursion stack\n\n";

    cout << "Key Insights:\n";
    cout << "  - Sort jobs descending to fail early\n";
    cout << "  - Binary search reduces answer space\n";
    cout << "  - Symmetry pruning is critical for efficiency\n";

    return 0;
}
