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

    /**
     * @brief Return right subtree
     * 
     * @return BST& 
     */
    BST& right_subtree();

    /**
     * @brief Return left subtree
     * 
     * @return BST& 
     */
    BST& left_subtree();

    /**
     * @brief Return const right subtree
     * 
     * @return const BST& 
     */
    const BST& right_subtree() const;

    /**
     * @brief Return const left subtree
     * 
     * @return const BST& 
     */
    const BST& left_subtree() const;

    /** 
     * @brief Copy other BSTnode to temp obj and return temp obj\
     * @brief It is deep copy
     * 
     * @param other 
     * @return BSTnode* 
     */
    BSTnode* copy_node(const BSTnode* other);

  public:
    BST();
    BST(const BST& other);
    BST(BST&& other);
    ~BST();

    /**
     * @brief Check whether root is equal to nullptr
     * 
     * @return true 
     * @return false 
     */
    bool is_empty() const;

    /**
     * @brief Check whether BST contain other
     * 
     * @param other 
     * @return true 
     * @return false 
     */
    bool contains(const T& other) const;
    
    /**
     * @brief Print whole BST
     * 
     * @param depth 
     */
    void print(int depth = 0) const;

    /**
     * @brief Get the maximum data
     * 
     * @return const T& 
     */
    const T& find_max() const;

    /**
     * @brief Get the minimum data
     * 
     * @return const T& 
     */
    const T& find_min() const;

    /**
     * @brief Get the data object
     * 
     * @return const T& 
     */
    const T& get_data() const;

    /**
     * @brief Get the left BSTnode
     * 
     * @return BSTnode* 
     */
    BSTnode* get_left() const;

    /**
     * @brief Get the right BSTnode
     * 
     * @return BSTnode* 
     */
    BSTnode* get_right() const;

    /**
     * @brief Return the size of BST
     * 
     * @return int 
     */
    int size() const;

    /**
     * @brief Return the kth largest BSTnode
     * 
     * @param k 
     * @return BSTnode* 
     */
    BSTnode* find_kth_largest_node(int k) const;

    /**
     * @brief Return the BSTnode that contain other data
     * 
     * @param other 
     * @return BSTnode* 
     */
    BSTnode* find_BST_node(const T& other) const;

    /**
     * @brief Insert data into BST
     * 
     * @param other 
     */
    void insert(const T& other);

    /**
     * @brief Remove data from BST
     * 
     * @param other 
     */
    void remove(const T& other);

    BST<T>& operator=(const BST<T>& other);
};

#include "bst.cpp"

#endif