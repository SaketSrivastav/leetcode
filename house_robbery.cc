#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

// There are n houses build in a line, each of which contains some value in it. A thief is going to steal the maximal value of these houses, but he can’t steal in two adjacent houses because owner of the stolen houses will tell his two neighbour left and right side. What is the maximum stolen value.
//     Examples:

// Input  : hval[] = {6, 7, 1, 3, 8, 2, 4}
// Output : 19
// Thief will steal 6, 1, 8 and 4 from house.

// Input  : hval[] = {5, 3, 4, 11, 2}
// Output : 16
// Thief will steal 5 and 11

// Soln:
// Thief options are whether to loot house i or not.
// If thief choose to loot ith house then loot value = ith house loot value + total toot till i-2th house
// If thief choose not to loot ith house then loot value = dp(i-1) because thief cannot loot adjacent house
// Base case: loot(0) = house_value(0)
//            loot(1) = max(house_value(1), house_value(0))
//   Formula: loot = max(house_value(i) + loot(i-2), loot(i-1))
int max_loot(vector<int> *hval, int n)
{
    if(n == 0) return 0;
    if(n == 1) return hval->at(0);
    if(n == 2) return max(hval->at(0), hval->at(1));

    vector<int> loot = {0, n};
    loot[0] = 0;
    loot[1] = hval->at(1);

    for(int i=2; i<n; i++) {
        loot[i] = max((hval->at(i)+loot[i-2]), loot[i-1]);
    }

    return loot[n-1];
}

int main()
{
    vector<int>hval = {6, 7, 1, 3, 8, 2, 4};
    srand(time(NULL));
    cout << "House value: ";
    for(auto val : hval)
        cout << val << " " ;
    cout << endl;
    cout << "Maximum loot possible : "
         << max_loot(&hval, hval.size()) << endl;

    hval.clear();
    cout << "House value: ";
    for(int i=0; i<7; i++) {
        int val = rand() % 10;
        hval.push_back(val);
        cout << val << " ";
    }
    cout << endl;
    cout << "Maximum loot possible : "
         << max_loot(&hval, hval.size()) << endl;

    return 0;
}
