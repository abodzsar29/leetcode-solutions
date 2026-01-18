#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

/*
This is the solution for the problem "Merge k Sorted Lists", classed "Hard" on LeetCode. It is found under:
https://leetcode.com/problems/merge-k-sorted-lists/description/

The problem involves merging k sorted linked lists into one sorted linked list.

Three different approaches are implemented:

1. Divide and Conquer (Primary Solution):
   - Recursively pairs up lists and merges them
   - Uses binary tree-like structure for merging
   - Time Complexity: O(N * log k), where N is total number of nodes and k is number of lists
   - Space Complexity: O(log k) for recursion stack

2. Priority Queue/Min-Heap Approach:
   - Uses min-heap to always get the smallest element
   - Efficient for large k with small lists
   - Time Complexity: O(N * log k)
   - Space Complexity: O(k) for the heap

3. Brute Force (for comparison):
   - Collect all values, sort them, create new list
   - Simple but not optimal for linked list structure
   - Time Complexity: O(N * log N)
   - Space Complexity: O(N)
*/

// Definition for singly-linked list node
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// Primary Solution: Divide and Conquer Approach
class SolutionDivideConquer {
public:
    ListNode* mergeKLists(std::vector<ListNode*>& lists) {
        if (lists.empty()) {
            return nullptr;
        }
        return divideAndConquer(0, lists.size() - 1, lists);
    }

private:
    // Recursively divide the problem into smaller subproblems
    ListNode* divideAndConquer(int left, int right, std::vector<ListNode*>& lists) {
        // Base case: single list
        if (left == right) {
            return lists[left];
        }
        
        // Divide: split the range in half
        int mid = left + (right - left) / 2;
        ListNode* l1 = divideAndConquer(left, mid, lists);
        ListNode* l2 = divideAndConquer(mid + 1, right, lists);
        
        // Conquer: merge the two halves
        return merge(l1, l2);
    }

    // Merge two sorted linked lists recursively
    ListNode* merge(ListNode* l1, ListNode* l2) {
        // Base cases
        if (!l1) return l2;
        if (!l2) return l1;
        
        // Recursive case: choose smaller head and recurse
        if (l1->val < l2->val) {
            l1->next = merge(l1->next, l2);
            return l1;
        } else {
            l2->next = merge(l1, l2->next);
            return l2;
        }
    }
};

// Alternative Solution: Priority Queue (Min-Heap) Approach
class SolutionPriorityQueue {
public:
    ListNode* mergeKLists(std::vector<ListNode*>& lists) {
        // Custom comparator for min-heap based on node values
        auto compare = [](ListNode* a, ListNode* b) {
            return a->val > b->val; // Min-heap: smaller values have higher priority
        };
        
        std::priority_queue<ListNode*, std::vector<ListNode*>, decltype(compare)> pq(compare);
        
        // Initialize heap with head of each non-empty list
        for (ListNode* head : lists) {
            if (head) {
                pq.push(head);
            }
        }
        
        // Dummy head to simplify list construction
        ListNode dummy(0);
        ListNode* tail = &dummy;
        
        // Process nodes in sorted order
        while (!pq.empty()) {
            // Get the smallest node
            ListNode* smallest = pq.top();
            pq.pop();
            
            // Add to result list
            tail->next = smallest;
            tail = tail->next;
            
            // Add next node from the same list to heap
            if (smallest->next) {
                pq.push(smallest->next);
            }
        }
        
        return dummy.next;
    }
};

// Brute Force Solution (for comparison)
class SolutionBruteForce {
public:
    ListNode* mergeKLists(std::vector<ListNode*>& lists) {
        std::vector<int> values;
        
        // Collect all values from all lists
        for (ListNode* head : lists) {
            ListNode* current = head;
            while (current) {
                values.push_back(current->val);
                current = current->next;
            }
        }
        
        // Sort all values
        std::sort(values.begin(), values.end());
        
        // Create new sorted list
        if (values.empty()) return nullptr;
        
        ListNode* head = new ListNode(values[0]);
        ListNode* current = head;
        
        for (size_t i = 1; i < values.size(); ++i) {
            current->next = new ListNode(values[i]);
            current = current->next;
        }
        
        return head;
    }
};

// Helper function to create a linked list from a vector
ListNode* createList(const std::vector<int>& values) {
    if (values.empty()) return nullptr;
    
    ListNode* head = new ListNode(values[0]);
    ListNode* current = head;
    
    for (size_t i = 1; i < values.size(); ++i) {
        current->next = new ListNode(values[i]);
        current = current->next;
    }
    
    return head;
}

// Helper function to convert linked list to vector for printing
std::vector<int> listToVector(ListNode* head) {
    std::vector<int> result;
    ListNode* current = head;
    
    while (current) {
        result.push_back(current->val);
        current = current->next;
    }
    
    return result;
}

// Helper function to print a vector
void printVector(const std::vector<int>& vec, const std::string& label) {
    std::cout << label << ": [";
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i];
        if (i != vec.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "]";
}

// Helper function to print multiple lists
void printLists(const std::vector<std::vector<int>>& inputLists) {
    std::cout << "Input Lists:\n";
    for (size_t i = 0; i < inputLists.size(); ++i) {
        std::cout << "  List " << (i + 1) << ": [";
        for (size_t j = 0; j < inputLists[i].size(); ++j) {
            std::cout << inputLists[i][j];
            if (j != inputLists[i].size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << "]\n";
    }
}

// Helper function to clean up linked list memory
void deleteList(ListNode* head) {
    while (head) {
        ListNode* temp = head;
        head = head->next;
        delete temp;
    }
}

// Helper function to create deep copy of lists for multiple tests
std::vector<ListNode*> createListsCopy(const std::vector<std::vector<int>>& inputLists) {
    std::vector<ListNode*> lists;
    for (const auto& listValues : inputLists) {
        lists.push_back(createList(listValues));
    }
    return lists;
}

int main() {
    // Create instances of all solution classes
    SolutionDivideConquer solutionDC;
    SolutionPriorityQueue solutionPQ;
    SolutionBruteForce solutionBF;
    
    // Test cases with input lists and expected outputs
    std::vector<std::pair<std::vector<std::vector<int>>, std::vector<int>>> testCases = {
        // Test Case 1: Basic example
        {{{1, 4, 5}, {1, 3, 4}, {2, 6}}, {1, 1, 2, 3, 4, 4, 5, 6}},
        
        // Test Case 2: Empty lists
        {{}, {}},
        
        // Test Case 3: Single empty list
        {{{}, {}}, {}},
        
        // Test Case 4: Single non-empty list
        {{{1, 2, 3}}, {1, 2, 3}},
        
        // Test Case 5: Lists with single elements
        {{{1}, {2}, {3}}, {1, 2, 3}},
        
        // Test Case 6: Overlapping ranges
        {{{1, 2, 3}, {2, 3, 4}, {3, 4, 5}}, {1, 2, 2, 3, 3, 3, 4, 4, 5}},
        
        // Test Case 7: Different lengths
        {{{1, 10, 20}, {2}, {3, 4, 5, 6, 7, 8, 9}}, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 20}},
        
        // Test Case 8: Negative numbers
        {{{-2, -1, 1}, {-3, 0, 2}}, {-3, -2, -1, 0, 1, 2}}
    };
    
    std::cout << "=== Testing Merge k Sorted Lists - All Approaches ===\n\n";
    
    // Test each approach
    for (size_t testNum = 0; testNum < testCases.size(); ++testNum) {
        const auto& testCase = testCases[testNum];
        const std::vector<std::vector<int>>& inputLists = testCase.first;
        const std::vector<int>& expected = testCase.second;
        
        std::cout << "Test Case " << (testNum + 1) << ":\n";
        printLists(inputLists);
        printVector(expected, "Expected");
        std::cout << "\n\n";
        
        // Test Divide and Conquer approach
        {
            std::vector<ListNode*> lists = createListsCopy(inputLists);
            ListNode* result = solutionDC.mergeKLists(lists);
            std::vector<int> resultVector = listToVector(result);
            
            printVector(resultVector, "Divide & Conquer");
            std::cout << " - " << (resultVector == expected ? "✓ PASS" : "✗ FAIL") << "\n";
            
            deleteList(result);
        }
        
        // Test Priority Queue approach
        {
            std::vector<ListNode*> lists = createListsCopy(inputLists);
            ListNode* result = solutionPQ.mergeKLists(lists);
            std::vector<int> resultVector = listToVector(result);
            
            printVector(resultVector, "Priority Queue ");
            std::cout << " - " << (resultVector == expected ? "✓ PASS" : "✗ FAIL") << "\n";
            
            deleteList(result);
        }
        
        // Test Brute Force approach
        {
            std::vector<ListNode*> lists = createListsCopy(inputLists);
            ListNode* result = solutionBF.mergeKLists(lists);
            std::vector<int> resultVector = listToVector(result);
            
            printVector(resultVector, "Brute Force    ");
            std::cout << " - " << (resultVector == expected ? "✓ PASS" : "✗ FAIL") << "\n";
            
            deleteList(result);
            // Clean up input lists for brute force (it doesn't modify them)
            for (ListNode* head : lists) {
                deleteList(head);
            }
        }
        
        std::cout << "\n";
    }
    
    // Algorithm complexity analysis
    std::cout << "=== Algorithm Analysis ===\n\n";
    
    std::cout << "1. Divide and Conquer Approach (Primary Solution):\n";
    std::cout << "   Time Complexity: O(N * log k)\n";
    std::cout << "     - N = total number of nodes across all lists\n";
    std::cout << "     - k = number of lists\n";
    std::cout << "     - Each merge operation: O(N), performed log k times\n";
    std::cout << "   Space Complexity: O(log k)\n";
    std::cout << "     - Recursion stack depth is log k\n";
    std::cout << "   Best for: General case, optimal time complexity\n\n";
    
    std::cout << "2. Priority Queue (Min-Heap) Approach:\n";
    std::cout << "   Time Complexity: O(N * log k)\n";
    std::cout << "     - N insertions/deletions from heap of size k\n";
    std::cout << "     - Each heap operation: O(log k)\n";
    std::cout << "   Space Complexity: O(k)\n";
    std::cout << "     - Heap stores at most k nodes\n";
    std::cout << "   Best for: Large k with memory constraints\n\n";
    
    std::cout << "3. Brute Force Approach:\n";
    std::cout << "   Time Complexity: O(N * log N)\n";
    std::cout << "     - Collecting values: O(N)\n";
    std::cout << "     - Sorting all values: O(N * log N)\n";
    std::cout << "     - Creating result list: O(N)\n";
    std::cout << "   Space Complexity: O(N)\n";
    std::cout << "     - Additional array to store all values\n";
    std::cout << "   Best for: Educational purposes only\n\n";
    
    std::cout << "Key Algorithmic Insights:\n";
    std::cout << "  - Divide and Conquer leverages the tree structure for optimal merging\n";
    std::cout << "  - Priority Queue maintains the smallest element efficiently\n";
    std::cout << "  - Both optimal approaches achieve O(N * log k) complexity\n";
    std::cout << "  - Choice depends on memory constraints and implementation preferences\n";
    
    return 0;
}
