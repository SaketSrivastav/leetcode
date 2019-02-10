#include <iostream>
#include <vector>

using namespace std;

bool is_match(string text, string pattern)
{
    cout << "Match:\n\ttext: " << text << "\n\tpattern: " << pattern << endl;
    if(pattern.empty()) return text.empty();
    if(text.empty()) return false;

    // Match first character of pattern or text
    bool first_match = (pattern[0] == text[0] || pattern[0] == '.') ? true : false;
    cout << "First Match:\n\ttext: " << text[0]
         << "\n\tpattern: " << pattern[0]
         << " --> " << (first_match ? "true" : "false") << endl;

    // If first character match then proceed with remaining text OR
    // in case of '*' move with same text to match multiple occurence of same char
    if(pattern.length() >= 2 && pattern[1] == '*') {
        // first_match means we check for the same character in text
        if(first_match) {
            cout << "Check for more occurrence of " << text[0] << endl;
            return is_match(text.substr(1, string::npos), pattern);
        }
        else {
            cout << "Check for next set of pattern " << endl;
            return is_match(text, pattern.substr(2));
        }
    } else {
        // match remaining text and pattern
        cout << "Check for next set of text " << text.substr(1) << " pattern " << pattern.substr(1) << endl;
        return first_match && (is_match(text.substr(1, string::npos), pattern.substr(1, string::npos)));
    }
}

bool is_match_dp(string text, string pattern)
{
    if(!pattern.length() || !text.length()) return false;

    vector<vector<bool>> dp(pattern.length()+1, vector<bool>(text.length()+1, false));
    dp[0][0] = true;

    for(int i=1; i<dp.size(); i++) {
        if(pattern[i-1] == '*')
            dp[0][i] = dp[0][i-2];
    }

    for(int i=1; i<dp.size(); i++) {
        for(int j=1; j<dp[0].size(); j++) {
            if(text[i] == pattern[j-1] || pattern[j-1] == '.') {
                dp[i][j] = dp[i-1][j-1];
            } else if(pattern[j-1] == '*') {
                dp[i][j] = dp[i][j-2];
            } else if(text[i-1] == pattern[j-2] || pattern[j-2] == '.') {
                dp[i][j] = dp[i-1][j];
            }
        }
    }

    return dp[dp.size()-1][dp[0].size()-1];
}

int main(int argc, char *argv[])
{
    string text1 = "aabccd";
    string pattern1 = "a*b*c*d";
    // string pattern1 = ".*";
    cout << "is_match(" << text1 << ", " << pattern1 << ") = "
         << (is_match(text1, pattern1) ? "true" : "false") << endl;
    cout << "is_match_dp(" << text1 << ", " << pattern1 << ") = "
         << (is_match_dp(text1, pattern1) ? "true" : "false") << endl;
    return 0;
}
