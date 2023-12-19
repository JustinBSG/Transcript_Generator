#include "bst.hpp"

using namespace std;

template <typename T>
BST<T>::BSTnode::BSTnode(const T& other) : data{other} {}

template <typename T>
BST<T>& BST<T>::right_subtree() {
  return root->right;
}

template <typename T>
BST<T>& BST<T>::left_subtree() {
  return root->left;
}

template <typename T>
const BST<T>& BST<T>::right_subtree() const {
  return root->right;
}

template <typename T>
const BST<T>& BST<T>::left_subtree() const {
  return root->left;
}

template <typename T>
BST<T>::BST() : root{nullptr} {}

template <typename T>
BST<T>::BST(const BST& other) : root{nullptr} {
  if (other.is_empty())
    return;

  root = new BSTnode(*other.root);
}

template <typename T>
BST<T>::BST(BST<T>&& other) {
  root = other.root;
  other.root = nullptr;
}

template <typename T>
BST<T>::~BST() {
  delete root;
}

template <typename T>
bool BST<T>::is_empty() const {
  return root == nullptr;
}

template <typename T>
bool BST<T>::contains(const T& other) const {
  if (is_empty())
    return false;

  if (root->data == other)
    return true;
  else if (other < root->data)
    return root->left.contains(other);
  else
    return root->right.contains(other);
}

template <typename T>
void BST<T>::print(int depth) const {
  if (is_empty())
    return;

  root->right.print(depth + 1);

  for (int j = 0; j < depth; j++)
    cout << '\t';
  cout << root->data << endl;

  root->left.print(depth + 1);
}

template <typename T>
const T& BST<T>::find_max() const {
  const BSTnode* temp = root;

  while (!temp->right.is_empty())
    temp = temp->right.root;

  return temp->data;
}

template <typename T>
const T& BST<T>::find_min() const {
  const BSTnode* temp = root;

  while (!temp->left.is_empty())
    temp = temp->left.root;

  return temp->data;
}

template <typename T>
const T& BST<T>::get_data() const {
  return root->data;
}

template <typename T>
typename BST<T>::BSTnode* BST<T>::get_left() const {
  return root->left;
}

template <typename T>
typename BST<T>::BSTnode* BST<T>::get_right() const {
  return root->right;
}

template <typename T>
int BST<T>::size() const {
  if (is_empty())
    return 0;

  return 1 + root->left.size() + root->right.size();
}

template <typename T>
typename BST<T>::BSTnode* BST<T>::find_kth_largest_node(int k) const {
  if (k > size())
    return nullptr;
  else if (root == nullptr)
    return nullptr;

  int rightSize = 0;
  if (!root->right.is_empty())
    rightSize = root->right.size();

  if (k <= rightSize)
    return root->right.find_kth_largest_node(k);
  else if (k > rightSize + 1)
    return root->left.find_kth_largest_node(k - rightSize - 1);
  else
    return this->root;
}

template <typename T>
typename BST<T>::BSTnode* BST<T>::find_BST_node(const T& other) const {
  if (is_empty())
    return nullptr;

  if (other == root->data)
    return root;
  else if (root->data < other)
    return root->left.find_BST_node(other);
  else
    return root->right.find_BST_node(other);
}

template <typename T>
void BST<T>::insert(const T& other) {
  if (is_empty())
    root = new BSTnode(other);
  else if (other < root->data)
    root->left.insert(other);
  else if (other > root->data)
    root->right.insert(other);
}

template <typename T>
void BST<T>::remove(const T& other) {
  if (is_empty())
    return;

  if (other < root->data)
    root->left.remove(other);
  else if (other > root->data)
    root->right.remove(other);
  else if (root->left.root && root->right.root) {
    root->data = root->right.find_min();
    root->right.remove(root->data);
  } else {
    BSTnode* temp = root;
    root = (root->left.is_empty()) ? root->right.root : root->left.root;
    temp->left.root = temp->right.root = nullptr;
    delete temp;
  }
}