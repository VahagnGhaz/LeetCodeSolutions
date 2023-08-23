#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
public:
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

  int maxSubArray(vector<int> &nums) {
    int maxSum = nums[0], currSum = nums[0];
    for (int i = 1; i < nums.size(); i++) {
      //   sliding window
      //    if (currSum < 0):
      //        currSum = 0
      // current_max+=num
      currSum = max(nums[i], currSum + nums[i]);
      maxSum = max(maxSum, currSum);
    }
    return maxSum;
  }

  void merge(vector<int> &nums1, int m, vector<int> &nums2, int n) {
    // 1
    // int a = m - 1, b = n - 1, i = 0;
    // for (i = n + m - 1; a >= 0 && b >= 0; i--)
    // {
    //     if (nums1[a] > nums2[b])
    //         nums1[i] = nums1[a--];
    //     else
    //         nums1[i] = nums2[b--];
    // }
    // while (b >= 0)
    // {
    //     nums1[i--] = nums2[b--];
    // }
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
  // 2 wrong
  //     int i = 0, j = 0;
  //     int currLen = m;
  //     int *ptr1 = nums1.data();
  //     int *ptr2 = nums2.data(); // pointers
  //     while (i < n + m && ptr1 != NULL && ptr2 != NULL)
  //     {
  //         if (*ptr1 > *ptr2)
  //         {
  //             for (j = currLen; j > i; j--)
  //                 nums1[j] = nums1[j - 1];
  //             nums1[i] = *ptr2;
  //             ptr2++;
  //             ptr1++;
  //             currLen++;
  //         }
  //         else
  //             ptr1++;
  //         i++;
  //     }
  //     for (i = currLen; i < n + m; i++)
  //     {
  //         nums1[i] = *ptr2;
  //         ptr2++;
  //     }
  // };
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
    //  std::vector<int> result;
    // int i = 0, j = 0;
    // std::sort(nums1.begin(), nums1.end());
    // std::sort(nums2.begin(), nums2.end());
    // while (i < nums1.size() && j < nums2.size())
    // {
    //     if (nums1[i] < nums2[j])
    //     {
    //         ++i;
    //     }
    //     else if (nums1[i] > nums2[j])
    //     {
    //         ++j;
    //     }
    //     else
    //     {
    //         result.push_back(nums1[i]);
    //         ++i;
    //         ++j;
    //     }
    // }
    // return result;

    // 3 hashmap
    unordered_map<int, int> map;
    int i, j;
    vector<int> maxVec;
    vector<int> minVec;
    vector<int> res;
    if (nums1.size() < nums2.size()) {
      maxVec = nums2;
    } else {
      minVec = nums1;
      maxVec = nums1;
      minVec = nums2;
    }
    for (const int &val : minVec)
      map[val]++;
    for (const int &val : maxVec) {
      if (map.count(val)) {
        res.push_back(val);
        map[val]--;
        if (map[val] == 0)
          map.erase(val);
      }
    }
    return res;
  }

  vector<vector<int>> matrixReshape(vector<vector<int>> &mat, int r, int c) {
    int n = mat.size();
    int m = mat.empty() ? 0 : mat[0].size();
    if (n * m != r * c)
      return mat;
    vector<vector<int>> res(r, vector<int>(c));
    int i = 0, j = 0;
    for (const auto &row : mat) {
      for (const auto &element : row) {
        res[i][j] = element;
        if (++j == c) {
          j = 0;
          i++;
        }
      }
    }
    return res;
  }

  vector<vector<int>> generate(int numRows) {
    // Pascal triangle
    vector<vector<int>> res(numRows);
    res[0] = {1};
    int i, j;
    for (i = 1; i < numRows; i++) {
      // res[i] = vector<int>(i + 1, 1);
      res[i].resize(i + 1, 1);
      for (j = 1; j < i; j++)
        res[i][j] = res[i - 1][j] + res[i - 1][j - 1];
    }
    return res;
  }
  bool isValidSudoku(vector<vector<char>> &board) {
    int i, j;
    int SIZE = 9;
    // hint
    unordered_map<int, unordered_set<char>> columns, rows, boxes;

    for (int i = 0; i < SIZE; i++) {
      for (int j = 0; j < SIZE; j++) {
        if (board[i][j] == '.')
          continue;
        if (rows[i].count(board[i][j]) || columns[j].count(board[i][j]) ||
            boxes[j / 3 + (i / 3) * 3].count(board[i][j]))
          return false;
        rows[i].insert(board[i][j]);
        columns[j].insert(board[i][j]);
        boxes[j / 3 + (i / 3) * 3].insert(board[i][j]);
      }
    }
    return true;
  }

  bool searchMatrix(vector<vector<int>> &matrix, int target) {
    int n = matrix.size();
    int m = matrix[0].size();
    int i, j;
    int l = 0, r = n - 1;
    while (l <= r) {
      int mid =
          (l + r) / 2; // l + (r - l) / 2; avoid int overflow but not necessary
      if (matrix[mid][m - 1] == target) {
        l = mid;
        break;
      } else if (matrix[mid][m - 1] < target)
        l = mid + 1;
      else
        r = mid - 1;
    }
    // l = upperBound, r = lowerbound => matrix[l] is the row we are interested
    // in
    // *** be carefull with enge case when l = matrix.size() or r = -1
    int upperBound = l < n ? l : n - 1;
    vector<int> &a = matrix[upperBound];
    l = 0, r = m - 1;
    while (l <= r) {
      int mid = (l + r) / 2;
      if (a[mid] == target) {
        return true;
      } else if (a[mid] < target)
        l = mid + 1;
      else
        r = mid - 1;
    }
    return false;
  }

  bool valueCompare(const pair<int, int> &a, const pair<int, int> &b) {
    // used for topKFrequent, compare by value (pair represent map's <key,
    // value>), getting compiler error when using, see lambda function instead
    return a.second > b.second;
  }
  vector<int> topKFrequent(vector<int> &nums, int k) {
    vector<int> mostFrequent;
    unordered_map<int, int> counter;
    // populate
    for (int num : nums) {
      counter[num]++;
    }
    // sort counter
    vector<pair<int, int>> sortedMap(counter.begin(), counter.end());
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
  // vector<vector<int>> matrix = {
  //     {1, 3, 5, 7}, {10, 11, 16, 20}, {23, 30, 34, 60}};
  int target = 2;
  vector<int> vec = {1};
  vector<int> res = s.topKFrequent(vec, target);
  for (int item : res)
    cout << item;
  // for (const auto &row : res)
  // {
  //     for (const auto &element : row)
  //     {
  //         std::cout << element << ' ';
  //     }
  // }
  return 0;
}