#include "../Inc/AVLT.hpp"

template <typename T>
AVL<T>::AVLnode::AVLnode(const T& other) : data{other}, height{0}, left{}, right{} {}

template <typename T>
AVL<T>& AVL<T>::get_right_subtree() const {
  return root->right;
}

template <typename T>
AVL<T>& AVL<T>::get_left_subtree() const {
  return root->left;
}

template <typename T>
int AVL<T>::get_height() const {
  return root->height;
}

template <typename T>
int AVL<T>::get_balance_factor() const {}

template <typename T>
void AVL<T>::fix_height() const {}

template <typename T>
void AVL<T>::rotate_left() {}

template <typename T>
void AVL<T>::rotate_right() {}

template <typename T>
void AVL<T>::balance() {}

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
  if (root->left.is_empty()) return root->left;

  return root->left.find_min();
}

template <typename T>
T& AVL<T>::find_max() const {
  if (root->right.is_empty()) return root->right;

  return root->right.find_max();
}

template <typename T>
AVL<T>::AVLnode* AVL<T>::find_node(const T& other) const {
  if (is_empty())
    return nullptr;
  else if (!contain(other))
    return nullptr;

  if (root->data == other)
    return root;
  else if (other < root->data)
    return root->left.find_node(other);
  else if (other > root->data)
    return root->right.find_node(other);
}

template <typename T>
AVL<T>::AVLnode* AVL<T>::find_kth_largest_node(int k) const {}

template <typename T>
void AVL<T>::print(int depth = 0) const {}

template <typename T>
void AVL<T>::insert(const T& other) {}

template <typename T>
void AVL<T>::remove(const T& other) {}