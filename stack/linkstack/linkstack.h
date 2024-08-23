/**
 * ************************************************************************
 * @filename: linkstack.h
 *
 * @brief : 链栈
 *
 *
 * @author : baiyebzx (baiyebzx1228@gmail.com)
 * @date : 2024-08-16
 *
 * ************************************************************************
 */

#ifndef _LINKSTACK_H_
#define _LINKSTACK_H_

namespace bu_tools {

/**
 * *****************************************************************
 * @brief : 链栈
 * @tparam T
 * *****************************************************************
 */
template <typename T>
class LSNode {

public:
  T m_data;
  LSNode *m_next;

  LSNode(const T &val) : m_data(val), m_next(nullptr) {}
};

/**
 * *****************************************************************
 * @brief : 链栈模板类
 * @tparam T
 * *****************************************************************
 */
template <typename T>
class LinkStack {
protected:
  LSNode<T> *m_top; // 栈顶指针
  int m_len;        // 栈中的元素个数

public:
  LinkStack() : m_top(nullptr), m_len(0) {}
  virtual ~LinkStack();
  LinkStack(const LinkStack<T> &other_s) : m_top(nullptr), m_len(0) {
    if (other_s.m_top) {
      LSNode<T> *current_right = other_s.m_top;
      m_top = new LSNode<T>(current_right->m_data);
      LSNode<T> *current_this = m_top;

      while (current_right->m_next) {
        current_right = current_right->m_next;
        current_this->m_next = new LSNode<T>(current_right->m_data);
        current_this = current_this->m_next;
      }
    }

    m_len = other_s.m_len;
  }

  void Clear();
  int GetLength() const;
  bool GetTop(T &e) const;
  bool IsEmpty() const;
  bool Pop(T &e);
  bool Pop();
  void Push(const T &e);
  LinkStack<T> &operator=(const LinkStack<T> &right_s);
  bool GetElem(int index, T &e) const;
};

/****************************************************************************************************

链栈成员函数的定义

****************************************************************************************************/

/**
 * *****************************************************************
 * @brief : Destroy the Link Stack< T>:: Link Stack object
 * @tparam T
 * *****************************************************************
 */
template <typename T>
inline LinkStack<T>::~LinkStack() {
  Clear();
}

/**
 * *****************************************************************
 * @brief : 清空链栈
 * @tparam T
 * *****************************************************************
 */

template <typename T>
inline void LinkStack<T>::Clear() {
  while (!IsEmpty()) {
    Pop();
  }
}

/**
 * *****************************************************************
 * @brief : 获取链栈中结点个数
 * @tparam T
 * @return int
 * *****************************************************************
 */
template <typename T>
inline int LinkStack<T>::GetLength() const {
  return m_len;
}

/**
 * *****************************************************************
 * @brief : 获取栈顶元素
 * @tparam T
 * @param  e
 * @return true
 * @return false
 * *****************************************************************
 */
template <typename T>
inline bool LinkStack<T>::GetTop(T &e) const {
  if (IsEmpty()) {
    return false;
  }
  e = m_top->m_data;
  return true;
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
inline bool LinkStack<T>::IsEmpty() const {
  return m_top == nullptr;
}

/**
 * *****************************************************************
 * @brief : 弹栈
 * @tparam T
 * @param  e
 * @return true
 * @return false
 * *****************************************************************
 */
template <typename T>
inline bool LinkStack<T>::Pop(T &e) {
  if (IsEmpty()) {
    return false;
  }

  //拆除结点
  LSNode<T> *temp = m_top;
  m_top = m_top->m_next;
  e=temp->m_data;


  delete temp;
  --m_len;
  return true;
}

/**
 * *****************************************************************
 * @brief : 弹栈
 * @tparam T 
 * @return true             
 * @return false            
 * *****************************************************************
 */
template <typename T>
inline bool LinkStack<T>::Pop() {
  if (IsEmpty()) {
    return false;
  }
  //拆除结点
  LSNode<T> *temp = m_top;
  m_top = m_top->m_next;

  delete temp;
  --m_len;
  return true;
}

/**
 * *****************************************************************
 * @brief : 压栈
 * @tparam T
 * @param  e
 * @return true
 * @return false
 * *****************************************************************
 */
template <typename T>
inline void LinkStack<T>::Push(const T &e) {
  LSNode<T> *new_node = new LSNode<T>(e);
  new_node->m_next = m_top;
  m_top = new_node;
  ++m_len;
}

/**
 * *****************************************************************
 * @brief : 重载赋值运算符
 * @tparam T
 * @param  right_s
 * @return LinkStack<T>&
 * *****************************************************************
 */
template <typename T>
inline LinkStack<T> &LinkStack<T>::operator=(const LinkStack<T> &right_s) {
  if (this == &right_s) {
    return *this;
  }

  if (!IsEmpty()) {
    Clear();
  }

  if (right_s.m_top) {
    LSNode<T> *current_right = right_s.m_top;
    m_top = new LSNode<T>(current_right->m_data);
    LSNode<T> *current_this = m_top;

    while (current_right->m_next) {
      current_right = current_right->m_next;
      current_this->m_next = new LSNode<T>(current_right->m_data);
      current_this = current_this->m_next;
    }
  }
  m_len = right_s.m_len;
  return *this;
}

/**
 * *****************************************************************
 * @brief : 获得指定位置结点的数据域
 * @tparam T
 * @param  index
 * @param  e
 * @return true
 * @return false
 * *****************************************************************
 */
template <typename T>
inline bool LinkStack<T>::GetElem(int index, T &e) const {
  if (index <= 0 || index > m_len) {
    return false;
  }

  LSNode<T> *current = m_top;
  for (int i = 1; i < index; ++i) {
    current = current->m_next;
  }

  e = current->m_data;
  return true;
}

} // namespace bu_tools

#endif // _LINKSTACK_H_