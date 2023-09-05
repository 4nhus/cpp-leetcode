#include <unordered_set>
#include <vector>

using namespace std;

class generatePowerSet {
  vector<vector<int>> subsets(vector<int> &nums) {
    vector<vector<int>> ret;
    vector<int> subset;

    recursiveSubsets(ret, subset, nums, 0);

    return ret;
  }

  void recursiveSubsets(vector<vector<int>> ret, vector<int> &subset,
                        vector<int> nums, int index) {
    if (index == nums.size()) {
      ret.push_back(subset);
      return;
    }

    subset.push_back(nums[index]);
    recursiveSubsets(ret, subset, nums, index + 1);

    subset.pop_back();
    recursiveSubsets(ret, subset, nums, index + 1);
  }
};
