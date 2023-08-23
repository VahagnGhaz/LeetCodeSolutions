#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right)
      : val(x), left(left), right(right) {}
};

class Solution {
public:
  void generateSubsets(vector<vector<int>> &subsets, vector<int> &subset,
                       vector<int> &nums, int idx) {
    if (idx == nums.size()) { // function is called nums.size() times(leaf node)
      subsets.push_back(subset);
      return;
    }
    subset.push_back(nums[idx]); // include nums[idx]
    generateSubsets(subsets, subset, nums, idx + 1);
    subset.pop_back(); // exclude nums[idx]
    generateSubsets(subsets, subset, nums, idx + 1);
  }
  vector<vector<int>> subsets(vector<int> &nums) {
    vector<vector<int>> subsets;
    vector<int> subset;
    generateSubsets(subsets, subset, nums, 0);
    return subsets;
  }
  vector<vector<int>> combinations;
  vector<int> combination;

  vector<vector<int>> combinationSum(vector<int> &candidates, int target) {

    for (int candidate : candidates) {
      int newCandidate = target - candidate;

      if (newCandidate == 0) { // found a combination
        combinations.push_back(combination);
        return combinations;
      }
      if (newCandidate < 0) {
        combination.pop_back(); // remove last added candidate
        return combinations;
      } //
      combination.push_back(newCandidate);
      combinationSum(candidates, newCandidate);
    }
    return combinations;
  }
};
int main() {
  Solution s;
  vector<int> nums = {2, 3, 6, 7};
  vector<vector<int>> res = s.combinationSum(nums, 7);
  for (auto vec : res) {
    for (auto val : vec) {
      cout << val << " ";
    }
    cout << "\n";
  }
  return 0;
}
