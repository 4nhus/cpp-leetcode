#include <deque>
#include <map>
#include <string>
#include <unordered_set>

using namespace std;

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

  int characterReplacement(string s, int k) {
    unordered_map<char, int> charFrequencies;

    int i = 0, j = 0, maxLength = 0;

    while (j < s.size()) {
      charFrequencies[s[j]]++;

      int highestFrequency = 0;

      for (auto pair : charFrequencies) {
        if (pair.second > highestFrequency) {
          highestFrequency = pair.second;
        }
      }

      if (j - i + 1 - highestFrequency > k) {
        while (j - i + 1 - highestFrequency > k) {
          charFrequencies[s[i]]--;
          i++;
        }
      } else {
        if (j - i + 1 > maxLength) {
          maxLength = j - i + 1;
        }
      }

      j++;
    }

    return maxLength;
  }

  bool checkInclusion(string s1, string s2) {
    if (s2.length() < s1.length()) {
      return false;
    }

    unordered_map<char, int> charCountS1;

    for (char c : s1) {
      charCountS1[c]++;
    }

    unordered_map<char, int> charCountSubstringS2;

    int i = 0;
    int j = s1.size() - 1;

    for (int k = i; k < j; k++) {
      charCountSubstringS2[s2[k]]++;
    }

    while (j < s2.length()) {
      charCountSubstringS2[s2[j]]++;

      bool included = true;

      for (auto pair : charCountS1) {
        if (charCountS1[pair.first] != charCountSubstringS2[pair.first]) {
          included = false;
          break;
        }
      }

      if (included) {
        return true;
      } else {
        charCountSubstringS2[s2[i]]--;

        i++;
        j++;
      }
    }

    return false;
  }

  string minWindow(string s, string t) {
    int m = s.length();
    int n = t.length();

    if (m < n) {
      return "";
    }

    map<char, int> tCharCount;
    unordered_map<char, int> sCharCount;

    for (int i = 0; i < n; i++) {
      tCharCount[t[i]]++;
    }

    int i = 0, j = 0;

    pair<int, int> retStringIndices;
    bool match = false, found = false;

    while (j < m) {
      sCharCount[s[j]]++;

      match = true;

      for (auto pair : tCharCount) {
        if (pair.second > sCharCount[pair.first]) {
          match = false;
          break;
        }
      }

      if (match) {
        retStringIndices = {i, j};
        found = true;
      }

      if (found) {
        if (match) {
          sCharCount[s[j]]--;
        } else {
          j++;
        }

        sCharCount[s[i]]--;
        i++;
      } else {
        j++;
      }
    }

    return found
               ? s.substr(retStringIndices.first,
                          retStringIndices.second - retStringIndices.first + 1)
               : "";
  }

  vector<int> maxSlidingWindow(vector<int> &nums, int k) {
    if (nums.size() == 1) {
      return nums;
    }

    int i = k - 1;

    vector<int> ret;
    deque<pair<int, int>> window;

    for (int j = 0; j < i; j++) {
      while (!window.empty() && nums[j] > window.back().first) {
        window.pop_back();
      }

      window.push_back({nums[j], j});
    }

    while (i < nums.size()) {
      if (window.empty()) {
        ret.push_back(nums[i]);
      } else {
        if (nums[i] >= window.front().first) {
          ret.push_back(nums[i]);
        } else {
          ret.push_back(window.front().first);
        }

        if (window.front().second == i - k + 1) {
          window.pop_front();
        }

        while (!window.empty() && nums[i] > window.back().first) {
          window.pop_back();
        }

        window.push_back({nums[i], i});
      }

      i++;
    }

    return ret;
  }
};