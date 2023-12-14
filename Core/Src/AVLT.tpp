#include <iostream>

#include "../Inc/avlt.hpp"

template <typename T>
AVL<T>::AVLnode::AVLnode(const T& other) : data{other}, height{0}, left{}, right{} {}

template <typename T>
AVL<T>& AVL<T>::get_right_subtree() {
  return root->right;
}

template <typename T>
AVL<T>& AVL<T>::get_left_subtree() {
  return root->left;
}

template <typename T>
const AVL<T>& AVL<T>::get_right_subtree() const {
  return root->right;
}

template <typename T>
const AVL<T>& AVL<T>::get_left_subtree() const {
  return root->left;
}

template <typename T>
int AVL<T>::get_height() const {
  return is_empty() ? -1 : root->height;
}

template <typename T>
int AVL<T>::get_balance_factor() const {
  return is_empty() ? 0 : root->right.get_height() - root->left.get_height();
}

template <typename T>
void AVL<T>::fix_height() const {
  if (!is_empty()) {
    root->height = 1 + max(root->left.get_height(), root->right.get_height());
  }
}

template <typename T>
int AVL<T>::size() const {
  if (is_empty())
    return 0;

  return 1 + root->left.size() + root->right.size();
}

template <typename T>
void AVL<T>::rotate_left() {
  AVLnode* temp = root->right.root;
  root->right = temp->left;
  temp->left = *this;
  fix_height();
  this->root = temp;
  fix_height();
}

template <typename T>
void AVL<T>::rotate_right() {
  AVLnode* temp = root->left.root;
  root->left = temp->right;
  temp->right = *this;
  fix_height();
  this->root = temp;
  fix_height();
}

template <typename T>
void AVL<T>::balance() {
  if (is_empty())
    return;
  fix_height();
  int balance_factor = get_balance_factor();
  if (balance_factor == 2) {
    if (root->right.get_balance_factor() < 0)  // Insert data into L of RT
      root->right.rotate_right();
    rotate_left();  // Insert data into L/R of RT
  } else if (balance_factor == -2) {
    if (root->left.get_balance_factor() > 0)  // Insert data into R of LT
      root->left.rotate_left();
    rotate_right();  // Insert data into L/R of LT
  }
}

template <typename T>
AVL<T>::AVL() : root{nullptr} {}

template <typename T>
AVL<T>::~AVL() {
  delete root;
}

template <typename T>
bool AVL<T>::is_empty() const {
  return (root == nullptr);
}

template <typename T>
bool AVL<T>::contain(const T& other) const {
  if (is_empty())
    return false;
  else if (other == root->data)
    return true;
  else if (other < root->data)
    return root->left.contain(other);
  else if (other > root->data)
    return root->right.contain(other);
}

template <typename T>
T& AVL<T>::find_min() const {
  if (root->left.is_empty())
    return root->data;

  return root->left.find_min();
}

template <typename T>
T& AVL<T>::find_max() const {
  if (root->right.is_empty())
    return root->data;

  return root->right.find_max();
}

template <typename T>
typename AVL<T>::AVLnode* AVL<T>::find_node(const T& other) const {
  if (is_empty())
    return nullptr;
  else if (!contain(other))
    return nullptr;

  if (root->data == other)
    return root;
  else if (other < root->data)
    return root->left.find_node(other);
  else if (other > root->data)
    return root->left.find_node(other);
}

template <typename T>
typename AVL<T>::AVLnode* AVL<T>::find_kth_largest_node(int k) const {
  if (k > size())
    return nullptr;
  else if (root == nullptr)
    return nullptr;

  int rightSize = 0;
  if (!root->right.isEmpty())
    rightSize = root->right.size();

  if (k <= rightSize)
    return root->right.kthLargest(k);
  else if (k > rightSize + 1)
    return root->left.kthLargest(k - rightSize - 1);
  else
    return this;
}

template <typename T>
void AVL<T>::print(int depth) const {
  if (is_empty())
    return;

  root->right.print(depth + 1);

  for (int i = 0; i < depth; i++)
    cout << "\t";

  cout << "(" << root->data << ")" << endl;

  root->left.print(depth + 1);
}

template <typename T>
void AVL<T>::insert(const T& other) {
  if (is_empty())
    root = new AVLnode{other};
  else if (other < root->data)
    root->left.insert(other);
  else if (other > root->data)
    root->right.insert(other);

  balance();
}

template <typename T>
void AVL<T>::remove(const T& other) {
  if (is_empty())
    return;

  if (other < root->data)
    root->left.remove(other);
  else if (other > root->data)
    root->right.remove(other);
  else {
    AVL& avl_right = root->right;
    AVL& avl_left = root->left;
    if (!avl_right.is_empty() && !avl_left.is_empty()) {
      root->data = avl_right.find_min();
      avl_right.remove(root->data);
    } else {
      AVLnode* temp = root;
      *this = avl_left.is_empty() ? avl_right : avl_left;
      avl_right.root = avl_left.root = nullptr;
      delete temp;
    }
  }

  balance();
}