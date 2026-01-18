#include <iostream>
#include <vector>

/*
This is the solution for the problem "Add Two Numbers", classed "Medium" on LeetCode. It is found under:
https://leetcode.com/problems/add-two-numbers/description/

The problem involves adding two numbers represented as linked lists, where each node contains a single digit
and the digits are stored in reverse order (least significant digit first).

Algorithm Approach:
- Uses a dummy head node to simplify list construction
- Iterates through both lists simultaneously, handling different lengths gracefully
- Maintains a carry variable for digit addition overflow
- Creates new nodes for the result list as we traverse

Time Complexity: O(max(m, n)), where m and n are the lengths of the two input lists.
Space Complexity: O(max(m, n)), for the output list (not counting input space).
*/

// Definition for singly-linked list node
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// Solution class implementing the add two numbers algorithm
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        // Create dummy head to simplify list construction
        ListNode* dummyHead = new ListNode(0);
        ListNode* tail = dummyHead;
        int carry = 0;

        // Continue while there are digits in either list or carry exists
        while (l1 != nullptr || l2 != nullptr || carry != 0) {
            // Get digit from each list (0 if list is exhausted)
            int digit1 = (l1 != nullptr) ? l1->val : 0;
            int digit2 = (l2 != nullptr) ? l2->val : 0;

            // Calculate sum and extract digit and carry
            int sum = digit1 + digit2 + carry;
            int digit = sum % 10;  // Current digit for result
            carry = sum / 10;      // Carry for next iteration

            // Create new node for current digit and append to result
            ListNode* newNode = new ListNode(digit);
            tail->next = newNode;
            tail = tail->next;

            // Move to next nodes in input lists (if they exist)
            l1 = (l1 != nullptr) ? l1->next : nullptr;
            l2 = (l2 != nullptr) ? l2->next : nullptr;
        }

        // Extract result and clean up dummy head
        ListNode* result = dummyHead->next;
        delete dummyHead;
        return result;
    }
};

// Helper function to create a linked list from a vector
ListNode* createList(const std::vector<int>& digits) {
    if (digits.empty()) return nullptr;
    
    ListNode* head = new ListNode(digits[0]);
    ListNode* current = head;
    
    for (size_t i = 1; i < digits.size(); ++i) {
        current->next = new ListNode(digits[i]);
        current = current->next;
    }
    
    return head;
}

// Helper function to convert linked list to vector for easy printing
std::vector<int> listToVector(ListNode* head) {
    std::vector<int> result;
    ListNode* current = head;
    
    while (current != nullptr) {
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

// Helper function to convert vector to number for verification
long long vectorToNumber(const std::vector<int>& digits) {
    long long number = 0;
    long long multiplier = 1;
    
    for (int digit : digits) {
        number += digit * multiplier;
        multiplier *= 10;
    }
    
    return number;
}

// Helper function to clean up linked list memory
void deleteList(ListNode* head) {
    while (head != nullptr) {
        ListNode* temp = head;
        head = head->next;
        delete temp;
    }
}

int main() {
    // Create an instance of the Solution class
    Solution solution;
    
    // Test cases with input lists and expected outputs
    std::vector<std::pair<std::pair<std::vector<int>, std::vector<int>>, std::vector<int>>> testCases = {
        // Test Case 1: 342 + 465 = 807 (represented as [2,4,3] + [5,6,4] = [7,0,8])
        {{{2, 4, 3}, {5, 6, 4}}, {7, 0, 8}},
        
        // Test Case 2: 0 + 0 = 0
        {{{0}, {0}}, {0}},
        
        // Test Case 3: 9999999 + 9999 = 10009998 (with multiple carries)
        {{{9, 9, 9, 9, 9, 9, 9}, {9, 9, 9, 9}}, {8, 9, 9, 9, 0, 0, 0, 1}},
        
        // Test Case 4: Different lengths - 99 + 1 = 100
        {{{9, 9}, {1}}, {0, 0, 1}},
        
        // Test Case 5: Single digits - 5 + 5 = 10
        {{{5}, {5}}, {0, 1}},
        
        // Test Case 6: One empty case simulation - 123 + 0 = 123
        {{{3, 2, 1}, {0}}, {3, 2, 1}},
        
        // Test Case 7: Large carry chain - 999 + 1 = 1000
        {{{9, 9, 9}, {1}}, {0, 0, 0, 1}}
    };
    
    std::cout << "=== Testing Add Two Numbers Algorithm ===\n\n";
    
    // Iterate through test cases
    for (size_t testNum = 0; testNum < testCases.size(); ++testNum) {
        const auto& testCase = testCases[testNum];
        const std::vector<int>& list1Digits = testCase.first.first;
        const std::vector<int>& list2Digits = testCase.first.second;
        const std::vector<int>& expectedResult = testCase.second;
        
        std::cout << "Test Case " << (testNum + 1) << ":\n";
        
        // Print input in both list and number format
        printVector(list1Digits, "List 1");
        std::cout << " (represents " << vectorToNumber(list1Digits) << ")\n";
        
        printVector(list2Digits, "List 2");
        std::cout << " (represents " << vectorToNumber(list2Digits) << ")\n";
        
        printVector(expectedResult, "Expected");
        std::cout << " (represents " << vectorToNumber(expectedResult) << ")\n";
        
        // Create linked lists from vectors
        ListNode* l1 = createList(list1Digits);
        ListNode* l2 = createList(list2Digits);
        
        // Call the solution
        ListNode* result = solution.addTwoNumbers(l1, l2);
        
        // Convert result back to vector for comparison
        std::vector<int> resultVector = listToVector(result);
        
        // Print actual result
        printVector(resultVector, "Actual  ");
        std::cout << " (represents " << vectorToNumber(resultVector) << ")\n";
        
        // Verify correctness
        bool isCorrect = (resultVector == expectedResult);
        std::cout << "Result: " << (isCorrect ? "✓ PASS" : "✗ FAIL") << "\n";
        
        // Additional verification using arithmetic
        long long num1 = vectorToNumber(list1Digits);
        long long num2 = vectorToNumber(list2Digits);
        long long expectedSum = num1 + num2;
        long long actualSum = vectorToNumber(resultVector);
        
        std::cout << "Arithmetic verification: " << num1 << " + " << num2 << " = " << expectedSum;
        std::cout << " (got " << actualSum << ") ";
        std::cout << (expectedSum == actualSum ? "✓" : "✗") << "\n\n";
        
        // Clean up memory
        deleteList(l1);
        deleteList(l2);
        deleteList(result);
    }
    
    // Algorithm complexity analysis
    std::cout << "=== Algorithm Analysis ===\n";
    std::cout << "Time Complexity: O(max(m, n))\n";
    std::cout << "  - m and n are the lengths of the two input lists\n";
    std::cout << "  - We traverse each list exactly once\n";
    std::cout << "  - Each node is processed in constant time\n\n";
    
    std::cout << "Space Complexity: O(max(m, n))\n";
    std::cout << "  - Output list length is at most max(m, n) + 1\n";
    std::cout << "  - Additional space for carry variable is O(1)\n";
    std::cout << "  - Dummy head technique simplifies implementation\n\n";
    
    std::cout << "Key Algorithmic Insights:\n";
    std::cout << "  - Dummy head eliminates special case handling for first node\n";
    std::cout << "  - Carry propagation handles overflow naturally\n";
    std::cout << "  - Graceful handling of lists of different lengths\n";
    std::cout << "  - Single pass through both lists ensures optimal efficiency\n";
    
    return 0;
}
