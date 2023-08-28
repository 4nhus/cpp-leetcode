#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

class Solution {
public:
  // Completed
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
      sort(numCounts.begin(), numCounts.end(),
           [](pair<int, int> a, pair<int, int> b) {
             return a.second > b.second;
           });

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

  class TwoPointers {
    bool isPalindrome(string s) {
      vector<char> chars;

      for (char c : s) {
        if (isalpha(c)) {
          chars.push_back(tolower(c));
        } else if (isdigit(c))
          chars.push_back(c);
      }

      int i = 0;
      int j = chars.size() - 1;

      while (i < j) {
        if (chars[i] != chars[j]) {
          return false;
        }
        i++;
        j--;
      }

      return true;
    }

    vector<int> twoSum(vector<int> &numbers, int target) {
      vector<int> ret;

      int i = 0;
      int j = numbers.size() - 1;

      while (true) {
        if (numbers[i] + numbers[j] > target) {
          j--;
        } else if (numbers[i] + numbers[j] < target) {
          i++;
        } else {
          ret.push_back(i + 1);
          ret.push_back(j + 1);
          return ret;
        }
      }

      return ret;
    }

    vector<vector<int>> threeSum(vector<int> &nums) {
      vector<vector<int>> ret;

      sort(nums.begin(), nums.end());

      for (int i = 0; i < nums.size(); i++) {
        int j = i + 1;
        int k = nums.size() - 1;
        int target = -nums[i];

        while (j < k) {
          if (nums[j] + nums[k] > target) {
            k--;
          } else if (nums[j] + nums[k] < target) {
            j++;
          } else {
            vector<int> triplet({nums[i], nums[j], nums[k]});

            ret.push_back(triplet);

            while (j < k && nums[j] == triplet[1]) {
              j++;
            }

            while (j < k && nums[k] == triplet[2]) {
              k--;
            }
          }
        }

        while (i + 1 < nums.size() && nums[i] == nums[i + 1]) {
          i++;
        }
      }

      return ret;
    }

    int maxArea(vector<int> &height) {
      int maxArea = 0;

      int i = 0, j = height.size() - 1;

      while (i < j) {
        int currHeight = min(height[i], height[j]);
        int area = currHeight * (j - i);

        if (area > maxArea) {
          maxArea = area;
        }

        while (height[i] <= currHeight && i < j) {
          i++;
        }

        while (height[j] <= currHeight && i < j) {
          j--;
        }
      }

      return maxArea;
    }

    int trap(vector<int> &height) {
      int i = 0;
      int j = height.size() - 1;
      int leftHeight = height[i];
      int rightHeight = height[j];
      int trappedWater = 0;

      while (i < j) {
        if (leftHeight <= rightHeight) {
          i++;
          if (height[i] < leftHeight) {
            trappedWater += leftHeight - height[i];
          } else {
            leftHeight = height[i];
          }
        } else {
          j--;
          if (height[j] < rightHeight) {
            trappedWater += rightHeight - height[j];
          } else {
            rightHeight = height[j];
          }
        }
      }

      return trappedWater;
    }

    bool isValid(string s) {
      stack<char> charStack;

      if (s.length() == 1) {
        return false;
      }

      for (char c : s) {
        if (c == '(' || c == '{' || c == '[') {
          charStack.push(c);
        } else if (c == ')') {
          if (charStack.empty() || charStack.top() != '(') {
            return false;
          } else {
            charStack.pop();
          }
        } else if (c == ']') {
          if (charStack.empty() || charStack.top() != '[') {
            return false;
          } else {
            charStack.pop();
          }
        } else {
          if (charStack.empty() || charStack.top() != '{') {
            return false;
          } else {
            charStack.pop();
          }
        }
      }

      return charStack.empty();
    }
  };

  class Stack {
    class MinStack {
    public:
      stack<int> intStack;
      stack<int> minStack;

      MinStack() {}

      void push(int val) {
        if (intStack.empty() || val < minStack.top()) {
          intStack.push(val);
          minStack.push(val);
        } else {
          intStack.push(val);
          minStack.push(minStack.top());
        }
      }

      void pop() {
        intStack.pop();
        minStack.pop();
      }

      int top() { return intStack.top(); }

      int getMin() { return minStack.top(); }
    };

    int evalRPN(vector<string> &tokens) {
      stack<int> intStack;

      int i1;
      int i2;

      for (string token : tokens) {
        if (token == "+") {
          i1 = intStack.top();
          intStack.pop();
          i2 = intStack.top();
          intStack.pop();
          intStack.push(i1 + i2);
        } else if (token == "-") {
          i2 = intStack.top();
          intStack.pop();
          i1 = intStack.top();
          intStack.pop();
          intStack.push(i1 - i2);
        } else if (token == "*") {
          i1 = intStack.top();
          intStack.pop();
          i2 = intStack.top();
          intStack.pop();
          intStack.push(i1 * i2);
        } else if (token == "/") {
          i2 = intStack.top();
          intStack.pop();
          i1 = intStack.top();
          intStack.pop();
          intStack.push(i1 / i2);
        } else {
          intStack.push(stoi(token));
        }
      }

      return intStack.top();
    }

    class generateParentheses {
      vector<string> generateParenthesis(int n) {
        vector<string> ret;
        string parentheses;
        parentheses.push_back('(');

        recursiveGenerateParenthesis(ret, parentheses, n, 1, 0);

        return ret;
      }

      void recursiveGenerateParenthesis(vector<string> &ret,
                                        string &parentheses, int numPairs,
                                        int numOpen, int numClosed) {
        if (numOpen == numPairs && numClosed == numPairs) {
          ret.push_back(parentheses);
        } else if (numOpen == numClosed) {
          parentheses.push_back('(');
          recursiveGenerateParenthesis(ret, parentheses, numPairs, numOpen + 1,
                                       numClosed);
          parentheses.pop_back();
        } else {
          if (numOpen < numPairs) {
            parentheses.push_back('(');
            recursiveGenerateParenthesis(ret, parentheses, numPairs,
                                         numOpen + 1, numClosed);
            parentheses.pop_back();
          }

          parentheses.push_back(')');
          recursiveGenerateParenthesis(ret, parentheses, numPairs, numOpen,
                                       numClosed + 1);
          parentheses.pop_back();
        }
      }
    };

    vector<int> dailyTemperatures(vector<int> &temperatures) {
      stack<pair<char, int>> tempStack;
      vector<int> ret(temperatures.size());

      for (int i = 0; i < temperatures.size(); i++) {
        if (tempStack.empty()) {
          tempStack.push({temperatures[i], i});
        } else {
          while (temperatures[i] > tempStack.top().first) {
            ret[tempStack.top().second] = i - tempStack.top().second;
            tempStack.pop();

            if (tempStack.empty()) {
              break;
            }
          }

          tempStack.push({temperatures[i], i});
        }
      }

      ret[temperatures.size() - 1] = 0;

      return ret;
    }

    int carFleet(int target, vector<int> &position, vector<int> &speed) {
      vector<pair<int, int>> cars;

      for (int i = 0; i < position.size(); i++) {
        cars.push_back({target - position[i], speed[i]});
      }

      sort(cars.begin(), cars.end(),
           [](auto c1, auto c2) { return c1.first > c2.first; });

      vector<double> fleets(cars.size());

      for (int i = 0; i < cars.size(); i++) {
        fleets[i] = ((double)cars[i].first / (double)cars[i].second);
      }

      int numFleets = 0;
      double currMax = -1;

      for (int i = cars.size() - 1; i >= 0; i--) {
        if (fleets[i] > currMax) {
          numFleets++;
          currMax = fleets[i];
        }
      }

      return numFleets;
    }

    int largestRectangleArea(vector<int> &heights) {
      stack<pair<int, int>> heightStack;

      int maxArea = 0;

      for (int i = 0; i < heights.size(); i++) {
        if (heightStack.empty()) {
          heightStack.push({heights[i], i});
        } else {
          int startIndex = i;

          while (heights[i] < heightStack.top().first) {
            int area = heightStack.top().first * (i - heightStack.top().second);
            if (area > maxArea) {
              maxArea = area;
            }

            startIndex = heightStack.top().second;
            heightStack.pop();

            if (heightStack.empty()) {
              break;
            }
          }

          heightStack.push({heights[i], startIndex});
        }
      }

      while (!heightStack.empty()) {
        int area = heightStack.top().first *
                   (heights.size() - heightStack.top().second);

        if (area > maxArea) {
          maxArea = area;
        }

        heightStack.pop();
      }

      return maxArea;
    }
  };

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

          return findMinEatingSpeed(piles, h, minEatingSpeed, lower,
                                    middle - 1);
        } else {
          return findMinEatingSpeed(piles, h, minEatingSpeed, middle + 1,
                                    upper);
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
  // Incomplete

  class SlidingWindow {
    int maxProfit(vector<int> &prices) {
      if (prices.size() == 1) {
        return 0;
      }

      int i = 0, j = 1;
      int maxProfit = 0;

      while (j < prices.size()) {

        while (j < prices.size() && prices[j] <= prices[i]) {
          i = j;
          j++;
        }

        if (j == prices.size()) {
          break;
        }

        int profit = prices[j] - prices[i];

        if (profit > maxProfit) {
          maxProfit = profit;
        }

        j++;
      }

      return maxProfit;
    }

    int lengthOfLongestSubstring(string s) {
      if (s.length() == 0) {
        return 0;
      }

      unordered_set<char> charsInSubstring;
      unordered_map<char, int> charLastPosition;

      int longestSubstringLength = 0;
      int substringLength = 0;

      int i = 0;
      int j = 0;

      while (j < s.length()) {
        if (charsInSubstring.count(s[j]) == 0) {
          substringLength++;
          charsInSubstring.insert(s[j]);
          charLastPosition[s[j]] = j;
          j++;
        } else {
          if (substringLength > longestSubstringLength) {
            longestSubstringLength = substringLength;
          }

          if (s[j - 1] == s[j]) {
            i = j;
          } else if (charLastPosition[s[j]] < i) {
          } else {
            while (s[i] != s[j]) {
              i++;
            }
            i++;
          }

          charLastPosition[s[j]] = j;

          j++;

          substringLength = j - i;
        }
      }

      return longestSubstringLength > substringLength ? longestSubstringLength
                                                      : substringLength;
    }
  };

  class LinkedList {
    class reverseLinkedList {
      struct ListNode {
        int val;
        ListNode *next;
        ListNode() : val(0), next(nullptr) {}
        ListNode(int x) : val(x), next(nullptr) {}
        ListNode(int x, ListNode *next) : val(x), next(next) {}
      };

      ListNode *reverseList(ListNode *head) {
        if (head == nullptr) {
          return head;
        }

        ListNode *prev = nullptr;
        ListNode *curr = head;
        ListNode *next = head->next;

        while (next != nullptr) {
          curr->next = prev;
          prev = curr;
          curr = next;
          next = next->next;
        }

        curr->next = prev;

        return curr;
      }
    };

    class mergeTwoSortedLinkedLists {
      struct ListNode {
        int val;
        ListNode *next;
        ListNode() : val(0), next(nullptr) {}
        ListNode(int x) : val(x), next(nullptr) {}
        ListNode(int x, ListNode *next) : val(x), next(next) {}
      };

      ListNode *mergeTwoLists(ListNode *list1, ListNode *list2) {
        if (list1 == nullptr) {
          return list2;
        } else if (list2 == nullptr) {
          return list1;
        }

        ListNode *head = list1->val < list2->val ? list1 : list2;
        ListNode *prev1;
        ListNode *prev2;
        ListNode *curr1 = list1;
        ListNode *curr2 = list2;
        ListNode *next1;
        ListNode *next2;

        while (curr1->next != nullptr && curr2->next != nullptr) {
          if (curr1->val < curr2->val) {
          }
        }

        return head;
      }
    };

    class reorderLinkedList {
      struct ListNode {
        int val;
        ListNode *next;
        ListNode() : val(0), next(nullptr) {}
        ListNode(int x) : val(x), next(nullptr) {}
        ListNode(int x, ListNode *next) : val(x), next(next) {}
      };

      void reorderList(ListNode *head) {}
    };

    class removeNthFromEndLinkedList {
      struct ListNode {
        int val;
        ListNode *next;
        ListNode() : val(0), next(nullptr) {}
        ListNode(int x) : val(x), next(nullptr) {}
        ListNode(int x, ListNode *next) : val(x), next(next) {}
      };

      ListNode *removeNthFromEnd(ListNode *head, int n){};
    };
  };
};
