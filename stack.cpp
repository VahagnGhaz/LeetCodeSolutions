#include <unordered_set>
#include <iostream>
#include <vector>
#include <stack>
#include <unordered_map>
#include <algorithm>
#include <iostream>
using namespace std;
// Definition for singly-linked list.
struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// Implement Queue using Stacks
class MyQueue
{
public:
    stack<int> st1, st2;
    int capacity;
    MyQueue()
    {
        capacity = 0;
    }

    void push(int x)
    {
        st1.push(x);
    }

    int pop()
    {
        if (!st2.empty())
        {
            int res = st2.top();
            st2.pop();
            return res;
        }
        if (st1.empty())
            throw runtime_error("Queue is empty");
        while (!st1.empty())
        {
            st2.push(st1.top());
            st1.pop();
        }
        int res = st2.top();
        st2.pop();
        return res;
    }

    int peek()
    {
        if (!st2.empty())
            return st2.top();
        if (st1.empty())
            throw runtime_error("Queue is empty");

        while (!st1.empty())
        {
            st2.push(st1.top());
            st1.pop();
        }
        return st2.top();
    }

    bool empty()
    {
        return st1.empty() && st2.empty();
    }
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */

class Solution
{
public:
    bool isValid(string s)
    {
        if (s.size() % 2 == 1)
            return false;
        unordered_map<char, char> closeOpenMap = {
            {'}', '{'},
            {')', '('},
            {']', '['}};
        stack<char> st;
        for (const char &c : s)
        {
            if (!st.empty() && closeOpenMap.count(c))
            {
                if (st.top() == closeOpenMap[c])
                    st.pop();
                else
                    return false;
            }
            else
                st.push(c);
        }
        return st.empty();
    }
};

int main()
{
    MyQueue myQueue = MyQueue();
    myQueue.push(1);         // queue is: [1]
    myQueue.push(2);         // queue is: [1, 2] (leftmost is front of the queue)
    cout << myQueue.peek();  // return 1
    cout << myQueue.pop();   // return 1, queue is [2]
    cout << myQueue.empty(); // return false
    // Solution s;
    // int pos = -1;
    // string str = "()";
    // bool res = s.isValid(str);

    // cout << res;
    // while (res != nullptr)
    // {
    //     cout << res->val;
    //     res = res->next;
    // }

    return 0;
}