/**
 * ************************************************************************
 * @filename: doublylinklist.h
 *
 * @brief : 双链表
 *
 *
 * @author : baiyebzx (baiyebzx1228@gmail.com)
 * @date : 2024-08-13
 *
 * ************************************************************************
 */

#ifndef _DOUBLYLINKLIST_H_
#define _DOUBLYLINKLIST_H_

namespace bu_tools {

/**
 * *****************************************************************
 * @brief : 双链表节点类
 * @tparam T
 * *****************************************************************
 */
template <typename T>
class DNode {
public:
  T m_data; // 节点存储的数据
  DNode<T> *m_prior; // 指向前一个节点的指针
  DNode<T> *m_next;  // 指向下一个节点的指针

  DNode(const T& val):m_data(val),m_prior(nullptr),m_next(nullptr){}

};


template<typename T>
class DoubleLinkList{

protected:
typedef DNode<T>* DNodePointer;

DNodePointer m_head; // 链表的头指针，指向第一个节点

};



} // namespace bu_tools

#endif // _DOUBLYLINKLIST_H_