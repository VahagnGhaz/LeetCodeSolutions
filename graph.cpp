#include <algorithm>
#include <climits>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;
class Node {
public:
  int val;
  vector<Node *> neighbors;
  Node() {
    val = 0;
    neighbors = vector<Node *>();
  }
  Node(int _val) {
    val = _val;
    neighbors = vector<Node *>();
  }
  Node(int _val, vector<Node *> _neighbors) {
    val = _val;
    neighbors = _neighbors;
  }
};
Node *listToGraph(vector<vector<int>> adjList) {
  // each vector represent neighbor indexes of node i
  unordered_map<int, Node *> indexToNode;
  int vecSize = adjList.size();
  if (adjList.empty())
    return nullptr;
  for (int i = 0; i < vecSize; i++) // populate map
    indexToNode[i + 1] = new Node(i + 1);
  for (int i = 0; i < vecSize; i++)             // add neighbors
    for (int j = 0; j < adjList[i].size(); j++) // add neighbors
      indexToNode[i + 1]->neighbors.push_back(indexToNode[adjList[i][j]]);
  return indexToNode[1];
}
class Solution {
public:
  void findIslandBfs(int &col, int &row, vector<vector<char>> &grid,
                     set<pair<int, int>> &visited) {
    // neetcode solution
    int columnSize = grid.size();
    int rowSize = grid[0].size();
    queue<pair<int, int>> q;
    q.push({col, row});
    visited.insert({col, row});

    while (!q.empty()) {
      auto [curCol, curRow] = q.front();
      q.pop();

      vector<pair<int, int>> neighbors = {{curCol - 1, curRow},
                                          {curCol + 1, curRow},
                                          {curCol, curRow - 1},
                                          {curCol, curRow + 1}};

      for (auto [newCol, newRow] : neighbors) {
        if (newCol < 0 || newCol >= columnSize || newRow < 0 ||
            newRow >= rowSize)
          continue;
        if (visited.count({newCol, newRow}) == 0 &&
            grid[newCol][newRow] == '1') {
          visited.insert({newCol, newRow});
          q.push({newCol, newRow});
        }
      }
    }
  }
  void findIslandDfs(int col, int row, vector<vector<char>> &grid) {
    // optimizations
    // 1) dfs search
    // 2) no visited set needed (but a good practice to not change the input)
    int columnSize = grid.size();
    int rowSize = grid[0].size();

    grid[col][row] = '0'; // mark visited

    vector<pair<int, int>> neighbors = {
        {col - 1, row}, {col + 1, row}, {col, row - 1}, {col, row + 1}};

    for (auto [newCol, newRow] : neighbors) {
      if (newCol < 0 || newCol >= columnSize || newRow < 0 || newRow >= rowSize)
        continue;
      // out of bound
      if (grid[newCol][newRow] == '1')
        findIslandDfs(newCol, newRow, grid);
    }
  };
  // 200. Number of Islands
  int numIslands(vector<vector<char>> &grid) {
    int columnSize = grid.size();
    int rowSize = grid[0].size();
    int numIsland = 0;
    // set<pair<int, int>> visited;
    for (int col = 0; col < columnSize; col++) {
      for (int row = 0; row < rowSize; row++) {
        if (grid[col][row] == '1') { // && visited.count({col, row}) == 0) {
          findIslandDfs(col, row, grid);
          numIsland++;
        }
      }
    }
    return numIsland;
  }
  // 133. Clone Graph
  unordered_map<Node *, Node *> oldToNew;
  Node *cloneGraph(Node *node) {
    if (node == nullptr)
      return nullptr;
    if (oldToNew.count(node) != 0)
      return oldToNew[node];
    oldToNew[node] = new Node(node->val);
    for (Node *neighbor : node->neighbors) {
      oldToNew[node]->neighbors.push_back(cloneGraph(neighbor));
    }
    return oldToNew[node];
  }
  // 695. Max Area of Island
  int getIslandArea(vector<vector<int>> &grid, int col, int row, int area) {
    int rowSize = grid[0].size();
    int colSize = grid.size();
    area++; // found a point
    grid[col][row] = 0; // mark visited 
    vector<pair<int, int>> neighbors = {
        {col + 1, row}, {col - 1, row}, {col, row - 1}, {col, row + 1}};
    for (auto &[i, j] : neighbors) {
      if (i < 0 || i >= colSize || j < 0 || j >= rowSize ||
          grid[i][j] == 0) // out of bounce or no island
        continue;
      area = getIslandArea(grid, i, j, area);
    }
    return area;
  }
  int maxAreaOfIsland(vector<vector<int>> &grid) {
    int maxArea = 0;
    int colSize = grid.size();
    int rowSize = grid[0].size();
    for (int i = 0; i < colSize; i++)
      for (int j = 0; j < rowSize; j++)
        if (grid[i][j] == 1) // found a island
          maxArea = max(maxArea, getIslandArea(grid, i, j, 0));
    return maxArea;
  }
};
int main() {
  Solution s;
  vector<vector<int>> grid = {{0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
                              {0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0},
                              {0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0}};
  // Node *root = listToGraph(adjList);
  // vector<int> list2 = {4, 1, 2};
  int res = s.maxAreaOfIsland(grid);
  cout << res;
  // for (auto val : res) {
  //   cout << val << ' ";
  // }

  return 0;
}