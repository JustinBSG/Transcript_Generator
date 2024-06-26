#include "../Inc/bst.hpp"

#include <iostream>
#include <stdexcept>

template <typename T>
BST<T>::BSTnode::BSTnode(const T& other) : data{other} {}

template <typename T>
BST<T>& BST<T>::get_right_subtree() {
  return root->right;
}

template <typename T>
BST<T>& BST<T>::get_left_subtree() {
  return root->left;
}

template <typename T>
const BST<T>& BST<T>::get_right_subtree() const {
  return root->right;
}

template <typename T>
const BST<T>& BST<T>::get_left_subtree() const {
  return root->left;
}

template <typename T>
typename BST<T>::BSTnode* BST<T>::copy_BSTnode(const BSTnode* other) {
  if (other == nullptr)
    return nullptr;

  BSTnode* temp = new BSTnode{other->data};
  temp->left.root = copy_BSTnode(other->left.root);
  temp->right.root = copy_BSTnode(other->right.root);
  return temp;
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
bool BST<T>::contain(const T& other) const {
  if (is_empty())
    return false;

  if (root->data == other)
    return true;
  else if (root->data > other)
    return root->left.contain(other);
  else
    return root->right.contain(other);
}

template <typename T>
void BST<T>::print(int depth) const {
  if (is_empty())
    return;

  root->right.print(depth + 1);

  for (int j = 0; j < depth; j++)
    std::cout << '\t';
  std::cout << root->data << std::endl;

  root->left.print(depth + 1);
}

template <typename T>
const T& BST<T>::find_max_data() const {
  try {
    if (size() == 0)
      throw std::logic_error("There is no any data inside BST!");

    const BSTnode* temp = root;

    while (!temp->right.is_empty())
      temp = temp->right.root;

    return temp->data;
  } catch (const std::exception& e) {
    std::cerr << "Exception: " << e.what() << std::endl;
    std::cerr << "Function: const T& BST<T>::find_max_data() const" << std::endl;
    throw;
  }
}

template <typename T>
const T& BST<T>::find_min_data() const {
  try {
    if (size() == 0)
      throw std::logic_error("There is no any data inside BST!");
    const BSTnode* temp = root;

    while (!temp->left.is_empty())
      temp = temp->left.root;

    return temp->data;
  } catch (const std::exception& e) {
    std::cerr << "Exception: " << e.what() << std::endl;
    std::cerr << "Function: const T& BST<T>::find_min_data() const" << std::endl;
    throw;
  }
}

template <typename T>
const T& BST<T>::get_data() const {
  return root->data;
}

template <typename T>
typename BST<T>::BSTnode* BST<T>::get_left_BSTnode() const {
  return root->left;
}

template <typename T>
typename BST<T>::BSTnode* BST<T>::get_right_BSTnode() const {
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
  try {
    if (k > size())
      throw std::invalid_argument("k should not be larger than the size of BST!");
    else if (k < 0)
      throw std::invalid_argument("k should not be smaller than 0!");
    else if (root == nullptr)
      throw std::invalid_argument("The root of BST should not be nullptr!");

    int rightSize = 0;
    if (!root->right.is_empty())
      rightSize = root->right.size();

    if (k <= rightSize)
      return root->right.find_kth_largest_node(k);
    else if (k > rightSize + 1)
      return root->left.find_kth_largest_node(k - rightSize - 1);
    else
      return this->root;
  } catch (const std::exception& e) {
    std::cerr << "Exception: " << e.what() << std::endl;
    std::cerr << "Function: BST<T>::BSTnode* BST<T>::find_kth_largest_node(int k) const"
              << std::endl;
    std::cerr << "Parameter: k = " << k << std::endl;
    std::cerr << "Internal variable:  root = "
              << (root == nullptr ? "nullptr" : static_cast<const void*>(root)) << std::endl;
    std::cerr << "                    size of BST = " << size() << std::endl;
    std::cerr << "                    leftSize = "
              << (root->right.is_empty() ? 0 : root->right.size()) << std::endl;
    throw;
  }
}

template <typename T>
typename BST<T>::BSTnode* BST<T>::find_kth_smallest_node(int k) const {
  try {
    if (k > size())
      throw std::invalid_argument("k should not be larger than the size of BST!");
    else if (k < 0)
      throw std::invalid_argument("k should not be smaller than 0!");
    else if (root == nullptr)
      throw std::invalid_argument("The root of BST should not be nullptr!");

    int leftSize = 0;
    if (!root->left.is_empty())
      leftSize = root->left.size();

    if (k <= leftSize)
      return root->left.find_kth_smallest_node(k);
    else if (k > leftSize + 1)
      return root->right.find_kth_smallest_node(k - leftSize - 1);
    else
      return this->root;
  } catch (const std::exception& e) {
    std::cerr << "Exception: " << e.what() << std::endl;
    std::cerr << "Function: BST<T>::BSTnode* BST<T>::find_kth_smallest_node(int k) const"
              << std::endl;
    std::cerr << "Parameter: k = " << k << std::endl;
    std::cerr << "Internal variable:  root = "
              << (root == nullptr ? "nullptr" : static_cast<const void*>(root)) << std::endl;
    std::cerr << "                    size of BST = " << size() << std::endl;
    std::cerr << "                    leftSize = "
              << (root->left.is_empty() ? 0 : root->left.size()) << std::endl;
    throw;
  }
}

template <typename T>
typename BST<T>::BSTnode* BST<T>::find_BSTnode(const T& other) const {
  if (is_empty())
    return nullptr;

  if (root->data == other)
    return root;
  else if (root->data > other)
    return root->left.find_BSTnode(other);
  else
    return root->right.find_BSTnode(other);
}

template <typename T>
void BST<T>::insert(const T& other) {
  if (is_empty())
    root = new BSTnode(other);
  else if (root->data > other)
    root->left.insert(other);
  else if (root->data < other)
    root->right.insert(other);
}

template <typename T>
void BST<T>::remove(const T& other) {
  if (is_empty())
    return;

  if (root->data > other)
    root->left.remove(other);
  else if (root->data < other)
    root->right.remove(other);
  else if (root->left.root && root->right.root) {
    root->data = root->right.find_min_data();
    root->right.remove(root->data);
  } else {
    BSTnode* temp = root;
    root = (root->left.is_empty()) ? root->right.root : root->left.root;
    temp->left.root = temp->right.root = nullptr;
    delete temp;
  }
}

template <typename T>
BST<T>& BST<T>::operator=(const BST<T>& other) {
  if (this != &other) {
    while (this->size() != 0)
      remove(root->data);
    root = copy_BSTnode(other.root);
  }
  return *this;
}

template <typename T>
BST<T>& BST<T>::operator=(BST<T>&& other) {
  if (this != &other) {
    while (this->size() != 0)
      remove(root->data);
    root = other.root;
    other.root = nullptr;
  }
  return *this;
}