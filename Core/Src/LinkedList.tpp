#include "../Inc/LinkedList.hpp"

template <typename T>
LLNode<T>::LLNode(const T &data, LLNode<T> *next, LLNode<T> *prev, int index)
    : data{data}, next{next}, prev{prev}, index{index} {};

template <typename T>
LLNode<T>::~LLNode() {
  if (next != nullptr && prev != nullptr) {  // delete middle node
    prev->next = next;
    next->prev = prev;
    prev = next = nullptr;
  } else if (next != nullptr && prev == nullptr) {  // delete first node

  } else if (next == nullptr && prev != nullptr) {  // delete last node
  }
}

template <typename T>
LLNode<T> *LLNode<T>::getNext() const {
  return next;
}

template <typename T>
LLNode<T> *LLNode<T>::getPrev() const {
  return prev;
}

template <typename T>
LinkedList<T>::LinkedList() {}

template <typename T>
LinkedList<T>::~LinkedList() {}

template <typename T>
int LinkedList<T>::getTotal_num_node() const {
  return total_num_node;
}

template <typename T>
void LinkedList<T>::insert(const T &other) {
  LLNode *new_ll = new LLNode{other};
  if (ll_ptr == nullptr)  // TODO: replace this part by findNode()
    ll_ptr = new_ll;
  else {
    LLNode *temp = ll_ptr;
    while (temp->next != nullptr) {
      temp = temp->next;
      if (temp->data >= other.data) break;
    }

    if (temp->prev == nullptr) {  // insert other at first
      ll_ptr = new_ll;
      new_ll->next = temp;
      temp->prev = new_ll;
    } else if (temp->next == nullptr) {  // insert other at last
      temp->next = new_ll;
      new_ll->prev = temp;
    } else {  // insert other in the middle
      temp->prev->next = new_ll;
      new_ll->prev = temp->prev;
      new_ll->next = temp;
      temp->prev = new_ll;
    }
  }

  updateIndex();
  total_num_node++;
}

template <typename T>
LLNode<T> *LinkedList<T>::findNode(const T &other) const {
  if () }

template <typename T>
void LinkedList<T>::swap(LLNode<T> *a, LLNode<T> *b) {}

template <typename T>
void LinkedList<T>::sort() {
  for (LLNode *temp = ll_ptr; temp->next != nullptr; temp = temp->next) {
    T smallest = temp->data;
    for (LLNode *target = temp; target != nullptr; target = target->next)
      if (smallest > target->data) smallest = target->data;
    swap(findNode(smallest), temp);
  }
}

template <typename T>
void LinkedList<T>::remove(const T &other) {}

template <typename T>
void LinkedList<T>::updateIndex() {
  LLNode *ptr = ll_ptr;
  for (int i = 0; i < total_num_node; i++) {
    ptr->index = i;
    ptr = ptr->next;
  }
}

template <typename T>
T &LinkedList<T>::operator[](int index) {
  LLNode *temp = ll_ptr;
  if (index >= total_num_node) {
    while (temp->next != nullptr)
      temp = temp->next;
    return temp->data;
  } else if (index < 0)
    return temp->data;

  for (int i = 0; i < total_num_node; i++) {
    if (i == index) return temp->data;
    temp = temp->next;
  }
}