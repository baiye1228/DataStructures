/**
 * ************************************************************************
 * @filename: seqstack.h
 *
 * @brief : 顺序栈
 *
 *
 * @author : baiyebzx (baiyebzx1228@gmail.com)
 * @date : 2024-08-16
 *
 * ************************************************************************
 */

#ifndef _SEQSTACK_H_
#define _SEQSTACK_H_

namespace bu_tools {

/**
 * *****************************************************************
 * @brief : 顺序栈模板类
 * @tparam T
 * *****************************************************************
 */
template <typename T>
class SeqStack {

protected:
  T *m_base;      // 存储栈元素的数组
  int m_top;      // 栈顶指针
  int m_capacity; // 栈的容量

public:
  SeqStack(int size = 10) : m_top(-1), m_capacity(size) {
    m_base = new T[m_capacity];
  }

  virtual ~SeqStack() {
    delete[] m_base;
  }

  SeqStack(const SeqStack<T> &other_s);

  void Clear();
  int GetLength() const;
  bool GetTop(T &e) const;
  int GetStackSize() const;
  bool IsEmpty() const;
  bool IsFull() const;
  SeqStack<T>& operator=(const SeqStack<T> &right_s);
  bool Pop(T &e);
  bool Pop();
  bool Push(const T &e);
  bool GetElem(int index,T&e)const;
};

/****************************************************************************************************

顺序栈模板类成员函数的定义

****************************************************************************************************/

/**
 * *****************************************************************
 * @brief : Construct a new Seq Stack< T>:: Seq Stack object
 * @tparam T
 * @param  other_s
 * *****************************************************************
 */
template <typename T>
inline SeqStack<T>::SeqStack(const SeqStack<T> &other_s) {
  m_capacity=other_s.m_capacity;
  m_top=other_s.m_top;

  m_base=new T[m_capacity];
  for(int i=0;i<=m_top;++i){
    m_base[i]=other_s.m_base[i];
  }
}

/**
 * *****************************************************************
 * @brief : 把顺序栈置空
 * @tparam T
 * *****************************************************************
 */
template <typename T>
inline void SeqStack<T>::Clear() {
  m_top = -1;
}

/**
 * *****************************************************************
 * @brief : 求顺序栈中元素个数
 * @tparam T
 * @return int
 * *****************************************************************
 */
template <typename T>
inline int SeqStack<T>::GetLength() const {
  return m_top + 1;
}

/**
 * *****************************************************************
 * @brief :
 * @tparam T
 * @param  e
 * @return true
 * @return false
 * *****************************************************************
 */
template <typename T>
inline bool SeqStack<T>::GetTop(T &e) const {
  if (IsEmpty()) {
    return false;
  }

  e = m_base[m_top];
  return true;
}

/**
 * *****************************************************************
 * @brief : 返回当前已分配的存储空间大小
 * @tparam T
 * @return int
 * *****************************************************************
 */
template <typename T>
inline int SeqStack<T>::GetStackSize() const {
  return m_capacity;
}

/**
 * *****************************************************************
 * @brief : 判断顺序栈
 * @tparam T
 * @return true
 * @return false
 * *****************************************************************
 */
template <typename T>
inline bool SeqStack<T>::IsEmpty() const {
  return m_top == -1;
}

/**
 * *****************************************************************
 * @brief : 判断顺序栈是否已满
 * @tparam T
 * @return true
 * @return false
 * *****************************************************************
 */
template <typename T>
inline bool SeqStack<T>::IsFull() const {
  return m_top == m_capacity - 1;
}

/**
 * *****************************************************************
 * @brief : 重载赋值运算符
 * @tparam T
 * @param  right_s
 * @return SeqStack<T>
 * *****************************************************************
 */
template <typename T>
inline SeqStack<T>& SeqStack<T>::operator=(const SeqStack<T> &right_s) {
  if (this != &right_s) {
    //释放原有的内容
    delete[] m_base;

    // 复制容量和栈顶指针
    m_capacity = right_s.m_capacity;
    m_top = right_s.m_top;

    // 分配新内存并复制元素
    m_base = new T[m_capacity];
    for (int i = 0; i <= m_top; ++i) {
      m_base[i] = right_s.m_base[i];
    }
  }

  return *this;
}

/**
 * *****************************************************************
 * @brief : 弹出栈顶元素
 * @tparam T
 * @param  e
 * @return true
 * @return false
 * *****************************************************************
 */
template <typename T>
inline bool SeqStack<T>::Pop(T &e) {
  if (IsEmpty()) {
    return false;
  }

  e = m_base[m_top];
  --m_top;
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
inline bool SeqStack<T>::Pop() {
  if (IsEmpty()) {
    return false;
  }

  --m_top;
  return true;
}

/**
 * *****************************************************************
 * @brief : 在栈顶压入元素
 * @tparam T
 * @param  e
 * *****************************************************************
 */
template <typename T>
inline bool SeqStack<T>::Push(const T &e) {
  if (IsFull()) {
    return false;
  }

  m_base[++m_top] = e;
  return true;
}

/**
 * *****************************************************************
 * @brief : 获取栈中的元素
 * @tparam T 
 * @param  index            
 * @param  e                
 * @return true             
 * @return false            
 * *****************************************************************
 */
template <typename T>
inline bool SeqStack<T>::GetElem(int index, T &e) const {
  if(index<0||index>m_top){
    return false;
  }

  e=m_base[index];
  return true;
}

} // namespace bu_tools

#endif // _SEQSTACK_H_