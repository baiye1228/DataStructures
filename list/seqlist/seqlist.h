/**
 * ************************************************************************
 * @filename: seqlist.h
 *
 * @brief :
 *
 *
 * @author : baiyebzx (baiyebzx1228@gmail.com)
 * @date : 2024-08-05
 *
 * ************************************************************************
 */

#ifndef _SEQLIST_H_
#define _SEQLIST_H_

#include <cassert>
#include <stdexcept>

namespace bu_tools {

/****************************************************************************************************

类外辅助函数

****************************************************************************************************/

/**
 * *****************************************************************
 * @brief : 相等
 * @tparam T
 * @param  l_e
 * @param  r_e
 * @return true
 * @return false
 * *****************************************************************
 */
template <typename T>
bool equal(const T &l_e, const T &r_e) {
  if (l_e == r_e) {
    return true;
  }
  return false;
}

/**
 * *****************************************************************
 * @brief : 大于
 * @tparam T
 * @param  l_e
 * @param  r_e
 * @return true
 * @return false
 * *****************************************************************
 */
template <typename T>
bool bigger(const T &l_e, const T &r_e) {
  if (l_e > r_e) {
    return true;
  }
  return false;
}

/**
 * *****************************************************************
 * @brief : 小于
 * @tparam T
 * @param  l_e
 * @param  r_e
 * @return true
 * @return false
 * *****************************************************************
 */
template <typename T>
bool smaller(const T &l_e, const T &r_e) {
  if (l_e < r_e) {
    return true;
  }
  return false;
}

/****************************************************************************************************

顺序表基类

****************************************************************************************************/

template <typename T>
class SeqList {

protected:
  T *m_elem;      // 指向动态分配数组的指针
  int m_capacity; // 顺序表的最大容量
  int m_n;        // 当前顺序表中的元素数量

private:
  void resize();

public:
  SeqList(/* args */);
  SeqList(const SeqList<T> &L);
  virtual ~SeqList();

  void clear();
  bool delete_elem(int index, T &e);
  bool get_elem(int index, T &e) const;
  int get_length() const;
  int get_capacity() const;
  bool insert(int index, const T &e);
  void append(const T &e);
  bool is_empty() const;
  int locate_elem(const T &e, bool (*compare)(const T &, const T &)) const;
  bool next_elem(const T &e, T &next_e) const;
  bool prior_elem(const T &e, T &prior_e) const;
  SeqList<T> &operator=(const SeqList<T> &right_L);
  T &operator[](int index);
  T &operator[](int index) const;
};

/****************************************************************************************************

类成员函数定义

****************************************************************************************************/

/**
 * *****************************************************************
 * @brief : 动态扩容函数
 * @tparam T
 * *****************************************************************
 */
template <typename T>
inline void SeqList<T>::resize() {

  m_capacity *= 2; // 常见的扩容策略是加倍容量
  T *new_data = new T[m_capacity];
  assert(new_data != 0);

  for (int i = 0; i < m_n; ++i) {
    new_data[i] = m_elem[i];
  }
  delete[] m_elem;   // 释放旧数组内存
  m_elem = new_data; // 更新数组指针
}

/**
 * *****************************************************************
 * @brief : Construct a new Seq List< T>:: Seq List object
 * @tparam T
 * *****************************************************************
 */
template <typename T>
inline SeqList<T>::SeqList() {
  m_capacity = 0;
  m_n = 0;
  m_elem = nullptr;
}

/**
 * *****************************************************************
 * @brief : Construct a new Seq List< T>:: Seq List object
 * @tparam T
 * @param  L        用于拷贝初始化的顺序表
 * *****************************************************************
 */
template <typename T>
inline SeqList<T>::SeqList(const SeqList<T> &L) {
  m_elem = new T[L.m_capacity];

  assert(m_elem != 0);

  m_capacity = L.m_capacity;
  m_n = L.m_n;

  for (int i = 1; i <= m_n; ++i) {
    m_elem[i - 1] = L.m_elem[i - 1];
  }
}

/**
 * *****************************************************************
 * @brief : Destroy the Seq List< T>:: Seq List object
 * @tparam T
 * *****************************************************************
 */
template <typename T>
inline SeqList<T>::~SeqList() {
  delete[] m_elem;
}

/**
 * *****************************************************************
 * @brief : 把顺序表置空
 * @tparam T
 * *****************************************************************
 */
template <typename T>
inline void SeqList<T>::clear() {

  if (m_elem != nullptr) {
    m_n = 0;
    m_capacity = 0;
    delete[] m_elem;
    m_elem = nullptr;
  }
}

/**
 * *****************************************************************
 * @brief : 删除指定位置元素
 * @tparam T
 * @param  index            指定序号
 * @param  e                删除的元素值
 * @return true
 * @return false
 * *****************************************************************
 */
template <typename T>
inline bool SeqList<T>::delete_elem(int index, T &e) {
  //判断是否越界
  if (index < 1 || index > m_n) {
    return false;
  }

  e = m_elem[index - 1];

  //元素往前移动
  for (int i = index + 1; i <= m_n; ++i) {
    m_elem[i - 2] = m_elem[i - 1];
  }

  --m_n;

  return true;
}

/**
 * *****************************************************************
 * @brief : 取指定位置元素
 * @tparam T
 * @param  index            指定序号
 * @param  e                指定位置元素值
 * @return true
 * @return false
 * *****************************************************************
 */
template <typename T>
inline bool SeqList<T>::get_elem(int index, T &e) const {
  //判断是否越界
  if (index < 1 || index > m_n) {
    return false;
  }

  e = m_elem[index - 1];

  return true;
}

/**
 * *****************************************************************
 * @brief : 顺序表中元素个数
 * @tparam T
 * @return int
 * *****************************************************************
 */
template <typename T>
inline int SeqList<T>::get_length() const {
  return m_n;
}

/**
 * *****************************************************************
 * @brief : 顺序表存储空间大小
 * @tparam T
 * @return int
 * *****************************************************************
 */
template <typename T>
inline int SeqList<T>::get_capacity() const {
  return m_capacity;
}

/**
 * *****************************************************************
 * @brief : 在指定序号之前插入一个元素
 * @tparam T
 * @param  index            指定序号
 * @param  e                待插元素
 * @return true
 * @return false
 * *****************************************************************
 */
template <typename T>
inline bool SeqList<T>::insert(int index, const T &e) {
  //判断是否越界
  if (index < 1 || index > m_n) {
    return false;
  }

  T *new_base;

  //判断当前空间是否已满
  if (m_n == m_capacity) {
    resize();
  }

  //元素后移
  for (int i = m_n; i >= index; --i) {
    m_elem[i] = m_elem[i - 1];
  }
  m_elem[index - 1] = e;

  ++m_n;
  return true;
}

/**
 * *****************************************************************
 * @brief : 追加元素
 * @tparam T
 * @param  e                追加的元素值
 * @return true
 * @return false
 * *****************************************************************
 */
template <typename T>
inline void SeqList<T>::append(const T &e) {

  //已经放满了
  if (m_n == m_capacity) {
    if (m_capacity == 0) {
      m_capacity = 1; //初始容积为1
    }
    resize();
  }

  m_elem[m_n] = e;

  ++m_n;
}

/**
 * *****************************************************************
 * @brief : 判断顺序表是否为空
 * @tparam T
 * @return true
 * @return false
 * *****************************************************************
 */
template <typename T>
inline bool SeqList<T>::is_empty() const {
  return m_n == 0;
}

/**
 * *****************************************************************
 * @brief : 查找第一个与e满足compare()关系的节点
 * @tparam T
 * @param  e
 * @param  compare
 * @return int
 * *****************************************************************
 */
template <typename T>
inline int SeqList<T>::locate_elem(const T &e, bool (*compare)(const T &, const T &)) const {
  int i = 1;
  for (i; i <= m_n && !(*compare)(m_elem[i - 1], e); ++i)
    ;

  if (i <= m_n) {
    return i;
  } else {
    return 0;
  }
}

/**
 * *****************************************************************
 * @brief : 返回某元素的后继
 * @tparam T
 * @param  e                待查元素
 * @param  next_e           待查元素后继
 * @return true
 * @return false
 * *****************************************************************
 */
template <typename T>
inline bool SeqList<T>::next_elem(const T &e, T &next_e) const {
  int i = locate_elem(e, equal);

  if (i < 1 || i == m_n) {
    return false;
  } else {
    get_elem(i + 1, next_e);
  }
  return true;
}

/**
 * *****************************************************************
 * @brief : 返回某元素前驱
 * @tparam T
 * @param  e
 * @param  prior_e
 * @return true
 * @return false
 * *****************************************************************
 */
template <typename T>
inline bool SeqList<T>::prior_elem(const T &e, T &prior_e) const {
  int i = locate_elem(e, equal);

  if (i <= 1) {
    return false;
  } else {
    get_elem(i - 1, prior_e);
  }
  return true;
}

/**
 * *****************************************************************
 * @brief : 重载赋值运算符
 * @tparam T
 * @param  right_L
 * @return SeqList<T>&
 * *****************************************************************
 */
template <typename T>
inline SeqList<T> &SeqList<T>::operator=(const SeqList<T> &right_L) {
  //避免自我赋值
  if (this != &right_L) {
    delete[] m_elem;

    m_elem = new T[right_L.m_capacity];
    assert(m_elem != 0);

    m_capacity = right_L.m_capacity;
  }
  m_n = right_L.m_n;
  for (int i = 0; i < m_n; ++i) {
    m_elem[i] = right_L.m_elem[i];
  }

  return *this;
}

/**
 * *****************************************************************
 * @brief : 重载[]运算符
 * @tparam T
 * @param  index
 * @return T&
 * *****************************************************************
 */
template <typename T>
inline T &SeqList<T>::operator[](int index) {
  //判断是否越界
  if (index < 1 || index > m_n) {
    throw std::out_of_range("给出的下标越界");
  }
  return m_elem[index - 1];
}

template <typename T>
inline T &SeqList<T>::operator[](int index) const {
  //判断是否越界
  if (index < 1 || index > m_n) {
    throw std::out_of_range("给出的下标越界");
  }
  return m_elem[index - 1];
}

} // namespace bu_tools

#endif // _SEQLIST_H_
