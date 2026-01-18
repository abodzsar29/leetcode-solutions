#include <iostream>
#include <vector>

/*
This is the solution for the problem "Remove Duplicates From Sorted List II", classed "Medium" on LeetCode. It is found under:
https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/description/

This problem uses the Dummy Node technique.

Time Complexity: O(n) where n is the number of nodes in the linked list
Space Complexity: O(1) as we're only using two pointers regardless of the list size
*/


// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        // Handle edge case
        if (!head || !head->next) return head;
        
        // Create dummy head
        ListNode* dummy = new ListNode(0);
        dummy->next = head;
        
        // Use prev pointer to track the last non-duplicate node
        ListNode* prev = dummy;
        ListNode* curr = head;
        
        while (curr) {
            // Skip all duplicates
            bool skipNode = false;
            while (curr->next && curr->val == curr->next->val) {
                skipNode = true;
                curr = curr->next;
            }
            
            // If duplicates were found, remove them
            if (skipNode) {
                prev->next = curr->next;
            } else {
                // Only advance prev if no duplicates were found
                prev = curr;
            }
            
            // Move to next node
            curr = curr->next;
        }
        
        // Get the new head
        head = dummy->next;
        
        // Clean up dummy node to avoid memory leak
        delete dummy;
        
        return head;
    }
};

// Helper function to create a linked list from a vector
ListNode* createLinkedList(const std::vector<int>& values) {
    if (values.empty()) return nullptr;
    
    ListNode* head = new ListNode(values[0]);
    ListNode* current = head;
    
    for (size_t i = 1; i < values.size(); ++i) {
        current->next = new ListNode(values[i]);
        current = current->next;
    }
    
    return head;
}

// Helper function to print a linked list
void printLinkedList(ListNode* head) {
    std::cout << "[";
    while (head) {
        std::cout << head->val;
        if (head->next) std::cout << ",";
        head = head->next;
    }
    std::cout << "]" << std::endl;
}

// Helper function to free memory of a linked list
void freeLinkedList(ListNode* head) {
    ListNode* temp;
    while (head) {
        temp = head;
        head = head->next;
        delete temp;
    }
}

int main() {
    // Test case 1: [1,2,3,3,4,4,5]
    std::vector<int> values1 = {1, 2, 3, 3, 4, 4, 5};
    ListNode* list1 = createLinkedList(values1);
    
    std::cout << "Original List 1: ";
    printLinkedList(list1);
    
    Solution solution;
    ListNode* result1 = solution.deleteDuplicates(list1);
    
    std::cout << "After removing duplicates: ";
    printLinkedList(result1);
    
    // Test case 2: [1,1,1,2,3]
    std::vector<int> values2 = {1, 1, 1, 2, 3};
    ListNode* list2 = createLinkedList(values2);
    
    std::cout << "\nOriginal List 2: ";
    printLinkedList(list2);
    
    ListNode* result2 = solution.deleteDuplicates(list2);
    
    std::cout << "After removing duplicates: ";
    printLinkedList(result2);
    
    // Test case 3: [1,2,2]
    std::vector<int> values3 = {1, 2, 2};
    ListNode* list3 = createLinkedList(values3);
    
    std::cout << "\nOriginal List 3: ";
    printLinkedList(list3);
    
    ListNode* result3 = solution.deleteDuplicates(list3);
    
    std::cout << "After removing duplicates: ";
    printLinkedList(result3);
    
    // Free memory
    freeLinkedList(result1);
    freeLinkedList(result2);
    freeLinkedList(result3);
    
    return 0;
}
