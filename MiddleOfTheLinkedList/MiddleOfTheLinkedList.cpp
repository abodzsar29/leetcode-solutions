#include <iostream>

/*
This is the solution for the problem "Middle of the Linked List", classed "Easy" on LeetCode. It is found under:
https://leetcode.com/problems/middle-of-the-linked-list/

It uses the Fast and Slow Pointers approach for its solution.

Time Complexity: O(n), where n is the length of the input array. The algorithm iterates through the array once.
Space Complexity: O(1), as the modification is done in-place without using any additional data structures.
*/

//Node:
struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {};
    ListNode(int x) : val(x), next(nullptr) {};
    ListNode(int x, ListNode* next) : val(x), next(next) {};
};

class Solution {
public:
    ListNode* middleNode(ListNode* head) {
        ListNode* fast = head;
        ListNode* slow = head;
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;
    }
};
// If there are 2 nodes in the list, fast jumps to the ->next of the second node which is nullptr.
// This makes the while loop's condition false and the function returns the position of the slow pointer

int main()
{
    std::cout << "Hello World!\n";
}
