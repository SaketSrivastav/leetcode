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
/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */
class IntervalCompare {
    public:
    int operator () (Interval& i1, Interval& i2) {
        return i1.start > i2.start;
    }
};

// Use priority queue for sorting
vector<Interval> merge(vector<Interval>& intervals) {
    if(intervals.empty()) return {};
    if(intervals.size() == 1) return intervals;

    // Sort them based on starting time
    priority_queue<Interval, vector<Interval>, IntervalCompare> pq;
    for(auto interval : intervals)
        pq.push(interval);

    vector<Interval> result = {};
    result.push_back(pq.top());
    pq.pop();

    // move ahead till we encounter end time of first interval is greater than
    // start time of following interval
    while(!pq.empty()) {
        Interval temp = pq.top();
        pq.pop();

        // When that happens we create 1 single interval with start time of
        // first interval and end time of last interval which satisfied the
        // condition
        if(temp.start <= result.back().end)
            result.back().end = max(result.back().end, temp.end);
        else
            result.push_back(temp);
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
