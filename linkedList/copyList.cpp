#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;
// 138. Copy List with Random Pointer
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
  Node *vectorToList(vector<vector<int>> vec) {
    unordered_map<int, Node *> map;
    Node *currentCopy = nullptr;
    int idx = 0;
    for (auto v : vec) // populate without connecting
      map[idx++] = new Node(v[0]);
    int vecLength = idx;
    map[vecLength] = nullptr; // last element
    idx = 0;

    int randomNodeIndex;
    for (auto v : vec) {
      map[idx]->next = map[idx + 1]; // next pointer
      if (v[1] != -1)                // random pointer
        randomNodeIndex = v[1];
      else
        randomNodeIndex = vecLength; // last index is for nullptr
      map[idx]->random = map[randomNodeIndex];
      idx++;
    }
    return map[0];
  }

  Node *copyRandomList(Node *head) {
    unordered_map<Node *, Node *> map; // {oldNode, newNode}
    Node *current = head;
    // create nodes without connecting and populate the map
    while (current != nullptr) {
      map[current] = new Node(current->val);
      current = current->next;
    }
    map[nullptr] = nullptr; // last node with random pointer
    current = head;
    while (current != nullptr) {
      map[current]->next = map[current->next];
      map[current]->random = map[current->random];
      current = current->next;
    }
    return map[head];
  }
};

int main() {
  Solution s;
  vector<vector<int>> vec = {{3, -1}, {3, 0}, {3, -1}};
  Node *head = s.vectorToList(vec);
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