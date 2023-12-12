#ifndef INC_LINKEDLIST_HPP
#define INC_LINKEDLIST_HPP

using namespace std;

template <typename T>
class LLNode {
  private:
    T data;
    LLNode<T> *next;
    LLNode<T> *prev;
    int index;

  public:
    LLNode(const T &data, LLNode<T> *next = nullptr, LLNode<T> *prev = nullptr,
           int index = 0);
    ~LLNode();

    /**
     * @brief Get the pointer of Next linked list node
     *
     * @return LLNode*
     */
    LLNode<T> *getNext() const;

    /**
     * @brief Get the pointer of Prev linked list node
     *
     * @return LLNode*
     */
    LLNode<T> *getPrev() const;
};

template <typename T>
class LinkedList {
  friend class LLNode;

  private:
    LLNode<T> *ll_ptr;
    int total_num_node;

  public:
    LinkedList();
    ~LinkedList();

    /**
     * @brief Get the Total number of node
     *
     * @return int
     */
    int getTotal_num_node() const;

    LLNode<T>* findNode(const T &other) const;

    /**
     * @brief Insert other data into the linked list in ascending order
     *
     * If the data exists in the linked list, insert it in front of the existed data
     *
     * @param other const reference of other data
     */
    void insert(const T &other);

    void swap(LLNode<T> *a, LLNode<T> *b);

    /**
     * @brief Sort the linked list by using Seleection sort
     *
     */
    void sort();

    /**
     * @brief Remove specific data on the linked list
     *
     * If the data do not exist in the linked list, do nothing
     *
     * @param other
     */
    void remove(const T &other);

    /**
     * @brief Update index that inside each LLNode
     *
     */
    void updateIndex();

    /**
     * @brief Get the data by overloading operator[]
     *
     * If the linked list is empty, error will be occurred.
     * If inputted index is out of the range, first or last data will be returned.
     *
     * @param index index of the linked link
     * @return T&
     */
    T &operator[](int index);
};

#include "../Src/LinkedList.tpp"

#endif INC_LINKEDLIST_HPP