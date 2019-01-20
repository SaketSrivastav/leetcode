#include <iostream>
#include <map>
#include <vector>

using namespace std;

class Trie {
private:
  map<char, Trie*> next = {};
  bool isword = false;
public:
  /** Initialize your data structure here. */
  Trie() {

  }

  /** Inserts a word into the trie. */
  void insert(string word) {
    Trie *node = this;
    for(char ch : word) {
      if(!node->next.count(ch)) {
        node->next[ch] = new Trie();
      }
      node = node->next[ch];
    }
    node->isword = true; // Mark the variable true because the last node maps to a word.
  }

  /** Returns if the word is in the trie. */
  bool search(string word) {
    Trie *node = this;
    for(char ch : word) {
      if(!node->next.count(ch)) {
        cout << "ch " << ch << " not found" << endl;
        return false;
      }
      node = node->next[ch];
    }

    return node->isword;
  }

  /** Returns if there is any word in the trie that starts with the given prefix. */
  bool startsWith(string prefix) {
    Trie *node = this;
    for(char ch : prefix) {
      if(!node->next.count(ch)) {
        cout << "ch " << ch << " not found" << endl;
        return false;
      }
      node = node->next[ch];
    }

    return true; // Return true because if we reach here then prefix exists in the trie
  }

  string lcp(vector<string> & strs) {
    int lcp_len = 0;
    Trie *node = this;
    string result = "";

    if(strs.empty()) return "";
    if(strs.size() == 1) return strs[0];

    for (auto it = strs.begin(); it != strs.end(); ++it) {
      node->insert(*it);
    }

    for(char ch : strs[0]) {
      if(!node->next.count(ch)) {
        break;
      }

      if(node->next.size() > 1){
        break;
      }

      node = node->next[ch];
      result += ch;
    }

    return result;
  }
};


int main(int argc, char *argv[])
{
  Trie *root = new Trie();
  //vector<string> lcp_test1 = {{"flower"}, {"flow"}, {"flight"}};
  //vector<string> lcp_test2 = {{"dog"}, {"racecar"}, {"car"}};
  vector<string> lcp_test3 = {{"aa"}, {"a"}};

  // cout << "lcp(flower, flow, flight): " << root->lcp(lcp_test1) << endl;
  // cout << "lcp(dog, racecar, car): " << root->lcp(lcp_test2) << endl;
  cout << "lcp(aa, a): " << root->lcp(lcp_test3) << endl;

  return 0;
}
