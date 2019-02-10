#include <iostream>
#include <queue>
#include <vector>

using namespace std;

typedef struct heapNode {
    int item;
    int thisList;
    int nextListIndex;
}HeapNode;

class HeapCompare
{
public:
    bool operator() (HeapNode x, HeapNode y) {
        return x.item > y.item;
    }
};

// T = nkLogK, S = O(kn)
//     nk times we add to heap, heapify take log k
vector<int> mergeKSortedList(vector<vector<int>> * inputArr, int n)
{
    // Create a Min Heap of K nodes
    priority_queue<HeapNode, vector<HeapNode>, HeapCompare> heap;
    // Store result in array of size k * n
    vector<int> result(inputArr->size(), INT_MAX);

    // Add all first elements of K list into heap.
    for(int i=0; i<inputArr->size(); i++) {
        cout << "Adding " << inputArr->at(i)[0] << endl;
        heap.push({inputArr->at(i)[0], i, 1});
    }

    // Extract min from heap and move index of the list from where the item was picked.
    // If the list is empty then mark that node value = INT_MAX
    for(int i=0; i<inputArr->size()*n; i++)
    {
        // Extract min
        HeapNode root = heap.top();
        heap.pop();
        // Add item to output array
        cout << "Add item to output array " << root.item << endl;
        result.push_back(root.item);

        // If list is not empty
        if(root.nextListIndex < n) {
            // Add next item from the list of root
            root.item = inputArr->at(root.thisList)[root.nextListIndex];
            root.nextListIndex += 1;
        } else {
            // If the root list is empty then add INT_MAX
            root.item = INT_MAX;
        }

        // Push new node with new root
        heap.push(root);
    }

    return result;
}

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
// T = O(n) S = O(1)
class Solution {
public:
    // Method to do merge of 2 sorted lists
    ListNode* merge2Lists(ListNode* l1, ListNode* l2)
    {
        if(l1 == NULL) return l2;
        if(l2 == NULL) return l1;

        // Add nodes to first list
        if(l1->val <= l2->val) {
            l1->next = merge2Lists(l1->next, l2);
            return l1;
        }

        // Add nodes to second list
        l2->next = merge2Lists(l1, l2->next);
        return l2;
    }

    // Apply merge2sorted list to merge k sorted list without using heap
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if(lists.size() == 0) return NULL;
        if(lists.size() == 1) return lists[0];

        while(lists.size() > 1) {
            lists.push_back(merge2Lists(lists[0], lists[1]));
            lists.erase(lists.begin()); // remove lists[0]
            lists.erase(lists.begin()); // remove lists[1]
        }

        return lists.front();
    }
};
