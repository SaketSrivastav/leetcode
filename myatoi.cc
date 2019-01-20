#include <iostream>
#include <climits>

using namespace std;

class Solution {
public:
    int my_atoi(char *s) {
        int result = 0, prev_result = 0, i = 0;
        bool is_pos = true;
        char *t = s;

        printf("Number range: (%d,%d)\n", INT_MIN, INT_MAX);
        do {
            if(t == nullptr) break;
            if(t[i] == '\0') break;
            if(t[i] == ' ') { i++ ; continue;}
            if(t[i] == '-' && result == 0) {
                is_pos = false;
                i++;
                continue;
            }
            if(t[i] == '+' && result == 0) {i++ ; continue;}
            if(t[i] == '+' && result != 0) {
                printf("Invalid number");
                break;
            }

            if(t[i] == '.') {cout << "Floating point number not suppeorted" << endl; break;}
            if(t[i] < '0' || t[i] > '9'){ i++ ; continue;};

            if(is_pos == false && t[i] == '-') {
                cout << "Invalid number" << endl ;
                break;
            }

            printf("appending %u to result %u\n",
                   (int(t[i]) - int('0')), result);
            result = (result * 10) + (int(t[i]) - int('0'));
            if(prev_result > result) {
                cout << "Overflow detected" << endl;
                if(is_pos == false) result = INT_MIN;
                else result = INT_MAX;
                break;
            }
            i++;
        }while(t[i] != '\0');

        if(is_pos == false && result != INT_MIN) result = -result;

        cout << "Result " << result << endl;
        return result;
    }
};

int main(int argc, char *argv[])
{
    char s[50];
    Solution soln;

    cout << "Please enter a number: ";
    cin >> s;

    soln.my_atoi(s);

    return 0;
}
