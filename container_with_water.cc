#include <iostream>
#include <climits>
#include <vector>

using namespace std;

// 2 pointer approach to maximize area

class Solution {
public:
    int maxArea(vector<int>& height) {
        int i = 0;
        int j = height.size() - 1;
        int max_area = 0;

        while(i < j) {
            printf("compare max_area %d and %d,%d\n",
                   max_area, height[i], height[j]);
            max_area = max(max_area, (height[i] * height[j]));
            if(height[i] < height[j])
                i++;
            else
                j--;
        }
        printf("Max_area = %d\n", max_area);
        return max_area;
    }
};

int main(int argc, char *argv[])
{
    vector<int> a = {1,8,6,2,5,4,8,3,7};
    class Solution soln;
    soln.maxArea(a);
    return 0;
}
