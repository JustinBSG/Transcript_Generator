#ifndef INC_AVLT_HPP
#define INC_AVLT_HPP

using namespace std;

template <typename T>
class AVL {
  private:
    struct AVLnode {
        T data;
        int height;
        AVL<T> left;
        AVL<T> right;
        AVLnode(const T& other);
    };
    AVLnode* root;

    AVL<T>& get_right_subtree();
    AVL<T>& get_left_subtree();
    const AVL<T>& get_right_subtree() const;
    const AVL<T>& get_left_subtree() const;
    int get_height() const;
    int get_balance_factor() const;
    void fix_height() const;
    int size() const;

    void rotate_left();
    void rotate_right();
    void balance();

  public:
    AVL() = default;
    ~AVL();

    bool is_empty() const;
    bool contain(const T& other) const;
    T& find_min() const;
    T& find_max() const;
    AVLnode* find_node(const T& other) const;
    AVLnode* find_kth_largest_node(int k) const;

    void print(int depth = 0) const;

    void insert(const T& other);
    void remove(const T& other);
};

#endif INC_AVLT_HPP