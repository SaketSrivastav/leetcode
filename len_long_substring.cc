#include <iostream>
#include <map>
#include <string>

using namespace std;

class Solution {
public:
  int lengthOfLongestSubstring(string s) {
    int i = 0, j = 0, ans = 0;

    map<char, int> hash_map;
    for (i = 0, j = 0; j < s.length(); ++j) {
      cout << endl << "char " << s.at(j) << " i " << i << " j " << j << endl;
      if(hash_map.count(s.at(j)) > 0) {
        i = max((hash_map.find(s.at(j)))->second, i);
        cout << "Found char at " << hash_map.find(s.at(j))->second << endl;
        cout << "i = " << i << endl;
      }

      ans = max(ans, j - i + 1);
      cout << "ans = " << ans << endl;
      auto it = hash_map.find(s.at(j));
      if(it == hash_map.end())
        hash_map.emplace(s.at(j), j+1);
      else
        it->second = j+1;

      for (auto it = hash_map.begin(); it != hash_map.end(); ++it) {
        cout << it->first << " -> " << it->second << endl;
      }
      cout << "map add " << s.at(j) << " - > " << j+1 << endl;
    }

    return ans;
  }

  void print_map(map<char, int> & mymap) {
  }
};

int main(int argc, char *argv[])
{
  string s1 ="abcabcbb";
  Solution s;

  cout << "Input: " << s1 << endl;
  cout << "Length " << s.lengthOfLongestSubstring(s1) << endl;
  return 0;
}
