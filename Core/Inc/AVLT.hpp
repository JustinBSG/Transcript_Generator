#ifndef INC_AVLT_HPP
#define INC_AVLT_HPP

using namespace std;

template <typename T>
class AVL {
  private:
    struct AVLnode {
      T data;
      int height;
      AVL left;
      AVL right;
      AVLnode(const T& other);
    };
    AVLnode *root;

    AVL& get_right_subtree() const;
    AVL& get_left_subtree() const;
    int get_height() const;
    int get_balance_factor() const;
    void fix_height() const;

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
    T& find_node(const T& other) const;
    T& find_kth_largest(int k) const;

    void print(int depth = 0) const;

    void insert(const T& other);
    void remove(const T& other);
};

#endif INC_AVLT_HPP