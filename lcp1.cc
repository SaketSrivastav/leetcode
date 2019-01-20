#include <iostream>
#include <map>
#include <vector>

using namespace std;

const ALPHABETS 26

class TrieNode {
private:
    TrieNode * parent;
    TrieNode * children[ALPHABETS];
};

class Trie {
private:

public:
  /** Initialize your data structure here. */
  Trie() {

  }

  /** Inserts a word into the trie. */
  void insert(string word) {
  }

  /** Returns if the word is in the trie. */
  bool search(string word) {
  }

  /** Returns if there is any word in the trie that starts with the given prefix. */
  bool startsWith(string prefix) {
  }

  string lcp(vector<string> & strs) {
  }
};
