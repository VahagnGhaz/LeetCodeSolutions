#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;
struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

struct DoubleListNode {
  int val;
  DoubleListNode *next;
  DoubleListNode *prev;
  DoubleListNode() : val(0), next(nullptr), prev(nullptr) {}
  DoubleListNode(int x) : val(x), next(nullptr), prev(nullptr) {}
  DoubleListNode(int x, DoubleListNode *next, DoubleListNode *prev)
      : val(x), next(next), prev(prev) {}
};

class LRUCache {
  /*
  1) use hashmap for cash and queue for keeping up with lru priorities, where
  queue head->next is least recently used (lru) and tail is new added elements
  stl queue is not much of a use,
   cause we need to find element inside the queue
    and move them to tail (see updateLru)
  so we use linkedList pointers - headLru (dummyPtr) and tailLru.
  cause of the updateLru the TC is O(n) and has Time Limit Exceeded error

  2) O(1) solution: doubleLinkedList and keep ListNode inside hashmap
  SC of both solutions is O(n)
  */
public:
  int cap = 0;
  unordered_map<int, DoubleListNode *> cache;
  //   ListNode *lruHead, *lruTail;
  DoubleListNode *lruHead, *lruTail;

  LRUCache(int capacity) {
    cap = capacity;
    lruHead = lruTail = new DoubleListNode();
  }
  void put(int key, int value) {
    if (cache.count(key) == 0) // new key does not exist in cash
    {
      DoubleListNode *newNode = new DoubleListNode(value);
      //   if (cap == 0) // if no space in cash
      //   {
      //     ListNode *lru = lruHead->next;       // least recent used node
      //     cache.erase(lru->val);               // evict
      //     lruHead->next = lruHead->next->next; // remove from queue
      //     if (lru == lruTail)                  // no element left
      //       lruTail = lruHead;
      //     delete lru;
      //   } else
      //     cap--;
      //   lruTail = lruTail->next = new ListNode(key, nullptr); // add to the
      //   end
      // } else
      //   updateLru(key);
      cache[key] = newNode;
    }
    int get(int key) {
      if (cache.count(key) == 0)
        return -1;
      updateLru(key);
      return cache[key];
    }
    // sol1: time limit Exceeded
    //   void updateLru(int key) {
    //     ListNode *current = lruHead;
    //     ListNode *foundNode = nullptr;
    //     // why current->next->next? if (foundNode == tailNode) return; (no
    //     update) while (current->next->next) {
    //       if (current->next->val == key) { // value exists in cash
    //         ListNode *foundNode = current->next;
    //         current->next = current->next->next; // remove from list
    //         foundNode->next = nullptr;           // add to the end
    //         lruTail = lruTail->next = foundNode;
    //         break;
    //       } else
    //         current = current->next; // update pointer
    //     }
    //   }
    //   int get(int key) {
    //     if (cache.count(key) == 0)
    //       return -1;
    //     updateLru(key);
    //     return cache[key];
    //   }
    //   void put(int key, int value) {
    //     if (cache.count(key) == 0) // new key does not exist in cash
    //     {
    //       if (cap == 0) // if no space in cash
    //       {
    //         ListNode *lru = lruHead->next; // least recent used node
    //         cache.erase(lru->val);               // evict
    //         lruHead->next = lruHead->next->next; // remove from queue
    //         if (lru == lruTail)                  // no element left
    //           lruTail = lruHead;
    //         delete lru;
    //       } else
    //         cap--;
    //       lruTail = lruTail->next = new ListNode(key, nullptr); // add to the
    //       end
    //     } else
    //       updateLru(key);
    //     cache[key] = value;
    //   }
  };

  int main() {
    LRUCache lRUCache = LRUCache(2);
    lRUCache.put(1, 1); // cache is {1=1}
    lRUCache.put(2, 2); // cache is {1=1, 2=2}
    lRUCache.get(1);    // return 1
    lRUCache.put(3, 3); // LRU key was 2, evicts key 2, cache is {1=1, 3=3}
    lRUCache.get(2);    // returns -1 (not found)
    lRUCache.put(4, 4); // LRU key was 1, evicts key 1, cache is {4=4, 3=3}
    lRUCache.get(1);    // return -1 (not found)
    lRUCache.get(3);    // return 3
    lRUCache.get(4);    // return 4
  }
