// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <iostream>
#include <cassert>
#include <limits>
#include <memory>

#include "./Binary_tree_prototype.h"

using std::boolalpha;
using std::cout;
using std::endl;
using std::numeric_limits;
using std::unique_ptr;

// @include
bool IsBST(const unique_ptr<BinaryTreeNode<int>>& root) {
  auto* n = root.get();
  // Stores the value of previous visited node.
  int last = numeric_limits<int>::min();
  bool result = true;

  while (n) {
    if (n->left.get()) {
      // Finds the predecessor of n.
      auto* pre = n->left.get();
      while (pre->right.get() && pre->right.get() != n) {
        pre = pre->right.get();
      }

      // Processes the successor link.
      if (pre->right.get()) {  // pre->right == n.
        // Reverts the successor link if predecessor's successor is n.
        pre->right.release();
        if (last > n->data) {
          result = false;
        }
        last = n->data;
        n = n->right.get();
      } else {  // If predecessor's successor is not n.
        pre->right.reset(n);
        n = n->left.get();
      }
    } else {
      if (last > n->data) {
        result = false;
      }
      last = n->data;
      n = n->right.get();
    }
  }
  return result;
}
// @exclude

int main(int argc, char* argv[]) {
  //      3
  //    2   5
  //  1    4 6
  auto root = unique_ptr<BinaryTreeNode<int>>(new BinaryTreeNode<int>{3});
  root->left = unique_ptr<BinaryTreeNode<int>>(new BinaryTreeNode<int>{2});
  root->left->left = unique_ptr<BinaryTreeNode<int>>(new BinaryTreeNode<int>{1});
  root->right = unique_ptr<BinaryTreeNode<int>>(new BinaryTreeNode<int>{5});
  root->right->left = unique_ptr<BinaryTreeNode<int>>(new BinaryTreeNode<int>{4});
  root->right->right = unique_ptr<BinaryTreeNode<int>>(new BinaryTreeNode<int>{6});
  assert(IsBST(root) == true);
  cout << boolalpha << IsBST(root) << endl;
  //      10
  //    2   5
  //  1    4 6
  root->data = 10;
  // should output false
  assert(!IsBST(root));
  cout << boolalpha << IsBST(root) << endl;
  // should output true
  assert(IsBST(nullptr) == true);
  cout << boolalpha << IsBST(nullptr) << endl;
  return 0;
}
