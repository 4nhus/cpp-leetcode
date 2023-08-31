#include <stack>
#include <string>

using namespace std;

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