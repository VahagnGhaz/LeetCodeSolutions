#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
public:
  // 1. Two Sum   Time: O(n) Space: O(n)
  vector<int> twoSum(vector<int> &nums, int target) {
    unordered_map<int, int> map;
    for (int i = 0; i < nums.size(); i++) {
      int complement = target - nums[i];
      if (map.count(complement)) { // O(1)
        return {map[complement], i};
      }
      map[nums[i]] = i;
    }
    return {};
  }
  // 383. Ransom Note
  bool canConstruct(string ransomNote, string magazine) {
    unordered_map<char, int> map;
    int i, j;
    for (const char &val : magazine)
      map[val]++;
    for (const char &val : ransomNote) {
      if (!map.count(val))
        return false;
      if (--map[val] == 0)
        map.erase(val);
    }
    return true;
  }
  // 217. Contains Duplicate
  bool containsDuplicate(vector<int> &nums) {
    unordered_set<int> set;
    for (int num : nums) {
      if (set.count(num)) {
        return true;
      }
      set.insert(num);
    }
    return false;
  }
  // 387. First Unique Character in a String
  int firstUniqChar(string s) {
    unordered_map<char, int> map;
    for (char c : s)
      map[c]++;

    //  for (const auto& pair : map) // auto == std::pair<const int, int>
    for (int i = 0; i < s.size(); i++) {
      if (map[s[i]] == 1)
        return i;
    }
    return -1;
  }
  vector<int> intersect(vector<int> &nums1, vector<int> &nums2) {
    // 1 brute (twoPointers.cpp)
    // 2 sort (twoPointers.cpp)      O(n log n + m log m)
    // 3 hashmap O(n)
    unordered_map<int, int> map;
    int i, j;
    vector<int> largeVec;
    vector<int> smallVec;
    vector<int> res;
    if (nums1.size() < nums2.size()) {
      largeVec = nums2;
      smallVec = nums1;
    } else {
      largeVec = nums1;
      smallVec = nums2;
    }
    for (const int &val : smallVec)
      map[val]++;
    for (const int &val : largeVec) {
      if (map.count(val) != 0) {
        res.push_back(val); // found common element
        map[val]--;
        if (map[val] == 0) // delete key:val pair so map.count() will return 0
          map.erase(val);
      }
    }
    return res;
  }
  //
  bool valueCompare(const pair<int, int> &a, const pair<int, int> &b) {
    // used for topKFrequent, compare by value (pair represent map's <key,
    // value>), getting compiler error when using, see lambda function instead
    return a.second > b.second;
  }
  // 347. Top K Frequent Elements
  vector<int> topKFrequent(vector<int> &nums, int k) {
    vector<int> mostFrequent;
    unordered_map<int, int> counter;
    // populate
    for (int num : nums)
      counter[num]++;
    // convert map to vector
    vector<pair<int, int>> sortedMap(counter.begin(), counter.end());
    // sort counter by value (pair.second)
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
  int target = 1;
  vector<int> vec = {1};
  vector<int> res = s.topKFrequent(vec, target);
  for (int item : res)
    cout << item;
  return 0;
}