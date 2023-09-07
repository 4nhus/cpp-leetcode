#include <vector>

using namespace std;

int climbStairs(int n) {
  if (n == 1) {
    return 1;
  }

  vector<int> numWaysToStep(n + 1);

  numWaysToStep[0] = 1;
  numWaysToStep[1] = 1;

  for (int i = 2; i <= n; i++) {
    numWaysToStep[i] = numWaysToStep[i - 1] + numWaysToStep[i - 2];
  }

  return numWaysToStep[n];
}
