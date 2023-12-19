#ifndef __BST_HPP__
#define __BST_HPP__

template <typename T>
class BST {
  private:
    struct BSTnode {
        T data;
        BST<T> left;
        BST<T> right;
        BSTnode(const T& other);
        BSTnode(const BSTnode& other) = default;
        ~BSTnode() = default;
    };

    BSTnode* root;
    BST& right_subtree();
    BST& left_subtree();
    const BST& right_subtree() const;
    const BST& left_subtree() const;

    BSTnode* copy_node(const BSTnode* other);

  public:
    BST();
    BST(const BST& other);
    BST(BST&& other);
    ~BST();

    bool is_empty() const;
    bool contains(const T& other) const;
    void print(int depth = 0) const;
    const T& find_max() const;
    const T& find_min() const;
    const T& get_data() const;
    BSTnode* get_left() const;
    BSTnode* get_right() const;
    int size() const;
    BSTnode* find_kth_largest_node(int k) const;
    BSTnode* find_BST_node(const T& other) const;

    void insert(const T& other);
    void remove(const T& other);

    BST<T>& operator=(const BST<T>& other);
};

#include "../Src/bst.cpp"

#endif