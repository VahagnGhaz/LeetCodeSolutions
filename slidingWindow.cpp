#include <algorithm>
#include <iostream>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
public:
  int maxProfit(vector<int> &prices) {
    // 1.
    // int lowestSoFar = prices[0]; // hint
    // int maxProfit = 0;
    // for (int i = 0; i < prices.size() - 1; i++) {
    //   if (prices[i + 1] < lowestSoFar)
    //     lowestSoFar = prices[i + 1];
    //   else
    //     maxProfit = max(maxProfit, prices[i + 1] - lowestSoFar);
    // }
    // return maxProfit;

    // 2. sliding window
    int left = 0, right = 1;
    int maxProfit = 0;
    int pricesLen = prices.size();
    while (right < pricesLen) {
      if (prices[left] < prices[right])
        maxProfit = max(maxProfit, prices[right] - prices[left]);
      else
        left = right;
      right += 1;
    }
    return maxProfit;
  };
  int lengthOfLongestSubstring(string s) {
    set<int> charactersSoFar; // order matters
    int idx = 0;
    int longestSubString = 0;
    int strLen = s.length();
    while (idx < strLen) {
      if (charactersSoFar.find(s[idx]) != charactersSoFar.end()) {
        // char exists in set
        charactersSoFar.erase(
            charactersSoFar.begin(),
            charactersSoFar.find(
                s[idx])); // delete everything before found char
      }
      charactersSoFar.insert(s[idx]);
      idx++;
      int charSize = charactersSoFar.size();
      longestSubString = max(longestSubString, charSize);
    }
    return longestSubString;
  }
};

int main() {
  Solution s;
  // vector<vector<int>> matrix = {
  //     {1, 3, 5, 7}, {10, 11, 16, 20}, {23, 30, 34, 60}};
  // int target = 2;
  // vector<int> vec = {7, 1, 5, 3, 6, 4};
  string str = "abcabcbb";
  int res = s.lengthOfLongestSubstring(str);
  cout << res;
  // for (int item : res)
  // cout << item;
  // for (const auto &row : res)
  // {
  //     for (const auto &element : row)
  //     {
  //         std::cout << element << ' ';
  //     }
  // }
  return 0;
}