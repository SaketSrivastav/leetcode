#include <iostream>

using namespace std;

int search_circ_array(vector<int>& array, int low, int high, int key)
{
    if(array.size() == 0) return -1;

    int mid = (low+high)/2;
    if(array[mid] == key) return mid;

    // Sorted left half
    if(array[low] <= array[mid]) {
        if(key >= array[low] && key < array[mid])
            return search_circ_array(array, low, mid-1, key);

        return search_circ_array(array, mid+1, high, key);
    }

    // Search the rotated part of array from mid to high
    if(key >= array[mid] && key <= array[high])
        return search_circ_array(array, mid+1, high, key);

    return search_circ_array(array, low, mid-1, key);
}
