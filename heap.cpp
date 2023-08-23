#include <iostream>
#include <vector>
using namespace std;

class KthLargest {
public:
int k;
  void heapify
  KthLargest(int k, vector<int> &nums) {
    k = k;
    heapify(nums);
  }

  int add(int val) {}
};

int main(int argc, char const *argv[]) {
  vector<int> nums = {4, 5, 8, 2};
  KthLargest kthLargest = KthLargest(3, &nums);
  kthLargest.add(3);  // return 4
  kthLargest.add(5);  // return 5
  kthLargest.add(10); // return 5
  kthLargest.add(9);  // return 8
  kthLargest.add(4);  // return 8
  return 0;
}
