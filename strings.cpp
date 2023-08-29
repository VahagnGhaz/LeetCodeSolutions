#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;
class Solution {
public:
  // 242. Valid Anagram
  bool isAnagram(string s, string t) {
    int i;
    sort(s.begin(), s.end());
    sort(t.begin(), t.end());
    return s == t;
  }
};

int main() {
  Solution s;
  string ransomNote = "anagtam", magazine = "nagaram";
  int res = s.isAnagram(ransomNote, magazine);
  cout << res;
  // for (const auto &row : res)
  // {
  //     for (const auto &element : row)
  //     {
  //         std::cout << element << ' ';
  //     }
  // }
  return 0;
}