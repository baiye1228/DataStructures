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
 * @brief : 双链表模板类
 * @tparam T
 * *****************************************************************
 */
template <typename T>
class DoubleLinkList {

private:
  void CopyList(const DoubleLinkList<T> &other_l);

protected:
  class Node {
  public:
    T m_data;         // 节点存储的数据
    Node *m_prior; // 指向前一个节点的指针
    Node *m_next;  // 指向下一个节点的指针

    Node(const T &val) : m_data(val), m_prior(nullptr), m_next(nullptr) {}
  };

  typedef Node *NodePointer;

  NodePointer m_head; // 链表的头指针，指向第一个节点
  int m_len;          // 链表中节点的个数

public:
  DoubleLinkList() : m_head(nullptr), m_len(0) {}
  DoubleLinkList(const DoubleLinkList& other_l):m_head(nullptr){
    CopyList(other_l);
  }
  virtual ~DoubleLinkList(){
    Clear();
  }

  void Clear();
  bool DeleteElem(const T &e);
  void Append(const T&e);
  bool Insert(int index,const T& e);
  bool GetElem(int index,T&e)const;
  int GetLength()const;
  bool IsEmpty()const;
  bool NextElem(const T&e,T& next_e)const;
  bool PriorElem(const T&e,T& prior_e)const;
  DoubleLinkList<T>& operator=(const DoubleLinkList<T>& right_l);

  
};

/****************************************************************************************************

循环双链表成员函数的定义

****************************************************************************************************/



/**
 * *****************************************************************
 * @brief : 内部复制函数
 * @tparam T 
 * @param  other_l          
 * *****************************************************************
 */
template <typename T>
inline void DoubleLinkList<T>::CopyList(const DoubleLinkList<T> &other_l) {
  if(other_l.m_head){
    NodePointer current=other_l.m_head;
    
    do {
      T e=current->m_data;
    Append(e);
    current=current->m_next;
    }while (current!=other_l.m_head);
  }
}


/**
 * *****************************************************************
 * @brief : 置空
 * @tparam T
 * *****************************************************************
 */
template <typename T>
inline void DoubleLinkList<T>::Clear() {
  if (m_head) {
    NodePointer current = m_head;

    do {
      NodePointer temp = current;
      current = current->m_next;
      delete temp;
    } while (current != m_head);
  }
  m_head = nullptr;
  m_len = 0;
}

/**
 * *****************************************************************
 * @brief : 删除数据域为e的第一个结点
 * @tparam T 
 * @param  e                
 * @return true             
 * @return false            
 * *****************************************************************
 */
template <typename T>
inline bool DoubleLinkList<T>::DeleteElem(const T &e) {
  if(!m_head){
    return false;
  }

  NodePointer current=m_head;

  do{
    if(current->m_data==e){
      if(current==m_head){
        m_head=m_head->m_next;
      }

      current->m_prior->m_next=current->m_next;
      current->m_next->m_prior=current->m_prior;

      if(current==current->m_next){
        m_head=nullptr;
      }

      delete current;
      --m_len;
      return true;
    }

    current=current->m_next;

  }while(current!=m_head);

  //没有找到
  return false;
}

/**
 * *****************************************************************
 * @brief : 往后追加结点
 * @tparam T 
 * @param  e                
 * @return true             
 * @return false            
 * *****************************************************************
 */
template <typename T>
inline void DoubleLinkList<T>::Append(const T &e) {
  NodePointer new_node=new Node(e);

  if(!m_head){
    
    m_head=new_node;
    m_head->m_next=m_head;
    m_head->m_prior=m_head;
    m_len=1;
  }
  else{
    NodePointer tail=m_head->m_prior;
    tail->m_next=new_node;
    new_node->m_prior=tail;
    new_node->m_next=m_head;
    m_head->m_prior=new_node;
    ++m_len;
  }

  
}

/**
 * *****************************************************************
 * @brief : 在指定位置插入结点
 * @tparam T 
 * @param  index            
 * @param  e                
 * @return true             
 * @return false            
 * *****************************************************************
 */
template <typename T>
inline bool DoubleLinkList<T>::Insert(int index, const T &e) {
  if(index<=0||index>m_len){
    return false;
  }

  NodePointer new_node=new Node(e);

  // 在头部插入新节点
  if(index==1){

    // 如果链表为空
    if(!m_head){
      m_head=new_node;
      m_head->m_next=m_head;
      m_head->m_prior=m_head;
    } else { // 链表不为空时
    NodePointer tail=m_head->m_prior;

    new_node->m_next=m_head;
    new_node->m_prior=tail;
    tail->m_next=new_node;
    m_head->m_prior=new_node;
    m_head = new_node; // 更新头指针
    }
  }
  else{
    NodePointer current=m_head;

    for(int i=0;i<index-1;++i){
      current = current->m_next; // 移动到指定位置前一个节点
    }

    new_node->m_next=current->m_next;
    new_node->m_prior=current;
    current->m_next->m_prior=new_node;
    current->m_next=new_node;

  }
  ++m_len; // 插入新节点后，节点个数增加
  return true;
}

/**
 * *****************************************************************
 * @brief : 取双链表第i个结点的数据域
 * @tparam T 
 * @param  index            
 * @param  e                
 * @return true             
 * @return false            
 * *****************************************************************
 */
template <typename T>
inline bool DoubleLinkList<T>::GetElem(int index, T &e) const {
  if(index<=0||index>m_len){
    return false;
  }

  NodePointer current=m_head;
  for(int i=0;i<index;++i){
    current=current->m_next;
  }

  e=current->m_data;
  return true;
}

// /**
//  * *****************************************************************
//  * @brief : 取循环双链表的头指针
//  * @tparam T 
//  * @return DoubleLinkList<T>::DNodePointer
//  * *****************************************************************
//  */
// template <typename T>
// inline typename  DoubleLinkList<T>::DNodePointer DoubleLinkList<T>::GetHead() const {
//   return m_head;
// }

/**
 * *****************************************************************
 * @brief : 获取循环双链表中的个数
 * @tparam T 
 * @return int              
 * *****************************************************************
 */
template <typename T>
inline int DoubleLinkList<T>::GetLength() const {
  return m_len;
}

/**
 * *****************************************************************
 * @brief : 判断双链表是否为空
 * @tparam T 
 * @return true             
 * @return false            
 * *****************************************************************
 */
template <typename T>
inline bool DoubleLinkList<T>::IsEmpty() const {
  return m_len==0;
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
inline bool DoubleLinkList<T>::NextElem(const T &e, T &next_e) const {
  NodePointer current=m_head;

  while(current&&current->m_next!=m_head&&current->m_data!=e){
    current=current->m_next;
  }

  if(current->m_data==e){
    next_e=current->m_next->m_data;
    return true;
  }
  else{
    return false;
  }
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
inline bool DoubleLinkList<T>::PriorElem(const T &e, T &prior_e) const {
  NodePointer current = m_head;

  while (current && current->m_next != m_head && current->m_data != e) {
    current = current->m_next;
  }

  if (current->m_data == e) {
    prior_e = current->m_prior->m_data;
    return true;
  } else {
    return false;
  }
}

/**
 * *****************************************************************
 * @brief : 
 * @tparam T 
 * @param  right_l          
 * @return DoubleLinkList<T>&
 * *****************************************************************
 */
template <typename T>
inline DoubleLinkList<T> &DoubleLinkList<T>::operator=(const DoubleLinkList<T> &right_l) {
  if(this!=&right_l){
    Clear();
    CopyList(right_l);
  }
  return *this;
}

} // namespace bu_tools

#endif // _DOUBLYLINKLIST_H_