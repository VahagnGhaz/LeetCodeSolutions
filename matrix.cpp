

#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
public:
  // 118. Pascal's Triangle
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
  // 566. Reshape the Matrix
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
  // 36. Valid Sudoku
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
  // 74. Search a 2D Matrix
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
    // l = upperBound, r = lowerBound => matrix[l] is the row we are interested
    // *** be careful with edge case when l = matrix.size() or r = -1
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
};
int main() { return 0; }
