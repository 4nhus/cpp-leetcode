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

  void recursiveSubsets(vector<vector<int>> &ret, vector<int> &subset,
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

class generateCombinationSums {
  vector<vector<int>> combinationSum(vector<int> &candidates, int target) {
    sort(candidates.begin(), candidates.end());

    int maxIndex = candidates.size();

    for (int i = 0; i < candidates.size(); i++) {
      if (candidates[i] > target) {
        maxIndex = i;
        break;
      }
    }

    vector<vector<int>> ret;
    vector<int> combination;

    recursiveCombinationSum(ret, combination, candidates, 0, target, 0,
                            maxIndex);
    return ret;
  }

  void recursiveCombinationSum(vector<vector<int>> &ret,
                               vector<int> &combination, vector<int> candidates,
                               int sum, int target, int index, int maxIndex) {
    if (sum == target) {
      ret.push_back(combination);
      return;
    } else if (sum > target) {
      return;
    }

    for (int i = index; i < maxIndex; i++) {
      combination.push_back(candidates[i]);
      recursiveCombinationSum(ret, combination, candidates, sum + candidates[i],
                              target, i, maxIndex);
      combination.pop_back();
    }
  }
};