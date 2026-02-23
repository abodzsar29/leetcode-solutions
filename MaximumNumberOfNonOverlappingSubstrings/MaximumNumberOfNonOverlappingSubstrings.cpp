#include <bits/stdc++.h>
using namespace std;

/*
This is the solution for the problem:
"Maximum Number of Non-Overlapping Substrings" (LeetCode #1520, Hard)

Link:
https://leetcode.com/problems/maximum-number-of-non-overlapping-substrings/

Problem summary:
- Given a string s, find the maximum number of non-overlapping substrings
  such that each substring contains all occurrences of every character inside it.
- If multiple answers exist, choose the one with minimum total length.

Core idea:
- Record first and last occurrence for each character.
- For every first occurrence position, attempt to build the minimal valid interval.
- Collect all valid intervals.
- Greedily select non-overlapping intervals by earliest ending index.
*/

class Solution {
public:
    vector<string> maxNumOfSubstrings(string s) {
        int n = (int)s.size();
        const int A = 26;

        vector<int> first(A, n), last(A, -1);

        for (int i = 0; i < n; ++i) {
            int c = s[i] - 'a';
            first[c] = min(first[c], i);
            last[c]  = max(last[c], i);
        }

        vector<pair<int,int>> intervals;

        // Build candidate intervals
        for (int i = 0; i < n; ++i) {
            int c0 = s[i] - 'a';
            if (i != first[c0]) continue;

            int l = i;
            int r = last[c0];
            bool ok = true;

            for (int j = l; j <= r; ++j) {
                int c = s[j] - 'a';
                if (first[c] < l) {
                    ok = false;
                    break;
                }
                r = max(r, last[c]);
            }

            if (ok) intervals.push_back({l, r});
        }

        // Greedy: pick intervals with earliest end
        sort(intervals.begin(), intervals.end(),
             [](const pair<int,int>& a, const pair<int,int>& b) {
                 if (a.second != b.second)
                     return a.second < b.second;
                 return a.first < b.first;
             });

        vector<string> ans;
        int prevEnd = -1;

        for (auto &[l, r] : intervals) {
            if (l > prevEnd) {
                ans.push_back(s.substr(l, r - l + 1));
                prevEnd = r;
            }
        }

        return ans;
    }
};

// --------------------------------
// Driver code & test harness
// --------------------------------

void run_test(const string& s, const vector<string>& expected) {
    Solution solution;
    vector<string> result = solution.maxNumOfSubstrings(s);

    cout << "s = \"" << s << "\"" << endl;

    cout << "Expected: [";
    for (int i = 0; i < (int)expected.size(); ++i) {
        cout << "\"" << expected[i] << "\"";
        if (i + 1 < (int)expected.size()) cout << ", ";
    }
    cout << "]" << endl;

    cout << "Result:   [";
    for (int i = 0; i < (int)result.size(); ++i) {
        cout << "\"" << result[i] << "\"";
        if (i + 1 < (int)result.size()) cout << ", ";
    }
    cout << "]" << endl;

    cout << ((result == expected) ? "✓ PASS" : "✗ FAIL") << endl;
    cout << string(50, '-') << endl;
}

int main() {
    cout << "=== Testing Maximum Number of Non-Overlapping Substrings ===\n\n";

    // Test Case 1: LeetCode example
    run_test(
        "adefaddaccc",
        {"e", "f", "ccc"}
    );

    // Test Case 2: Single large valid substring
    run_test(
        "abbaccd",
        {"bb", "cc", "d"}
    );

    // Test Case 3: All unique chars
    run_test(
        "abc",
        {"a", "b", "c"}
    );

    // Test Case 4: Entire string required
    run_test(
        "abab",
        {"abab"}
    );

    cout << "\n=== Algorithm Analysis ===\n\n";

    cout << "Time Complexity:\n";
    cout << "  - Building first/last arrays: O(n)\n";
    cout << "  - Interval expansion: O(n) overall (alphabet limited to 26)\n";
    cout << "  - Sorting intervals: O(26 log 26) ~ O(1)\n";
    cout << "  - Total: O(n)\n\n";

    cout << "Space Complexity:\n";
    cout << "  - O(1) auxiliary space (excluding output)\n\n";

    cout << "Key Insights:\n";
    cout << "  - Only start intervals at first occurrences\n";
    cout << "  - Expand interval until it contains all characters inside it\n";
    cout << "  - Greedy interval scheduling maximizes count of substrings\n";

    return 0;
}
