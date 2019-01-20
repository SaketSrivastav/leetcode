#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  // Solves using dynamic programing by solving following subproblems
  // palindrome of length 1 = each character in the string.
  // palindrome of length 2 = p(i,j) = s[i] == s[i+1]
  // palindrome of length > 2 = p(i,j) = p(i+1, j-1) && s[i] == s[j]
  // We build a table[i][j] bottom up,
  // table[i][j] = (table[i+1][j-1]) and s[i] == s[j]
  // Base cases: table[i][i] = 1
  //             table[i][i+1] = 1 iff s[i] == s[i+1]
  // Complexity: O(n^2), O(n^2) space. table[n][n]
  string longestPalindrome(string s) {
    int lenS = s.size();
    string substr = "\0";
    vector<vector<bool>>table;
    int maxlength = 0;
    int start = 0;

    if(lenS == 0) return substr;

    table.resize(lenS, vector<bool>(lenS, false));

    //Base case: palindrome of len =1
    cout << "Base case 1: " << s << endl;
    for(int i=0; i<lenS; i++) {
      table[i][i] = true;
    }
    maxlength = 1;
    print_table(table);

    cout << "Base case 2: " << s << endl;
    //Base case: palindrome of length = 2
    for(int i=0; i<lenS-1; i++) {
      if(s[i] == s[i+1]){
        table[i][i+1] = true;
        maxlength = 2;
        start = i;
      }
    }

    print_table(table);
    for (int k=3; k<=lenS; k++) {
      for(int i=0; i<lenS-k+1; i++) {
        int j = i+k-1;
        if(table[i+1][j-1] == 1 &&
           (s[i] == s[j])){
          table[i][j] = true;
          if(k > maxlength) {
            start = i;
            maxlength = k;
          }
        }
      }
    }
    print_table(table);
    cout << "start: " << start << " maxlength: " << maxlength << endl;
    substr = s.substr(start, maxlength);
    return substr;
  }

  void print_table(vector<vector<bool>> & table)
  {
    cout << "\nPrint DP table" << endl;
    for(int i=0; i<table[0].size(); i++){
      for(int j=0; j<table[0].size(); j++){
        cout << table[i][j] << " ";
      }
      cout << endl;
    }
  }
};

int main(int argc, char *argv[])
{
  string s;
  string result;
  Solution soln;

  cout << "Input: " ;
  cin >> s;
  result = soln.longestPalindrome(s);
  cout << "Output: " << result << endl;
  return 0;
}
