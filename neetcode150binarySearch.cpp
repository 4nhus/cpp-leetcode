#include <string>
#include <unordered_map>

using namespace std;

class BinarySearch {
  class binarySearch {
    int search(vector<int> &nums, int target) {
      return recursiveBinarySearch(nums, target, 0, nums.size() - 1);
    }

    int recursiveBinarySearch(vector<int> &nums, int target, int lower,
                              int upper) {
      if (lower == upper) {
        return nums[lower] == target ? lower : -1;
      } else if (lower > upper) {
        return -1;
      }

      int middle = (lower + upper) / 2;

      if (nums[middle] == target) {
        return middle;
      } else if (nums[middle] < target) {
        return recursiveBinarySearch(nums, target, middle + 1, upper);
      } else {
        return recursiveBinarySearch(nums, target, lower, middle - 1);
      }
    }
  };

  class binarySearchMatrix {
    bool searchMatrix(vector<vector<int>> &matrix, int target) {
      int m = matrix.size() - 1;
      int n = matrix[0].size() - 1;

      int row = findRow(matrix, target, n, 0, m);

      if (row == -1) {
        return false;
      }

      return binary_search(matrix[row].begin(), matrix[row].end(), target);
    }

    int findRow(vector<vector<int>> &matrix, int target, int n, int lower,
                int upper) {
      if (lower == upper) {
        return (matrix[lower][0] <= target && matrix[lower][n] >= target)
                   ? lower
                   : -1;
      } else if (lower > upper) {
        return -1;
      }

      int middle = (lower + upper) / 2;

      if (matrix[middle][0] <= target && matrix[middle][n] >= target) {
        return middle;
      } else if (matrix[middle][0] > target) {
        return findRow(matrix, target, n, lower, middle - 1);
      } else {
        return findRow(matrix, target, n, middle + 1, upper);
      }
    }
  };

  class KokoEatingBananas {
    int minEatingSpeed(vector<int> &piles, int h) {
      int maxPileSize = 1;

      for (int pile : piles) {
        if (pile > maxPileSize) {
          maxPileSize = pile;
        }
      }

      return findMinEatingSpeed(piles, h, maxPileSize, 1, maxPileSize);
    }

    bool canEatBananas(vector<int> piles, int h, int k) {
      int hoursTaken = 0;

      for (int i = 0; i < piles.size(); i++) {
        if (piles[i] <= k) {
          hoursTaken++;
        } else {
          hoursTaken += piles[i] % k == 0 ? piles[i] / k : (piles[i] / k) + 1;
        }

        if (hoursTaken > h) {
          return false;
        }
      }

      return true;
    }

    int findMinEatingSpeed(vector<int> piles, int h, int minEatingSpeed,
                           int lower, int upper) {
      if (lower == upper) {
        return canEatBananas(piles, h, lower) ? lower : minEatingSpeed;
      } else if (lower > upper) {
        return minEatingSpeed;
      }

      int middle = (lower + upper) / 2;

      if (canEatBananas(piles, h, middle)) {
        if (middle < minEatingSpeed) {
          minEatingSpeed = middle;
        }

        return findMinEatingSpeed(piles, h, minEatingSpeed, lower, middle - 1);
      } else {
        return findMinEatingSpeed(piles, h, minEatingSpeed, middle + 1, upper);
      }
    }
  };

  class rotatedSortedArray {
    int binarySearch(vector<int> &nums, int target) {
      return recursiveBinarySearch(nums, target, 0, nums.size() - 1);
    }

    int recursiveBinarySearch(vector<int> &nums, int target, int lower,
                              int upper) {
      if (lower == upper) {
        return nums[lower] == target ? lower : -1;
      } else if (lower > upper) {
        return -1;
      }

      int middle = (lower + upper) / 2;

      if (nums[middle] == target) {
        return middle;
      } else if (nums[middle] < target) {
        return recursiveBinarySearch(nums, target, middle + 1, upper);
      } else {
        return recursiveBinarySearch(nums, target, lower, middle - 1);
      }
    }

    int findMin(vector<int> &nums) {
      if (nums.size() == 1) {
        return nums[0];
      } else if (nums.size() == 2) {
        return nums[0] < nums[1] ? nums[0] : nums[1];
      }

      return recursiveFindMin(nums, 0, nums.size() - 1);
    }

    int recursiveFindMin(vector<int> &nums, int lower, int upper) {
      if (lower + 1 == upper) {
        return nums[lower] < nums[upper] ? nums[lower] : nums[upper];
      }

      int middle = (lower + upper) / 2;

      if (nums[middle] < nums[middle - 1]) {
        return nums[middle];
      }

      if (nums[lower] < nums[middle] && nums[lower] < nums[upper]) {
        return nums[lower];
      } else if (nums[middle] < nums[lower] && nums[middle] < nums[upper]) {
        return recursiveFindMin(nums, lower, middle - 1);
      } else {
        return recursiveFindMin(nums, middle + 1, upper);
      }
    }

    int findMinIndex(vector<int> &nums) {
      if (nums.size() == 1) {
        return 0;
      } else if (nums.size() == 2) {
        return nums[0] < nums[1] ? 0 : 1;
      }

      return recursiveFindMinIndex(nums, 0, nums.size() - 1);
    }

    int recursiveFindMinIndex(vector<int> &nums, int lower, int upper) {
      if (lower + 1 == upper) {
        return nums[lower] < nums[upper] ? lower : upper;
      }

      int middle = (lower + upper) / 2;

      if (nums[middle] < nums[middle - 1]) {
        return middle;
      }

      if (nums[lower] < nums[middle] && nums[lower] < nums[upper]) {
        return lower;
      } else if (nums[middle] < nums[lower] && nums[middle] < nums[upper]) {
        return recursiveFindMinIndex(nums, lower, middle - 1);
      } else {
        return recursiveFindMinIndex(nums, middle + 1, upper);
      }
    }

    int search(vector<int> &nums, int target) {
      if (nums.size() == 1) {
        return nums[0] == target ? 0 : -1;
      } else if (nums.size() == 2) {
        if (nums[0] == target) {
          return 0;
        } else if (nums[1] == target) {
          return 1;
        } else {
          return -1;
        }
      }

      int minIndex = findMinIndex(nums);

      if (minIndex == 0) {
        return binarySearch(nums, target);
      } else if (target <= nums[nums.size() - 1]) {
        return recursiveBinarySearch(nums, target, minIndex, nums.size() - 1);
      } else {
        return recursiveBinarySearch(nums, target, 0, minIndex - 1);
      }
    }
  };

  class TimeMap {
  public:
    unordered_map<string, vector<pair<int, string>>> timeMap;

    TimeMap() {}

    void set(string key, string value, int timestamp) {
      timeMap[key].push_back({timestamp, value});
    }

    string get(string key, int timestamp) {
      if (timeMap.find(key) == timeMap.end()) {
        return "";
      } else {
        return timeMap[key][0].first > timestamp
                   ? ""
                   : findValue(key, timestamp, 0, timeMap[key].size() - 1);
      }
    }

    string findValue(string key, int timestamp, int lower, int upper) {
      if (lower == upper) {
        return timeMap[key][lower].second;
      } else if (lower > upper) {
        return timeMap[key][upper].second;
      } else if (lower + 1 == upper) {
        return timeMap[key][upper].first <= timestamp
                   ? timeMap[key][upper].second
                   : timeMap[key][lower].second;
      }

      int middle = (lower + upper) / 2;

      if (timeMap[key][middle].first == timestamp) {
        return timeMap[key][middle].second;
      } else if (timeMap[key][middle].first < timestamp) {
        return findValue(key, timestamp, middle + 1, upper);
      } else {
        return findValue(key, timestamp, lower, middle - 1);
      }
    }
  };

  class MedianOfSortedArrays {
    double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2) {
      int m = nums1.size();
      int n = nums2.size();

      if (m > n) {
        return findMedianSortedArrays(nums2, nums1);
      }

      int total = m + n;

      int low = 0;
      int high = m;

      double result = 0.0;

      while (low <= high) {
        // nums1
        int i = low + (high - low) / 2;
        // nums2
        int j = (total + 1) / 2 - i;

        int left1 = (i > 0) ? nums1[i - 1] : INT_MIN;
        int right1 = (i < m) ? nums1[i] : INT_MAX;
        int left2 = (j > 0) ? nums2[j - 1] : INT_MIN;
        int right2 = (j < n) ? nums2[j] : INT_MAX;

        // partition is correct
        if (left1 <= right2 && left2 <= right1) {
          // even
          if (total % 2 == 0) {
            result = (max(left1, left2) + min(right1, right2)) / 2.0;
            // odd
          } else {
            result = max(left1, left2);
          }
          break;
        } else if (left1 > right2) {
          high = i - 1;
        } else {
          low = i + 1;
        }
      }

      return result;
    };
  };
};
