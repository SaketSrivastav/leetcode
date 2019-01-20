#include <vector>
#include <iostream>
#include <map>
#include <algorithm>
using namespace std;

vector<vector<int> > threeNumberSum(vector<int> array, int targetSum) {
	vector<vector<int>> result;
	if(array.size() == 0) return {};

	map<int, int> my_map;

	for(int i=0; i<array.size(); i++) {
		for(int j=i+1; j<array.size(); j++) {
			my_map[array[j]] = j;
		}

        map<int,int>::iterator mapIt;
		for(int j=i+1; j<array.size(); j++) {
			mapIt = my_map.find(abs(array[i] + array[j] - targetSum));
            cout << "i = " << array[i] << " j = " << array[j] << " search = " << (abs(array[i] + array[j] - targetSum)) << endl;
			if(mapIt != my_map.end()) {
                cout << "i = " << array[i] << " j = " << array[j] << " found = " << (abs(array[i] + array[j] - targetSum)) << endl;
				result.push_back({array[i], array[j], (int)mapIt->first});
			}
		}
		my_map.clear();
	}

    return result;
}

int main(int argc, char *argv[])
{
    vector<int> test = {0, 4, 7, 4, 3};
    vector<vector<int>> result = threeNumberSum(test, 11);
    for (int i = 0; i < result.size(); ++i) {
        for (int j = 0; j < result[0].size(); ++j) {
            cout << result[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    return 0;
}
