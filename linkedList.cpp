#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;
// Definition for singly-linked list.
// struct ListNode
// {
//     int val;
//     ListNode *next;
//     ListNode(int x) : val(x), next(nullptr) {}
// };
struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};
ListNode *vectorToLinkedList(const vector<int> &vec) {
  if (vec.empty()) {
    return nullptr;
  }

  ListNode *head = new ListNode(vec[0]);
  ListNode *current = head;

  for (int i = 1; i < vec.size(); i++) {
    current->next = new ListNode(vec[i]); // new ListNode{vec[i], nullptr};
    current = current->next;
  }
  return head;
}

class Solution {
public:
  // 141. Linked List Cycle
  bool hasCycle(ListNode *head) {
    // hash set
    // unordered_set<ListNode *> nodes;
    // while (head != nullptr)
    // {
    //     if (nodes.count(head))
    //         return true;
    //     nodes.insert(head);
    //     head = head->next;
    // }
    // return false;

    // fast slow pointer
    ListNode *fast = head;
    ListNode *slow = head;
    while (fast != nullptr && fast->next != nullptr) {

      slow = slow->next;
      fast = fast->next->next;
      if (slow == fast)
        return true;
    }
    return false;
  }
  // 21. Merge Two Sorted Lists
  ListNode *mergeTwoLists(ListNode *list1, ListNode *list2) {
    ListNode *head, *l;
    head = l = new ListNode();
    while (list1 != nullptr && list2 != nullptr) {
      if (list1->val < list2->val) {
        l->next = list1; // new ListNode(list1->val);
        list1 = list1->next;
      } else {
        l->next = list2; // new ListNode(list2->val);
        list2 = list2->next;
      }
      l = l->next;
    }
    l->next = list1 == nullptr ? list2 : list1;
    return head->next;
  }
  // 203. Remove Linked List Elements
  ListNode *removeElements(ListNode *head, int val) {
    ListNode *dummy = new ListNode(0, head);
    // tail->next = head;
    ListNode *tail = dummy;
    while (tail != nullptr && tail->next != nullptr) {
      if (tail->next->val == val) {
        // ListNode *nodeToRemove = tail->next;
        // tail->next = nodeToRemove->next;
        // delete nodeToRemove;
        tail->next = tail->next->next;
      }
      // tail = tail->next->next;
      else
        tail = tail->next;
    }
    return dummy->next;
  }
  // 206. Reverse Linked List
  ListNode *reverseList(ListNode *head) {
    ListNode *curr = head;
    ListNode *nxt = nullptr;
    ListNode *prev = nullptr;
    while (curr != nullptr) {
      nxt = curr->next;
      curr->next = prev;
      prev = curr;
      curr = nxt;
    }
    return prev;
  }
  // 83. Remove Duplicates from Sor
  ListNode *deleteDuplicates(ListNode *head) {
    // ListNode * dummy = new ListNode(0, head);
    ListNode *tail = head;
    while (tail != nullptr && tail->next != nullptr) {
      if (tail->val == tail->next->val)
        tail->next = tail->next->next;
      else
        tail = tail->next;
    }
    return head;
  }
  // 2. Add Two Numbers
  ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
    int sum, remainder = 0;
    ListNode *sumList = new ListNode();
    ListNode *head = sumList;
    int a, b;
    while (l1 || l2) {
      sumList = sumList->next =
          new ListNode(); // add new node and update sumList
      a = 0, b = 0, remainder = 0;
      if (l1) // if l1 is not none get the value and update
      {
        a = l1->val;
        l1 = l1->next;
      }
      if (l2) {
        b = l2->val;
        l2 = l2->next;
      }
      sum = a + b + remainder;

      if (sum > 9) {
        sum -= 10;
        remainder = 1;
      }
      sumList->val = sum;
    }
    if (remainder)
      sumList->next = new ListNode(1);

    return head->next;
  }
  // 143. Reorder List
  void reorderList(ListNode *head) {
    // edge case is handled, but has speed improvement if included
    if (!head)
      return;
    ListNode *current = head;
    int length = 0;
    // traverse and find len of list: O(n)
    while (current != nullptr) {
      current = current->next;
      length++;
    }
    // find middle node
    int half = length % 2 == 0 ? length / 2 : length / 2 + 1;
    int idx = 0;
    current = head;
    while (idx < half) {
      current = current->next;
      idx++;
    }
    // reverse from half till the end
    ListNode *previous = nullptr; // always initialize to nullptr
    ListNode *nxt = nullptr;
    while (current != nullptr) {
      nxt = current->next;
      current->next = previous;
      previous = current;
      current = nxt;
    }
    // now previous points to last element of the list
    // and goes backward till the half 5->4->null
    // head 1->2->3->4->5, need to have 1->5->3->4->3
    // intersect two lists
    ListNode *nxt1 = nullptr;
    ListNode *nxt2 = nullptr;
    current = head;
    while (previous != nullptr) {
      nxt1 = current->next;
      current->next = previous;
      nxt2 = previous->next;
      previous->next = nxt1;
      current = nxt1;
      previous = nxt2;
    }
    if (nxt1 != nullptr)    // if list is empty or has one elem => nxt is NULL
      nxt1->next = nullptr; // ** nxt1 is the last element
  }

  ListNode *removeNthFromEnd(ListNode *head, int n) {
    // n is postion from tail
    if (head == nullptr)
      return head;
    if (head->next == nullptr && n == 1) // **
      return nullptr;
    ListNode *current = head;
    int length = 0;
    // traverse and find len of list: O(n)
    while (current) {
      current = current->next;
      length++;
    }
    n = length - n; /// n is postion from head (3)
    ListNode *node = new ListNode(-1, head);
    int idx = 0;

    // [1, 2](2) vs [1,2,3,4,5](2)
    while (idx <= n) {
      node = node->next;
      idx++;
    }
    // node->next is the element we need to remove
    node->next = node->next->next;
    return head;
  }
};
int main() {
  Solution s;
  int pos = 2;
  vector<int> list1 = {1, 2, 3, 4, 5};
  // vector<int> list2 = {5, 6, 4};

  ListNode *h1 = vectorToLinkedList(list1);
  // ListNode *h2 = vectorToLinkedList(list2);
  ListNode *res = s.removeNthFromEnd(h1, pos);

  while (res != nullptr) {
    cout << res->val;
    res = res->next;
  }

  return 0;
}