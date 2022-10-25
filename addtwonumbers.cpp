// Add Two Numbers LeetCode Problem Solution 
// Difficulty Level: Medium
// Written by David Mekhtiev <davidmek@umich.edu>
// Current status: 1565 / 1568 test cases passed.

#include <iostream>
#include <deque>
#include <vector>
#include <cmath>

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// Solution 
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        // Deques for storing values & digits of computed sum
        std::deque<int> l1_vals;
        std::deque<int> l2_vals; 
        std::deque<int> sum_digits;
        bool zero_input = false;
        if (l1->val == 0 && l2->val == 0 &&
            l1->next == nullptr && l2->next == nullptr) { zero_input = true; }
        // Loops to store vals from linked lists in deques
        while (l1->next != nullptr) {
            l1_vals.push_front(l1->val);
            l1 = l1->next;
        }
        while (l2->next != nullptr) {
            l2_vals.push_front(l2->val);
            l2 = l2->next;
        }
        if (l1->next == nullptr) { l1_vals.push_front(l1->val); } 
        if (l2->next == nullptr) { l2_vals.push_front(l2->val); }
        // Parse full integers stored in linked lists and appended to
        // deques from before
        uint64_t l1_num = 0, l2_num = 0, sum = 0;
        size_t tens_place = l1_vals.size() - 1;
        for (auto it1 = l1_vals.begin(); it1 != l1_vals.end(); it1++) {
            l1_num += static_cast<uint64_t>(*(it1))
                      * static_cast<uint64_t>(std::pow(10, tens_place--));
        }
        tens_place = l2_vals.size() - 1;
        for (auto it2 = l2_vals.begin(); it2 != l2_vals.end(); it2++) {
            l2_num += static_cast<uint64_t>(*(it2))
                      * static_cast<uint64_t>(std::pow(10, tens_place--));
        }
        sum = l1_num + l2_num;
        // Place all digits of sum into deque
        while (sum > 0) {
            uint64_t digit = sum % 10;
            sum /= 10;
            sum_digits.push_back(static_cast<int>(digit));
        }
        // Edge case for input of single elems both w/ 0
        if (zero_input) { 
            sum_digits.push_back(static_cast<int>(sum)); 
        }
        // Create linked list to sum number and return ptr
        // Root Node 
        ListNode* rootNode = new ListNode;
        rootNode = nullptr;
        // Remaining Nodes 
        while (!sum_digits.empty()) {
            ListNode* newNode = new ListNode;
            newNode->val = sum_digits.back();
            sum_digits.pop_back();
            newNode->next = rootNode;
            rootNode = newNode;
        }
        return rootNode;
    }
};

// Global variables
// // Test 1 from LeetCode
// // Input L1 -> [2,4,3]
// // Input L2 -> [5,6,4]
// std::vector<int> l1_input {2, 4, 3};
// std::vector<int> l2_input {5, 6, 4};

// // Test 2 from LeetCode
// // Input L1 -> [0]
// // Input L2 -> [1]
// std::vector<int> l1_input {0};
// std::vector<int> l2_input {1};

// Test 3 from LeetCode 
// Input L1 -> []
// Input L2 -> []
std::vector<int> l1_input {0, 8, 8, 8, 8, 2, 9, 3, 1, 1};
std::vector<int> l2_input {0, 9, 1, 5, 5, 5, 1, 1, 6};

// Driver for running tests
int main () {
    // Create linked list L1.
    // Root Node 
    ListNode* rootNode_L1 = new ListNode;
    rootNode_L1 = nullptr;
    // Remaining Nodes 
    while (l1_input.size() != 0) {
        ListNode* newNode = new ListNode;
        newNode->val = l1_input.back();
        l1_input.pop_back();
        newNode->next = rootNode_L1;
        rootNode_L1 = newNode;
    }
    // Create linked list L2.
    // Root Node 
    ListNode* rootNode_L2 = new ListNode;
    rootNode_L2 = nullptr;
    // Remaining Nodes 
    while (l2_input.size() != 0) {
        ListNode* newNode = new ListNode;
        newNode->val = l2_input.back();
        l2_input.pop_back();
        newNode->next = rootNode_L2;
        rootNode_L2 = newNode;
    }
    Solution instance;
    instance.addTwoNumbers(rootNode_L1, rootNode_L2);
}
