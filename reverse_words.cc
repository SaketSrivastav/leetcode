#include <iostream>

using namespace std;

void swap(char& a, char& b)
{
    char temp = a;
    a = b;
    b = temp;
}

void reverse(int begin, int end, string& s)
{
    cout << "Reversing: " << s.substr(begin, end-begin) << endl;
    while(begin < end) {
        char temp = s.at(begin);
        s.at(begin) = s.at(end);
        s.at(end) = temp;
        begin++;
        end--;
    }
}

void reverse_words(string& s)
{
    cout << "Given string: " << s
         << "\nlength " << s.length() << endl;
    if(s.length() == 0) return;
    if(s.length() == 1) return;

    // Reverse each word in the string.
    int begin = 0;
    int end = 0;
    while(end < s.length()) {
        end++;
        if(end == s.length())
            break;

        if(s.at(end) == ' ') {
            reverse(begin, end, s);
            begin = end + 1;
        }
        else if(s.at(end) == '\0') {
            cout << "String ends" << endl;
            reverse(begin, end-1, s);
        }
    }

    reverse(0, end-1, s);
    cout << "Reverse word string: " << s << endl;
    return;
}

int main(int argc, char *argv[])
{
    string s = "i love programming";
    reverse_words(s);

    s = "";
    reverse_words(s);

    s = "programming";
    reverse_words(s);

    return 0;
}
