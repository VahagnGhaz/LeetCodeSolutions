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

  bool canSumWithMemo(vector<int> &candidates, int target,
                      unordered_map<int, bool> &canSumMemo) {
    // n: candidates size (tree width), m: target (tree depth)
    // memoized: Time: O(n*m) Space: O(m) callStack height
    if (canSumMemo.count(target)) // saved in Memo, true or false
      return canSumMemo[target];
    if (target == 0) // found a combination sum up to target
      return true;
    if (target < 0) // combination does not sum up to target
      return false;
    for (int candidate : candidates) {
      int newCandidate = target - candidate;
      if (canSumWithMemo(candidates, newCandidate, canSumMemo)) {
        canSumMemo[target] = true;
        return true;
      }
      // else continue to check other candidates
    }
    canSumMemo[target] = false; // all candidates fail to sum to target
    return false;
  };
  bool howSum(vector<int> &candidates, int target, vector<int> &combination) {
    // change combination given as reference
    if (target == 0)
      return true;
    if (target < 0)
      return false;

    for (int candidate : candidates) {
      int newCandidate = target - candidate;
      // if found the last sum element , recursively append the rest
      if (howSum(candidates, newCandidate, combination)) {
        combination.push_back(candidate);
        return true;
      }
    }
    return false;
  }
  bool howSumWithMemo(vector<int> &candidates, int target,
                      vector<int> &combination,
                      unordered_map<int, bool> &canSumMemo) {
    // change combination given as reference
    if (canSumMemo.count(target)) // saved in Memo, true or false
      return canSumMemo[target];
    if (target == 0)
      return true;
    if (target < 0)
      return false;

    for (int candidate : candidates) {
      int newCandidate = target - candidate;
      // if found the last sum element , recursively append the rest
      if (howSum(candidates, newCandidate, combination)) {
        combination.push_back(candidate);
        canSumMemo[target] = true;
        return true;
      }
    }
    canSumMemo[target] = false;
    return false;
  }
  // 70. Climbing Stairs

  int countWaysMemo(int n, unordered_map<int, int> memo) {
    // memory limit exceeded: Time: O(n), Space: O(n)
    if (memo.count(n) != 0)
      return memo[n];
    memo[n] = countWaysMemo(n - 1, memo) + countWaysMemo(n - 2, memo);
    return memo[n];
  }
  int climbStairs(int n) {
    // unordered_map<int, int> memo{{1, 1}, {2, 2}}; // default cases
    // return countWays(n, memo);
    // tabular solution (no need for array for this one: basic fib)
    if (n == 1)
      return 1;
    int one = 1, two = 2, tmp = 0;
    for (int i = 2; i < n; i++) {
      tmp = two;
      two = one + two;
      one = tmp;
    }
    return two;
  }
  int getMinCost(vector<int> &cost, int index, unordered_map<int, int> memo) {
    if (memo.count(index) != 0)
      return memo[index];
    if (index == cost.size())
      return cost[index];
    memo[index] =
        getMinCost(cost, index + 1, memo) + getMinCost(cost, index + 2, memo);
    return memo[index];
  }
  int minCostClimbingStairs(vector<int> &cost) {
    unordered_map<int, int> memo; // default cases
    return min(getMinCost(cost, 0, memo), getMinCost(cost, 1, memo));
  }
};
int main() {
  Solution s;
  vector<int> nums = {10, 15, 20};
  int res = s.minCostClimbingStairs(nums);
  cout << res << endl;
  // for (auto vec : comb)
  //   cout << vec;

  //   for (auto vec : res) {
  //     for (auto val : vec) {
  //       cout << val << " ";
  //     }
  //     cout << "\n";
  //   }
  return 0;
}
