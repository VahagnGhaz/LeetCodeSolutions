#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;
// 146. LRU Cache
struct DoubleListNode {
  int val;
  int idx; // for tracking map key
  DoubleListNode *next;
  DoubleListNode *prev;
  DoubleListNode() : val(0), next(nullptr), prev(nullptr) {}
  DoubleListNode(int val, int idx)
      : val(val), idx(idx), next(nullptr), prev(nullptr) {}
  DoubleListNode(int val, int idx, DoubleListNode *next, DoubleListNode *prev)
      : val(val), idx(idx), next(next), prev(prev) {}
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
  SC of both solutions is O(n),
  ! doubleLinkedList head is keeping least recently
  used value, while tail is keeping the recently used value
  // CAREFUL
  // 1) value and index are different, need to update value every time
  // 2) can update the cache even if cache is not full
  // 3) when NewRecentlyUsed == leastRecentlyUsed is edge case
  */
public:
  int cap = 0;
  unordered_map<int, DoubleListNode *> cache;
  DoubleListNode *leastRecentlyUsed, *recentlyUsed; // head, tail

  LRUCache(int capacity) {
    cap = capacity;
    leastRecentlyUsed = recentlyUsed = nullptr;
  }
  void updateRecentlyUsed(int key) {
    DoubleListNode *NewRecentlyUsed = cache[key];
    if (NewRecentlyUsed == recentlyUsed) // no updated needed
      return;
    if (NewRecentlyUsed == leastRecentlyUsed)      // (see point (3) in docs)
      leastRecentlyUsed = leastRecentlyUsed->next; // new LRU
    else // NewRecentlyUsed->prev is not null:
      NewRecentlyUsed->prev->next = NewRecentlyUsed->next; // unbind

    NewRecentlyUsed->next->prev = NewRecentlyUsed->prev;
    NewRecentlyUsed->next = nullptr; // tail value
    NewRecentlyUsed->prev = recentlyUsed;

    recentlyUsed->next = NewRecentlyUsed;
    recentlyUsed = NewRecentlyUsed;
  }

  void addToCache(int key, int value) {
    DoubleListNode *newNode =
        new DoubleListNode(value, key, nullptr, recentlyUsed);
    if (recentlyUsed == nullptr) // the first added value
      leastRecentlyUsed = newNode;
    else
      recentlyUsed->next = newNode;
    recentlyUsed = newNode; // update tail to newest value
    cache[key] = newNode;
    cap--;
  }
  void removeLeastRecentlyUsed(int key, int value) {
    recentlyUsed->next = new DoubleListNode(value, key, nullptr, recentlyUsed);
    recentlyUsed = recentlyUsed->next;
    DoubleListNode *nodeToDelete = leastRecentlyUsed;
    leastRecentlyUsed->next->prev = nullptr; // unbind
    leastRecentlyUsed = leastRecentlyUsed->next;
    cache.erase(nodeToDelete->idx); // remove from cache
    delete nodeToDelete;
  }
  void put(int key, int value) {
    if (cap != 0 && cache.count(key) == 0) // (see point (2) in docs)
      addToCache(key, value);
    else {
      if (cache.count(key) != 0) { // new key exists in cache
        cache[key]->val = value;   // update value (see point (1) in docs)
        updateRecentlyUsed(key);
      } else // new key does not exists in cache
        removeLeastRecentlyUsed(key, value);
      cache[key] = recentlyUsed;
    }
  }
  int get(int key) {
    if (cache.count(key) == 0)
      return -1;
    updateRecentlyUsed(key);
    return cache[key]->val;
  }
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
