/**
 * ************************************************************************
 * @filename: crosssparsematrix.h
 *
 * @brief : 稀疏矩阵（十字链表）
 *
 *
 * @author : baiyebzx (baiyebzx1228@gmail.com)
 * @date : 2024-09-01
 *
 * ************************************************************************
 */

#ifndef _CROSSSPARSEMATRIX_H_
#define _CROSSSPARSEMATRIX_H_

#include <algorithm>
namespace bu_tools {

/**
 * *****************************************************************
 * @brief : 稀疏矩阵模板类（十字链表）
 * @tparam T
 * *****************************************************************
 */
template <typename T>
class CrossSparseMatrix {

private:
  /*****************************************************************

  嵌套结点类

  *****************************************************************/

  class Node {
  public:
    int m_row;     //行
    int m_col;     //列
    T m_value;     //存储的值
    Node *m_right; //指向右侧的结点
    Node *m_down;  //指向下方的结点

    Node() {
      m_row = -1;
      m_col = -1;
      m_right = nullptr;
      m_down = nullptr;
    }
    Node(int r, int c, const T &val) : m_row(r), m_col(c), m_value(val), m_right(nullptr), m_down(nullptr) {}
  };

  typedef Node *NodePointer;

protected:
  /*****************************************************************

  数据域

  *****************************************************************/
  int m_rows;                //行数
  int m_cols;                //列数
  int m_total;               //非零元素个数
  NodePointer *m_rows_heads; //行链表指针数组
  NodePointer *m_cols_heads; //列链表指针数组

public:
  /*****************************************************************

  成员函数

  *****************************************************************/

  CrossSparseMatrix(int r, int c) : m_rows(r), m_cols(c), m_total(0) {
    m_rows_heads = new NodePointer[m_rows];
    m_cols_heads = new NodePointer[m_cols];
  }
  virtual ~CrossSparseMatrix();
  CrossSparseMatrix(const CrossSparseMatrix &other) : m_rows(other.m_rows), m_cols(other.m_cols), m_total(0) {
    m_rows_heads = new NodePointer[m_rows];
    m_cols_heads = new NodePointer[m_cols];

    for (int i = 0; i < m_rows; ++i) {
      NodePointer current = other.m_rows_heads[i];
      while (current != nullptr) {
        Insert(current->m_col, current->m_col, current->m_value);
        current = current->m_right;
      }
    }
  }

  //移动构造函数
  CrossSparseMatrix(CrossSparseMatrix &&other) noexcept {
    m_rows = other.m_rows;
    m_cols = other.m_cols;
    m_total = other.m_total;

    m_rows_heads = new NodePointer[m_rows];
    m_cols_heads = new NodePointer[m_cols];

    for (int i = 0; i < m_rows; ++i) {
      m_rows_heads[i] = other.m_rows_heads[i];
      other.m_rows_heads[i] = nullptr;
    }
    for (int i = 0; i < m_cols; ++i) {
      m_cols_heads[i] = other.m_cols_heads[i];
      other.m_cols_heads[i] = nullptr;
    }

    delete[] other.m_rows_heads;
    delete[] other.m_cols_heads;
    other.m_total = 0;
  }

  //移动赋值运算符
  CrossSparseMatrix &operator=(CrossSparseMatrix &&other) noexcept {
    if (this != &other) {
      m_rows = other.m_rows;
      m_cols = other.m_cols;
      m_total = other.m_total;

      m_rows_heads = new NodePointer[m_rows];
      m_cols_heads = new NodePointer[m_cols];

      for (int i = 0; i < m_rows; ++i) {
        m_rows_heads[i] = other.m_rows_heads[i];
        other.m_rows_heads[i] = nullptr;
      }
      for (int i = 0; i < m_cols; ++i) {
        m_cols_heads[i] = other.m_cols_heads[i];
        other.m_cols_heads[i] = nullptr;
      }

      delete[] other.m_rows_heads;
      delete[] other.m_cols_heads;
      other.m_total = 0;
    }

    return *this;
  }

  void Clear();
  int GetRows() const;
  int GetCols() const;
  int GetTotal() const;
  bool IsEmpty() const;
  bool Insert(int r, int c, const T &value);
  bool GetValue(int r, int c, T &e) const;

  CrossSparseMatrix<T> &operator=(const CrossSparseMatrix<T> &other);
  CrossSparseMatrix<T> operator+(const CrossSparseMatrix<T> &other);
};

/////////////////////////////////////////////////////////////////////////////////////////////////////
/*

成员函数的定义

*/
/////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * *****************************************************************
 * @brief : Destroy the Cross Sparse Matrix< T>:: Cross Sparse Matrix object
 * @tparam T
 * *****************************************************************
 */
template <typename T>
inline CrossSparseMatrix<T>::~CrossSparseMatrix() {
  Clear();
  if (!m_rows_heads) {
    delete[] m_rows_heads;
  }

  if (!m_cols_heads) {
    delete[] m_cols_heads;
  }
}

/**
 * *****************************************************************
 * @brief : 置空,不改变结构,只清空结点
 * @tparam T
 * *****************************************************************
 */
template <typename T>
inline void CrossSparseMatrix<T>::Clear() {
  if (m_total == 0) {
    return;
  }

  //清空结点
  for (int i = 0; i < m_rows; ++i) {
    NodePointer current = m_rows_heads[i];
    while (current != nullptr) {
      NodePointer to_delete = current;
      current = current->m_right;
      delete to_delete;
    }
  }
  //将两个指针数组全部置空
  for (int i = 0; i < m_rows; ++i) {
    m_rows_heads[i] = nullptr;
  }

  for (int i = 0; i < m_cols; ++i) {
    m_cols_heads[i] = nullptr;
  }

  m_total = 0;
}

/**
 * *****************************************************************
 * @brief : 获取行
 * @tparam T
 * @return int
 * *****************************************************************
 */
template <typename T>
inline int CrossSparseMatrix<T>::GetRows() const {
  return m_rows;
}

/**
 * *****************************************************************
 * @brief : 获取列
 * @tparam T
 * @return int
 * *****************************************************************
 */
template <typename T>
inline int CrossSparseMatrix<T>::GetCols() const {
  return m_cols;
}

/**
 * *****************************************************************
 * @brief : 获取非零元素个数
 * @tparam T
 * @return int
 * *****************************************************************
 */
template <typename T>
inline int CrossSparseMatrix<T>::GetTotal() const {
  return m_total;
}

/**
 * *****************************************************************
 * @brief : 判断是否为空
 * @tparam T
 * @return true
 * @return false
 * *****************************************************************
 */
template <typename T>
inline bool CrossSparseMatrix<T>::IsEmpty() const {
  return m_total == 0;
}

/**
 * *****************************************************************
 * @brief : 插入元素
 * @tparam T
 * @param  r
 * @param  c
 * @param  value
 * @return true
 * @return false
 * *****************************************************************
 */
template <typename T>
inline bool CrossSparseMatrix<T>::Insert(int r, int c, const T &value) {
  if (r < 0 || r >= m_rows || c < 0 || c >= m_cols) {
    return false;
  }

  NodePointer new_node = new Node(r, c, value);

  //插入到行链表中
  if (m_rows_heads[r] == nullptr || m_rows_heads[r]->m_col > c) { //插入时是本行第一个结点
    new_node->m_right = m_rows_heads[r];
    m_rows_heads[r] = new_node;
  } else {

    NodePointer current = m_rows_heads[r];
    while (current->m_right != nullptr && current->m_right->m_col < c) {
      current = current->m_right;
    }
    if (current->m_right != nullptr && current->m_right->m_col == c) {
      current->m_right->m_value = value;
    } else {
      new_node->m_right = current->m_right;
      current->m_right = new_node;
    }
  }

  //插入到列链表中
  if (m_cols_heads[c] == nullptr || m_cols_heads[c]->m_row > r) { //插入时是本列的第一个结点
    new_node->m_down = m_cols_heads[c];
    m_cols_heads[c] = new_node;
  } else {
    NodePointer current = m_cols_heads[c];
    while (current->m_down != nullptr && current->m_down->m_row < r) {
      current = current->m_down;
    }

    //存在同行同列的情况
    if (current->m_down != nullptr && current->m_down->m_row == r) {
      current->m_down->m_value = value;
    } else {
      new_node->m_down = current->m_down;
      current->m_down = new_node;
    }
  }

  ++m_total;
  return true;
}

/**
 * *****************************************************************
 * @brief : 获取值
 * @tparam T
 * @param  r
 * @param  c
 * @return T&
 * *****************************************************************
 */
template <typename T>
inline bool CrossSparseMatrix<T>::GetValue(int r, int c, T &e) const {
  if (r < 0 || r >= m_rows || c < 0 || c >= m_cols) {
    return false;
  }

  NodePointer current = m_rows_heads[r];
  while (current != nullptr && current->m_col != c) {
    current = current->m_right;
  }

  if (!current) {
    return false;
  } else {
    e = current->m_value;
    return true;
  }
}

/**
 * *****************************************************************
 * @brief : 重载赋值运算符
 * @tparam T
 * @param  other
 * @return CrossSparseMatrix<T>&
 * *****************************************************************
 */
template <typename T>
inline CrossSparseMatrix<T> &CrossSparseMatrix<T>::operator=(const CrossSparseMatrix<T> &other) {
  if (this != &other) {
    Clear(); //清空矩阵
    delete[] m_rows_heads;
    delete[] m_cols_heads;

    //允许改变结构
    m_rows = other.m_rows;
    m_cols = other.m_cols;

    m_rows_heads = new NodePointer[m_rows];
    m_cols_heads = new NodePointer[m_cols];

    for (int i = 0; i < m_rows; ++i) {
      NodePointer current = other.m_rows_heads[i];
      while (current != nullptr) {
        Insert(current->m_row, current->m_col, current->m_value);
        current = current->m_right;
      }
    }
  }

  return *this;
}

/**
 * *****************************************************************
 * @brief : 重载加法运算符
 * @tparam T
 * @param  other
 * @return CrossSparseMatrix<T>&
 * *****************************************************************
 */
template <typename T>
inline CrossSparseMatrix<T> CrossSparseMatrix<T>::operator+(const CrossSparseMatrix<T> &other) {
  if (m_rows != other.m_rows || m_cols != other.m_cols) {
    return CrossSparseMatrix(0, 0);
  }

  CrossSparseMatrix result(m_rows, m_cols);
  for (int i = 0; i < m_rows; ++i) {
    NodePointer current_this = m_rows_heads[i];
    NodePointer current_other = other.m_rows_heads[i];

    while (current_this != nullptr || current_other != nullptr) {
      if (current_this == nullptr) { //这个位置是0
        result.Insert(current_other->m_row, current_other->m_col, current_other->m_value);
        current_other = current_other->m_right;
      } else if (current_other == nullptr) {
        result.Insert(current_this->m_row, current_this->m_col, current_this->m_value);
        current_this = current_this->m_right;
      } else if (current_this->m_col < current_other->m_col) {
        result.Insert(current_this->m_row, current_this->m_col, current_this->m_value);
        current_this = current_this->m_right;
      } else if (current_this->m_col > current_other->m_col) {
        result.Insert(current_other->m_row, current_other->m_col, current_other->m_value);
        current_other = current_other->m_right;
      } else {
        result.Insert(current_this->m_row, current_this->m_col, current_this->m_value + current_other->m_value);
        current_this = current_this->m_right;
        current_other = current_other->m_right;
      }
    }
  }

  return std::move(result);
}

} // namespace bu_tools

#endif // _CROSSSPARSEMATRIX_H_