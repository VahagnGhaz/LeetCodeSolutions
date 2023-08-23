#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

class Solution {
public:
  bool isPalindrome(string s) {
    // sol1: lower and filter into newStr
    int left = 0, right = s.size() - 1;
    while (left < right) {
      while (!iswalnum(s[left]) && left < right) {
        left++;
        // if (left >= right)
        //   return true;
      }

      while (!iswalnum(s[right]) && left < right) {
        right--;
        // if (left >= right)
        //   return true;
      }

      if (tolower(s[left++]) != tolower(s[right--])) // case:  ",." left = right
        return false;
    }
    return true;
  }
  vector<int> twoSum(vector<int> &numbers, int target) {
    // twoSum (2): numbers are sorted O(n):O(1)
    // see array->twoSum(1) for hashmap solution of unsorted array O(n):O(n)
    int left = 0, right = numbers.size() - 1;
    while (left < right) {
      int sum = numbers[left] + numbers[right];
      if (sum == target)
        return vector<int>{left + 1, right + 1};
      else if (sum < target)
        left++;
      else
        right--;
    }
    // will not reach here: There is exactly one solution
    return vector<int>{-1, -1};
  }
};

int main() {
  Solution s;
  vector<int> l = {2, 7, 11, 15};

  vector<int> res = s.twoSum(l, 9);
  for (int num : res)
    cout << num;
}