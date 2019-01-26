#include <iostream>
#include <queue>
#include <cstdlib>
#include <cmath>

using namespace std;

class Running_Median {
private:
    // Max heap: default
    priority_queue<int, vector<int>, less<int>> low_half;
    // Min heap
    priority_queue<int, vector<int>, greater<int>> rt_half;
    double median;

    // Remove the top element of the greater half
    // and insert in other half
    void rebalance_halves()
    {
        // If one of the heaps grow bigger
        int h_size = low_half.size() > rt_half.size() ?
            low_half.size() - rt_half.size() :
            rt_half.size() - low_half.size();

        if(h_size != 2)
            return;

        // cout << "Rebalancing " << endl;
        if(low_half.size() > rt_half.size())
        {
            rt_half.push(low_half.top());
            low_half.pop();
        } else {
            low_half.push(rt_half.top());
            rt_half.pop();
        }
    }

    void calculate_median()
    {
        if(low_half.size() == rt_half.size())
            median = (double)(low_half.top() + rt_half.top()) / 2;
        else
            median = (low_half.size() > rt_half.size() ? low_half.top() :
                              rt_half.top());
        // cout << "Median = " << median << endl;
    }

public:
    void insert(int num)
    {
        // If input num is greater than low half (max heap)
        // then num belongs in the right half (min heap)
        if(low_half.empty() || num < low_half.top()) {
            cout << "Add " << num << " to low half" << endl;
            low_half.push(num);
        } else {
            cout << "Add " << num << " to right half" << endl;
            rt_half.push(num);
        }

        rebalance_halves();

        // update median for every insertion
        calculate_median();

        return;
    }

    double get_median()
    {
        return median;
    }
};

int main(int argc, char *argv[])
{
    Running_Median rm = Running_Median();
    srand(time(NULL));
    for(int i=0; i<10; i++) {
        int num = rand() % 100;
        cout << "Inserting: " << num << endl;
        rm.insert(num);
        cout << "Running median " << rm.get_median() << endl;
    }
    return 0;
}
