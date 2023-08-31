#include <map>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class ArraysAndHashing {
  bool containsDuplicate(vector<int> &nums) {
    unordered_set<int> numSet;

    // Insert into map, checking for duplicates
    for (int num : nums) {
      if (numSet.count(num) != 0) {
        return true;
      } else {
        numSet.insert(num);
      }
    }

    return false;
  }

  bool isAnagram(string s, string t) {
    unordered_map<char, int> charCount;

    // Not anagram if mismatch string length
    if (s.length() != t.length()) {
      return false;
    } else {
      // Count chars in s
      for (char c : s) {
        charCount[c]++;
      }
      // Count chars in t
      for (char c : t) {
        if (charCount[c] == 0) {
          return false;
        } else {
          charCount[c]--;
        }
      }
      return true;
    }
  }

  vector<int> twoSum(vector<int> &nums, int target) {
    unordered_map<int, int> targetNums;
    vector<int> ret;
    int i = 0;

    // Add potential pair partner into map for each num
    for (int num : nums) {
      if (targetNums.find(num) != targetNums.end() && targetNums[num] != i) {
        ret.push_back(i);
        ret.push_back(targetNums[num]);
        return ret;
      } else {
        targetNums[target - num] = i;
      }
      i++;
    }

    return ret;
  }

  vector<vector<string>> groupAnagrams(vector<string> &strs) {
    unordered_map<string, vector<string>> anagrams;

    // create anagram groups
    for (string s : strs) {
      string sCopy = s;
      sort(sCopy.begin(), sCopy.end());
      anagrams[sCopy].push_back(s);
    }

    vector<vector<string>> ret;

    for (auto pair : anagrams) {
      ret.push_back(pair.second);
    }

    return ret;
  }

  vector<int> topKFrequent(vector<int> &nums, int k) {
    unordered_map<int, int> numCount;
    for (int num : nums) {
      numCount[num]++;
    }

    vector<pair<int, int>> numCounts;
    for (auto pair : numCount) {
      numCounts.push_back(pair);
    }

    // sort nums by frequency
    sort(
        numCounts.begin(), numCounts.end(),
        [](pair<int, int> a, pair<int, int> b) { return a.second > b.second; });

    vector<int> ret;
    for (int i = 0; i < k; k++) {
      ret.push_back(numCounts[i].first);
    }

    return ret;
  }

  vector<int> productExceptSelf(vector<int> &nums) {
    vector<int> ret(nums.size());
    int product = nums[0];

    // calculate left products
    for (int i = 1; i < nums.size(); i++) {
      ret[i] = product;
      product *= nums[i];
    }

    product = nums[nums.size() - 1];

    // calculate right products
    for (int i = nums.size() - 2; i > 0; i--) {
      ret[i] *= product;
      product *= nums[i];
    }

    ret[0] = product;

    return ret;
  }

  bool isValidSudoku(vector<vector<char>> &board) {
    vector<map<char, int>> rows(9);
    vector<map<char, int>> columns(9);
    vector<map<char, int>> boxes(9);

    int i = 0;
    for (vector<char> row : board) {
      for (int j = 0; j < 9; j++) {
        if (row[j] != '.') {
          rows[i][row[j]]++;
          columns[j][row[j]]++;
          if (i < 3) {
            if (j < 3) {
              boxes[0][row[j]]++;
            } else if (j < 6) {
              boxes[1][row[j]]++;
            } else {
              boxes[2][row[j]]++;
            }
          } else if (i < 6) {
            if (j < 3) {
              boxes[3][row[j]]++;
            } else if (j < 6) {
              boxes[4][row[j]]++;
            } else {
              boxes[5][row[j]]++;
            }
          } else {
            if (j < 3) {
              boxes[6][row[j]]++;
            } else if (j < 6) {
              boxes[7][row[j]]++;
            } else {
              boxes[8][row[j]]++;
            }
          }
        }
      }
      i++;
    }

    for (auto charCount : rows) {
      for (auto pair : charCount) {
        if (pair.second > 1) {
          return false;
        }
      }
    }

    for (auto charCount : columns) {
      for (auto pair : charCount) {
        if (pair.second > 1) {
          return false;
        }
      }
    }

    for (auto charCount : boxes) {
      for (auto pair : charCount) {
        if (pair.second > 1) {
          return false;
        }
      }
    }

    return true;
  }

  int longestConsecutive(vector<int> &nums) {
    unordered_set<int> numSet(nums.begin(), nums.end());

    int max = 0;
    for (int num : nums) {
      if (numSet.find(num - 1) == numSet.end()) {
        int cur = 1;
        while (numSet.find(num + 1) != numSet.end()) {
          cur++;
          num++;
        }
        if (cur > max) {
          max = cur;
        }
      }
    }

    return max;
  }
};
