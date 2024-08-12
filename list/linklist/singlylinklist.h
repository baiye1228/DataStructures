/**
 * ************************************************************************
 * @filename: singlylinklist.h
 *
 * @brief : 非循环单链表基类
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

非循环单链表的节点类

****************************************************************************************************/
template <typename T>
class Node {
public:
  T m_data;
  Node<T> *m_next;

  Node(T val) : m_data(val), m_next(nullptr) {}
};

/****************************************************************************************************

非循环单链表数据结构C++类

****************************************************************************************************/

template <typename T>
class SinglyLinkList {
private:
  void copy_list(const SinglyLinkList<T> &other_L);

protected:
  typedef Node<T> *NodePointer;

  NodePointer m_head; //头指针
  int m_len;          //节点个数

public:
  SinglyLinkList() : m_head(nullptr), m_len(0) {}
  SinglyLinkList(const SinglyLinkList &other_L) : m_head(nullptr) {
    copy_list(other_L);
  }
  virtual ~SinglyLinkList();

  void adverse();
  void clear();
  void append(const T &value);
  bool delete_elem(const T &e);
  void delete_repeat();
  bool get_elem(int index, T &e) const;
  NodePointer get_head() const;
  int get_length() const;
  bool insert(int index, const T &e);
  bool is_empty() const;
  int locate_elem(const T &e, bool (*compare)(const T &, const T &)) const;
  bool next_elem(const T &e, T &next_e) const;
  bool prior_elem(const T &e, T &prior_e) const;
  SinglyLinkList<T> &operator=(const SinglyLinkList<T> &right_L);
};

/****************************************************************************************************

成员函数定义

****************************************************************************************************/

/**
 * *****************************************************************
 * @brief :内部的复制函数
 * @tparam T
 * @param  other_L
 * *****************************************************************
 */
template <typename T>
inline void SinglyLinkList<T>::copy_list(const SinglyLinkList<T> &other_L) {
  if (other_L.m_head == nullptr) {
    m_head = nullptr;
    return;
  }

  m_head = new Node<T>(other_L.m_head->m_data);

  NodePointer currentThis = m_head;
  NodePointer currentOther = other_L.m_head->m_next;

  while (currentOther != nullptr) {
    currentThis->m_next = new Node<T>(currentOther->m_data);
    currentThis = currentThis->m_next;
    currentOther = currentOther->m_next;
  }
  m_len=other_L.m_len;
}

/**
 * *****************************************************************
 * @brief : Destroy the Singly Link List< T>:: Singly Link List object
 * @tparam T
 * *****************************************************************
 */
template <typename T>
inline SinglyLinkList<T>::~SinglyLinkList() {
  NodePointer current = m_head;
  while (current != nullptr) {
    NodePointer next_node = current->m_next;
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
inline void SinglyLinkList<T>::adverse() {

  NodePointer prev = nullptr;
  NodePointer current = m_head;
  NodePointer next = nullptr;

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
inline void SinglyLinkList<T>::clear() {
  NodePointer current = m_head;
  while (current != nullptr) {
    NodePointer next = current->m_next;
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
inline void SinglyLinkList<T>::append(const T &value) {
  NodePointer new_node = new Node<T>(value);
  if (!m_head) {
    m_head = new_node;

  } else {
    NodePointer current = m_head;
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
inline bool SinglyLinkList<T>::delete_elem(const T &e) {
  if (!m_head) {
    return false;
  }

  if (m_head->m_data == e) {
    NodePointer temp = m_head;
    m_head = m_head->m_next;
    delete temp;
    --m_len;
    return true;
  }

  NodePointer current = m_head;
  while (current->m_next && current->m_next->m_data != e) {
    current = current->m_next;
  }

  if (current->m_next) {
    NodePointer temp = current->m_next;
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
inline void SinglyLinkList<T>::delete_repeat() {
  if (!m_head) {
    return;
  }

  NodePointer current = m_head;

  while (current != nullptr && current->m_next != nullptr) {
    NodePointer runner = current;
    while (runner->m_next != nullptr) {
      if (runner->m_next->m_data == current->m_data) {
        NodePointer temp = runner->m_next;
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
inline bool SinglyLinkList<T>::get_elem(int index, T &e) const {
  NodePointer current = m_head;
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
 * @return SinglyLinkList<T>::NodePointer
 * *****************************************************************
 */
template <typename T>
inline typename SinglyLinkList<T>::NodePointer SinglyLinkList<T>::get_head() const {
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
inline int SinglyLinkList<T>::get_length() const {
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
inline bool SinglyLinkList<T>::insert(int index, const T &e) {
  if (index <= 0 || index > m_len) {
    return false;
  }

  NodePointer new_node = new Node<T>(e);

  if (index == 1) { // 在第一个节点之前插入（即头部插入）
    new_node->m_next = m_head;
    m_head = new_node;
    ++m_len;
  } else {
    NodePointer current = m_head;
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
inline bool SinglyLinkList<T>::is_empty() const {
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
inline int SinglyLinkList<T>::locate_elem(const T &e, bool (*compare)(const T &, const T &)) const {

  NodePointer current = m_head;
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
inline bool SinglyLinkList<T>::next_elem(const T &e, T &next_e) const {
  NodePointer current = m_head;

  while (current && !equal(current->m_data, e)) {
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
inline bool SinglyLinkList<T>::prior_elem(const T &e, T &prior_e) const {
  NodePointer prev = nullptr;
  NodePointer current = m_head;

  while (current && !equal(current->m_data, e)) {
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
 * @param  right_L
 * @return SinglyLinkList<T>
 * *****************************************************************
 */
template <typename T>
inline SinglyLinkList<T> &SinglyLinkList<T>::operator=(const SinglyLinkList<T> &right_L) {
  if (this == &right_L) {
    return *this;
  }

  clear();
  copy_list(right_L);
  return *this;
}

} // namespace bu_tools

#endif // _SINGLYLINKLIST_H_
