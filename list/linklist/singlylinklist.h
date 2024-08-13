/**
 * ************************************************************************
 * @filename: singlylinklist.h
 *
 * @brief : 单链表基类
 *
 *
 * @author : baiyebzx (baiyebzx1228@gmail.com)
 * @date : 2024-08-05
 *
 * ************************************************************************
 */

#ifndef _SINGLYLINKLIST_H_
#define _SINGLYLINKLIST_H_

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

单链表的节点类

****************************************************************************************************/
template <typename T>
class SNode {
public:
  T m_data;
  SNode<T> *m_next;

  SNode(const T &val) : m_data(val), m_next(nullptr) {}
};

/****************************************************************************************************

非循环单链表数据结构C++类

****************************************************************************************************/

template <typename T>
class SinglyLinkList {
private:
  void CopyList(const SinglyLinkList<T> &other_L);

protected:
  typedef SNode<T> *SNodePointer;

  SNodePointer m_head; //头指针
  int m_len;           //节点个数

public:
  SinglyLinkList() : m_head(nullptr), m_len(0) {}
  SinglyLinkList(const SinglyLinkList &other_l) : m_head(nullptr) {
    CopyList(other_l);
  }
  virtual ~SinglyLinkList();

  void Reverse();
  void Clear();
  void Append(const T &value);
  bool DeleteElem(const T &e);
  void DeleteRepeat();
  bool GetElem(int index, T &e) const;
  SNodePointer GetHead() const;
  int GetLength() const;
  bool Insert(int index, const T &e);
  bool IsEmpty() const;
  int LocateElem(const T &e, bool (*compare)(const T &, const T &)) const;
  bool NextElem(const T &e, T &next_e) const;
  bool PriorElem(const T &e, T &prior_e) const;
  SinglyLinkList<T> &operator=(const SinglyLinkList<T> &right_l);
};

/****************************************************************************************************

成员函数定义

****************************************************************************************************/

/**
 * *****************************************************************
 * @brief :内部的复制函数
 * @tparam T
 * @param  other_l
 * *****************************************************************
 */
template <typename T>
inline void SinglyLinkList<T>::CopyList(const SinglyLinkList<T> &other_l) {
  if (other_l.m_head == nullptr) {
    m_head = nullptr;
    return;
  }

  m_head = new SNode<T>(other_l.m_head->m_data);

  SNodePointer curren_this = m_head;
  SNodePointer current_other = other_l.m_head->m_next;

  while (current_other != nullptr) {
    curren_this->m_next = new SNode<T>(current_other->m_data);
    curren_this = curren_this->m_next;
    current_other = current_other->m_next;
  }
  m_len = other_l.m_len;
}

/**
 * *****************************************************************
 * @brief : Destroy the Singly Link List< T>:: Singly Link List object
 * @tparam T
 * *****************************************************************
 */
template <typename T>
inline SinglyLinkList<T>::~SinglyLinkList() {
  SNodePointer current = m_head;
  while (current != nullptr) {
    SNodePointer next_node = current->m_next;
    delete current;
    current = next_node;
  }
}

/**
 * *****************************************************************
 * @brief : 逆置
 * @tparam T
 * *****************************************************************
 */
template <typename T>
inline void SinglyLinkList<T>::Reverse() {

  SNodePointer prev = nullptr;
  SNodePointer current = m_head;
  SNodePointer next = nullptr;

  while (current != nullptr) {
    next = current->m_next;
    current->m_next = prev;
    prev = current;
    current = next;
  }
  m_head = prev; // 新的头节点是原来的最后一个节点
}

/**
 * *****************************************************************
 * @brief : 置空
 * @tparam T
 * *****************************************************************
 */
template <typename T>
inline void SinglyLinkList<T>::Clear() {
  SNodePointer current = m_head;
  while (current != nullptr) {
    SNodePointer next = current->m_next;
    delete current;
    current = next;
  }
  m_head = nullptr;
  m_len = 0;
}

/**
 * *****************************************************************
 * @brief : 往后追加节点
 * @tparam T
 * @param  value            节点元素值
 * *****************************************************************
 */
template <typename T>
inline void SinglyLinkList<T>::Append(const T &value) {
  SNodePointer new_node = new SNode<T>(value);
  if (!m_head) {
    m_head = new_node;

  } else {
    SNodePointer current = m_head;
    while (current->m_next) {
      current = current->m_next;
    }
    current->m_next = new_node;
  }
  ++m_len;
}

/**
 * *****************************************************************
 * @brief : 删除值为e的节点
 * @tparam T
 * @param  e
 * @return true
 * @return false
 * *****************************************************************
 */
template <typename T>
inline bool SinglyLinkList<T>::DeleteElem(const T &e) {
  if (!m_head) {
    return false;
  }

  if (m_head->m_data == e) {
    SNodePointer temp = m_head;
    m_head = m_head->m_next;
    delete temp;
    --m_len;
    return true;
  }

  SNodePointer current = m_head;
  while (current->m_next && current->m_next->m_data != e) {
    current = current->m_next;
  }

  if (current->m_next) {
    SNodePointer temp = current->m_next;
    current->m_next = current->m_next->m_next;
    delete temp;
    --m_len;
    return true;
  }
  return false;
}

/**
 * *****************************************************************
 * @brief : 删除重复值
 * @tparam T
 * *****************************************************************
 */
template <typename T>
inline void SinglyLinkList<T>::DeleteRepeat() {
  if (!m_head) {
    return;
  }

  SNodePointer current = m_head;

  while (current != nullptr && current->m_next != nullptr) {
    SNodePointer runner = current;
    while (runner->m_next != nullptr) {
      if (runner->m_next->m_data == current->m_data) {
        SNodePointer temp = runner->m_next;
        runner->m_next = runner->m_next->m_next;
        delete temp;
        --m_len;
      } else {
        runner = runner->m_next;
      }
    }
    current = current->m_next;
  }
}

/**
 * *****************************************************************
 * @brief : 取第i个节点
 * @tparam T
 * @param  index            指定位置
 * @param  e                第i个节点的值
 * @return true
 * @return false
 * *****************************************************************
 */
template <typename T>
inline bool SinglyLinkList<T>::GetElem(int index, T &e) const {
  SNodePointer current = m_head;
  int count = 1;

  while (current) {
    if (count == index) {
      e = current->m_data;
      return true;
    }
    ++count;
    current = current->m_next;
  }
  return false;
}

/**
 * *****************************************************************
 * @brief : 获取单链表表头
 * @tparam T
 * @return SinglyLinkList<T>::SNodePointer
 * *****************************************************************
 */
template <typename T>
inline typename SinglyLinkList<T>::SNodePointer SinglyLinkList<T>::GetHead() const {
  return m_head;
}

/**
 * *****************************************************************
 * @brief : 获取链表的结点的个数
 * @tparam T
 * @return int
 * *****************************************************************
 */
template <typename T>
inline int SinglyLinkList<T>::GetLength() const {
  return m_len;
}

/**
 * *****************************************************************
 * @brief : 在指定结点之前插入一个数据域为e的结点
 * @tparam T
 * @param  index            指定结点
 * @param  e                数据域
 * @return true
 * @return false
 * *****************************************************************
 */
template <typename T>
inline bool SinglyLinkList<T>::Insert(int index, const T &e) {
  if (index <= 0 || index > m_len) {
    return false;
  }

  SNodePointer new_node = new SNode<T>(e);

  if (index == 1) { // 在第一个节点之前插入（即头部插入）
    new_node->m_next = m_head;
    m_head = new_node;
    ++m_len;
  } else {
    SNodePointer current = m_head;
    int i = 1;

    while (current != nullptr && i < index - 1) {
      current = current->m_next;
      ++i;
    }

    if (current == nullptr) {
      delete new_node;
    } else {
      new_node->m_next = current->m_next;
      current->m_next = new_node;
      ++m_len;
    }
  }

  return true;
}

/**
 * *****************************************************************
 * @brief :判断是否为空
 * @tparam T
 * @return true
 * @return false
 * *****************************************************************
 */
template <typename T>
inline bool SinglyLinkList<T>::IsEmpty() const {
  return m_len == 0;
}

/**
 * *****************************************************************
 * @brief : 查找第一个数据域与e满足compare()关系的节点
 * @tparam T
 * @param  e
 * @param  compare
 * @return int
 * *****************************************************************
 */
template <typename T>
inline int SinglyLinkList<T>::LocateElem(const T &e, bool (*compare)(const T &, const T &)) const {

  SNodePointer current = m_head;
  int i = 1;

  while (current && !(compare)(current->m_data, e)) {
    current = current->m_next;
    ++i;
  }

  if (!current) {
    return 0;
  }

  return i;
}

/**
 * *****************************************************************
 * @brief : 返回某结点后继的数据域
 * @tparam T
 * @param  e
 * @param  next_e
 * @return true
 * @return false
 * *****************************************************************
 */
template <typename T>
inline bool SinglyLinkList<T>::NextElem(const T &e, T &next_e) const {
  SNodePointer current = m_head;

  while (current && !Equal(current->m_data, e)) {
    current = current->m_next;
  }

  if (!current || !current->m_next) {
    return false;
  }

  next_e = current->m_next->m_data;

  return true;
}

/**
 * *****************************************************************
 * @brief : 返回某结点前驱的数据域
 * @tparam T
 * @param  e
 * @param  prior_e
 * @return true
 * @return false
 * *****************************************************************
 */
template <typename T>
inline bool SinglyLinkList<T>::PriorElem(const T &e, T &prior_e) const {
  SNodePointer prev = nullptr;
  SNodePointer current = m_head;

  while (current && !Equal(current->m_data, e)) {
    prev = current;
    current = current->m_next;
  }

  if (!current || !prev) {
    return false;
  }

  prior_e = prev->m_data;
  return true;
}

/**
 * *****************************************************************
 * @brief :重载赋值运算符
 * @tparam T
 * @param  right_l
 * @return SinglyLinkList<T>
 * *****************************************************************
 */
template <typename T>
inline SinglyLinkList<T> &SinglyLinkList<T>::operator=(const SinglyLinkList<T> &right_l) {
  if (this == &right_l) {
    return *this;
  }

  Clear();
  CopyList(right_l);
  return *this;
}

} // namespace bu_tools

#endif // _SINGLYLINKLIST_H_
