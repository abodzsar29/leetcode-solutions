from typing import List
import bisect

"""
This is the solution for the problem:
"Snapshot Array" (LeetCode #1146, Medium)

Link:
https://leetcode.com/problems/snapshot-array/

Problem summary:
- Implement a SnapshotArray that supports:
    set(index, val)
    snap() -> returns snap_id
    get(index, snap_id) -> value at index when snapshot was taken
- Efficient implementation must avoid copying the entire array per snapshot.

Core idea:
- For each index, store a list of (snap_id, value) changes.
- set(): append/overwrite change for the current snap_id
- snap(): increment snap_id
- get(): binary search for the last snap_id <= requested
"""


class SnapshotArray:

    def __init__(self, length: int):
        self.snap_id = 0
        # Each index keeps a sorted list of (snap_id, value)
        self.data = [[(0, 0)] for _ in range(length)]

    def set(self, index: int, val: int) -> None:
        if self.data[index][-1][0] == self.snap_id:
            self.data[index][-1] = (self.snap_id, val)
        else:
            self.data[index].append((self.snap_id, val))

    def snap(self) -> int:
        self.snap_id += 1
        return self.snap_id - 1

    def get(self, index: int, snap_id: int) -> int:
        arr = self.data[index]
        i = bisect.bisect_right(arr, (snap_id, float("inf"))) - 1
        return arr[i][1]


# -------------------------------
# Driver code & test harness
# -------------------------------

def run_test(length, operations, expected):
    """
    operations: list of tuples like
        ("set", index, value)
        ("snap",)
        ("get", index, snap_id)
    expected: list of outputs for snap/get operations
    """
    sa = SnapshotArray(length)
    outputs = []

    for op in operations:
        if op[0] == "set":
            _, idx, val = op
            sa.set(idx, val)
        elif op[0] == "snap":
            outputs.append(sa.snap())
        elif op[0] == "get":
            _, idx, sid = op
            outputs.append(sa.get(idx, sid))

    print(f"Length = {length}")
    print(f"Operations = {operations}")
    print(f"Expected: {expected}")
    print(f"Result:   {outputs}")
    print("✓ PASS" if outputs == expected else "✗ FAIL")
    print("-" * 50)


if __name__ == "__main__":
    print("=== Testing SnapshotArray ===\n")

    # Test Case 1: LeetCode example
    run_test(
        3,
        [
            ("set", 0, 5),
            ("snap",),
            ("set", 0, 6),
            ("get", 0, 0)
        ],
        expected=[0, 5]
    )

    # Test Case 2: Multiple snapshots
    run_test(
        2,
        [
            ("set", 1, 7),
            ("snap",),
            ("snap",),
            ("get", 1, 0),
            ("get", 1, 1)
        ],
        expected=[0, 1, 7, 7]
    )

    # Test Case 3: Overwrite within same snapshot
    run_test(
        1,
        [
            ("set", 0, 4),
            ("set", 0, 9),
            ("snap",),
            ("get", 0, 0)
        ],
        expected=[0, 9]
    )

    print("\n=== Algorithm Analysis ===\n")
    print("Time Complexity:")
    print("  - set(): O(1)")
    print("  - snap(): O(1)")
    print("  - get(): O(log k) (binary search per index)")
    print("\nSpace Complexity:")
    print("  - O(total number of updates)")
    print("\nKey Insights:")
    print("  - Store only changes rather than full snapshots")
    print("  - Each index maintains its own version history")
    print("  - Binary search retrieves historical values efficiently")

