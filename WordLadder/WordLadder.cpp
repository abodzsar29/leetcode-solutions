#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <queue>
using namespace std;

/*
This is the solution for the problem "Word Ladder", classed "Hard" on LeetCode. It is found under:
https://leetcode.com/problems/word-ladder/
*/

// Approach 1: Breadth-First Search

class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> wordSet(wordList.begin(), wordList.end());
        if (wordSet.find(endWord) == wordSet.end()) return 0;

        queue<pair<string, int>> queue;
        queue.push({ beginWord, 1 });
        unordered_set<string> visited;
        visited.insert(beginWord);

        while (!queue.empty()) {
            auto [word, level] = queue.front();
            queue.pop();

            for (int i = 0; i < word.size(); i++) {
                string newWord = word;
                for (char letter = 'a'; letter <= 'z'; letter++) {
                    newWord[i] = letter;

                    if (newWord == word) continue;
                    if (newWord == endWord) return level + 1;

                    if (wordSet.find(newWord) != wordSet.end() && visited.find(newWord) == visited.end()) {
                        queue.push({ newWord, level + 1 });
                        visited.insert(newWord);
                    }
                }
            }
        }
        return 0;
    }
};


int main() {
    
    return 0;
}

