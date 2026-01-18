#include <iostream>
#include <unordered_map>
#include <vector>
#include <chrono>
using namespace std;

/*
This is the solution for the problem "Fibonacci Number", classed "Easy" on LeetCode. It is found under:
https://leetcode.com/problems/fibonacci-number/description/

Below are two different dynamic programming approaches to solve this problem:
1. Memoization (Top-down): Recursive approach with caching of results
2. Tabulation (Bottom-up): Iterative approach that builds up the solution

Both have O(n) time complexity, but they differ in their execution patterns and practical performance.
*/

// Solution 1: Dynamic Programming with Memoization (Top-down approach)
class SolutionMemoization {
public:
    int fib(int n) {
        unordered_map<int, int> hashMap = {
            {0,0},
            {1,1}
        };
        return fibDP(n, hashMap);
    }
    
    // Recursive helper function with memoization
    int fibDP(int n, unordered_map<int, int>& hashMap) {
        // If we've already calculated this value, return it from cache
        if (hashMap.find(n) != hashMap.end()) {
            return hashMap[n];
        }
        // Otherwise calculate it and store in cache
        hashMap[n] = fibDP(n-1, hashMap) + fibDP(n-2, hashMap);
        return hashMap[n];
    }
};

// Solution 2: Dynamic Programming with Tabulation (Bottom-up approach)
class SolutionTabulation {
public:
    int fib(int n) {
        // Handle base cases
        if(n <= 1) {
            return n;
        }
        
        // Initialize table with base cases
        unordered_map<int, int> hashMap = {
            {0,0},
            {1,1}
        };

        // Build the solution bottom-up
        for(int i = 2; i <= n; ++i) {
            hashMap[i] = hashMap[i-1] + hashMap[i-2];
        }
        
        // Return the final result
        return hashMap[n];
    }
};

// Solution 3: Space-optimized iterative solution
class SolutionOptimized {
public:
    int fib(int n) {
        // Handle base cases
        if (n <= 1) {
            return n;
        }
        
        // Only store the last two values
        int prev = 0;
        int curr = 1;
        
        for (int i = 2; i <= n; i++) {
            int next = prev + curr;
            prev = curr;
            curr = next;
        }
        
        return curr;
    }
};

int main() {
    // Create instances of all Solution classes
    SolutionMemoization solutionMemo;
    SolutionTabulation solutionTabu;
    SolutionOptimized solutionOpt;
    
    // Test cases
    std::vector<int> testCases = {
        0,    // Expected output: 0
        1,    // Expected output: 1
        2,    // Expected output: 1
        3,    // Expected output: 2
        4,    // Expected output: 3
        5,    // Expected output: 5
        10,   // Expected output: 55
        20,   // Expected output: 6765
        30,   // Expected output: 832040
        40    // Expected output: 102334155
    };
    
    std::cout << "COMPARING FIBONACCI IMPLEMENTATIONS\n";
    std::cout << "===================================\n\n";
    
    // Iterate through test cases
    for (const auto& n : testCases) {
        std::cout << "n = " << n << "\n";
        
        // Measure time for Memoization approach
        auto start1 = std::chrono::high_resolution_clock::now();
        int resultMemo = solutionMemo.fib(n);
        auto end1 = std::chrono::high_resolution_clock::now();
        auto duration1 = std::chrono::duration_cast<std::chrono::nanoseconds>(end1 - start1);
        
        // Measure time for Tabulation approach
        auto start2 = std::chrono::high_resolution_clock::now();
        int resultTabu = solutionTabu.fib(n);
        auto end2 = std::chrono::high_resolution_clock::now();
        auto duration2 = std::chrono::duration_cast<std::chrono::nanoseconds>(end2 - start2);
        
        // Measure time for Optimized approach
        auto start3 = std::chrono::high_resolution_clock::now();
        int resultOpt = solutionOpt.fib(n);
        auto end3 = std::chrono::high_resolution_clock::now();
        auto duration3 = std::chrono::duration_cast<std::chrono::nanoseconds>(end3 - start3);
        
        // Print results
        std::cout << "F(" << n << ") = " << resultMemo << "\n";
        std::cout << "Memoization time: " << duration1.count() << " ns\n";
        std::cout << "Tabulation time: " << duration2.count() << " ns\n";
        std::cout << "Optimized time: " << duration3.count() << " ns\n\n";
    }
    
    // Solution Comparison
    std::cout << "SOLUTION COMPARISON\n";
    std::cout << "===================\n\n";
    
    std::cout << "1. Memoization (Top-down) Approach\n";
    std::cout << "-------------------------------\n";
    std::cout << "- Uses recursion with a hash map to cache previously computed values\n";
    std::cout << "- Time Complexity: O(n) - Each Fibonacci number is calculated exactly once\n";
    std::cout << "- Space Complexity: O(n) - For the recursion stack and hash map\n";
    std::cout << "- Advantages:\n";
    std::cout << "  * More intuitive implementation that follows the mathematical definition\n";
    std::cout << "  * Calculates only necessary values (lazy evaluation)\n";
    std::cout << "- Disadvantages:\n";
    std::cout << "  * Function call overhead for recursion\n";
    std::cout << "  * Risk of stack overflow for very large n values\n\n";
    
    std::cout << "2. Tabulation (Bottom-up) Approach\n";
    std::cout << "--------------------------------\n";
    std::cout << "- Uses iteration to build up solutions in a hash map\n";
    std::cout << "- Time Complexity: O(n) - Each Fibonacci number is calculated exactly once\n";
    std::cout << "- Space Complexity: O(n) - For the hash map storing all values\n";
    std::cout << "- Advantages:\n";
    std::cout << "  * Avoids recursion overhead and stack overflow risks\n";
    std::cout << "  * Often faster in practice for large inputs\n";
    std::cout << "- Disadvantages:\n";
    std::cout << "  * Calculates all values up to n even if not all are needed\n\n";
    
    std::cout << "3. Space-Optimized Approach\n";
    std::cout << "-------------------------\n";
    std::cout << "- Iterative approach that only stores the most recent two values\n";
    std::cout << "- Time Complexity: O(n) - Each step takes constant time\n";
    std::cout << "- Space Complexity: O(1) - Only need to store two values regardless of input size\n";
    std::cout << "- Advantages:\n";
    std::cout << "  * Most memory-efficient solution\n";
    std::cout << "  * Often the fastest in practice due to better cache performance\n";
    std::cout << "- Disadvantages:\n";
    std::cout << "  * Can't provide easy access to intermediate values\n\n";
    
    std::cout << "Performance Notes:\n";
    std::cout << "-----------------\n";
    std::cout << "- For small values of n, the differences between approaches may be negligible\n";
    std::cout << "- For larger values of n:\n";
    std::cout << "  * The optimized solution generally performs best due to better cache locality\n";
    std::cout << "  * Tabulation typically outperforms memoization due to lack of function call overhead\n";
    std::cout << "  * Memoization may be faster for sparse computations where not all values are needed\n";
    std::cout << "- The hash map in both DP approaches adds some overhead compared to using arrays\n";
    std::cout << "- For extremely large n values, all these approaches would need to handle integer overflow\n";
    
    return 0;
}

