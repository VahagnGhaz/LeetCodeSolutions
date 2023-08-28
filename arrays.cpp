#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
public:
  bool valueCompare(const pair<int, int> &a, const pair<int, int> &b) {
    // used for topKFrequent, compare by value (pair represent map's <key,
    // value>), getting compiler error when using, see lambda function instead
    return a.second > b.second;
  }
  vector<int> topKFrequent(vector<int> &nums, int k) {
    vector<int> mostFrequent;
    unordered_map<int, int> counter;
    // populate
    for (int num : nums) {
      counter[num]++;
    }
    // sort counter
    vector<pair<int, int>> sortedMap(counter.begin(), counter.end());
    sort(sortedMap.begin(), sortedMap.end(),
         [](const pair<int, int> &a, const pair<int, int> &b) {
           return a.second > b.second;
         });
    for (int i = 0; i < k; i++)
      mostFrequent.push_back(sortedMap[i].first);
    return mostFrequent;
  }
};

int main() {
  Solution s;
  // vector<vector<int>> matrix = {
  //     {1, 3, 5, 7}, {10, 11, 16, 20}, {23, 30, 34, 60}};
  int target = 2;
  vector<int> vec = {1};
  vector<int> res = s.topKFrequent(vec, target);
  for (int item : res)
    cout << item;
  // for (const auto &row : res)
  // {
  //     for (const auto &element : row)
  //     {
  //         std::cout << element << ' ';
  //     }
  // }
  return 0;
}