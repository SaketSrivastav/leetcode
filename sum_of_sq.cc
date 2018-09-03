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


// Correct solution: uses DP and builds the table bottom up
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
    cout << endl;
    for(int i=0; i<dp.size(); i++)
      printf("%d ", dp[i]);
    cout << endl;
    dp[i] = i;
    printf("\ndp[%d] = %d\n", i, dp[i]);

    // Go through all smaller numbers to
    // to recursively find minimum
    for (int x = 1; x <= i; x++) {
      int temp = x*x;
      if (temp > i)
      {
        printf("tmp %d > i %d\n", temp, i);
        break;
      }
      else{
        printf("dp[%d] = min(dp[%d], 1+dp[%d]) = %d\n",
               i, dp[i], (i-temp),
               min(dp[i], 1+dp[i-temp]));
        dp[i] = min(dp[i], 1+dp[i-temp]);
      }
    }
  }

  // Store result and free dp[]
  int res = dp[n];

  return res;
}

// Greedy solution which computes the perfect squares top down from sqrt(n) -> 0
// Counter example :
//      22 => Greedy soln: 4 = (4^2 + 2^2 + 1^1 + 1^1)
//            DP soln: 3 = 3^2 + 3^2 + 2^2
int sum_of_sq_gr(int n) {
  vector<int> l;
  int d = 0;

  if(n <= 0) return 0;

  d = n;

  while(d != 0) {
    int sum = 0;
    int sq_n = 0;
    sq_n = sqrt(d);
    cout << "sq_n " << sq_n << " d = " << d << endl;
    l.push_back(sq_n);
    for (int i = 0; i < l.size(); ++i) {
      cout << "summing " << l[i] << endl;
      sum += (l[i] * l[i]);
    }

    cout << "sum = " << sum << endl;
    d = n - sum;
  }

      cout << "Perfect squares used: " << endl;
    for (int i = 0; i < l.size(); ++i) {
      cout << l[i] << " -> "<< l[i]*l[i] << " " ;
    }
    cout << endl;

  return l.size();
}

void test_sum_of_sq(int n) {
  cout << "sum_of_sq_dp(" << n << "): "<< sum_of_sq_dp(n) << endl;
  cout << "sum_of_sq_gr(" << n << "): "<< sum_of_sq_gr(n) << endl;
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
