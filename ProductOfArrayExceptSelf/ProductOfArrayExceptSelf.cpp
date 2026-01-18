#include <iostream>
#include <vector>
#include <algorithm>

/*
This is the solution for the problem "Product of Array Except Self", classed "Medium" on LeetCode. It is found under:
https://leetcode.com/problems/product-of-array-except-self/description/

The problem asks to return an array where each element is the product of all elements in the input array
except the element at that index, without using division and in O(n) time.

Three different approaches are implemented:

1. Optimal Two-Pass Approach (Primary Solution):
   - First pass: Calculate prefix products (product of all elements to the left)
   - Second pass: Calculate suffix products and combine with prefix
   - Time Complexity: O(n), Space Complexity: O(1) extra space (result array doesn't count)

2. Left-Right Arrays Approach:
   - Create separate arrays for left and right products
   - More intuitive but uses extra space
   - Time Complexity: O(n), Space Complexity: O(n)

3. Brute Force Approach (for comparison):
   - For each index, calculate product of all other elements
   - Simple but inefficient
   - Time Complexity: O(n^2), Space Complexity: O(1)
*/

// Primary Solution: Optimal Two-Pass Approach
class SolutionOptimal {
public:
    std::vector<int> productExceptSelf(std::vector<int>& nums) {
        int n = nums.size();
        std::vector<int> result(n, 1);
        
        // First pass: Calculate prefix products
        // result[i] contains product of all elements to the left of i
        int prefix = 1;
        for (int i = 0; i < n; ++i) {
            result[i] = prefix;
            prefix *= nums[i];
        }
        
        // Second pass: Calculate suffix products and combine with prefix
        // Multiply result[i] with product of all elements to the right of i
        int suffix = 1;
        for (int i = n - 1; i >= 0; --i) {
            result[i] *= suffix;
            suffix *= nums[i];
        }
        
        return result;
    }
};

// Alternative Solution: Left-Right Arrays Approach
class SolutionLeftRight {
public:
    std::vector<int> productExceptSelf(std::vector<int>& nums) {
        int n = nums.size();
        std::vector<int> left(n, 1);   // Products of elements to the left
        std::vector<int> right(n, 1);  // Products of elements to the right
        std::vector<int> result(n);
        
        // Fill left array: left[i] = product of all elements to the left of i
        for (int i = 1; i < n; ++i) {
            left[i] = left[i - 1] * nums[i - 1];
        }
        
        // Fill right array: right[i] = product of all elements to the right of i
        for (int i = n - 2; i >= 0; --i) {
            right[i] = right[i + 1] * nums[i + 1];
        }
        
        // Combine left and right products
        for (int i = 0; i < n; ++i) {
            result[i] = left[i] * right[i];
        }
        
        return result;
    }
};

// Brute Force Solution (for comparison and educational purposes)
class SolutionBruteForce {
public:
    std::vector<int> productExceptSelf(std::vector<int>& nums) {
        int n = nums.size();
        std::vector<int> result(n);
        
        // For each index, calculate product of all other elements
        for (int i = 0; i < n; ++i) {
            int product = 1;
            for (int j = 0; j < n; ++j) {
                if (i != j) {
                    product *= nums[j];
                }
            }
            result[i] = product;
        }
        
        return result;
    }
};

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

// Helper function to verify correctness by brute force calculation
std::vector<int> bruteForceVerify(const std::vector<int>& nums) {
    int n = nums.size();
    std::vector<int> result(n);
    
    for (int i = 0; i < n; ++i) {
        int product = 1;
        for (int j = 0; j < n; ++j) {
            if (i != j) {
                product *= nums[j];
            }
        }
        result[i] = product;
    }
    
    return result;
}

// Helper function to demonstrate step-by-step calculation for educational purposes
void demonstrateSteps(const std::vector<int>& nums) {
    int n = nums.size();
    std::cout << "Step-by-step breakdown for input: ";
    printVector(nums, "");
    std::cout << "\n\n";
    
    // Show prefix calculation
    std::cout << "Prefix products (left to right):\n";
    std::vector<int> prefix(n, 1);
    int prefixProduct = 1;
    for (int i = 0; i < n; ++i) {
        prefix[i] = prefixProduct;
        std::cout << "  Index " << i << ": prefix = " << prefix[i];
        if (i > 0) {
            std::cout << " (product of elements before index " << i << ")";
        } else {
            std::cout << " (no elements before index 0)";
        }
        std::cout << "\n";
        prefixProduct *= nums[i];
    }
    
    // Show suffix calculation
    std::cout << "\nSuffix products (right to left):\n";
    std::vector<int> suffix(n, 1);
    int suffixProduct = 1;
    for (int i = n - 1; i >= 0; --i) {
        suffix[i] = suffixProduct;
        std::cout << "  Index " << i << ": suffix = " << suffix[i];
        if (i < n - 1) {
            std::cout << " (product of elements after index " << i << ")";
        } else {
            std::cout << " (no elements after index " << (n-1) << ")";
        }
        std::cout << "\n";
        suffixProduct *= nums[i];
    }
    
    // Show final result
    std::cout << "\nFinal result (prefix * suffix):\n";
    for (int i = 0; i < n; ++i) {
        int result = prefix[i] * suffix[i];
        std::cout << "  Index " << i << ": " << prefix[i] << " * " << suffix[i] << " = " << result << "\n";
    }
    std::cout << "\n";
}

int main() {
    // Create instances of all solution classes
    SolutionOptimal solutionOptimal;
    SolutionLeftRight solutionLeftRight;
    SolutionBruteForce solutionBruteForce;
    
    // Test cases with various scenarios
    std::vector<std::vector<int>> testCases = {
        // Test Case 1: Basic example from LeetCode
        {1, 2, 3, 4},
        
        // Test Case 2: Contains zeros
        {-1, 1, 0, -3, 3},
        
        // Test Case 3: All positive numbers
        {2, 3, 4, 5},
        
        // Test Case 4: Contains negative numbers
        {-1, -2, -3, -4},
        
        // Test Case 5: Mixed positive and negative
        {1, -2, 3, -4, 5},
        
        // Test Case 6: Single zero
        {1, 0, 3, 4},
        
        // Test Case 7: Multiple zeros
        {0, 0, 2, 3},
        
        // Test Case 8: Two elements
        {1, 2},
        
        // Test Case 9: Large numbers
        {10, 20, 30},
        
        // Test Case 10: All ones
        {1, 1, 1, 1}
    };
    
    std::cout << "=== Testing Product of Array Except Self - All Approaches ===\n\n";
    
    // Test each approach
    for (size_t testNum = 0; testNum < testCases.size(); ++testNum) {
        std::vector<int> nums = testCases[testNum];
        
        std::cout << "Test Case " << (testNum + 1) << ":\n";
        printVector(nums, "Input");
        std::cout << "\n";
        
        // Get expected result using brute force verification
        std::vector<int> expected = bruteForceVerify(nums);
        printVector(expected, "Expected");
        std::cout << "\n";
        
        // Test Optimal Two-Pass approach
        {
            std::vector<int> numsCopy = nums;
            std::vector<int> result = solutionOptimal.productExceptSelf(numsCopy);
            printVector(result, "Optimal (2-pass)");
            std::cout << " - " << (result == expected ? "✓ PASS" : "✗ FAIL") << "\n";
        }
        
        // Test Left-Right Arrays approach
        {
            std::vector<int> numsCopy = nums;
            std::vector<int> result = solutionLeftRight.productExceptSelf(numsCopy);
            printVector(result, "Left-Right    ");
            std::cout << " - " << (result == expected ? "✓ PASS" : "✗ FAIL") << "\n";
        }
        
        // Test Brute Force approach
        {
            std::vector<int> numsCopy = nums;
            std::vector<int> result = solutionBruteForce.productExceptSelf(numsCopy);
            printVector(result, "Brute Force   ");
            std::cout << " - " << (result == expected ? "✓ PASS" : "✗ FAIL") << "\n";
        }
        
        std::cout << "\n";
    }
    
    // Demonstrate step-by-step calculation for educational purposes
    std::cout << "=== Step-by-Step Algorithm Demonstration ===\n\n";
    std::vector<int> demoInput = {1, 2, 3, 4};
    demonstrateSteps(demoInput);
    
    // Algorithm complexity analysis
    std::cout << "=== Algorithm Analysis ===\n\n";
    
    std::cout << "1. Optimal Two-Pass Approach (Primary Solution):\n";
    std::cout << "   Time Complexity: O(n)\n";
    std::cout << "     - Two passes through the array: O(n) + O(n) = O(n)\n";
    std::cout << "     - Each operation in the loop is O(1)\n";
    std::cout << "   Space Complexity: O(1) extra space\n";
    std::cout << "     - Only uses constant extra variables (prefix, suffix)\n";
    std::cout << "     - Result array doesn't count as extra space per problem constraints\n";
    std::cout << "   Best for: Production code, optimal time and space\n\n";
    
    std::cout << "2. Left-Right Arrays Approach:\n";
    std::cout << "   Time Complexity: O(n)\n";
    std::cout << "     - Three passes: left array, right array, combination\n";
    std::cout << "     - Still linear time overall\n";
    std::cout << "   Space Complexity: O(n)\n";
    std::cout << "     - Additional left and right arrays of size n\n";
    std::cout << "   Best for: Educational purposes, easier to understand\n\n";
    
    std::cout << "3. Brute Force Approach:\n";
    std::cout << "   Time Complexity: O(n^2)\n";
    std::cout << "     - Nested loops: for each element, iterate through all others\n";
    std::cout << "     - n * (n-1) operations ≈ O(n^2)\n";
    std::cout << "   Space Complexity: O(1) extra space\n";
    std::cout << "     - Only uses constant extra variables\n";
    std::cout << "   Best for: Understanding the problem, small inputs only\n\n";
    
    std::cout << "Key Algorithmic Insights:\n";
    std::cout << "  - The key insight is that product except self = prefix product * suffix product\n";
    std::cout << "  - Prefix products: cumulative product from left to current index (exclusive)\n";
    std::cout << "  - Suffix products: cumulative product from right to current index (exclusive)\n";
    std::cout << "  - Two-pass optimization eliminates need for separate arrays\n";
    std::cout << "  - Handle zeros carefully: one zero makes most products zero, multiple zeros make all zero\n";
    std::cout << "  - No division operator needed, satisfying the problem constraint\n\n";
    
    std::cout << "Special Cases Handling:\n";
    std::cout << "  - Single zero: Only the zero's position gets non-zero product\n";
    std::cout << "  - Multiple zeros: All positions get zero product\n";
    std::cout << "  - Negative numbers: Sign changes propagate correctly through products\n";
    std::cout << "  - Large numbers: May cause integer overflow in practice\n";
    
    return 0;
}
