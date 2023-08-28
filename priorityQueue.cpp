#include <algorithm>
#include <cmath>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

class KthLargest {
public:
  // cause we only add and not remove, keep only first k elements, the rest
  // won't be accessed, minHeap: the top is the smallest
  priority_queue<int, vector<int>, greater<int>> minHeap;
  int sizeK;
  KthLargest(int k, vector<int> &nums) {
    sizeK = k;
    for (int i = 0; i < nums.size(); i++) {
      minHeap.push(nums[i]); // takes care of ordering
      // If more than k elements are in the heap, pop the smallest
      if (minHeap.size() > k) {
        minHeap.pop();
      }
    }
  }
  // only keep largest k elements

  int add(int val) {
    // if (minHeap.size() != sizeK) // heap is not full
    // {
    //   minHeap.push(val); // takes care of ordering
    //   return minHeap.top();
    // }
    // // heap is full
    // int MinValue = minHeap.top();
    // if (val > MinValue) { // got a bigger value
    //   minHeap.pop();      // remove smallest
    //   minHeap.push(val);  // takes care of ordering
    //   return minHeap.top();
    // }
    // return MinValue;

    // more elegant
    minHeap.push(val);          // takes care of ordering
    if (minHeap.size() > sizeK) // heap is exceeded k elements
      minHeap.pop();            // remove smallest
    return minHeap.top();       // return smallest element of k size minHeap
  }
};

// int main(int argc, char const *argv[]) {
//   vector<int> nums = {};
//   // KthLargest kthLargest = KthLargest(3, nums);
//   KthLargest *obj = new KthLargest(1, nums);
//   cout << obj->add(3) << endl;
//   cout << obj->add(3) << endl;  // return 4 last value of ()
//   cout << obj->add(5) << endl;  // return 5
//   cout << obj->add(10) << endl; // return 5
//   cout << obj->add(9) << endl;  // return 8
//   cout << obj->add(4) << endl;  // return 8
//   return 0;
// }

class Solution {
public:
  int lastStoneWeight(vector<int> &stones) {
    // Time: O(nlogn)
    priority_queue<int> weights;
    int firstStone, secondStone;
    for (int stoneWeight : stones)
      weights.push(stoneWeight);
    while (weights.size() > 1) { // O(n)
      firstStone = weights.top();
      weights.pop(); // O(logn)
      secondStone = weights.top();
      weights.pop();
      if (firstStone != secondStone)
        weights.push(firstStone - secondStone); // O(logn)
    }
    weights.push(0); // in case weights are empty
    return weights.top();
  }

  vector<vector<int>> kClosest(vector<vector<int>> &points, int k) {
    vector<vector<int>> closesKPoints;
    // 1. sort Time: O(nlogn + k)

    // auto closerToOrigin = [](const vector<int> &a, const vector<int> &b) {
    //   return sqrt(pow(a[0], 2) + pow(a[1], 2)) <
    //          sqrt(pow(b[0], 2) + pow(b[1], 2));
    // };
    // sort(points.begin(), points.end(), closerToOrigin);
    // for (int i = 0; i < k; i++)
    //   closesKPoints.push_back(points[i]);

    // 2. priority_queue: Time ((n + k)logn)
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>,
                   greater<pair<int, pair<int, int>>>>
        pointAndDistances; //  min heap {distance,{x,y}}
    int pointsSize = points.size();
    for (int i = 0; i < pointsSize; i++) {
      int y = points[i][1];
      int x = points[i][0];
      int distance = y * y + x * x;
      // use the first element of the pair to sort the heap be default
      pointAndDistances.push({distance, {x, y}});
    }

    while (k--) {
      auto x = pointAndDistances.top();
      pointAndDistances.pop();

      closesKPoints.push_back({x.second.first, x.second.second});
    }
    return closesKPoints;
  }
  //
};
int main() {
  Solution s;
  vector<vector<int>> points = {{3, 3}, {5, -1}, {-2, 4}};
  vector<vector<int>> res = s.kClosest(points, 2);
  // cout << res;
  for (auto vec : res) {
    for (auto i : vec)
      cout << i << endl;
  }

  return 0;
}
