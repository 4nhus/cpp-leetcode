#include <algorithm>
#include <queue>
#include <string>

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

class constructBinaryTreeFromPreorderAndInorderTraversal {
public:
  static TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder) {
    TreeNode *root = new TreeNode(preorder[0]);

    int numLeft;
    int numRight;

    for (int i = 0; i < preorder.size(); i++) {
      if (inorder[i] == root->val) {
        numLeft = i;
        numRight = preorder.size() - 1 - numLeft;
        break;
      }
    }

    if (numLeft != 0) {
      root->left =
          recursiveBuildTree(preorder, inorder, 1, numLeft, 0, numLeft - 1);
    }

    if (numRight != 0) {
      root->right = recursiveBuildTree(preorder, inorder, numLeft + 1,
                                       preorder.size() - 1, numLeft + 1,
                                       preorder.size() - 1);
    }

    return root;
  }

  static TreeNode *recursiveBuildTree(vector<int> preorder, vector<int> inorder,
                                      int preorderStart, int preorderEnd,
                                      int inorderStart, int inorderEnd) {
    if (preorderStart == preorderEnd) {
      return new TreeNode(preorder[preorderStart]);
    } else {
      TreeNode *root = new TreeNode(preorder[preorderStart]);

      int numLeft;
      int numRight;

      for (int i = inorderStart; i < inorderEnd + 1; i++) {
        if (inorder[i] == root->val) {
          numLeft = i - inorderStart;
          numRight = preorderEnd - preorderStart - numLeft;
          break;
        }
      }

      if (numLeft != 0) {
        root->left = recursiveBuildTree(preorder, inorder, preorderStart + 1,
                                        preorderStart + numLeft, inorderStart,
                                        numLeft - 1 + inorderStart);
      }

      if (numRight != 0) {
        root->right = recursiveBuildTree(
            preorder, inorder, preorderStart + numLeft + 1, preorderEnd,
            inorderStart + numLeft + 1, inorderEnd);
      }

      return root;
    }
  }
};

class binaryTreeMaximumPathSum {
  int maxPathSum(TreeNode *root) {
    int ret = root->val;
    maxPathSumNoSplit(root, ret);
    return ret;
  }

  int maxPathSumNoSplit(TreeNode *root, int &ret) {
    if (!root) {
      return 0;
    }

    int leftMax = maxPathSumNoSplit(root->left, ret);
    int rightMax = maxPathSumNoSplit(root->right, ret);
    if (leftMax < 0) {
      leftMax = 0;
    }
    if (rightMax < 0) {
      rightMax = 0;
    }

    ret = max(ret, root->val + leftMax + rightMax);

    return root->val + max(leftMax, rightMax);
  }
};

class serialiseAndDeserialiseBinaryTree {
  // Encodes a tree to a single string
  string serialize(TreeNode *root) {
    string ret = "";

    preorderTraverse(root, ret);

    return ret;
  }

  // Decodes your encoded data to tree
  TreeNode *deserialize(string data) {
    if (data == "N") {
      return nullptr;
    }

    int count = 0;

    TreeNode *root = reconstructTree(data, count);

    return root;
  }

  void preorderTraverse(TreeNode *root, string &ret) {
    if (root) {
      ret.append(to_string(root->val));
      ret.append(".");

      preorderTraverse(root->left, ret);
      preorderTraverse(root->right, ret);
    } else {
      ret.append("N");
    }
  }

  TreeNode *reconstructTree(string data, int &count) {
    TreeNode *root;

    if (data[count] == 'N') {
      root = nullptr;
      count++;
    } else if (data[count] == '-') {
      string digits = "";

      for (int i = count + 1; data[i] != '.'; i++) {
        digits += data[i];
      }

      root = new TreeNode(-stoi(digits));
      count += (2 + digits.length());

      root->left = reconstructTree(data, count);
      root->right = reconstructTree(data, count);
    } else {
      string digits = "";

      for (int i = count; data[i] != '.'; i++) {
        digits += data[i];
      }

      root = new TreeNode(stoi(digits));
      count += (1 + digits.length());

      root->left = reconstructTree(data, count);
      root->right = reconstructTree(data, count);
    }

    return root;
  }
};