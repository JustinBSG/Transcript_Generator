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
  try {
    if (other == nullptr)
      throw std::runtime_error("Pointer is nullptr!");
    BSTnode* temp = new BSTnode{ohter->data};
    temp->left.root = copy_BSTnode(other->left.root);
    temp->right.root = copy_BSTnode(other->right.root);
    return temp;
  } catch (const std::exception& e) {
    std::cerr << "Exception: " << e.what() << std::endl;
    std::cerr << "Function: BST<T>::BSTnode* BST<T>::copy_BSTnode()" << std::endl;
    std::cerr << "Parameter: " << (other == nullptr ? "nullptr" : other) << std::endl;
    std::cerr << "Internal Variable: " << std::endl;
    throw;
  }
}

template <typename T>
BST<T>::BST() : root{nullptr} {}

template <typename T>
BST<T>::BST(const BST& other) {}

template <typename T>
BST<T>::BST(BST&& other) {}

template <typename T>
BST<T>::~BST() {
  delete root;
}

template <typename T>
bool BST<T>::is_empty() const {
  return root == nullptr;
}

template <typename T>
bool BST<T>::contain(const T& other) const {}

template <typename T>
void BST<T>::print(int depth) const {}

template <typename T>
const T& BST<T>::find_max_data() const {}

template <typename T>
const T& BST<T>::find_min_data() const {}

template <typename T>
const T& BST<T>::get_data() const {}

template <typename T>
BST<T>::BSTnode* BST<T>::get_left_BSTnode() const {}

template <typename T>
BST<T>::BSTnode* BST<T>::get_right_BSTnode() const {}

template <typename T>
int BST<T>::size() const {}

template <typename T>
BST<T>::BSTnode* BST<T>::find_kth_largest_node(int k) const {}

template <typename T>
BST<T>::BSTnode* BST<T>::find_kth_smallest_node(int k) const {}

template <typename T>
BST<T>::BSTnode* BST<T>::find_BSTnode(const T& other) const {}

template <typename T>
void insert(const T& other) {}

template <typename T>
void remove(const T& other) {}

template <typename T>
BST<T>& BST<T>::operator=(const BST<T>& other) {}

template <typename T>
BST<T>& BST<T>::operator=(BST<T>&& other) {}