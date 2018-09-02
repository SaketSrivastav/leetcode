#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

// Recursive brute force: O(n^n)
int sum_of_sq(int n) {
  int res = n;

  // cout << "calc: " << n ;
  // 0 = 0
  // 1 = 1^1 = 1
  // 2 = 1^2 + 1^2 = 2
  // 3 = 1^2 + 1^2 + 1^2 = 3
  if(n <= 3) {
    // cout << "return: " << n << endl;
    return n;
  }

  for(int i = 1; i<=sqrt(n) ; i++) {
    int tmp = i * i;
    int res1;
    if(tmp > n) break;

    // cout << " tmp: " << tmp << endl;
    res1 = 1+sum_of_sq(n - tmp);
    // cout << "min(" << res << ", " << res1 << ")" << endl;
    res = min(res, res1);
  }

  // cout << "return: " << res << endl;
  return res;
}


int sum_of_sq_dp(int n) {
  // Create a dynamic programming table
  // to store sq
  vector<int> dp;

  dp.resize(n+1);

  // getMinSquares table for base case entries
  dp[0] = 0;
  dp[1] = 1;
  dp[2] = 2;
  dp[3] = 3;

  // getMinSquares rest of the table using recursive
  // formula
  for (int i = 4; i <= (n); i++)
  {
    // max value is i as i can always be represented
    // as 1*1 + 1*1 + ...
    // cout << endl;
    // for(int i=0; i<dp.size(); i++)
    //   printf("%d ", dp[i]);
    // cout << endl;
    dp[i] = i;
    // printf("\ndp[%d] = %d\n", i, dp[i]);

    // Go through all smaller numbers to
    // to recursively find minimum
    for (int x = 1; x <= i; x++) {
      int temp = x*x;
      if (temp > i)
      {
        // printf("tmp %d > i %d\n", temp, i);
        break;
      }
      else{
        // printf("dp[%d] = min(dp[%d], 1+dp[%d]) = %d\n",
        //        i, dp[i], (i-temp),
        //        min(dp[i], 1+dp[i-temp]));
        dp[i] = min(dp[i], 1+dp[i-temp]);
      }
    }
  }

  // Store result and free dp[]
  int res = dp[n];

  return res;
}

void test_sum_of_sq(int n) {
  cout << "sum_of_sq_dp(" << n << "): "<< sum_of_sq_dp(n) << endl;
  // cout << "sum_of_sq(" << n << "): "<< sum_of_sq(n) << endl;
}

int main(int argc, char *argv[])
{
  if(!atoi(argv[1])) return 0;
  int n = atoi(argv[1]);
  cout << "input: " << n << endl;
  test_sum_of_sq(n);
  return 0;
}
