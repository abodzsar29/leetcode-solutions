#include <iostream>

/*
This is the solution for the problem "Reverse Linked List", classed "Easy" on LeetCode. It is found under:
https://leetcode.com/problems/reverse-linked-list/

It uses the Fast and Slow Pointers approach for its solution.

Time Complexity: O(n), where n is the size of the list. Each node is visited once.
Space Complexity: O(1), as the modification is done in-place without using any additional data structures.
*/

struct ListNode {
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : val(x), next(next) {}
};


ListNode* reverseList(ListNode* head) {
	ListNode* prev = nullptr;
	ListNode* current = head;
	while (current != nullptr) {
		ListNode* nextNode = current->next;
		current->next = prev;
		prev = current;
		current = nextNode;
	}
	return prev;
}

int main() {


	return 0;
}
