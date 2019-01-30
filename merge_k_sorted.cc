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

// Sorts a single list and stores in 1 of the list
Node * sortedMergeList(Node *a, Node *b)
{
    Node * result = NULL;

    if( a == NULL ) return b;
    if ( b == NULL ) return a;

    if(a->data <= b->data)
    {
        result = a;
        result->next = sortedMergeList(a->next, b);
    } else {
        result = b;
        result->next = sortedMergeList(a, b->next);
    }

    return result;
}

// arr[0..last] and generates the sorted output
Node* mergeKLists(Node* arr[], int last)
{
    // repeat until only one list is left
    while (last != 0)
    {
        int i = 0, j = last;

        // (i, j) forms a pair
        while (i < j)
        {
            // merge List i with List j and store
            // merged list in List i
            arr[i] = SortedMerge(arr[i], arr[j]);

            // consider next pair
            i++, j--;

            // If all pairs are merged, update last
            if (i >= j)
                last = j;
        }
    }

    return arr[0];
}

int main(int argc, char *argv[])
{
    vector<vector<int>> test1 = {{1,3,5,7,9}, {2,4,6,8}, {0,10,12}};
    cout << "test1: [";
    for(auto list : test1) {
        cout << "[";
        for(auto num : list) {
            cout << num << " ";
        }
        cout << "], " << endl;
    }
    cout << "]" << endl;
    vector<int> result1 = mergeKSortedList(&test1, 5);

    cout << "Result1: ";
    for(auto num : result1) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
