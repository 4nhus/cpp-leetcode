#include <stack>
#include <string>

using namespace std;

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

  void recursiveGenerateParenthesis(vector<string> &ret, string &parentheses,
                                    int numPairs, int numOpen, int numClosed) {
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
        recursiveGenerateParenthesis(ret, parentheses, numPairs, numOpen + 1,
                                     numClosed);
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
    int area =
        heightStack.top().first * (heights.size() - heightStack.top().second);

    if (area > maxArea) {
      maxArea = area;
    }

    heightStack.pop();
  }

  return maxArea;
}
