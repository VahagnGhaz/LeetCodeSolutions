#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

class Solution {
public:
  // 704. Binary Search
  int search(vector<int> &nums, int target) {
    int left = 0;
    int right = nums.size() - 1;
    while (left <= right) {
      int mid = (left + right) / 2;
      if (nums[mid] == target) {
        return mid;
      } else if (nums[mid] < target) {
        left = mid + 1;
      } else {
        right = mid - 1;
      }
    }
    return -1;
  }
  int minEatingSpeed(vector<int> &piles, int h) {
    // check all possible k s
    // brute force: O(n^2)
    // auto maxCountIterator = max_element(piles.begin(), piles.end()); // O(n)
    // int maxVal = *maxCountIterator;
    // for (int k = 1; k <= maxVal; k++) {

    // binary search O(nlogn)
    sort(piles.begin(), piles.end()); //  O(nlogn)
    int maxVal = piles.back();        // O(1)
    for (int k = 1; k <= maxVal; k++) {
      int time = h;
      for (int bananaCount : piles) {
        int timeWasted =
            bananaCount % k == 0 ? bananaCount / k : bananaCount / k + 1;
        time -= timeWasted;
        if (time < 0)
          break;
      }
      if (time >= 0) {
        return k;
      }
    }
    return -1;
  };
};

int main() {
  Solution s;
  int target = 8;
  vector<int> list1 = {3, 6, 7, 11};

  int res = s.minEatingSpeed(list1, target);
  cout << res;
}