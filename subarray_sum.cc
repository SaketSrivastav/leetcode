#include <iostream>
#include <vector>

using namespace std;

// Given a list of integers and a number K, return which contiguous elements of the list sum to K.
// For example, if the list is [1, 2, 3, 4, 5] and K is 9, then it should return [2, 3, 4].
// Soln: Add numbers in array till you cross the number K. Then subtract
vector<int> subarray_sum_k(vector<int> array, int target)
{
    if(array.size() == 0) return {};

    vector<int> result;
    int curr_sum = 0, j = 0;
    for(auto num : array) {
        while(curr_sum > target && !result.empty()) {
            curr_sum = curr_sum - result.front();
            cout << "remove " << result.front() << endl;
            result.erase(result.begin());
        }

        if(curr_sum == target) {
            return result;
        }

        curr_sum += num;
        result.push_back(num);
    }

    return result;
}

void print_vector(vector<int> * array) {
    for(int i; i<array->size(); i++) {
        cout << array->at(i) << " ";
    }
    cout << endl;
}

int main() {
    vector<int> test1 = {1,2,3,4,5,6};
    vector<int> result1 = subarray_sum_k(test1, 9);
    cout << "Test1: ";
    print_vector(&test1);
    cout << "target: " << 9 << endl;
    cout << "Result: ";
    print_vector(&result1);
    return 0;
}
