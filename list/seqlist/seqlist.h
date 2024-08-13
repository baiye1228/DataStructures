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
bool Equal(const T &l_e, const T &r_e) {
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
bool Bigger(const T &l_e, const T &r_e) {
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
bool Smaller(const T &l_e, const T &r_e) {
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
  int m_len;      // 当前顺序表中的元素数量

private:
  void Resize();

public:
  SeqList(/* args */);
  SeqList(const SeqList<T> &L);
  virtual ~SeqList();

  void Clear();
  bool DeleteElem(int index, T &e);
  bool GetElem(int index, T &e) const;
  int GetLength() const;
  int GetCapacity() const;
  bool Insert(int index, const T &e);
  void Append(const T &e);
  bool IsEmpty() const;
  int LocateElem(const T &e, bool (*compare)(const T &, const T &)) const;
  bool NextElem(const T &e, T &next_e) const;
  bool PriorElem(const T &e, T &prior_e) const;
  SeqList<T> &operator=(const SeqList<T> &right_l);
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
inline void SeqList<T>::Resize() {

  m_capacity *= 2; // 常见的扩容策略是加倍容量
  T *new_data = new T[m_capacity];
  assert(new_data != 0);

  for (int i = 0; i < m_len; ++i) {
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
  m_len = 0;
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
  m_len = L.m_len;

  for (int i = 1; i <= m_len; ++i) {
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
inline void SeqList<T>::Clear() {

  if (m_elem != nullptr) {
    m_len = 0;
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
inline bool SeqList<T>::DeleteElem(int index, T &e) {
  //判断是否越界
  if (index < 1 || index > m_len) {
    return false;
  }

  e = m_elem[index - 1];

  //元素往前移动
  for (int i = index + 1; i <= m_len; ++i) {
    m_elem[i - 2] = m_elem[i - 1];
  }

  --m_len;

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
inline bool SeqList<T>::GetElem(int index, T &e) const {
  //判断是否越界
  if (index < 1 || index > m_len) {
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
inline int SeqList<T>::GetLength() const {
  return m_len;
}

/**
 * *****************************************************************
 * @brief : 顺序表存储空间大小
 * @tparam T
 * @return int
 * *****************************************************************
 */
template <typename T>
inline int SeqList<T>::GetCapacity() const {
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
inline bool SeqList<T>::Insert(int index, const T &e) {
  //判断是否越界
  if (index < 1 || index > m_len) {
    return false;
  }

  T *new_base;

  //判断当前空间是否已满
  if (m_len == m_capacity) {
    Resize();
  }

  //元素后移
  for (int i = m_len; i >= index; --i) {
    m_elem[i] = m_elem[i - 1];
  }
  m_elem[index - 1] = e;

  ++m_len;
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
inline void SeqList<T>::Append(const T &e) {

  //已经放满了
  if (m_len == m_capacity) {
    if (m_capacity == 0) {
      m_capacity = 1; //初始容积为1
    }
    Resize();
  }

  m_elem[m_len] = e;

  ++m_len;
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
inline bool SeqList<T>::IsEmpty() const {
  return m_len == 0;
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
inline int SeqList<T>::LocateElem(const T &e, bool (*compare)(const T &, const T &)) const {
  int i = 1;
  for (i; i <= m_len && !(*compare)(m_elem[i - 1], e); ++i)
    ;

  if (i <= m_len) {
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
inline bool SeqList<T>::NextElem(const T &e, T &next_e) const {
  int i = LocateElem(e, Equal);

  if (i < 1 || i == m_len) {
    return false;
  } else {
    GetElem(i + 1, next_e);
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
inline bool SeqList<T>::PriorElem(const T &e, T &prior_e) const {
  int i = LocateElem(e, Equal);

  if (i <= 1) {
    return false;
  } else {
    GetElem(i - 1, prior_e);
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
inline SeqList<T> &SeqList<T>::operator=(const SeqList<T> &right_l) {
  //避免自我赋值
  if (this != &right_l) {
    delete[] m_elem;

    m_elem = new T[right_l.m_capacity];
    assert(m_elem != 0);

    m_capacity = right_l.m_capacity;
  }
  m_len = right_l.m_len;
  for (int i = 0; i < m_len; ++i) {
    m_elem[i] = right_l.m_elem[i];
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
  if (index < 1 || index > m_len) {
    throw std::out_of_range("给出的下标越界");
  }
  return m_elem[index - 1];
}

template <typename T>
inline T &SeqList<T>::operator[](int index) const {
  //判断是否越界
  if (index < 1 || index > m_len) {
    throw std::out_of_range("给出的下标越界");
  }
  return m_elem[index - 1];
}

} // namespace bu_tools

#endif // _SEQLIST_H_
