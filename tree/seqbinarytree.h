/**
 * ************************************************************************
 * @filename: seqbinarytree.h
 *
 * @brief : 二叉树（顺序存储）
 *
 *
 * @author : baiyebzx (baiyebzx1228@gmail.com)
 * @date : 2024-09-02
 *
 * ************************************************************************
 */

#ifndef _SEQBINARYTREE_H_
#define _SEQBINARYTREE_H_

#include <cmath>

namespace bu_tools {

/**
 * *****************************************************************
 * @brief : 二叉树（顺序存储）
 * @tparam T
 * *****************************************************************
 */
template <typename T>
class SeqBinaryTree {

protected:
  /*****************************************************************

  数据域

  *****************************************************************/
  T *m_nodes;        // 用于存储节点的数组
  int m_capacity;    // 数组的最大容量
  int m_final_index; // 最后一个结点的位置
  int m_count;       //结点个数

  /*****************************************************************

    成员函数声明

    *****************************************************************/
public:
  SeqBinaryTree(int cap = 15) : m_capacity(cap), m_final_index(-1), m_count(0) {
    m_nodes = new T[m_capacity];
    //初始化节点为默认值
    for (int i = 0; i < m_capacity; ++i) {
      m_nodes[i] = T();
    }
  }
  virtual ~SeqBinaryTree();

  void Clear();
  bool SetNode(int index, const T &value);
  T &GetNode(int index) const;
  int GetCount() const;
  bool IsValidNode(int index) const;
  bool IsEmpty()const;
  int CalculateDepth() const;
  int CountLeaves() const;
  void Mirror();

private:
  void Resize();

public:
  /*****************************************************************

  定义前序遍历迭代器

  *****************************************************************/
  class PreOrderIterator {
  private:
    const SeqBinaryTree *m_tree;
    int m_index;

    int NextIndex(int i) const {
      //如果当前节点有左子节点，返回左子节点的索引
      if (m_tree->IsValidNode(2 * i + 1)) {
        return 2 * i + 1;
      }

      //如果没有左子节点，检查当前节点的右子节点
      if (m_tree->IsValidNode(2 * i + 2)) {
        return 2 * i + 2;
      }
      // 如果没有右子节点，回溯到父节点并检查父节点的右子树
      while (true) {
        // 如果当前节点是根节点且右子树已经访问过，结束遍历
        if (i == 0) {
          return -1;
        }

        // 回溯到父节点
        int parent = (i - 1) / 2;

        // 如果当前节点是左子节点，检查父节点的右子节点
        if (i == 2 * parent + 1) {
          if (m_tree->IsValidNode(2 * parent + 2)) {
            return 2 * parent + 2;
          }
        }

        // 继续回溯到更高层的祖先节点
        i = parent;
      }

      // 如果当前节点是最后一个被访问的节点，则返回-1
      return -1;
    }

  public:
    PreOrderIterator(const SeqBinaryTree *t, int index) : m_tree(t), m_index(index) {}

    // 前置++操作符
    PreOrderIterator &operator++() {
      m_index = NextIndex(m_index);
      return *this;
    }

    // 后置++操作符
    PreOrderIterator operator++(int) {
      PreOrderIterator temp = *this;
      m_index = NextIndex(m_index);
      return temp;
    }

    const T &operator*() const {
      return m_tree->GetNode(m_index);
    }

    bool operator==(const PreOrderIterator &other) const {
      return m_index == other.m_index;
    }

    bool operator!=(const PreOrderIterator &other) const {
      return !(*this == other);
    }
  };

  // 获取前序遍历的开始迭代器
  PreOrderIterator PreOrderBegin() const {
    return PreOrderIterator(this, 0);
  }
  // 获取前序遍历的结束迭代器
  PreOrderIterator PreOrderEnd() const {
    return PreOrderIterator(this, -1);
  }

  /*****************************************************************

  定义中序遍历迭代器

  *****************************************************************/
  class InOrderIterator {
  private:
    const SeqBinaryTree *m_tree;
    int m_index;

    int NextIndex(int i) const {
      // if(i>=m_tree->m_final_index){
      //   return -1; // 如果索引超出范围，返回-1
      // }

      //如果有右子树，找到右子树的最左子结点
      int right_child = 2 * i + 2;
      if (m_tree->IsValidNode(right_child)) {
        int next = right_child;
        while (m_tree->IsValidNode(2 * next + 1)) {
          next = 2 * next + 1;
        }
        return next;
      }

      //没有右子树，向上寻找父节点
      int current = i;
      while (current > 0) {
        int parent = (current - 1) / 2;
        if (2 * parent + 1 == current) {
          // 当前是左子结点，返回父节点
          return parent;
        }
        current = parent;
      }
      return -1;
    }

  public:
    InOrderIterator(const SeqBinaryTree *t, int i) : m_tree(t), m_index(i) {}

    // 前置++操作符
    InOrderIterator &operator++() {
      m_index = NextIndex(m_index);
      return *this;
    }

    // 后置++操作符
    InOrderIterator operator++(int) {
      InOrderIterator temp = *this;
      m_index = NextIndex(m_index);
      return temp;
    }

    const T &operator*() const {
      return m_tree->GetNode(m_index);
    }

    bool operator==(const InOrderIterator &other) const {
      return m_index == other.m_index;
    }

    bool operator!=(const InOrderIterator &other) const {
      return !(*this == other);
    }
  };

  // 获取中序遍历的开始迭代器
  InOrderIterator InOrderBegin() const {

    int first_index = 0;
    //往左滑到底
    while (IsValidNode(first_index * 2 + 1)) {
      first_index = first_index * 2 + 1;
    }

    return InOrderIterator(this, first_index);
  }
  // 获取中序遍历的结束迭代器
  InOrderIterator InOrderEnd() const {
    return InOrderIterator(this, -1);
  }

  /*****************************************************************

  定义后序遍历迭代器

  *****************************************************************/
  class PostOrderIterator {
  private:
    const SeqBinaryTree *m_tree;
    int m_index;

    int NextIndex(int i) const {
      // 如果当前结点是根结点
      if (i == 0) {
        return -1; // 根结点是最后一个后序结点
      }

      // 获取父节点序号
      int parent = (i - 1) / 2;

      // 如果当前结点是左子结点
      if (2 * parent + 1 == i) {
        int right_child = 2 * parent + 2;
        // 如果有右子树，则返回右子树的最后一个结点
        if (m_tree->IsValidNode(right_child)) {
          int next = right_child;

          //当前结点存在左或右子树
          while (m_tree->IsValidNode(next * 2 + 1) || m_tree->IsValidNode(next * 2 + 2)) {
            // 查找右子树中的最后一个后序结点
            while (m_tree->IsValidNode(2 * next + 1)) {
              next = 2 * next + 1; // 向左子树走到底
            }

            if (m_tree->IsValidNode(2 * next + 2)) {
              next = 2 * next + 2; // 向右子树走到底
            }
          }

          return next;
        }
        // 没有右子树，返回父节点
        return parent;
      }

      // 如果当前结点是右子结点，返回父节点
      return parent;
    }

  public:
    PostOrderIterator(const SeqBinaryTree *t, int i) : m_tree(t), m_index(i) {}

    //前置++操作符
    PostOrderIterator &operator++() {
      m_index = NextIndex(m_index);
      return *this;
    }

    //后置++操作符
    PostOrderIterator operator++(int) {
      PostOrderIterator temp = *this;
      m_index = NextIndex(m_index);
      return temp;
    }

    const T &operator*() const {
      return m_tree->GetNode(m_index);
    }

    bool operator==(const PostOrderIterator &other) const {
      return m_index == other.m_index;
    }

    bool operator!=(const PostOrderIterator &other) const {
      return !(*this == other);
    }
  };
  // 获取后序遍历的开始迭代器
  PostOrderIterator PostOrderBegin() const {
    int first_index = 0;

    while (IsValidNode(first_index * 2 + 1) || IsValidNode(first_index * 2 + 2)) {
      //往左滑到底
      while (IsValidNode(first_index * 2 + 1)) {
        first_index = first_index * 2 + 1;
      }
      //往右滑
      if (IsValidNode(first_index * 2 + 2)) {
        first_index = first_index * 2 + 2;
      }
    }

    return PostOrderIterator(this, first_index);
  }
  // 获取中序遍历的结束迭代器
  PostOrderIterator PostOrderEnd() const {
    return PostOrderIterator(this, -1);
  }
};

/****************************************************************************************************

顺序存储二叉树成员函数定义

****************************************************************************************************/

/**
 * *****************************************************************
 * @brief : Destroy the Seq Binary Tree< T>:: Seq Binary Tree object
 * @tparam T
 * *****************************************************************
 */
template <typename T>
inline SeqBinaryTree<T>::~SeqBinaryTree() {
  delete[] m_nodes;
}

/**
 * *****************************************************************
 * @brief : 置空
 * @tparam T
 * *****************************************************************
 */
template <typename T>
inline void SeqBinaryTree<T>::Clear() {
  delete[] m_nodes;
  m_nodes = nullptr;
  m_final_index = 0;
  m_count = 0;
}

/**
 * *****************************************************************
 * @brief : 设置或添加结点
 * @tparam T
 * @param  index 从0开始
 * @param  value
 * @return true
 * @return false
 * *****************************************************************
 */
template <typename T>
inline bool SeqBinaryTree<T>::SetNode(int index, const T &value) {
  if (index < 0) {
    return false;
  }

  // 如果插入的是根节点或者父节点存在，允许插入
  if (index == 0 || m_nodes[(index - 1) / 2] != T()) {
    // 如果索引超出当前容量，扩展容量
    while (index > m_capacity) {
      Resize();
    }
    m_nodes[index] = value;
    if (index > m_final_index) {
      m_final_index = index;
    }

    //结点成功插入，总结点数加1
    ++m_count;
    return true;
  }

  // 父节点不存在，无法插入
  return false;
}

/**
 * *****************************************************************
 * @brief : 获取结点的值
 * @tparam T
 * @param  index 从0开始
 * @return T&
 * *****************************************************************
 */
template <typename T>
inline T &SeqBinaryTree<T>::GetNode(int index) const {
  return m_nodes[index];
}

/**
 * *****************************************************************
 * @brief : 获取结点总数
 * @tparam T
 * @return int
 * *****************************************************************
 */
template <typename T>
inline int SeqBinaryTree<T>::GetCount() const {
  return m_count;
}

/**
 * *****************************************************************
 * @brief : 检查结点是否有效
 * @tparam T
 * @param  index 从0开始
 * @return true
 * @return false
 * *****************************************************************
 */
template <typename T>
inline bool SeqBinaryTree<T>::IsValidNode(int index) const {
  return index <= m_final_index && m_nodes[index] != T();
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
inline bool SeqBinaryTree<T>::IsEmpty() const {
  return m_count==0;
}

/**
 * *****************************************************************
 * @brief : 计算二叉树深度
 * @tparam T
 * @param  index            从0开始
 * @return int
 * *****************************************************************
 */
template <typename T>
inline int SeqBinaryTree<T>::CalculateDepth() const {
  return static_cast<int>(std::log2(m_final_index + 1)) + 1;
}

/**
 * *****************************************************************
 * @brief : 计算叶子数
 * @tparam T
 * @return int
 * *****************************************************************
 */
template <typename T>
inline int SeqBinaryTree<T>::CountLeaves() const {
  int count_leaves = 0;

  // 遍历所有有效结点，判断是否为叶子结点
  for (int i = 0; i <= m_final_index; ++i) {
    if (m_nodes[i] == T()) {
      //跳过空结点
      continue;
    }

    // 判断是否为叶子结点：没有左孩子或右孩子
    bool is_leaf = true;
    if (IsValidNode(2 * i + 1)) {
      is_leaf = false; //存在左孩子
    }
    if (IsValidNode(2 * i + 2)) {
      is_leaf = false; //存在右孩子
    }

    if (is_leaf) {
      ++count_leaves;
    }
  }

  return count_leaves;
}

/**
 * *****************************************************************
 * @brief : 交换二叉树所有结点左右子树
 * @tparam T
 * *****************************************************************
 */
template <typename T>
inline void SeqBinaryTree<T>::Mirror() {

  for (int i = 1; i < CalculateDepth(); ++i) {
    int start = pow(2, i) - 1;
    int end = pow(2, i + 1) - 2;

    while (start < end) {
      T temp = m_nodes[start];
      m_nodes[start] = m_nodes[end];
      m_nodes[end] = temp;

      ++start;
      --end;
    }
  }
}

/**
 * *****************************************************************
 * @brief : 动态扩容，保证一个完全二叉树的容量
 * @tparam T
 * @param  new_capacity
 * *****************************************************************
 */
template <typename T>
inline void SeqBinaryTree<T>::Resize() {
  int exp = static_cast<int>(std::log2(m_capacity + 1));
  int new_capacity = static_cast<int>(pow(2, exp + 1)) - 1;

  T *new_nodes = new T[new_capacity];

  for (int i = 0; i < m_capacity; ++i) {
    new_nodes[i] = m_nodes[i];
  }

  for (int i = m_capacity; i < new_capacity; ++i) {
    new_nodes[i] = T();
  }

  delete[] m_nodes;
  m_nodes = new_nodes;
  m_capacity = new_capacity;
}

} // namespace bu_tools

#endif // _SEQBINARYTREE_H_