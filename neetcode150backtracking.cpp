#include <string>
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

  vector<vector<int>> subsetsWithDup(vector<int> &nums) {
    sort(nums.begin(), nums.end());

    vector<vector<int>> ret;
    vector<int> subset;

    recursiveSubsetsWithDup(ret, subset, nums, 0);

    return ret;
  }

  void recursiveSubsetsWithDup(vector<vector<int>> &ret, vector<int> &subset,
                               vector<int> nums, int index) {
    if (index == nums.size()) {
      ret.push_back(subset);
      return;
    }

    subset.push_back(nums[index]);
    recursiveSubsetsWithDup(ret, subset, nums, index + 1);
    subset.pop_back();

    while (index + 1 < nums.size() && nums[index] == nums[index + 1]) {
      index++;
    }

    recursiveSubsetsWithDup(ret, subset, nums, index + 1);
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

  vector<vector<int>> combinationSum2(vector<int> &candidates, int target) {
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

    recursiveCombinationSum2(ret, combination, candidates, 0, target, 0,
                             maxIndex);
    return ret;
  }

  void recursiveCombinationSum2(vector<vector<int>> &ret,
                                vector<int> &combination,
                                vector<int> candidates, int sum, int target,
                                int index, int maxIndex) {
    if (sum == target) {
      ret.push_back(combination);
      return;
    } else if (index == maxIndex) {
      return;
    } else if (sum > target) {
      return;
    }

    combination.push_back(candidates[index]);
    recursiveCombinationSum2(ret, combination, candidates,
                             sum + candidates[index], target, index + 1,
                             maxIndex);
    combination.pop_back();

    while (index + 1 < candidates.size() &&
           candidates[index] == candidates[index + 1]) {
      index++;
    }

    recursiveCombinationSum2(ret, combination, candidates, sum, target,
                             index + 1, maxIndex);
  }
};

vector<vector<int>> permute(vector<int> &nums) {
  vector<vector<int>> ret;

  sort(nums.begin(), nums.end());

  ret.push_back(nums);

  while (next_permutation(nums.begin(), nums.end())) {
    ret.push_back(nums);
  }

  return ret;
}

class wordSearch {
  bool exist(vector<vector<char>> &board, string word) {
    if (board.size() * board[0].size() < word.length()) {
      return false;
    }

    vector<vector<char>> newBoard;

    for (char row = 0; row < board.size(); row++) {
      for (char col = 0; col < board[0].size(); col++) {
        newBoard = board;
        if (findWord(newBoard, row, col, 0, word)) {
          return true;
        }
      }
    }

    return false;
  }

  bool findWord(vector<vector<char>> &board, int row, int col, int index,
                string targetWord) {
    if (row < 0 || row >= board.size() || col < 0 || col >= board[0].size()) {
      return false;
    }

    if (index == targetWord.length()) {
      return true;
    }

    if (board[row][col] == '-') {
      return false;
    }

    if (board[row][col] == targetWord[index]) {
      if (index + 1 == targetWord.length()) {
        return true;
      }

      board[row][col] = '-';

      if (findWord(board, row - 1, col, index + 1, targetWord) ||
          findWord(board, row + 1, col, index + 1, targetWord) ||
          findWord(board, row, col - 1, index + 1, targetWord) ||
          findWord(board, row, col + 1, index + 1, targetWord)) {
        return true;
      }

      board[row][col] = targetWord[index];

      return false;
    } else {
      return false;
    }
  }
};
