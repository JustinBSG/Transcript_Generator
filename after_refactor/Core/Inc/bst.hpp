#ifndef BST_HPP
#define BST_HPP

template<typename T>
class BST {
  private:
    struct BSTnode {
      T data;
      BST<T> left;
      BST<T> right;
      BSTnode(const T& other);
      ~BSTnode() = default;
    };

    BSTnode* root;

    /**
     * @brief Get the right subtree object
     * 
     * @return BST& 
     */
    BST& get_right_subtree();

    /**
     * @brief Get the left subtree object
     * 
     * @return BST& 
     */
    BST& get_left_subtree();

    /**
     * @brief Get the const right subtree object
     * 
     * @return const BST& 
     */
    const BST& get_right_subtree() const;

    /**
     * @brief Get the const left subtree object
     * 
     * @return const BST& 
     */
    const BST& get_left_subtree() const;

    /**
     * @brief Copy other BSTnode and return it\
     * @brief It is deep copy
     * 
     * @param other 
     * @return BSTnode* 
     */
    BSTnode* copy_BSTnode(const BSTnode* other);

  public:
    BST();
    
    // copy constructor
    BST(const BST& other);
    
    // move constructor
    BST(BST&& other);

    // destructor
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
    bool contain(const T& other) const;

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
    const T& find_max_data() const;

    /**
     * @brief Get the minimum data
     * 
     * @return const T& 
     */
    const T& find_min_data() const;

    /**
     * @brief Get the data object
     * 
     * @return const T& 
     */
    const T& get_data() const;

    /**
     * @brief Get the left BSTnode object
     * 
     * @return BSTnode* 
     */
    BSTnode* get_left_BSTnode() const;

    /**
     * @brief Get the right BSTnode object
     * 
     * @return BSTnode* 
     */
    BSTnode* get_right_BSTnode() const;

    /**
     * @brief Get the size of BST
     * 
     * @return int 
     */
    int size() const;

    /**
     * @brief Return the kth largest BSTnode \
     * @brief Range of k: 1 <= k <= size of BST
     * 
     * @param k 
     * @return BSTnode* 
     */
    BSTnode* find_kth_largest_node(int k) const;

    /**
     * @brief Return the kth smallest BSTnode \
     * @brief Range of k: 1 <= k <= size of BST
     * 
     * @param k 
     * @return BSTnode* 
     */
    BSTnode* find_kth_smallest_node(int k) const;

    /**
     * @brief Return the BSTnode that contain other data \
     * @brief return nullptr if other data is not found
     * 
     * @param other 
     * @return BSTnode* 
     */
    BSTnode* find_BSTnode(const T& other) const;

    /**
     * @brief Insert data into BST
     * 
     * @param other 
     */
    void insert(const T& other);

    /**
     * @brief Remove other data from BST \
     * @brief do nothing if other data does not exist in BST or BST is empty
     * 
     * @param other 
     */
    void remove(const T& other);

    // copy operator
    BST<T>& operator=(const BST<T>& other);

    // move operator
    BST<T>& operator=(BST<T>&& other);
};

#include "../Src/bst.cpp"

#endif // BST_HPP