#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <set>

/*
This is the solution for the problem "Group Anagrams", classed "Medium" on LeetCode. It is found under:
https://leetcode.com/problems/group-anagrams/description/

The problem involves grouping strings that are anagrams of each other into separate groups.
Two strings are anagrams if they contain the same characters with the same frequency.

Three different approaches are implemented:

1. Sorting-based Approach (Primary Solution):
   - Sort each string to create a canonical form
   - Use sorted string as key in hash map
   - Time Complexity: O(N * K * log K), where N is number of strings, K is max string length
   - Space Complexity: O(N * K) for storage

2. Character Frequency Counting:
   - Count frequency of each character to create signature
   - Use frequency signature as key
   - Time Complexity: O(N * K), where N is number of strings, K is max string length
   - Space Complexity: O(N * K) for storage

3. Prime Number Encoding (Alternative):
   - Assign prime numbers to each character
   - Use product of primes as unique signature
   - Time Complexity: O(N * K)
   - Space Complexity: O(N * K)
*/

// Primary Solution: Sorting-based Approach
class SolutionSorting {
public:
    std::vector<std::vector<std::string>> groupAnagrams(std::vector<std::string>& strs) {
        std::unordered_map<std::string, int> groupIndex;
        std::vector<std::vector<std::string>> result;

        for (const auto& word : strs) {
            // Create canonical form by sorting characters
            std::string sortedWord = word;
            std::sort(sortedWord.begin(), sortedWord.end());

            // Check if this anagram group already exists
            if (groupIndex.count(sortedWord)) {
                // Add to existing group
                result[groupIndex[sortedWord]].push_back(word);
            } else {
                // Create new group
                groupIndex[sortedWord] = result.size();
                result.push_back({word});
            }
        }

        return result;
    }
};

// Alternative Solution: Character Frequency Counting
class SolutionFrequency {
public:
    std::vector<std::vector<std::string>> groupAnagrams(std::vector<std::string>& strs) {
        std::unordered_map<std::string, std::vector<std::string>> groups;

        for (const auto& word : strs) {
            // Create frequency signature
            std::string signature = getFrequencySignature(word);
            groups[signature].push_back(word);
        }

        // Convert map to result format
        std::vector<std::vector<std::string>> result;
        for (const auto& pair : groups) {
            result.push_back(pair.second);
        }

        return result;
    }

private:
    // Generate frequency-based signature for a word
    std::string getFrequencySignature(const std::string& word) {
        std::vector<int> count(26, 0);
        
        // Count frequency of each character
        for (char c : word) {
            count[c - 'a']++;
        }
        
        // Create signature string from frequencies
        std::string signature;
        for (int i = 0; i < 26; ++i) {
            if (count[i] > 0) {
                signature += char('a' + i) + std::to_string(count[i]);
            }
        }
        
        return signature;
    }
};

// Alternative Solution: Prime Number Encoding
class SolutionPrime {
public:
    std::vector<std::vector<std::string>> groupAnagrams(std::vector<std::string>& strs) {
        std::unordered_map<long long, std::vector<std::string>> groups;

        for (const auto& word : strs) {
            // Create prime-based signature
            long long signature = getPrimeSignature(word);
            groups[signature].push_back(word);
        }

        // Convert map to result format
        std::vector<std::vector<std::string>> result;
        for (const auto& pair : groups) {
            result.push_back(pair.second);
        }

        return result;
    }

private:
    // Prime numbers for each letter a-z
    const std::vector<int> primes = {
        2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 
        43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101
    };

    // Generate prime product signature for a word
    long long getPrimeSignature(const std::string& word) {
        long long product = 1;
        
        for (char c : word) {
            product *= primes[c - 'a'];
            // Note: This can overflow for very long strings
        }
        
        return product;
    }
};

// Helper function to print a 2D vector of strings
void printGroups(const std::vector<std::vector<std::string>>& groups, const std::string& label) {
    std::cout << label << ":\n";
    for (size_t i = 0; i < groups.size(); ++i) {
        std::cout << "  Group " << (i + 1) << ": [";
        for (size_t j = 0; j < groups[i].size(); ++j) {
            std::cout << "\"" << groups[i][j] << "\"";
            if (j != groups[i].size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << "]\n";
    }
}

// Helper function to print input vector
void printInput(const std::vector<std::string>& strs) {
    std::cout << "Input: [";
    for (size_t i = 0; i < strs.size(); ++i) {
        std::cout << "\"" << strs[i] << "\"";
        if (i != strs.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "]\n";
}

// Helper function to normalize groups for comparison (sort groups and within groups)
std::vector<std::vector<std::string>> normalizeGroups(std::vector<std::vector<std::string>> groups) {
    // Sort each group internally
    for (auto& group : groups) {
        std::sort(group.begin(), group.end());
    }
    
    // Sort groups by their first element for consistent comparison
    std::sort(groups.begin(), groups.end(), [](const std::vector<std::string>& a, const std::vector<std::string>& b) {
        return a.empty() ? true : (b.empty() ? false : a[0] < b[0]);
    });
    
    return groups;
}

// Helper function to check if two group results are equivalent
bool areGroupsEquivalent(std::vector<std::vector<std::string>> groups1, std::vector<std::vector<std::string>> groups2) {
    groups1 = normalizeGroups(groups1);
    groups2 = normalizeGroups(groups2);
    return groups1 == groups2;
}

// Helper function to verify anagram property
bool areAnagrams(const std::string& s1, const std::string& s2) {
    if (s1.length() != s2.length()) return false;
    
    std::string sorted1 = s1, sorted2 = s2;
    std::sort(sorted1.begin(), sorted1.end());
    std::sort(sorted2.begin(), sorted2.end());
    
    return sorted1 == sorted2;
}

// Helper function to validate that groups contain valid anagrams
bool validateAnagramGroups(const std::vector<std::vector<std::string>>& groups) {
    for (const auto& group : groups) {
        if (group.size() <= 1) continue;
        
        // Check that all strings in the group are anagrams of each other
        for (size_t i = 1; i < group.size(); ++i) {
            if (!areAnagrams(group[0], group[i])) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    // Create instances of all solution classes
    SolutionSorting solutionSort;
    SolutionFrequency solutionFreq;
    SolutionPrime solutionPrime;
    
    // Test cases with various anagram scenarios
    std::vector<std::vector<std::string>> testCases = {
        // Test Case 1: Basic anagram groups
        {"eat", "tea", "tan", "ate", "nat", "bat"},
        
        // Test Case 2: No anagrams (all unique)
        {"abc", "def", "ghi"},
        
        // Test Case 3: All same anagrams
        {"abc", "bca", "cab", "acb", "bac", "cba"},
        
        // Test Case 4: Single character strings
        {"a", "b", "a", "c", "b"},
        
        // Test Case 5: Empty and single string
        {""},
        
        // Test Case 6: Mixed lengths
        {"ab", "ba", "abc", "bca", "cab", "a", "b"},
        
        // Test Case 7: Case with repeated letters
        {"aab", "aba", "baa", "ab", "ba"},
        
        // Test Case 8: Longer strings
        {"listen", "silent", "enlist", "hello", "world", "dlrow"},
        
        // Test Case 9: Single letters and longer words
        {"a", "aa", "aaa", "b", "bb", "bbb"}
    };
    
    std::cout << "=== Testing Group Anagrams - All Approaches ===\n\n";
    
    // Test each approach
    for (size_t testNum = 0; testNum < testCases.size(); ++testNum) {
        std::vector<std::string> input = testCases[testNum];
        
        std::cout << "Test Case " << (testNum + 1) << ":\n";
        printInput(input);
        std::cout << "\n";
        
        // Test Sorting approach
        std::vector<std::string> inputCopy1 = input;
        auto result1 = solutionSort.groupAnagrams(inputCopy1);
        printGroups(result1, "Sorting Approach");
        bool valid1 = validateAnagramGroups(result1);
        std::cout << "Validation: " << (valid1 ? "✓ PASS" : "✗ FAIL") << "\n\n";
        
        // Test Frequency approach
        std::vector<std::string> inputCopy2 = input;
        auto result2 = solutionFreq.groupAnagrams(inputCopy2);
        printGroups(result2, "Frequency Approach");
        bool valid2 = validateAnagramGroups(result2);
        bool equivalent12 = areGroupsEquivalent(result1, result2);
        std::cout << "Validation: " << (valid2 ? "✓ PASS" : "✗ FAIL") << "\n";
        std::cout << "Equivalent to Sorting: " << (equivalent12 ? "✓ YES" : "✗ NO") << "\n\n";
        
        // Test Prime approach (with overflow warning for long strings)
        std::vector<std::string> inputCopy3 = input;
        auto result3 = solutionPrime.groupAnagrams(inputCopy3);
        printGroups(result3, "Prime Encoding Approach");
        bool valid3 = validateAnagramGroups(result3);
        bool equivalent13 = areGroupsEquivalent(result1, result3);
        std::cout << "Validation: " << (valid3 ? "✓ PASS" : "✗ FAIL") << "\n";
        std::cout << "Equivalent to Sorting: " << (equivalent13 ? "✓ YES" : "✗ NO") << "\n";
        
        std::cout << "\n" << std::string(60, '-') << "\n\n";
    }
    
    // Algorithm complexity analysis
    std::cout << "=== Algorithm Analysis ===\n\n";
    
    std::cout << "1. Sorting-based Approach (Primary Solution):\n";
    std::cout << "   Time Complexity: O(N * K * log K)\n";
    std::cout << "     - N = number of strings\n";
    std::cout << "     - K = maximum length of a string\n";
    std::cout << "     - Sorting each string: O(K * log K)\n";
    std::cout << "   Space Complexity: O(N * K)\n";
    std::cout << "     - Hash map storage and result storage\n";
    std::cout << "   Best for: General case, simple and reliable\n\n";
    
    std::cout << "2. Character Frequency Counting:\n";
    std::cout << "   Time Complexity: O(N * K)\n";
    std::cout << "     - Counting characters: O(K) per string\n";
    std::cout << "     - Creating signature: O(K) per string\n";
    std::cout << "   Space Complexity: O(N * K)\n";
    std::cout << "     - Hash map and frequency arrays\n";
    std::cout << "   Best for: Optimization when K is large\n\n";
    
    std::cout << "3. Prime Number Encoding:\n";
    std::cout << "   Time Complexity: O(N * K)\n";
    std::cout << "     - Computing prime product: O(K) per string\n";
    std::cout << "   Space Complexity: O(N * K)\n";
    std::cout << "     - Hash map storage\n";
    std::cout << "   Best for: Mathematical elegance (with overflow concerns)\n";
    std::cout << "   Limitation: Can overflow with long strings\n\n";
    
    std::cout << "Key Algorithmic Insights:\n";
    std::cout << "  - Anagram detection requires finding canonical representation\n";
    std::cout << "  - Sorting provides simple, reliable canonical form\n";
    std::cout << "  - Frequency counting avoids sorting overhead\n";
    std::cout << "  - Prime encoding mathematically elegant but overflow-prone\n";
    std::cout << "  - Hash map enables O(1) group lookup and formation\n";
    std::cout << "  - Trade-off between implementation simplicity and optimal complexity\n";
    
    return 0;
}
