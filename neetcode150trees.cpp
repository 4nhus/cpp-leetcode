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
