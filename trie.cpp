#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
using namespace std;
struct TrieNode {
  bool endOfString;
  unordered_map<char, TrieNode *> children;
};
// 208. Implement Trie (Prefix Tree)
class Trie {
public:
  TrieNode *root;
  Trie() { root = new TrieNode(); }

  void insert(string word) {
    TrieNode *node = root;
    for (char letter : word) {
      if (node->children.count(letter) == 0)
        node->children[letter] = new TrieNode();
      node = node->children[letter];
    }

    node->endOfString = true; // last node
  }

  bool search(string word) {
    TrieNode *node = root;
    for (char letter : word) {
      if (node->children.count(letter) == 0)
        return false;
      node = node->children[letter];
    }
    return node->endOfString;
  }

  bool startsWith(string prefix) {
    TrieNode *node = root;
    for (char letter : prefix) {
      if (node->children.count(letter) == 0)
        return false;
      node = node->children[letter];
    }
    return true;
  }
};

class WordDictionary {
public:
  TrieNode *root;
  WordDictionary() { root = new TrieNode(); }

  void addWord(string word) {
    TrieNode *node = root;
    for (char letter : word) {
      if (node->children.count(letter) == 0)
        node->children[letter] = new TrieNode();
      node = node->children[letter];
    }

    node->endOfString = true; // last node
  }

  //   bool bfs(TrieNode *root, string word) {
  // queue<TrieNode *> q;
  // q.push(root);
  // while (!q.empty()) {
  //   TrieNode *node = q.front();
  //   q.pop();
  //   for (auto &pair : node->children) { // {"a": TrieNode * node}
  //     if (bfs(pair.second, word))
  //       return true;
  //     q.push()
  //   }
  //     }
  //   }
  bool search(string word) {
    TrieNode *node = root;
    for (char letter : word) {
      if (letter == '.') {
        queue<TrieNode *> q;
        q.push(node);
        while (!q.empty()) {
          TrieNode *node = q.front();
          q.pop();
          for (auto &pair : node->children) { // {"a": TrieNode * node}
            if (search(word))
              return true;
            // q.push()
          }
        }
        else {
          if (node->children.count(letter) == 0)
            return false;
          node = node->children[letter];
        }
      }
      return node->endOfString;
    }
  };
};
int main() {
  Trie trie = Trie();
  trie.insert("apple");
  cout << trie.search("apple") << endl;   // return True
  cout << trie.search("app") << endl;     // return False
  cout << trie.startsWith("app") << endl; // return True
  trie.insert("app");
  cout << trie.search("app") << endl; // return True
  return 0;
}
