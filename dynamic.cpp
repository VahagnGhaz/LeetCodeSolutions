#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;

class Solution {
public:
  bool canSum(vector<int> &candidates, int target) {
    // n: candidates size (tree width), m: target (tree depth)
    // Time: O(n^m) Space: O(m) callStack height
    if (target == 0) // found a combination
      return true;
    if (target < 0)
      return false;
    for (int candidate : candidates) {
      int newCandidate = target - candidate;
      if (canSum(candidates, newCandidate))
        return true;
    }
    return false;
  };

  bool canSumWithCache(vector<int> &candidates, int target,
                       unordered_map<int, bool> &canSumCache) {
    // n: candidates size (tree width), m: target (tree depth)
    // memoized: Time: O(n*m) Space: O(m) callStack height
    if (canSumCache.count(target)) // saved in cache, true or false
      return canSumCache[target];
    if (target == 0) // found a combination sum up to target
      return true;
    if (target < 0) // combination does not sum up to target
      return false;
    for (int candidate : candidates) {
      int newCandidate = target - candidate;
      if (canSumWithCache(candidates, newCandidate, canSumCache)) {
        canSumCache[target] = true;
        return true;
      }
      // else continue to check other candidates
    }
    canSumCache[target] = false; // all candidates fail to sum to target
    return false;
  };

  void howSum(vector<int> &candidates, int target, vector<int> &combination) {
    if (target == 0) // found a combination
    {
      combination = {};
      return;
    }
    if (target < 0) {
      combination = {-1};
      return;
    }
    for (int candidate : candidates) {
      int newCandidate = target - candidate;
      howSum(candidates, newCandidate, combination);
      if (combination.empty() || combination[0] != -1) {
        combination.push_back(newCandidate);
        return;
        // return combination;
      }
    }
    combination = {-1};
  }
};
int main() {
  Solution s;
  vector<int> nums = {2, 3, 6, 7};
  //   vector<vector<int>> res = s.canSumWithCache(nums, 7);
  unordered_map<int, bool> cache;
  vector<int> comb;
  // vector<int> res = s.howSum(nums, 7, comb);
  s.howSum(nums, 7, comb);
  for (auto vec : comb)
    cout << vec;

  //   for (auto vec : res) {
  //     for (auto val : vec) {
  //       cout << val << " ";
  //     }
  //     cout << "\n";
  //   }
  return 0;
}
