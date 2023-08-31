#include <algorithm>

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
