/**
 * ************************************************************************
 * @filename: linkqueue.h
 *
 * @brief : 非循环链队
 *
 *
 * @author : baiyebzx (baiyebzx1228@gmail.com)
 * @date : 2024-08-28
 *
 * ************************************************************************
 */

#ifndef _LINKQUEUE_H_
#define _LINKQUEUE_H_

namespace bu_tools {

/**
 * *****************************************************************
 * @brief : 非循环链队
 * @tparam T
 * *****************************************************************
 */
template <typename T>
class LinkQueue {
private:
  //嵌套结点类
  class Node {
  public:
    T m_data;
    Node *m_next;

    Node(const T &val) : m_data(val), m_next(nullptr) {}
  };

  typedef Node *NodePointer;

protected:
  NodePointer m_front;
  NodePointer m_rear;
  int m_len;

public:
  LinkQueue() : m_front(nullptr), m_rear(nullptr), m_len(0) {}

  virtual ~LinkQueue() {
    Clear();
  }

  LinkQueue(const LinkQueue &other) : m_front(nullptr), m_rear(nullptr), m_len(0) {
    NodePointer current = other.m_front;
    while (current) {
      EnQueue(current->m_data);
      current = current->m_next;
    }
  }

  void Clear();
  bool DeQueue(T &e);
  bool DeQueue();
  bool EnQueue(const T &e);
  bool GetFront(T &e) const;
  int GetLength() const;
  bool IsEmpty() const;
  LinkQueue<T> &operator=(const LinkQueue<T> &right_q);

  /*****************************************************************

  嵌套的非常量迭代器类

  *****************************************************************/
  class Iterator {
  private:
    NodePointer current;

  public:
    Iterator(NodePointer node) : current(node) {}

    T &operator*() {
      return current->m_data;
    }

    Iterator &operator++() {
      if (current) {
        current = current->m_next;
      }
      return *this;
    }

    bool operator==(const Iterator &other) const {
      return current == other.current;
    }

    bool operator!=(const Iterator &other) const {
      return current != other.current;
    }
  };

  Iterator begin() const {
    return Iterator(m_front);
  }

  Iterator end() const {
    return Iterator(m_rear);
  }
};

/////////////////////////////////////////////////////////////////////////////////////////////////////
/*

非循环链队成员函数定义

*/
/////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * *****************************************************************
 * @brief : 置空
 * @tparam T
 * *****************************************************************
 */
template <typename T>
inline void LinkQueue<T>::Clear() {
  while (!IsEmpty()) {
    DeQueue();
  }
  m_len = 0;
}

/**
 * *****************************************************************
 * @brief : 出队列
 * @tparam T
 * @param  e
 * @return true
 * @return false
 * *****************************************************************
 */
template <typename T>
inline bool LinkQueue<T>::DeQueue(T &e) {
  if (IsEmpty()) {
    return false;
  }

  NodePointer temp = m_front;
  m_front = m_front->m_next;
  if (!m_front) {
    m_rear = nullptr;
  }
  e = temp->m_data;
  delete temp;
  --m_len;

  return true;
}

/**
 * *****************************************************************
 * @brief : 出队列
 * @tparam T
 * @return true
 * @return false
 * *****************************************************************
 */
template <typename T>
inline bool LinkQueue<T>::DeQueue() {
  if (IsEmpty()) {
    return false;
  }

  NodePointer temp = m_front;
  m_front = m_front->m_next;
  if (!m_front) {
    m_rear = nullptr;
  }
  delete temp;
  --m_len;

  return true;
}

/**
 * *****************************************************************
 * @brief : 入队列
 * @tparam T
 * @param  e
 * @return true
 * @return false
 * *****************************************************************
 */
template <typename T>
inline bool LinkQueue<T>::EnQueue(const T &e) {
  NodePointer new_node = new Node(e);

  if (IsEmpty()) {
    m_front = m_rear = new_node;
  } else {
    m_rear->m_next = new_node;
    m_rear = new_node;
  }
  ++m_len;
  return true;
}

/**
 * *****************************************************************
 * @brief : 获取队头元素
 * @tparam T
 * @param  e
 * @return true
 * @return false
 * *****************************************************************
 */
template <typename T>
inline bool LinkQueue<T>::GetFront(T &e) const {
  if (IsEmpty()) {
    return false;
  }

  e=m_front->m_data;
  return true;
}

/**
 * *****************************************************************
 * @brief : 获取结点个数
 * @tparam T
 * @return int
 * *****************************************************************
 */
template <typename T>
inline int LinkQueue<T>::GetLength() const {
  return m_len;
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
inline bool LinkQueue<T>::IsEmpty() const {
  return m_len == 0;
}

/**
 * *****************************************************************
 * @brief : 重载赋值运算符
 * @tparam T
 * @param  right_q
 * @return LinkQueue<T>&
 * *****************************************************************
 */
template <typename T>
inline LinkQueue<T> &LinkQueue<T>::operator=(const LinkQueue<T> &right_q) {
  if (this != &right_q) {
    Clear();

    NodePointer current = right_q.m_front;
    while (current) {
      EnQueue(current->m_data);
      current = current->m_next;
    }
  }

  return *this;
}

} // namespace bu_tools

#endif // _LINKQUEUE_H_