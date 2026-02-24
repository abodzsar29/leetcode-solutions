/*
This is the solution for the problem:
"Find in Mountain Array" (LeetCode #1095, Hard)

Link:
https://leetcode.com/problems/find-in-mountain-array/

Problem summary:
- A mountain array increases strictly, then decreases strictly.
- You can only access values through MountainArray API:
      get(index)
      length()
- Return the minimum index where target exists.
- If not found, return -1.

Core idea:
- Binary search to find peak index
- Binary search left (ascending)
- Binary search right (descending)
- Cache API calls to reduce repeated access
*/

#include <bits/stdc++.h>
using namespace std;

// -------------------------------
// Mock MountainArray for testing
// -------------------------------
class MountainArray {
private:
    vector<int> arr;

public:
    MountainArray(vector<int> v) : arr(v) {}

    int get(int index) {
        return arr[index];
    }

    int length() {
        return (int)arr.size();
    }
};

class Solution {
public:
    int findInMountainArray(int target, MountainArray &mountainArr) {
        int n = mountainArr.length();
        unordered_map<int,int> cache;

        auto getVal = [&](int idx) {
            if (cache.count(idx)) return cache[idx];
            return cache[idx] = mountainArr.get(idx);
        };

        // Step 1: Find peak
        int lo = 0, hi = n - 1;
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            if (getVal(mid) < getVal(mid + 1))
                lo = mid + 1;
            else
                hi = mid;
        }
        int peak = lo;

        auto binSearch = [&](int L, int R, bool inc) {
            while (L <= R) {
                int mid = L + (R - L) / 2;
                int v = getVal(mid);

                if (v == target) return mid;

                if (inc) {
                    if (v < target) L = mid + 1;
                    else R = mid - 1;
                } else {
                    if (v < target) R = mid - 1;
                    else L = mid + 1;
                }
            }
            return -1;
        };

        // Step 2: Search left
        int ans = binSearch(0, peak, true);
        if (ans != -1) return ans;

        // Step 3: Search right
        return binSearch(peak + 1, n - 1, false);
    }
};

// -------------------------------
// Driver code & test harness
// -------------------------------

void run_test(vector<int> arr, int target, int expected) {
    MountainArray mountain(arr);
    Solution sol;

    int result = sol.findInMountainArray(target, mountain);

    cout << "Array = [ ";
    for (int x : arr) cout << x << " ";
    cout << "]\n";

    cout << "Target:   " << target << "\n";
    cout << "Expected: " << expected << "\n";
    cout << "Result:   " << result << "\n";
    cout << (result == expected ? "PASS" : "FAIL") << "\n";
    cout << string(50, '-') << "\n";
}

int main() {
    cout << "=== Testing Find in Mountain Array ===\n\n";

    run_test({1,2,3,4,5,3,1}, 3, 2);
    run_test({0,1,2,4,2,1}, 3, -1);
    run_test({1,5,2}, 2, 2);
    run_test({0,5,3,1}, 1, 3);

    cout << "\n=== Algorithm Analysis ===\n\n";
    cout << "Time Complexity: O(log n)\n";
    cout << "Space Complexity: O(log n) cache\n";
}
