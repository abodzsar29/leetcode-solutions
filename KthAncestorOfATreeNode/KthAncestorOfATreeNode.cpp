#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

/*
 * LeetCode 1483 — Kth Ancestor of a Tree Node
 * Binary Lifting solution + full driver tests
 */

class TreeAncestor {
private:
    int LOG;
    vector<vector<int>> up;

public:
    TreeAncestor(int n, vector<int>& parent) {
        LOG = ceil(log2(n)) + 1;
        up.assign(LOG, vector<int>(n, -1));

        for (int i = 0; i < n; i++)
            up[0][i] = parent[i];

        for (int j = 1; j < LOG; j++) {
            for (int i = 0; i < n; i++) {
                int prev = up[j-1][i];
                if (prev != -1)
                    up[j][i] = up[j-1][prev];
            }
        }
    }

    int getKthAncestor(int node, int k) {
        for (int j = 0; j < LOG && node != -1; j++) {
            if (k & (1 << j))
                node = up[j][node];
        }
        return node;
    }
};

int main() {

    /*
     * Tree:
     *          0
     *       /  |  \
     *      1   2   3
     *     / \
     *    4   5
     */

    vector<int> parent = {-1,0,0,0,1,1};
    int n = parent.size();

    TreeAncestor solver(n, parent);

    struct Test {
        int node;
        int k;
        int expected;
    };

    vector<Test> tests = {
        {5,1,1},
        {5,2,0},
        {5,3,-1},
        {4,1,1},
        {4,2,0},
        {3,1,0}
    };

    int passed = 0;

    for (int i = 0; i < tests.size(); i++) {
        int result = solver.getKthAncestor(tests[i].node, tests[i].k);

        cout << "Test " << i+1
             << " | node=" << tests[i].node
             << " k=" << tests[i].k
             << " -> result=" << result
             << " expected=" << tests[i].expected;

        if (result == tests[i].expected) {
            cout << "  PASS\n";
            passed++;
        } else {
            cout << "  FAIL\n";
        }
    }

    cout << "\nPassed " << passed << " / " << tests.size() << " tests\n";

    return 0;
}

