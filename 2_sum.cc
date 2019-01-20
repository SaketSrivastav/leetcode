#include <iostream>
#include <vector>
#include <unordered_map>
#include <stdexcept>

using namespace std;

class Solution {
public:
  vector<int> twoSum(vector<int>& nums, int target) {
    unordered_map<int, int> h_t;
    vector<int> result;
    for (int i = 0; i < nums.size(); ++i) {
      int tmp = target - nums[i];
      unordered_map<int, int>::const_iterator it = h_t.find(tmp);
      if(it != h_t.end() && it->second != i) {
        result.push_back(nums[i]);
        result.push_back(nums[it->second]);
        return result;
      }
      h_t.emplace(nums[i], i);
    }

    throw invalid_argument("Solution not found");
  }
};

void test_2_sum() {
  vector<int> v = {2,7,11,15};
  int target = 0;
  vector<int> result;
  Solution sol = Solution();

  cout << "Input: " ;
  for (int i = 0; i < v.size(); ++i) {
    cout << i << " --> " << v[i] << endl;
  }

  cout << "Enter target: ";
  cin >> target;

  try {
    result = sol.twoSum(v, target);
    cout << "Solution: " << result[0] << " " << result[1] << endl;
  }
  catch( exception &e) {
    cout << e.what() << endl;
  }
}

int main(int argc, char *argv[])
{
  test_2_sum();
  return 0;
}
