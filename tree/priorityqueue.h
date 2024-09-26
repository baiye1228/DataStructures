/**
 * ************************************************************************
 * @filename: priorityqueue.h
 * 
 * @brief : 优先队列
 * 
 * 
 * @author : baiyebzx (baiyebzx1228@gmail.com)
 * @date : 2024-09-23
 * 
 * ************************************************************************
 */

#ifndef _PRIORITYQUEUE_H_
#define _PRIORITYQUEUE_H_

#include "seqbinarytree.h"

namespace bu_tools{

/**
 * *****************************************************************
 * @brief : 优先队列
 * @tparam T
 * *****************************************************************
 */
template <typename T>
class PriorityQueue : public SeqBinaryTree<T> {
private:
  /*****************************************************************

  内部嵌套比较器

  *****************************************************************/
  struct Comarator {
    bool m_is_min_heap; //是否是最小堆

    Comarator(bool min_heap = true) : m_is_min_heap(min_heap) {}

    bool operator()(const T &left, const T &right) const {

      if (m_is_min_heap) {
        return left > right; // 最小堆，比较值
      } else {
        return left < right; // 最大堆，比较值
      }
    }

    bool operator()(const T *left, const T *right) const {
      if (m_is_min_heap) {
        return *left > *right; // 最小堆，比较指针所指的值
      } else {
        return *left < *right; // 最大堆，比较指针所指的值
      }
    }
  };

  Comarator m_comp; //比较器

  void SiftUp(int index);
  void SiftDown(int index);

public:
  PriorityQueue(bool min_heap = true) : m_comp(min_heap) {}

  void Push(const T &value);
  bool Pop(T &value);
  const T &Top() const;
};

/**
 * *****************************************************************
 * @brief : 上浮操作
 * @tparam T
 * @param  index
 * *****************************************************************
 */
template <typename T>
inline void PriorityQueue<T>::SiftUp(int index) {
  while (index > 0) {
    int parent = (index - 1) / 2;
    //父结点小于等于子节点
    if (!m_comp(this->m_nodes[parent], this->m_nodes[index])) {
      break;
    }
    T temp = this->m_nodes[parent];
    this->m_nodes[parent] = this->m_nodes[index];
    this->m_nodes[index] = temp;
    index = parent;
  }
}

/**
 * *****************************************************************
 * @brief : 下沉操作
 * @tparam T
 * @param  index
 * *****************************************************************
 */
template <typename T>
inline void PriorityQueue<T>::SiftDown(int index) {
  int n = this->m_final_index;
  while (2 * index + 1 < n) {
    int left_child = 2 * index + 1;
    int right_child = 2 * index + 2;
    int swap_index = left_child;

    if (right_child < n && m_comp(this->m_nodes[left_child], this->m_nodes[right_child])) {
      swap_index = right_child;
    }

    if (!m_comp(this->m_nodes[index], this->m_nodes[swap_index])) {
      break;
    }

    T temp = this->m_nodes[index];
    this->m_nodes[index] = this->m_nodes[swap_index];
    this->m_nodes[swap_index] = temp;

    // 更新索引，继续下一次循环，检查新的子树是否满足堆的性质
    index = swap_index;
  }
}

/**
 * *****************************************************************
 * @brief : 插入元素
 * @tparam T
 * @param  value
 * *****************************************************************
 */
template <typename T>
inline void PriorityQueue<T>::Push(const T &value) {
  //在最后插入
  this->SetNode(this->m_final_index + 1, value);
  SiftUp(this->m_final_index);
}

/**
 * *****************************************************************
 * @brief : 删除并返回优先级最高的元素
 * @tparam T
 * @param  value
 * @return true
 * @return false
 * *****************************************************************
 */
template <typename T>
inline bool PriorityQueue<T>::Pop(T &value) {
  if (this->IsEmpty()) {
    value = T();
    return false;
  }

  value = this->m_nodes[0];
  this->m_nodes[0] = this->m_nodes[this->m_final_index];
  --this->m_final_index;
  --this->m_count;

  if (!this->IsEmpty()) {
    SiftDown(0);
  }

  return true;
}

/**
 * *****************************************************************
 * @brief : 返回优先级最高的元素
 * @tparam T
 * @return const T&
 * *****************************************************************
 */
template <typename T>
inline const T &PriorityQueue<T>::Top() const {
  if (this->IsEmpty()) {
    return T();
  }

  return this->m_nodes[0];
}

} // namespace bu_tools






#endif // _PRIORITYQUEUE_H_