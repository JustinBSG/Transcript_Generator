#include "../Inc/AVLT.hpp"

template <typename T>
AVL<T>::AVLnode::AVLnode(const T& other) : data{other}, height{0}, left{}, right{} {}

template <typename T>
AVL<T>& AVL<T>::get_right_subtree() const {}

template <typename T>
AVL<T>& AVL<T>::get_left_subtree() const {}

template <typename T>
int AVL<T>::get_height() const {}

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
AVL<T>::~AVL() {}

template <typename T>
bool AVL<T>::is_empty() const {}

template <typename T>
bool AVL<T>::contain(const T& other) const {}

template <typename T>
T& AVL<T>::find_min() const {}

template <typename T>
T& AVL<T>::find_max() const {}

template <typename T>
T& AVL<T>::find_node(const T& other) const {}

template <typename T>
T& AVL<T>::find_kth_largest(int k) const {}

template <typename T>
void AVL<T>::print(int depth = 0) const {}

template <typename T>
void AVL<T>::insert(const T& other) {}

template <typename T>
void AVL<T>::remove(const T& other) {}