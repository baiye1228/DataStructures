/**
 * ************************************************************************
 * @filename: tripletsparsematrix.h
 *
 * @brief : 稀疏矩阵（三元组）
 *
 *
 * @author : baiyebzx (baiyebzx1228@gmail.com)
 * @date : 2024-08-29
 *
 * ************************************************************************
 */

#ifndef _TRIPLETSPARSEMATRIX_H_
#define _TRIPLETSPARSEMATRIX_H_

#include <algorithm>
namespace bu_tools {

/**
 * *****************************************************************
 * @brief : 稀疏矩阵（三元组）模板类
 * @tparam T
 * *****************************************************************
 */
template <typename T>
class TripletSparseMatrix {
private:
  /*****************************************************************

  嵌套三元组类

  *****************************************************************/

  class Triple {

  public:
    int m_row; //所在行
    int m_col; //所在列
    T m_value;

    Triple() {
      m_row = -1;
      m_col = -1;
    }
    Triple(int r, int c, const T &v) : m_row(r), m_col(c), m_value(v) {}
  };

  /*****************************************************************

  数据域

  *****************************************************************/
protected:
  int m_rows;     //行数
  int m_cols;     //列数
  int m_total;    //非零元素个数
  int m_capacity; //存储空间大小
  Triple *m_data;

  /*****************************************************************

  成员函数声明

  *****************************************************************/

private:
  void Resize();
  void InsertAt(int index, const Triple &elem);

public:
  void Clear();
  void Transpose(TripletSparseMatrix<T> &matrix) const;
  void TransposeFast(TripletSparseMatrix<T> &matrix) const;
  int GetRows() const;
  int GetCols() const;
  int GetTolal() const;
  bool IsEmpty() const;
  bool Insert(int r, int c, const T &e);
  bool GetValue(int r, int c, T &e) const;
  TripletSparseMatrix<T> &operator=(const TripletSparseMatrix<T> &other);
  TripletSparseMatrix<T> operator+(const TripletSparseMatrix<T> &other);
  TripletSparseMatrix<T> operator*(const TripletSparseMatrix<T> &other);

  TripletSparseMatrix(int r, int c, int cap = 10) : m_rows(r), m_cols(c), m_capacity(cap), m_total(0) {
    m_data = new Triple[m_capacity];
  }
  virtual ~TripletSparseMatrix() {
    delete[] m_data;
  }
  TripletSparseMatrix(const TripletSparseMatrix &other) {
    m_rows = other.m_rows;
    m_cols = other.m_cols;

    m_total = other.m_total;
    m_capacity = other.m_capacity;

    m_data = new Triple[m_capacity];

    for (int i = 0; i < m_total; ++i) {
      m_data[i] = other.m_data[i];
    }
  }

  //移动构造函数
  TripletSparseMatrix(TripletSparseMatrix &&other) noexcept {
    m_rows = other.m_rows;
    m_cols = other.m_cols;
    m_total = other.m_total;
    m_capacity = other.m_capacity;

    m_data = other.m_data;

    //清空other
    other.m_data = nullptr;
    other.m_total = 0;
  }

  //移动赋值运算符
  TripletSparseMatrix &operator=(TripletSparseMatrix &&other) noexcept {
    if (this != &other) {
      delete[] m_data;

      m_rows = other.m_rows;
      m_cols = other.m_cols;
      m_total = other.m_total;
      m_capacity = other.m_capacity;

      m_data = other.m_data;

      //清空other
      other.m_data = nullptr;
      other.m_total = 0;
    }
    return *this;
  }

  /*****************************************************************

  嵌套迭代器

  *****************************************************************/
  class Iterator {

  private:
    Triple *m_current; //当前指向的三元组

  public:
    Iterator(Triple *ptr) : m_current(ptr) {}

    //解引用
    const Triple &operator*() const {
      return *m_current;
    }

    //指针操作
    const Triple *operator->() const {
      return m_current;
    }

    // 前置++操作符
    Iterator &operator++() {
      ++m_current;
      return *this;
    }

    // 后置++操作符
    Iterator operator++(int) {
      Iterator temp = *this;
      ++m_current;
      return temp;
    }

    // 相等比较操作符
    bool operator==(const Iterator &other) const { return m_current == other.m_current; }

    // 不相等比较操作符
    bool operator!=(const Iterator &other) const { return m_current != other.m_current; }
  };

  // begin() 函数返回指向第一个元素的迭代器
  Iterator begin() const {
    return Iterator(m_data);
  }

  // end() 函数返回指向超出最后一个元素的迭代器
  Iterator end() const {
    return Iterator(m_data + m_total);
  }
};

/////////////////////////////////////////////////////////////////////////////////////////////////////
/*

稀疏矩阵成员函数定义

*/
/////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * *****************************************************************
 * @brief : 扩容
 * @tparam T
 * *****************************************************************
 */
template <typename T>
inline void TripletSparseMatrix<T>::Resize() {
  m_capacity *= 2;
  Triple *new_data = new Triple[m_capacity];

  for (int i = 0; i < m_total; ++i) {
    new_data[i] = m_data[i];
  }

  delete[] m_data;
  m_data = new_data;
}

/**
 * *****************************************************************
 * @brief : 在指定位置插入元素，后续元素后移
 * @tparam T
 * @param  index
 * @param  elem
 * *****************************************************************
 */
template <typename T>
inline void TripletSparseMatrix<T>::InsertAt(int index, const Triple &elem) {
  if (!m_data) {
    m_data = new Triple[m_capacity];
  }
  if (m_total == m_capacity) {
    Resize();
  }

  if (m_data[index].m_row != -1) {
    for (int i = m_total; i > index; --i) {
      m_data[i] = m_data[i - 1];
    }
  }

  m_data[index] = elem;
  ++m_total;
}

/**
 * *****************************************************************
 * @brief : 置空,不改变稀疏矩阵结构
 * @tparam T
 * *****************************************************************
 */
template <typename T>
inline void TripletSparseMatrix<T>::Clear() {
  if (m_data) {
    delete[] m_data;
  }
  m_capacity = 10;
  m_data = nullptr;
  m_total = 0;
}

/**
 * *****************************************************************
 * @brief : 简单转置，直接交换行列
 * @tparam T
 * @param  matrix
 * *****************************************************************
 */
template <typename T>
inline void TripletSparseMatrix<T>::Transpose(TripletSparseMatrix<T> &matrix) const {
  matrix.Clear();

  //改变传入对象的结构
  matrix.m_rows = m_cols;
  matrix.m_cols = m_rows;

  int row, col;
  T val;
  for (int i = 0; i < m_total; ++i) {
    row = m_data[i].m_col;
    col = m_data[i].m_row;
    val = m_data[i].m_value;

    matrix.Insert(row, col, val);
  }
}

/**
 * *****************************************************************
 * @brief : 快速转置
 * @tparam T
 * @param  matrix
 * *****************************************************************
 */
template <typename T>
inline void TripletSparseMatrix<T>::TransposeFast(TripletSparseMatrix<T> &matrix) const {

  int col_count[m_cols] = {0};
  int position[m_cols] = {0};

  // 统计每列非零元素的个数
  for (int i = 0; i < m_total; ++i) {
    int col = m_data[i].m_col;
    col_count[col]++;
  }

  // 计算每列元素在转置矩阵中的起始位置
  for (int i = 1; i < m_cols; ++i) {
    position[i] = position[i - 1] + col_count[i - 1];
  }

  // 填充转置矩阵
  matrix.Clear();
  matrix.m_capacity = m_capacity;
  matrix.m_rows = m_cols;
  matrix.m_cols = m_rows;
  // matrix.m_total=m_total;
  matrix.m_data = new Triple[matrix.m_capacity];

  Triple elem;
  for (int i = 0; i < m_total; ++i) {
    int col = m_data[i].m_col;
    int pos = position[col];
    ++position[col];

    elem.m_row = m_data[i].m_col;
    elem.m_col = m_data[i].m_row;
    elem.m_value = m_data[i].m_value;

    matrix.InsertAt(pos, elem);
  }
}

/**
 * *****************************************************************
 * @brief : 获取行数
 * @tparam T
 * @return int
 * *****************************************************************
 */
template <typename T>
inline int TripletSparseMatrix<T>::GetRows() const {
  return m_rows;
}

/**
 * *****************************************************************
 * @brief : 获取列数
 * @tparam T
 * @return int
 * *****************************************************************
 */
template <typename T>
inline int TripletSparseMatrix<T>::GetCols() const {
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
inline int TripletSparseMatrix<T>::GetTolal() const {
  return m_total;
}

/**
 * *****************************************************************
 * @brief : 是否为空
 * @tparam T
 * @return true
 * @return false
 * *****************************************************************
 */
template <typename T>
inline bool TripletSparseMatrix<T>::IsEmpty() const {
  return m_total == 0;
}

/**
 * *****************************************************************
 * @brief : 插入
 * @tparam T
 * @param  r
 * @param  c
 * @param  e
 * *****************************************************************
 */
template <typename T>
inline bool TripletSparseMatrix<T>::Insert(int r, int c, const T &e) {
  if (r > m_rows || c > m_cols || r < 0 || c < 0) {
    return false;
  }

  //查找是否存在同行同列的元素
  for (int i = 0; i < m_total; ++i) {
    if (m_data[i].m_row > r) {
      break;
    }
    if (m_data[i].m_row == r && m_data[i].m_col == c) {
      m_data[i].m_value = e;
      return true;
    }
  }

  // 查找插入位置
  int index = 0;
  while (index < m_total && (m_data[index].m_row < r || (m_data[index].m_row == r && m_data[index].m_col < c))) {
    ++index;
  }

  // 在找到的位置插入新元素
  InsertAt(index, Triple(r, c, e));
  return true;
}

/**
 * *****************************************************************
 * @brief :
 * @tparam T
 * @param  r
 * @param  c
 * @return T&
 * *****************************************************************
 */
template <typename T>
inline bool TripletSparseMatrix<T>::GetValue(int r, int c, T &e) const {
  for (int i = 0; i < m_total; ++i) {
    if (m_data[i].m_row == r && m_data[i].m_col == c) {
      e = m_data[i].m_value;
      return true;
    }
  }

  return false;
}

/**
 * *****************************************************************
 * @brief : 重载赋值运算符
 * @tparam T
 * @param  other
 * @return TripletSparseMatrix<T>&
 * *****************************************************************
 */
template <typename T>
inline TripletSparseMatrix<T> &TripletSparseMatrix<T>::operator=(const TripletSparseMatrix<T> &other) {
  if (this != &other) {
    delete[] m_data;

    m_rows = other.m_rows;
    m_cols = other.m_cols;
    m_total = other.m_total;
    m_capacity = other.m_capacity;

    m_data = new Triple[m_capacity];

    for (int i = 0; i < m_total; ++i) {
      m_data[i] = other.m_data[i];
    }
  }

  return *this;
}

/**
 * *****************************************************************
 * @brief : 重载加法运算符
 * @tparam T
 * @param  other
 * @return TripletSparseMatrix<T>&
 * *****************************************************************
 */
template <typename T>
inline TripletSparseMatrix<T> TripletSparseMatrix<T>::operator+(const TripletSparseMatrix<T> &other) {
  // 检查矩阵尺寸是否相同
  if (m_rows != other.m_rows || m_cols != other.m_cols) {
    return TripletSparseMatrix(0, 0);
  }

  TripletSparseMatrix result(m_rows, m_cols);

  int i = 0, j = 0, index = 0;
  while (i < m_total && j < other.m_total) {
    //行列排序更小的先进
    if (m_data[i].m_row < other.m_data[j].m_row || (m_data[i].m_row == other.m_data[j].m_row && m_data[i].m_col < other.m_data[j].m_col)) {
      // result.Insert(m_data[i].m_row,m_data[i].m_col,m_data[i].m_value);
      result.InsertAt(index, m_data[i]);
      ++i;
      ++index;
    } else if (m_data[i].m_row > other.m_data[j].m_row || (m_data[i].m_row == other.m_data[j].m_row && m_data[i].m_col > other.m_data[j].m_col)) {
      // result.Insert(other.m_data[j].m_row,other.m_data[j].m_col,other.m_data[j].m_value);
      result.InsertAt(index, other.m_data[j]);
      ++j;
      ++index;
    } else {
      T sum = m_data[i].m_value + other.m_data[j].m_value;
      if (sum != 0) {
        result.Insert(m_data[i].m_row, m_data[i].m_col, sum);
        ++index;
      }
      ++i;
      ++j;
    }
  }

  while (i < m_total) {
    result.InsertAt(index, m_data[i]);
    ++i;
    ++index;
  }

  while (i < other.m_total) {
    result.InsertAt(index, other.m_data[j]);
    ++j;
    ++index;
  }

  return std::move(result);
}

/**
 * *****************************************************************
 * @brief : 重载乘法运算符
 * @tparam T
 * @param  other
 * @return TripletSparseMatrix<T>&
 * *****************************************************************
 */
template <typename T>
inline TripletSparseMatrix<T> TripletSparseMatrix<T>::operator*(const TripletSparseMatrix<T> &other) {
  if (m_cols != other.m_rows) {
    return TripletSparseMatrix(0, 0);
  }

  TripletSparseMatrix result(m_rows, other.m_cols);

  for (int i = 0; i < m_rows; ++i) {         //当前矩阵的行
    for (int j = 0; j < other.m_cols; ++j) { //另一个矩阵的列
      T sum = 0;
      T val1 = 0, val2 = 0;
      for (int k = 0; k < m_cols; ++k) {
        if (GetValue(i, k, val1) && other.GetValue(k, j, val2)) {
          sum += val1 * val2;
        }
      }

      if (sum != 0) {
        result.Insert(i, j, sum);
      }
    }
  }

  return std::move(result);
}

} // namespace bu_tools

#endif // _TRIPLETSPARSEMATRIX_H_