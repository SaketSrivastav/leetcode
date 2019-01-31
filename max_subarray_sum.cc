#include <vector>
using namespace std;

// T = O(n), S = O(1)
int kadanesAlgorithm(vector<int> array) {
	if(array.size() == 0) return INT_MIN;
	if(array.size() == 1) return array[0];
	int maxSoFar = array[0];
	int maxEndingHere = array[0];
	for(int i=1; i<array.size(); i++) {
		maxEndingHere = max(array[i], maxEndingHere + array[i]);
		maxSoFar = max(maxSoFar, maxEndingHere);
	}
	return maxSoFar;
}

int main(int argc, char *argv[])
{
    vector<int> test1 = {1,2,3,4,5,6,7,8,9,10};

    cout << "Input: ";
    for(auto num : test1)
        cout << num << " ";
    cout << endl;

    cout << "Max Subarray Sum: " << kadanesAlgorithm(test1) << endl;
    return 0;
}
