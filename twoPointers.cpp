#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

class Solution {
public:
  // 88. Merge Sorted Array
  void merge(vector<int> &nums1, int m, vector<int> &nums2, int n) {
    // 1
    // for (i = n + m - 1; a >= 0 && b >= 0; i--)
    // ...
    // while (b >= 0)
    //     nums1[i--] = nums2[b--];
    // 2
    //  we have to iterated through all the elements in nums2, but what if a < b
    //  => all a s are in their correct place, just fill b's (else statement)
    int a = m - 1, b = n - 1, i = 0;
    for (i = n + m - 1; b >= 0;
         i--) // if b == 0 all nums2 are sorted so nums 1 are in their place (in
              // the begining of the array)
    {
      if (a >= 0 &&
          nums1[a] > nums2[b]) // if a == 0  all num1 are in their place
        nums1[i] = nums1[a--];
      else
        nums1[i] = nums2[b--];
    }
  }
  //  350. Intersection of Two Arrays II
  vector<int> intersect(vector<int> &nums1, vector<int> &nums2) {
    // 1 brute
    // std::vector<bool> seen1(nums1.size(), false);
    // std::vector<bool> seen2(nums2.size(), false);
    // vector<int> res;
    // for (int i = 0; i < nums1.size(); i++)
    // {
    //     for (int j = 0; j < nums2.size(); j++)
    //     {
    //         if (nums1[i] == nums2[j] && !seen1[i] && !seen2[j])
    //         {
    //             res.push_back(nums1[i]);
    //             seen1[i] = true;
    //             seen2[j] = true;
    //         }
    //     }
    // }
    // return res;

    // 2 sort (two pointers)        /*This algorithm is O(n log n + m log m),
    // where n and m are the sizes of nums1 and nums2 respectively, due to the
    // sort operation. If the arrays are already sorted, this reduces to O(n +
    // m) as it's just a single pass over each array.*/
    std::vector<int> result;
    int i = 0, j = 0;
    std::sort(nums1.begin(), nums1.end());
    std::sort(nums2.begin(), nums2.end());
    while (i < nums1.size() && j < nums2.size()) {
      if (nums1[i] < nums2[j]) {
        ++i;
      } else if (nums1[i] > nums2[j]) {
        ++j;
      } else {
        result.push_back(nums1[i]);
        ++i;
        ++j;
      }
    }
    return result;
  }
  // 125. Valid Palindrome
  bool isPalindrome(string s) {
    // sol1: lower and filter into newStr
    int left = 0, right = s.size() - 1;
    while (left < right) {
      // skip non numeric values
      while (!iswalnum(s[left]) && left < right)
        left++;
      while (!iswalnum(s[right]) && left < right)
        right--;
      if (tolower(s[left++]) != tolower(s[right--])) // case:  ",." left = right
        return false;
    }
    return true;
  }

  // 167. Two Sum II - Input Array Is Sorted Time: O(n) Space: O(1)
  vector<int> twoSum(vector<int> &numbers, int target) {
    // see hashing->twoSum(1) for hashmap solution of unsorted array O(n):O(n)
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
    // will NOT reach here, one solution is guaranteed 
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