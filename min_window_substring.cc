#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

// Input: string s
//        pattern t
const int DEBUG = 0;

string min_win_substr(string s, string t)
{
    // Sanity check
    if(t.empty() || s.empty()) return "";
    if(t.length() > s.length()) return "";

    cout << "Input: " << s << ", " << t << endl;

    // Map to store all ascii char
    unordered_map<char, int> char_map;
    // store the occurence of each char in pattern
    for(auto ch : t) {
        char_map[ch] += 1;
    }

    if(DEBUG) {
        cout << "Character hash map: " << endl;
        for(auto ch : char_map)
            cout << ch.first << " -> " << ch.second << endl;

    }
    int left = 0, right = 0; // Window containing all pattern characters
    int sIdx = 0, eIdx = 0;  // Min length window containing pattern
    int remaining = t.length(); // All remaining characters that needs to match pattern in the given window
    while(right < s.length()) {
        // If char is found in string and pattern
        if(DEBUG) {
            cout << "curr_char " << s[right] << endl;
            cout << "remaining " << remaining << endl;
        }
        if(char_map.find(s[right]) != char_map.end()) {
            remaining--;
            char_map[s[right]]--;
            if(DEBUG)
                cout << "char found " << s[right] << " remaining " << remaining << endl;
        }

        right++;

        while(remaining == 0) {
            // Found a window, check if it minimum then adjust sIdx and eIdx
            if(DEBUG) {
                cout << "window found: " << s.substr(left, right-left)
                     << " index " << left << " " << right << endl;
            }

            if(eIdx == 0 || (right - left) <= (eIdx - sIdx)) {
                sIdx = left;
                eIdx = right;
                if(DEBUG)
                cout << "curr min window " << sIdx << " " << eIdx << endl;
            }

            // Try to shrink the window
            if(DEBUG)
                cout << "\nshrink from left " << left+1 << " curr_left " << s[left] << endl;
            if(char_map.find(s[left]) != char_map.end()) {
                // increase the count because we need to find it in the new window
                // therefore we need to increase the remaining character count
                char_map[s[left]] += 1;
                remaining++;
            }

            left++;
        }
    }

    return s.substr(sIdx, (eIdx-sIdx));
}

int main(int argc, char *argv[])
{
    cout << "test1: " << min_win_substr("acbdnracbn", "acbn") << endl;
    cout << "test2: " << min_win_substr("aaaaaaaaaaa", "b") << endl;
    cout << "test3: " << min_win_substr("acbdnracbna", "aacbn") << endl;
    return 0;
}
