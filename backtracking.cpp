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
  vector<vector<int>> allSubsets;
  vector<int> subset;
  void generateSubsets(vector<int> &nums, int idx) {
    if (idx == nums.size()) { // function is called nums.size() times(leaf node)
      allSubsets.push_back(subset);
      return;
    }
    subset.push_back(nums[idx]); // include nums[idx]
    generateSubsets(nums, idx + 1);
    subset.pop_back(); // exclude nums[idx]
    generateSubsets(nums, idx + 1);
  }
  vector<vector<int>> subsets(vector<int> &nums) {
    generateSubsets(nums, 0);
    return allSubsets;
  }
  int sum = 0;
  vector<int> combination;
  vector<vector<int>> allCombinations;
  void generateCombinations(vector<int> &candidates, int idx, int target) {

    if (sum == target) {
      allCombinations.push_back(combination);
      return;
    }
    if (sum > target || idx == candidates.size())
      return;

    combination.push_back(candidates[idx]); // include nums[idx]
    sum += candidates[idx];
    generateCombinations(candidates, idx, target);

    combination.pop_back(); // exclude nums[idx]
    sum -= candidates[idx];
    generateCombinations(candidates, idx + 1, target); // shift the pointer
    return;
  }

  vector<vector<int>> combinationSum(vector<int> &candidates, int target) {
    generateCombinations(candidates, 0, target);
    return allCombinations;
  }
  vector<vector<int>> allPermutations;
  vector<int> permutation;
  void generatePermutations(vector<int> &nums, int idx) {
    if (idx == nums.size()) { // function is called nums.size() times(leaf node)
      allPermutations.push_back(subset);
      return;
    }
    permutation.push_back(nums[idx]); // include nums[idx]
    generatePermutations(nums, idx + 1);
  }
  vector<vector<int>> permute(vector<int> &nums) {
    generatePermutations(nums, 0);
    return allPermutations;
  }
};
int main() {
  Solution s;
  vector<int> nums = {1, 2, 3};
  // vector<vector<int>> res = s.combinationSum(nums, 7);
  vector<vector<int>> res = s.permute(nums);
  for (auto vec : res) {
    for (auto val : vec) {
      cout << val << " ";
    }
    cout << "\n";
  }
  return 0;
}
