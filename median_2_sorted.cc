#include <iostream>
#include <vector>

using namespace std;

// Brute Force: Merge 2 sorted arrays and find median.
//              i) if length of merged array is even then m = x+y/2
//             ii) if length if merged array is odd then m = x/2;
// Log(n) soln: Using the sorted property and binary search create partitions such
//              that all elements on left of both arrays are greater than all the elements in the
//              right side. Once we do that we get the relevant numbers to calculate median.
// There are two sorted arrays nums1 and nums2 of size m and n respectively.
// Find the median of the two sorted arrays. The overall run time complexity should be O(log (m+n)).
//
// Solution
// Take minimum size of two array. Possible number of partitions are from 0 to m in m size array.
// Try every cut in binary search way. When you cut first array at i then you cut second array at (m + n + 1)/2 - i
// Now try to find the i where a[i-1] <= b[j] and b[j-1] <= a[i]. So this i is partition around which lies the median.
//
// Time complexity is O(log(min(x,y))
// Space complexity is O(1)
//

class Solution {
public:
  double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
    int pX = 0, pY = 0, start = 0, end = 0;
    int lenX = 0, lenY = 0;
    int maxLeftX = 0, maxLeftY = 0;
    int minRightX = 0, minRightY = 0;

    // Flip the input if input array 1 has length greater than array 2
    if(nums1.size() > nums2.size())
      return findMedianSortedArrays(nums2, nums1);

    lenX = nums1.size();
    lenY = nums2.size();
    printf("Process arrays of lenX %d lenY %d\n", lenX, lenY);
    start = 0;
    end = lenX;
    while(start <= end) {
      printf("Start %d end %d\n", start, end);
      pX = (start + end) / 2;
      pY = ((lenX + lenY + 1) / 2) - pX;

      printf("pX %d pY %d\n", pX, pY);
      maxLeftX = (pX == 0) ? INT_MIN : nums1[pX-1];
      minRightX = (pX == lenX) ? INT_MAX : nums1[pX];

      maxLeftY = (pY == 0) ? INT_MIN : nums2[pY-1];
      minRightY = (pY == lenY) ? INT_MAX : nums2[pY];

      printf("maxLeftX %d maxLeftY %d\n", maxLeftX, maxLeftY);
      printf("minRightX %d minRightY %d\n", minRightX, minRightY);

      if(maxLeftX <= minRightY && maxLeftY <= minRightX) {
        if(((lenX + lenY) % 2) == 0){
          printf("Found elements: %d and %d\n", max(maxLeftX, maxLeftY),
                 min(minRightX, minRightY));
          return (double)(max(maxLeftX, maxLeftY) + min(minRightX, minRightY)) / 2;
        }
        else {
          printf("Found elements: %d \n", max(maxLeftX, maxLeftY));
          return max(maxLeftX, maxLeftY);
        }
      } else if(maxLeftX > minRightY) {
        end = pX - 1;
        printf("Too far right, move left end = %d\n", end);
      } else if(maxLeftY > minRightX) {
        start = pX + 1;
        printf("Too far left, move right start = %d\n", start);
      }
    }
    printf("Invalid input\n");
    return INT_MIN;
  }
};

int main(int argc, char *argv[])
{
  vector<int> x = {1, 3};
  vector<int> y = {2};
  Solution soln;

  cout << "x = ";
  for (int i = 0; i < x.size(); ++i) {
    cout << x[i] << " ";
  }
  cout << endl;

  cout << "y = ";
  for (int i = 0; i < y.size(); ++i) {
    cout << y[i] << " ";
  }
  cout << endl;

  double result = soln.findMedianSortedArrays(x, y);
  cout << "Median of x and y is " << result << endl;

  return 0;
}
