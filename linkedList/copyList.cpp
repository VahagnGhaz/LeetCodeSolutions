#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

class Node {
public:
  int val;
  Node *next;
  Node *random;

  Node(int _val) {
    val = _val;
    next = nullptr;
    random = nullptr;
  }
};

class Solution {
public:
  Node *vectorToBinary(vector<vector<int>> vec) {
    unordered_map<int, Node *> map;
    Node *currentCopy = nullptr;
    int idx = 0;
    for (auto v : vec)
      map[idx++] = new Node(v[0]);
    int length = idx;
    map[length] = nullptr; // last element
    // current = head;
    idx = 0;
    // for (auto &pair : map) {
    //   cout << pair.first << " " << pair.second << endl;
    // }
    int randomNodeIndex;
    for (auto v : vec) {
      map[idx]->next = map[idx + 1];
      if (v[1] != -1)
        randomNodeIndex = v[1];
      else
        randomNodeIndex = length;
      map[idx]->random = map[randomNodeIndex];
      idx++;
    }
    return map[0];
  }

  Node *copyRandomList(Node *head) {
    unordered_map<int, pair<int, Node *>> map; // {idx, (node->val, node)}
    Node *current = head;
    // create nodes without connecting and populate the map
    int idx = 0;
    while (current != nullptr) {
      map[idx] = pair{current->val, new Node(current->val)};
      current = current->next;
      idx++;
    }
    map[idx] = pair{-1, nullptr}; // last node with random pointer
    // iterate again, populate next and random pointers
    current = head;
    int randomNodeIndex, nextNodeIndex;
    idx = 0;
    while (current != nullptr) {

      if (current->next != nullptr)
        nextNodeIndex = current->next->val;
      else
        nextNodeIndex = -1; // last node

      map[idx].second->next = map[nextNodeIndex].second;
      if (current->random != nullptr)
        randomNodeIndex = current->random->val;
      else
        randomNodeIndex = -1;
      map[idx].second->random = map[randomNodeIndex].second;
      current = current->next;
      idx++;
    }
    return map[idx].second; // head
  }
};

int main() {
  Solution s;
  vector<vector<int>> vec = {{3, -1}, {3, 0}, {3, -1}};
  Node *head = s.vectorToBinary(vec);
  Node *res = s.copyRandomList(head);
  while (res != nullptr) {
    cout << res->val << " ";
    if (res->random != nullptr)
      cout << res->random->val << " ";
    else
      cout << "null ";
    res = res->next;
  }
  return 0;
}