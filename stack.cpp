#include <algorithm>
#include <iostream>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;
// Definition for singly-linked list.
struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// 232. Implement Queue using Stacks
class MyQueue {
public:
  stack<int> st1, st2;
  int capacity;
  MyQueue() { capacity = 0; }

  void push(int x) { st1.push(x); }

  int pop() {
    if (!st2.empty()) {
      int res = st2.top();
      st2.pop();
      return res;
    }
    if (st1.empty())
      throw runtime_error("Queue is empty");
    while (!st1.empty()) {
      st2.push(st1.top());
      st1.pop();
    }
    int res = st2.top();
    st2.pop();
    return res;
  }

  int peek() {
    if (!st2.empty())
      return st2.top();
    if (st1.empty())
      throw runtime_error("Queue is empty");

    while (!st1.empty()) {
      st2.push(st1.top());
      st1.pop();
    }
    return st2.top();
  }

  bool empty() { return st1.empty() && st2.empty(); }
};

class MinStack {
public:
  // stack<int> minValue;
  stack<pair<int, int>> stack; // <value, minValueSoFar>
  int minSoFar;
  MinStack() {}
  void push(int val) {
    if (stack.empty())
      minSoFar = val;
    else
      minSoFar = min(stack.top().second, val);
    stack.push(pair{val, minSoFar});
  }
  void pop() { stack.pop(); }

  int top() { return stack.top().first; }

  int getMin() { return stack.top().second; }
};
// int main() {
//   MinStack minStack = MinStack();
//   minStack.push(-2);
//   minStack.push(0);
//   minStack.push(-1);
//   cout << minStack.getMin() << endl; // return -3
//   cout << minStack.top() << endl;    // return 0
//   minStack.pop();
//   cout << minStack.getMin() << endl; // return -2
//   return 0;
// }

class Solution {
public:
  // 20. Valid Parentheses
  bool isValid(string s) {
    if (s.size() % 2 == 1)
      return false;
    unordered_map<char, char> closeOpenMap = {
        {'}', '{'}, {')', '('}, {']', '['}};
    stack<char> st;
    for (const char &c : s) {
      if (!st.empty() && closeOpenMap.count(c)) { // if has opened parentheses
        if (st.top() == closeOpenMap[c])
          st.pop();
        else
          return false; // if latest is not closing parentheses
      } else
        st.push(c); // add opening parentheses
    }
    return st.empty();
  }
};

// int main() {
//   MyQueue myQueue = MyQueue();
//   myQueue.push(1);         // queue is: [1]
//   myQueue.push(2);         // queue is: [1, 2] (leftmost is front of the
//   queue) cout << myQueue.peek();  // return 1 cout << myQueue.pop();   //
//   return 1, queue is [2] cout << myQueue.empty(); // return false
//   // Solution s;
//   // int pos = -1;
//   // string str = "()";
//   // bool res = s.isValid(str);

//   // cout << res;
//   // while (res != nullptr)
//   // {
//   //     cout << res->val;
//   //     res = res->next;
//   // }

//   return 0;
// }