#ifndef INC_LINKEDLIST_HPP
#define INC_LINKEDLIST_HPP

// #include <iostream>

using namespace std;

template <typename T>
class LinkedList {
  private:
    struct LLNode {
        T data;
        LLNode *next;
        LLNode *prev;
        LLNode(const T &, LLNode *next = nullptr, LLNode *prev = nullptr);
    } *ll_ptr;

  public:
    LinkedList();
    ~LinkedList();

    T getData() const;
    LLNode *getNext() const;
    LLNode *getPrev() const;

    int getTotal_num() const;

    void insert(const T &);
    void sort();
    void remove(const T &);
};

#include "LinkedList.tpp"

#endif INC_LINKEDLIST_HPP