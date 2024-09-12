/**
 * ************************************************************************
 * @filename: huffmantree.h
 *
 * @brief : 哈夫曼树
 *
 *
 * @author : baiyebzx (baiyebzx1228@gmail.com)
 * @date : 2024-09-10
 *
 * ************************************************************************
 */

#ifndef _HUFFMANTREE_H_
#define _HUFFMANTREE_H_

#include "linkbinarytree.h"
#include "seqbinarytree.h"
#include <iostream>

using std::cout;

namespace bu_tools {

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
    bool operator()(const T &left, const T &right) const {
      if (left && right) {
        return *left > *right; // 比较指针所指的值
      }
      return left > right; // 如果有任一指针为空，返回指针地址比较结果
    }

    
  };

  Comarator m_comp; //比较器

  void SiftUp(int index);
  void SiftDown(int index);

public:
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

/////////////////////////////////////////////////////////////////////////////////////////////////////
/*

哈夫曼树主体类

*/
/////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * *****************************************************************
 * @brief : 哈夫曼树的数据对
 * @tparam T
 * @tparam W
 * *****************************************************************
 */
template <typename T, typename W>
class HuffmanItem {
public:
  T m_data;   //数据
  W m_weight; //权值

  HuffmanItem() {
    m_data = T();
    m_weight = W();
  }

  HuffmanItem(const T &data, const W &weight) {
    m_data = data;
    m_weight = weight;
  }

  bool IsEmpty() const {
    return m_data == T() && m_weight == W();
  }

  //用于优先队列比较
  bool operator>(const HuffmanItem &other) const {
    return m_weight > other.m_weight;
  }
  //用于优先队列比较
  bool operator<(const HuffmanItem &other) const {
    return m_weight < other.m_weight;
  }

  bool operator!=(const HuffmanItem &other) const {
    return m_data != other.m_data && m_weight != other.m_weight;
  }

  bool operator==(const HuffmanItem &other) const {
    return m_data == other.m_data && m_weight == other.m_weight;
  }
};

/**
 * *****************************************************************
 * @brief : 哈夫曼树模板类
 * @tparam T
 * @tparam W
 * *****************************************************************
 */
template <typename T, typename W>
class HuffmanTree : protected LinkBinaryTree<HuffmanItem<T, W>> {
protected:
  typedef typename LinkBinaryTree<HuffmanItem<T, W>>::NodePointer HuffmanNodePointer;
  typedef typename LinkBinaryTree<HuffmanItem<T, W>>::Node HuffmanNode;

private:
  void HelpPrintHuffmanCodes(HuffmanNodePointer node, int *code, int top) const;

public:
  HuffmanTree(HuffmanItem<T, W> *items, int n);
  void PrintHuffmanCodes() const;
};

/**
 * *****************************************************************
 * @brief : 辅助生成哈夫曼编码
 * @tparam T
 * @tparam W
 * @param  node
 * @param  code
 * @param  top
 * *****************************************************************
 */
template <typename T, typename W>
inline void HuffmanTree<T, W>::HelpPrintHuffmanCodes(HuffmanNodePointer node, int *code, int top) const {
  if (node->m_left) {
    code[top] = 0;
    HelpPrintHuffmanCodes(node->m_left, code, top + 1);
  }

  if (node->m_right) {
    code[top] = 1;
    HelpPrintHuffmanCodes(node->m_right, code, top + 1);
  }

  // 叶子节点，输出字符和对应的编码
  if (!node->m_left && !node->m_right) {
    cout << node->m_value.m_data << "  " << node->m_value.m_weight << " : ";
    for (int i = 0; i < top; ++i) {
      cout << code[i];
    }
    cout << "\n";
  }
}

/**
 * *****************************************************************
 * @brief : Construct a new Huffman Tree< T,  W>:: Huffman Tree object
 * @tparam T
 * @tparam W
 * @param  items            哈夫曼树数据对数组
 * @param  n                哈夫曼树数据对数组的元素个数
 * *****************************************************************
 */
template <typename T, typename W>
inline HuffmanTree<T, W>::HuffmanTree(HuffmanItem<T, W> *items, int n) {
  PriorityQueue<HuffmanNodePointer> pq;

  // 创建初始的n个叶子节点并插入优先级队列
  for (int i = 0; i < n; ++i) {
    HuffmanNodePointer p = new HuffmanNode(items[i]);
    pq.Push(p);
  }

  // 使用哈夫曼算法构建树
  HuffmanNodePointer left, right, parent;

  while (!pq.IsEmpty()) {
    // HuffmanItem<T, W> left_val, right_val, temp;
    // pq.Pop(left_val);
    // pq.Pop(right_val);
    // left = new HuffmanNode(left_val);
    // right = new HuffmanNode(right_val);
    // temp.m_data = T();
    // temp.m_weight = left_val.m_weight + right_val.m_weight;
    // parent = new HuffmanNode(temp);
    // parent->m_left = left;
    // parent->m_right = right;

    // if (!pq.IsEmpty()) {
    //   pq.Push(parent->m_value);
    // }

    pq.Pop(left);
    pq.Pop(right);

    HuffmanItem<T, W> temp(T(), left->m_value.m_weight + right->m_value.m_weight);

    parent = new HuffmanNode(temp);
    parent->m_left = left;
    parent->m_right = right;

    if (!pq.IsEmpty()) {
      pq.Push(parent);
    }
  }

  this->m_root = parent;
}

/**
 * *****************************************************************
 * @brief : 遍历树并输出每个字符的哈夫曼编码
 * @tparam T
 * @tparam W
 * *****************************************************************
 */
template <typename T, typename W>
inline void HuffmanTree<T, W>::PrintHuffmanCodes() const {
  int code[100];
  HelpPrintHuffmanCodes(this->m_root, code, 0);
}

} // namespace bu_tools

#endif // _HUFFMANTREE_H_