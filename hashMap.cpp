#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
public:
  // 1. Two Sum
  vector<int> twoSum(vector<int> &nums, int target) {
    unordered_map<int, int> map;
    for (int i = 0; i < nums.size(); i++) {
      int complement = target - nums[i];
      if (map.count(complement)) {
        return {map[complement], i};
      }
      map[nums[i]] = i;
    }
    return {};
  }
};
int main() {
  Solution s;
  vector<int> nums = {2, 7, 11, 15};
  int target = 9;
  vector<int> res = s.twoSum(nums, target);
  for (const auto &element : res) {
    cout << element << " ";
  }
  return 0;
}