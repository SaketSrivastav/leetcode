/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * class NestedInteger {
 *   public:
 *     // Constructor initializes an empty nested list.
 *     NestedInteger();
 *
 *     // Constructor initializes a single integer.
 *     NestedInteger(int value);
 *
 *     // Return true if this NestedInteger holds a single integer, rather than a nested list.
 *     bool isInteger() const;
 *
 *     // Return the single integer that this NestedInteger holds, if it holds a single integer
 *     // The result is undefined if this NestedInteger holds a nested list
 *     int getInteger() const;
 *
 *     // Set this NestedInteger to hold a single integer.
 *     void setInteger(int value);
 *
 *     // Set this NestedInteger to hold a nested list and adds a nested integer to it.
 *     void add(const NestedInteger &ni);
 *
 *     // Return the nested list that this NestedInteger holds, if it holds a nested list
 *     // The result is undefined if this NestedInteger holds a single integer
 *     const vector<NestedInteger> &getList() const;
 * };
 */
class Solution {
public:
    int depthSumHelper(vector<NestedInteger>& nestedList, int depth)
    {
        if(nestedList.size() == 0)
            return 0;
        int sum = 0;
        for(int i=0; i<nestedList.size(); i++) {
            auto node = nestedList.at(i);
            if(node.isInteger()) {
                sum += (node.getInteger() * depth);
                cout << "Found integer " << node.getInteger()
                     << " running sum " << sum << endl;
            }
            else {
                cout << "Found list at position " << i
                     << " running sum " << sum << endl;
                sum += depthSumHelper(node.getList(), depth+1);
                cout << "After list sum  " << sum << endl;
            }
        }

        cout << "Return sum " << sum << endl;
        return sum;
    }

    int depthSum(vector<NestedInteger>& nestedList) {
        int sum = depthSumHelper(nestedList, 1);
        cout << "Final sum " << sum << endl;
        return sum;
    }
};
