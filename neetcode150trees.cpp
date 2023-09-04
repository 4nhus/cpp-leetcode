#include <algorithm>
#include <queue>

using namespace std;

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right)
      : val(x), left(left), right(right) {}
};

TreeNode *invertTree(TreeNode *root) {
  if (root == nullptr) {
    return;
  }

  TreeNode *right = invertTree(root->left);
  TreeNode *left = invertTree(root->right);

  root->left = left;
  root->right = right;

  return root;
}

int maxDepth(TreeNode *root) {
  if (root == nullptr) {
    return 0;
  }

  return max(maxDepth(root->left) + 1, maxDepth(root->right) + 1);
}

int diameterOfBinaryTree(TreeNode *root) {
  if (root == nullptr) {
    return 0;
  }

  return max(
      max(diameterOfBinaryTree(root->left), diameterOfBinaryTree(root->right)),
      maxDepth(root->left) + maxDepth(root->right));
}

bool isBalanced(TreeNode *root) {
  if (root == nullptr) {
    return true;
  }
  return isBalanced(root->left) && isBalanced(root->right) &&
         abs(maxDepth(root->left) - maxDepth(root->right)) <= 1;
}

bool isSameTree(TreeNode *p, TreeNode *q) {
  if (p == nullptr && q == nullptr) {
    return true;
  } else if (p == nullptr) {
    return false;
  } else if (q == nullptr) {
    return false;
  }

  return p->val == q->val && isSameTree(p->left, q->left) &&
         isSameTree(p->right, q->right);
}

bool isSubtree(TreeNode *root, TreeNode *subRoot) {
  if (root == nullptr) {
    return false;
  }

  return isSameTree(root, subRoot) || isSubtree(root->left, subRoot) ||
         isSubtree(root->right, subRoot);
}

TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q) {
  if (root->val > p->val && root->val > q->val) {
    return lowestCommonAncestor(root->left, p, q);
  } else if (root->val < p->val && root->val < q->val) {
    return lowestCommonAncestor(root->right, p, q);
  } else {
    return root;
  }
}

class binaryTreeLevelOrderTraversal {
  vector<vector<int>> levelOrder(TreeNode *root) {
    vector<vector<int>> ret;

    if (root == nullptr) {
      return ret;
    }

    queue<pair<TreeNode *, short>> nodeQueue;
    nodeQueue.push({root, 0});

    short currentLevel = 0;
    vector<int> nodesInCurrentLevel;

    while (!nodeQueue.empty()) {
      pair<TreeNode *, short> node = nodeQueue.front();
      nodeQueue.pop();

      if (node.second != currentLevel) {
        ret.push_back(nodesInCurrentLevel);
        currentLevel++;
        nodesInCurrentLevel.clear();
      }

      nodesInCurrentLevel.push_back(node.first->val);

      if (node.first->left != nullptr) {
        nodeQueue.push({node.first->left, currentLevel + 1});
      }

      if (node.first->right != nullptr) {
        nodeQueue.push({node.first->right, currentLevel + 1});
      }
    }

    ret.push_back(nodesInCurrentLevel);

    return ret;
  }
};

class binaryTreeRightSideView {
  vector<int> rightSideView(TreeNode *root) {
    if (root == nullptr) {
      vector<int> ret;
      return ret;
    }

    vector<int> ret(maxDepth(root));

    fillOutView(ret, root, 0);

    return ret;
  }

  void fillOutView(vector<int> &ret, TreeNode *root, int depth) {
    ret[depth] = root->val;

    if (root->left != nullptr) {
      fillOutView(ret, root->left, depth + 1);
    }

    if (root->right != nullptr) {
      fillOutView(ret, root->right, depth + 1);
    }
  }
};

class countGoodNodesInBinaryTree {
  int goodNodes(TreeNode *root) {
    int count = 1;

    countGoodNodes(count, root->left, root->val);
    countGoodNodes(count, root->right, root->val);

    return count;
  }

  void countGoodNodes(int &count, TreeNode *root, int max) {
    if (root == nullptr) {
      return;
    }

    if (root->val >= max) {
      count++;
      max = root->val;
    }

    countGoodNodes(count, root->left, max);
    countGoodNodes(count, root->right, max);
  }
};

class validateBinarySearchTree {
  bool isValidBST(TreeNode *root) {
    if (root == nullptr) {
      return true;
    }

    if (root->left == nullptr && root->right == nullptr) {
      return true;
    } else if (root->left == nullptr) {
      return validateBST(root->right, root->val, LLONG_MAX);
    } else if (root->right == nullptr) {
      return validateBST(root->left, LLONG_MIN, root->val);
    } else {
      return validateBST(root->right, root->val, LLONG_MAX) &&
             validateBST(root->left, LLONG_MIN, root->val);
    }
  }

  bool validateBST(TreeNode *root, long min, long max) {
    if (root == nullptr) {
      return true;
    }

    if (root->val <= min || root->val >= max) {
      return false;
    }

    if (root->left == nullptr && root->right == nullptr) {
      return true;
    } else if (root->left == nullptr) {
      return validateBST(root->right, root->val, max);
    } else if (root->right == nullptr) {
      return validateBST(root->left, min, root->val);
    } else {
      return validateBST(root->right, root->val, max) &&
             validateBST(root->left, min, root->val);
    }
  }
};

class kthSmallestElementInABST {
  int kthSmallest(TreeNode *root, int k) {
    vector<int> values;

    addNodes(values, root);

    sort(values.begin(), values.end());

    return values[k - 1];
  }

  void addNodes(vector<int> &values, TreeNode *root) {
    if (root == nullptr) {
      return;
    }

    values.push_back(root->val);
    addNodes(values, root->left);
    addNodes(values, root->right);
  }
};