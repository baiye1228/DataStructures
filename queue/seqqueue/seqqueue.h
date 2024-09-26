/**
 * ************************************************************************
 * @filename: seqqueue.h
 *
 * @brief : 顺序队列
 *
 *
 * @author : baiyebzx (baiyebzx1228@gmail.com)
 * @date : 2024-08-24
 *
 * ************************************************************************
 */

#ifndef _SEQQUEUE_H_
#define _SEQQUEUE_H_

namespace bu_tools {

/**
 * *****************************************************************
 * @brief : 顺序循环队列模板类
 * @tparam T
 * *****************************************************************
 */
template <typename T>
class SeqQueue {
protected:
  T *m_base;      // 队列数组指针
  int m_front;    // 队头索引
  int m_rear;     // 队尾索引
  int m_capacity; // 队列的容量

public:
  SeqQueue(int cap = 15) : m_capacity(cap), m_front(0), m_rear(0) {
    m_base = new T[m_capacity];
  }
  SeqQueue(const SeqQueue<T> &other_q);

  virtual ~SeqQueue() {
    delete[] m_base;
  }

  void Clear();
  bool DeQueue(T &e);
  bool DeQueue();
  bool EnQueue(const T &e);
  bool GetFront(T &e) const;
  int GetLength() const;
  int GetCapacity() const;
  bool IsEmpty() const;
  bool IsFull() const;
  SeqQueue<T> &operator=(const SeqQueue<T> &right_q);

  /*****************************************************************

  嵌套的非常量迭代器类

  *****************************************************************/

  class Iterator {

  private:
    const SeqQueue &m_queue;
    int m_index; //当前指定标号

  public:
    Iterator(const SeqQueue &q, int start_index) : m_queue(q), m_index(start_index) {}

    T operator*() const {
      return m_queue.m_base[m_index];
    }

    Iterator &operator++() {
      m_index = (m_index + 1) % m_queue.m_capacity;

      return *this;
    }

    bool operator!=(const Iterator &other) const {
      return m_index != other.m_index;
    }

    bool operator==(const Iterator &other) const {
      return m_index == other.m_index;
    }
  };

  Iterator begin() const {
    return Iterator(*this, m_front);
  }

  Iterator end() const {
    return Iterator(*this, m_rear);
  }
};

/////////////////////////////////////////////////////////////////////////////////////////////////////
/*

顺序循环队列成员函数的定义

*/
/////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * *****************************************************************
 * @brief : Construct a new Seq Queue< T>:: Seq Queue object
 * @tparam T
 * @param  other_q
 * *****************************************************************
 */
template <typename T>
inline SeqQueue<T>::SeqQueue(const SeqQueue<T> &other_q) {
  m_base = new T[other_q.m_capacity];

  m_capacity = other_q.m_capacity;

  m_front = other_q.m_front;
  m_rear = other_q.m_rear;

  for (int i = m_front; i % m_capacity != m_rear;) {
    m_base[i] = other_q.m_base[i];
    i = (i + 1) % m_capacity;
  }
}

/**
 * *****************************************************************
 * @brief : 置空
 * @tparam T
 * *****************************************************************
 */
template <typename T>
inline void SeqQueue<T>::Clear() {
  m_front = m_rear;
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
inline bool SeqQueue<T>::DeQueue(T &e) {
  if (IsEmpty()) {
    return false;
  }

  e = m_base[m_front];
  m_front = (m_front + 1) % m_capacity;
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
inline bool SeqQueue<T>::DeQueue() {
  if (IsEmpty()) {
    return false;
  }
  m_front = (m_front + 1) % m_capacity;
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
inline bool SeqQueue<T>::EnQueue(const T &e) {
  if (IsFull()) {
    return false;
  }

  m_base[m_rear] = e;
  m_rear = (m_rear + 1) % m_capacity;
  return true;
}

/**
 * *****************************************************************
 * @brief : 读循环顺序队列队头的元素
 * @tparam T
 * @param  e
 * @return true
 * @return false
 * *****************************************************************
 */
template <typename T>
inline bool SeqQueue<T>::GetFront(T &e) const {
  if (IsEmpty()) {
    return false;
  }

  e = m_base[m_front];
  return true;
}

/**
 * *****************************************************************
 * @brief : 获取循环队列中元素的个数
 * @tparam T
 * @return int
 * *****************************************************************
 */
template <typename T>
inline int SeqQueue<T>::GetLength() const {
  return (m_rear - m_front + m_capacity) % m_capacity;
}

/**
 * *****************************************************************
 * @brief : 获取循环顺序队列存储空间大小
 * @tparam T
 * @return int
 * *****************************************************************
 */
template <typename T>
inline int SeqQueue<T>::GetCapacity() const {
  return m_capacity;
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
inline bool SeqQueue<T>::IsEmpty() const {
  return m_front == m_rear;
}

/**
 * *****************************************************************
 * @brief : 判断是否已满
 * @tparam T
 * @return true
 * @return false
 * *****************************************************************
 */
template <typename T>
inline bool SeqQueue<T>::IsFull() const {
  return (m_rear + 1) % m_capacity == m_front;
}

/**
 * *****************************************************************
 * @brief : 重载赋值运算符
 * @tparam T
 * @param  right_q
 * @return SeqQueue<T>&
 * *****************************************************************
 */
template <typename T>
inline SeqQueue<T> &SeqQueue<T>::operator=(const SeqQueue<T> &right_q) {
  if (this != &right_q) {
    delete[] m_base;

    m_capacity = right_q.m_capacity;
    m_front = right_q.m_front;
    m_rear = right_q.m_rear;

    m_base = new T[m_capacity];

    for (int i = m_front; i % m_capacity != m_rear;) {
      m_base[i] = right_q.m_base[i];
      i = (i + 1) % m_capacity;
    }
  }

  return *this;
}

} // namespace bu_tools

#endif // _SEQQUEUE_H_
