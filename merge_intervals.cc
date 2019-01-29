#include <iostream>
#include <vector>

using namespace std;

// sort based on start time
// use a stack to store the final set of overlapped intervals
// push to stack if end time of top of stack is smaller than start time of interval
// pop from stack when end time is greater than start time of interval
// pop and replace end time of top of stack with end time of interval and push to stack.
// at the end stack will have final overlapped intervals.

int compare_interval(vector<int> i1, vector<int> i2)
{
    return i1[0] < i2[0];
}

vector<vector<int>> merge_intervals(vector<vector<int>> * intervals)
{
    if(intervals->size() == 0) return {{}};
    if(intervals->size() == 1) return *intervals;

    // Use vector as stack
    vector<vector<int>> result;

    sort(intervals->begin(), intervals->end(), compare_interval);
    result.push_back(intervals->at(0));
    for(auto curr_interval : *intervals) {
        if(curr_interval[0] > result.back()[1])
            result.push_back(curr_interval);
        else {
            vector<int> new_int = result.back();
            new_int[1] = curr_interval[1];
            result.pop_back();
            result.push_back(new_int);
        }
    }

    return result;
}

int main(int argc, char *argv[])
{
    vector<vector<int>> test_data = {{1,3}, {2,4}, {5,7}, {6,8}};
    cout << "Input: ";
    for(auto curr : test_data)
        cout << "[" << curr[0] << ", " << curr[1] << "] ";
    cout << endl;
    vector<vector<int>> result = merge_intervals(&test_data);
    cout << "Output: ";
    for(auto curr : result)
        cout << "[" << curr[0] << ", " << curr[1] << "] ";
    cout << endl;
    return 0;
}
