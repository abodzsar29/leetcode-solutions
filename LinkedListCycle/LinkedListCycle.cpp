#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
This is the solution for the problem "Linked List Cycle", classed "Easy" on LeetCode. It is found under:
https://leetcode.com/problems/linked-list-cycle/description/?envType=study-plan-v2&envId=top-interview-150

It is included in the "Top Interview 150" problem set, which covers comprehensive interview topics.
*/

// Approach 1: Appending each Node into a vector, then using find() to check if duplicates exist
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
 
class Solution {
public:
    bool hasCycle(ListNode* head) {
        vector<ListNode*> members = {};
        while (head != nullptr) {
            members.push_back(head);
            head = head->next;
            if (find(members.begin(), members.end(), head) != members.end()) {
                return true;
            }
        }
        return false;
    }
};

// Approach 2: Fast and Slow Pointer Approach
class Solution {
public:
    bool hasCycle(ListNode* head) {
        ListNode* fast = head;
        ListNode* slow = head;
        while (fast != NULL && fast->next != NULL) {  // Logic makes sure there are at least 2 Nodes in List
            slow = slow->next;
            fast = fast->next->next;
            if (fast == slow) return true;
        }
        return false;
    }
};



int main() {

}

