#include <vector>
#include <iostream>
using namespace std;

// Do not edit the class below except for the buildHeap,
// siftDown, siftUp, peek, remove, and insert methods.
// Feel free to add new properties and methods to the class.
class MinHeap {
public:
    vector<int> heap;

    MinHeap(vector<int> vector) {
        heap = buildHeap(&vector);
    }

    // T = O(N) and S = O(1)
    vector<int> buildHeap(vector<int>* vector) {
        // Find the first parent and siftdown from first parent to the root
        int firstParentIdx = ((vector->size() - 1) - 1) / 2;
        for(int currentIdx = firstParentIdx; currentIdx >= 0; currentIdx--) {
            siftDown(currentIdx, vector->size()-1, vector);
        }
        return *vector;
    }

    // T = O(log N) and S = O(1)
    void siftDown(int currentIdx, int endIdx, vector<int>* heap) {
        int childOneIdx = -1;
        int childTwoIdx = -1;
        int idxToSwap = -1;

        // Find the idx to swap because in siftDown
        // it could be one of the child.
        childOneIdx = currentIdx * 2 + 1;
        while(childOneIdx <= endIdx) { // There must be a child to siftDown
            childTwoIdx = currentIdx * 2 + 2;
            if(childTwoIdx <= endIdx)
                childTwoIdx = currentIdx * 2 + 2;
            else
                childTwoIdx = -1;

            // If childTwo exist and smaller than childOne then select childTwoIdx
            if(childTwoIdx != -1 && heap->at(childTwoIdx) < heap->at(childOneIdx)) {
                idxToSwap = childTwoIdx;
            } else {
                idxToSwap = childOneIdx;
            }

            if(heap->at(idxToSwap) < heap->at(currentIdx)) {
                swap(idxToSwap, currentIdx, heap);
                currentIdx = idxToSwap;
                childOneIdx = currentIdx * 2 + 1;
            } else { // We reached leaf node, no more siftdown possible
                break;
            }
        }
    }

    // T = O(log N) and S = O(1)
    void siftUp(int currentIdx, vector<int>* heap) {
        // Calculate parentIdx = (currentIdx - 1) / 2 => heap to array property
        // Swap while currentIdx < parentIdx

        // Get Parent
        int parentIdx = currentIdx > 0 ? (currentIdx-1) / 2 : 0;
        while(parentIdx > 0 && heap->at(currentIdx) < heap->at(parentIdx)) {
            swap(currentIdx, parentIdx, heap);
            currentIdx = parentIdx;
            parentIdx = (currentIdx-1) / 2;
        }
    }

    // Root element of heap
    int peek() {
        return heap[0];
    }

    int remove() {
        if(heap.size() == 0) return -1;

        // Swap last element with root
        // Pop the element
        // SiftDown from root
        swap(0, heap.size()-1, &heap);
        int valueToRemove = heap[heap.size()-1];
        heap.pop_back();
        siftDown(0, heap.size()-1, &heap);
        return valueToRemove;
    }

    void insert(int value) {
        // Add the element to end of the array and siftup
        // to the right place in array
        heap.push_back(value);
        siftUp((heap.size()-1), &heap);
    }

    // Helper method
    void swap(int i, int j, vector<int>* heap) {
        int tmp = heap->at(i);
        heap->at(i) = heap->at(j);
        heap->at(j) = tmp;
    }

    void print() {
        for(auto idx : heap) {
            cout << idx << " ";
        }
        cout << endl;
    }
};

int main(int argc, char *argv[])
{
    MinHeap test1 = MinHeap({2, 3, 1});
    test1.print();
    test1.insert(76);
    test1.print();
    test1.remove();
    test1.print();
    test1.remove();
    test1.print();
    test1.insert(45);
    test1.print();
    return 0;
}
