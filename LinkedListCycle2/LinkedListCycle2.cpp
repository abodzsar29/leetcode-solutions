#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;


/*
This is the solution for the problem "Linked List Cycle II", classed "Medium" on LeetCode. It is found under:
https://leetcode.com/problems/linked-list-cycle-ii/description/
      //
This problem uses the Fast & Slow Pointer technique.

Time Complexity: O(n) where n is the number of nodes in the linked list
Space Complexity: O(1) as we're only using two pointers regardless of the list size
*/

// Definition for singly-linked list
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

// Function to create a linked list from a vector
ListNode* createLinkedList(const vector<int>& values, int cyclePos) {
    if (values.empty()) return nullptr;
    
    ListNode* head = new ListNode(values[0]);
    ListNode* current = head;
    ListNode* cycleNode = nullptr;
    
    // Keep track of cycle position node
    if (cyclePos == 0) cycleNode = head;
    
    // Create the rest of the list
    for (int i = 1; i < values.size(); i++) {
        current->next = new ListNode(values[i]);
        current = current->next;
        
        if (i == cyclePos) cycleNode = current;
    }
    
    // Create cycle if needed
    if (cyclePos != -1 && cycleNode) {
        current->next = cycleNode;
    }
    
    return head;
}

// Function to print linked list (limited to avoid infinite loops)
void printList(ListNode* head, int limit = 20) {
    ListNode* current = head;
    int count = 0;
    
    cout << "List: ";
    
    // Using a set to detect cycles while printing
    unordered_set<ListNode*> visited;
    
    while (current && count < limit) {
        cout << current->val;
        
        // Check if we've already visited this node (cycle detection)
        if (visited.find(current) != visited.end()) {
            cout << " -> ... (cycle detected)";
            break;
        }
        
        visited.insert(current);
        current = current->next;
        
        if (current) cout << " -> ";
        count++;
    }
    
    if (count >= limit && current) {
        cout << " ... (more nodes)";
    }
    
    cout << endl;
}

// Free memory from linked list
void freeList(ListNode* head) {
    unordered_set<ListNode*> visited;
    ListNode* current = head;
    
    while (current && visited.find(current) == visited.end()) {
        visited.insert(current);
        ListNode* temp = current;
        current = current->next;
        delete temp;
    }
}

class Solution {
public:
    ListNode* detectCycle(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head;

        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;

            if (slow == fast) {
                slow = head;

                while (slow != fast) {
                    slow = slow->next;
                    fast = fast->next;
                }

                return slow;
            }
        }

        return nullptr;
    }
};


int main() {
    // Test cases
    vector<vector<int>> testCases = {
        {3, 2, 0, -4},  // cycle at position 1
        {1, 2},         // cycle at position 0
        {1},            // no cycle
        {1, 2, 3, 4, 5} // no cycle
    };
    
    vector<int> cyclePositions = {1, 0, -1, -1};
    
    Solution solution;
    
    for (int i = 0; i < testCases.size(); i++) {
        cout << "\nTest Case " << i+1 << ":" << endl;
        ListNode* head = createLinkedList(testCases[i], cyclePositions[i]);
        
        printList(head);
        
        ListNode* cycleStart = solution.detectCycle(head);
        
        if (cycleStart) {
            cout << "Cycle detected! Starting at node with value: " << cycleStart->val << endl;
        } else {
            cout << "No cycle detected." << endl;
        }
        
        // Free memory
        freeList(head);
    }
    
    return 0;
}
