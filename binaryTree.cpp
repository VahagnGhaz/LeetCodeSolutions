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

TreeNode *findNodeByValue(TreeNode *root, int val) {
  if (!root)
    return nullptr;
  queue<TreeNode *> q;
  q.push(root);

  while (!q.empty()) {
    TreeNode *curr = q.front();
    q.pop();
    if (curr->val == val)
      return curr;
    if (curr->left)
      q.push(curr->left);
    if (curr->right)
      q.push(curr->right);
  }
  return nullptr;
}
TreeNode *vectorToBinaryTree(vector<int> &vec) {
  // levelOrdered vec => BFS
  // null is expected to be -1
  if (vec.empty())
    return nullptr;

  int index = 0;
  int size = vec.size();
  TreeNode *root = new TreeNode(vec[index++]);
  queue<TreeNode *> q;
  q.push(root);

  while (index < size) {
    TreeNode *curr = q.front();
    q.pop();

    // Create left child
    if (vec[index] != -1) {
      curr->left = new TreeNode(vec[index]);
      q.push(curr->left);
    }
    index++;

    // Create right child
    if (index < size && vec[index] != -1) {
      curr->right = new TreeNode(vec[index]);
      q.push(curr->right);
    }
    index++;
  }
  return root;
}
// Helper function to print level order traversal of the tree
void printLevelOrder(TreeNode *root) {
  if (!root)
    return;

  queue<TreeNode *> q;
  q.push(root);

  while (!q.empty()) {
    TreeNode *curr = q.front();
    q.pop();

    cout << curr->val << " ";

    if (curr->left)
      q.push(curr->left);
    if (curr->right)
      q.push(curr->right);
  }
}

class Solution {
public:
  int maxDepth(TreeNode *root) {
    // 1: recursive DFS: call stack, Time: O(n) Space: O(h)
    if (root == nullptr)
      return 0;
    int left = maxDepth(root->left);
    int right = maxDepth(root->right);
    return 1 + max(left, right);

    // 2: BFS Time: O(n) Space: O(w)
    // queue<TreeNode *> q;
    // q.push(root);
    // if (root == nullptr)
    //   return 0;
    // int level = 0;
    // while (!q.empty()) {
    //   int queueSize = q.size();
    //   for (int i = 0; i < queueSize; i++) {
    //     TreeNode *node = q.front();
    //     q.pop(); // pop returns null
    //     if (node->left)
    //       q.push(node->left);
    //     if (node->right)
    //       q.push(node->right);
    //   }
    //   level++;
    // }
    // return level;

    // 3: iterative DFS
    // stack<pair<TreeNode *, int>> s;
    // if (root == nullptr)
    //   return 0;
    // int level = 0;
    // s.push({root, level});
    // while (!s.empty()) {
    //   auto [node, currentLevel] = s.top();
    //   s.pop();
    //   currentLevel++;
    //   level = max(level, currentLevel);
    //   if (node->right)
    //     s.push({node->right, currentLevel});
    //   if (node->left)
    //     s.push({node->left, currentLevel});
    // }
    // return level;
  }
  TreeNode *invertTree(TreeNode *root) {
    if (root == nullptr)
      return nullptr;
    TreeNode *tmp = root->right;
    root->right = invertTree(root->left);
    root->left = invertTree(tmp);
    // 2: first invert then go down
    // root->right = root->left;
    // root->left = tmp;
    // invertTree(root->left);
    // invertTree(root->right);
    return root;
  }
  int isBalancedCore(TreeNode *root, bool &answer) {
    // get height
    // helper function for isBalanced, can assign answer globally in Solution

    if (root == nullptr)
      return 0;
    int leftSize = isBalancedCore(root->left, answer);
    int rightSize = isBalancedCore(root->right, answer);
    if (abs(leftSize - rightSize) > 1)
      answer = false;
    return 1 + max(leftSize, rightSize);
  }
  bool isBalanced(TreeNode *root) {
    // 1: recursive DFS: call stack
    bool balanced = true;
    isBalancedCore(root, balanced);
    return balanced;
  }
  int diameter; // assigned globally
  int diameterOfBinaryTreeCore(TreeNode *root) {
    if (root == nullptr)
      return 0;
    int leftDiameter = diameterOfBinaryTreeCore(root->left);
    int rightDiameter = diameterOfBinaryTreeCore(root->right);
    diameter = max(diameter, leftDiameter + rightDiameter);
    return 1 + max(leftDiameter, rightDiameter);
  }
  int diameterOfBinaryTree(TreeNode *root) {
    diameter = 0;
    diameterOfBinaryTreeCore(root);
    return diameter;
  }
  bool isSameTree(TreeNode *p, TreeNode *q) {
    if (p == nullptr && q == nullptr)
      return true;
    if (p == nullptr || q == nullptr)
      return false;
    bool sameLeft = isSameTree(p->left, q->left);
    bool sameRight = isSameTree(p->right, q->right);
    return sameLeft && sameRight && p->val == q->val; // **
  }

  bool isSubtree(TreeNode *root, TreeNode *subRoot) {
    if (root == nullptr)
      return false;
    if (subRoot == nullptr)
      // edge case, but not necessary, cause isSameTree will always return false
      // and will traverse whole root returning  false || false
      return true;
    if (isSameTree(root, subRoot))
      return true;
    return isSubtree(root->left, subRoot) || isSubtree(root->right, subRoot);
  }
  TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q) {
    // 1. works for all kinds of trees: Time: O(n) Space: O(logn) if balanced
    // else O(n) ( maximum depth of the recursion stack )
    // if (root == nullptr)
    //   return 0; // leaf node
    // if (root == p || root == q)
    //   return root; // return root if its p or q
    // TreeNode *leftCommon = lowestCommonAncestor(root->left, p, q);
    // TreeNode *rightCommon = lowestCommonAncestor(root->right, p, q);
    // if (leftCommon == nullptr && rightCommon == nullptr)
    //   return nullptr; // p and q are not under root
    // else if (leftCommon != nullptr && rightCommon != nullptr)
    //   return root; // p and q are on different side => their root is LCA
    // else if (leftCommon != nullptr) // found p OR q on one side
    //   return leftCommon;            // return not null node (p or q)
    // else                            // if (rightCommon != nullptr)
    //   return rightCommon;

    // 2. tree is binarySearch: Time: O(logN) if balanced  Space: O(1)
    while (root != nullptr) {
      if (root->val > p->val && root->val > q->val)
        root = root->left; // both values are on the left subTree
      else if (root->val < p->val && root->val < q->val)
        root = root->right; // both values are on the right subTree
      else // p and q are on different sides, or one of them equals root
        return root;
    }
    return nullptr; // guaranteed to not reach here
  }
  vector<vector<int>> levelOrder(TreeNode *root) {
    // BFS
    vector<vector<int>> levels;
    if (root == nullptr)
      return levels;
    queue<TreeNode *> q;
    q.push(root);
    while (!q.empty()) {
      int queueSize = q.size(); // 1, 2, 3, ...
      vector<int> level;        // empty
      for (int i = 0; i < queueSize; i++) {
        TreeNode *current = q.front();
        q.pop();
        level.push_back(current->val);
        if (current->left != nullptr)
          q.push(current->left);
        if (current->right != nullptr)
          q.push(current->right);
      }
      levels.push_back(level);
    }
    return levels;
  }
  vector<int> rightSideView(TreeNode *root) {
    // for every level keep rightest node
    vector<int> rightSide;
    if (root == nullptr)
      return rightSide;
    // BFS
    queue<TreeNode *> queue;
    queue.push(root);
    TreeNode *current = nullptr;
    while (!queue.empty()) {
      int queueSize = queue.size(); //  1, 2, 2^2, ...
      for (int i = 0; i < queueSize; i++) {
        current = queue.front();
        queue.pop();
        // if (current != nullptr) {
        //   queue.push(current->left);
        //   queue.push(current->right);
        // }
        if (current->left)
          queue.push(current->left);
        if (current->right)
          queue.push(current->right);
      }
      // rightmost node of the level = stack's last value
      rightSide.push_back(current->val);
    }
    return rightSide;
  }
  bool isValidBST(TreeNode *root) {
    bool bstInvariant = true;
    if (root == nullptr)
      return bstInvariant;
    // check each subTree existence and validity separately
    if (root->left != nullptr)
      bstInvariant = root->left->val < root->val;
    if (root->right != nullptr)
      bstInvariant = bstInvariant && root->right->val > root->val;
    return bstInvariant && isValidBST(root->left) && isValidBST(root->left);
  }
};
int main() {
  Solution s;
  vector<int> list1 = {5, 4, 6, -1, -1, 3, 7};
  // vector<int> list2 = {4, 1, 2};
  TreeNode *root1 = vectorToBinaryTree(list1);
  bool res = s.isValidBST(root1);
  cout << res;
  // for (auto val : res) {
  //   cout << val << " ";
  // }
  // TreeNode *q = findNodeByValue(root1, 4);

  // TreeNode *root2 = vectorToBinaryTree(list2);
  //   TreeNode *res = s.invertTree(root);
  // cout << res->val;
  //   printLevelOrder(root);
  // while (res != nullptr)
  // {
  //     cout << res->val;
  //     res = res->next;
  // }

  return 0;
}