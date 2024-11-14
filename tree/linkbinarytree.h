/**
 * ************************************************************************
 * @filename: linkbinarytree.h
 *
 * @brief : 二叉树（二叉链表存储）
 *
 *
 * @author : baiyebzx (baiyebzx1228@gmail.com)
 * @date : 2024-09-06
 *
 * ************************************************************************
 */

#ifndef _LINKBINARYTREE_H_
#define _LINKBINARYTREE_H_

#include "../stack/seqstack/seqstack.h"
#include "seqbinarytree.h"
#include <iostream>

using std::cout;

namespace bu_tools {

template <typename T>
class LinkBinaryTree {

  /*****************************************************************

  嵌套结点类

  *****************************************************************/
protected:
  class Node {
  public:
    T m_value;
    Node *m_left;
    Node *m_right;

    Node(const T &val=T()) : m_value(val), m_left(nullptr), m_right(nullptr) {}

    Node(const Node& other){
      m_value=other.m_value;
      m_left=other.m_left;
      m_right=other.m_right;
    }


    bool operator>(const Node& other)const{
      return m_value>other.m_value;
    }

    bool operator<(const Node &other) const {
      return m_value < other.m_value;
    }

    bool operator!=(const Node &other) const {
      return m_value != other.m_value;
    }

    bool operator==(const Node &other) const {
      return m_value == other.m_value;
    }
  };

  /*****************************************************************

  数据域

  *****************************************************************/

  typedef Node *NodePointer;
  NodePointer m_root;




  /*****************************************************************

  成员函数声明

  *****************************************************************/
private:
  void HelpDeleteNode(NodePointer node);
  int HelpCalculateDepth(NodePointer node) const;
  int HelpCountLeaves(NodePointer node) const;
  int HelpCountNodes(NodePointer node) const;
  void HelpPreOrderRecursive(NodePointer node) const;
  void HelpInOrderRecursive(NodePointer node) const;
  void HelpPostOrderRecursive(NodePointer node) const;
  void HelpMirror(NodePointer node);
  void HelpLinkToSequential(NodePointer node, int index, SeqBinaryTree<T> &seq_tree) const;

  /**
   * *****************************************************************
   * @brief : 辅助顺序存储转换成二叉链表
   * @param  seq_tree
   * @param  index
   * @return NodePointer
   * *****************************************************************
   */
  NodePointer HelpSequentialToLink(const SeqBinaryTree<T> &seq_tree, int index) {
    //检查是否存在这个结点
    if (!seq_tree.IsValidNode(index)) {
      return nullptr;
    }

    NodePointer node = new Node(seq_tree.GetNode(index));

    node->m_left = HelpSequentialToLink(seq_tree, index * 2 + 1);
    node->m_right = HelpSequentialToLink(seq_tree, index * 2 + 2);

    return node;
  }

public:
  LinkBinaryTree() : m_root(nullptr) {}
  virtual ~LinkBinaryTree();

  void Clear();
  int CalculateDepth() const;
  int CountLeaves() const;
  int CountNodes() const;
  bool IsEmpty() const;
  void PreOrderRecursive() const;
  void InOrderRecursive() const;
  void PostOrderRecursive() const;
  void Mirror();
  void LinkToSequential(SeqBinaryTree<T> &seq_tree) const;
  void SequentialToLink(const SeqBinaryTree<T> &seq_tree);

  /*****************************************************************

  定义前序遍历迭代器

  *****************************************************************/
  class PreOrderIterator {
  private:
    SeqStack<NodePointer> m_stack;
    NodePointer m_current;

    NodePointer NextNode(NodePointer node) {
      if (!m_stack.GetTop(node)) { //栈空
        return nullptr;
      }

      m_stack.Pop();

      // 先访问右子树，因为栈是后进先出
      if (node->m_right) {
        m_stack.Push(node->m_right);
      }
      if (node->m_left) {
        m_stack.Push(node->m_left);
      }

      return node;
    }

  public:
    PreOrderIterator(NodePointer node) : m_current(nullptr) {
      if (node) {
        m_stack.Push(node);
        m_current = NextNode(node);
      }
    }

    // 前置++操作符
    PreOrderIterator &operator++() {
      m_current = NextNode(m_current);
      return *this;
    }

    // 后置++操作符
    PreOrderIterator operator++(int) {
      PreOrderIterator temp = *this;
      m_current = NextNode(m_current);
      return temp;
    }

    T &operator*() const {
      return m_current->m_value;
    }

    bool operator==(const PreOrderIterator &other) const {
      return m_current == other.m_current;
    }

    bool operator!=(const PreOrderIterator &other) const {
      return !(*this == other);
    }
  };

  // 获取前序遍历的开始迭代器
  PreOrderIterator PreOrderBegin() const {
    return PreOrderIterator(m_root);
  }
  // 获取前序遍历的结束迭代器
  PreOrderIterator PreOrderEnd() const {
    return PreOrderIterator(nullptr);
  }

  /*****************************************************************

  定义中序遍历迭代器

  *****************************************************************/
  class InOrderIterator {
  private:
    SeqStack<NodePointer> m_stack;
    NodePointer m_current;

    NodePointer NextNode(NodePointer node) {
      if (!m_stack.GetTop(node)) {
        return nullptr;
      }

      m_stack.Pop();

      NodePointer result = node;

      node = node->m_right;
      while (node) {
        m_stack.Push(node);
        node = node->m_left;
      }

      return result;
    }

  public:
    InOrderIterator(NodePointer node) : m_current(nullptr) {
      while (node) { //往左滑到底
        m_stack.Push(node);
        node = node->m_left;
      }
      m_current = NextNode(node);
    }

    // 前置++操作符
    InOrderIterator &operator++() {
      m_current = NextNode(m_current);
      return *this;
    }

    // 后置++操作符
    InOrderIterator operator++(int) {
      InOrderIterator temp = *this;
      m_current = NextNode(m_current);
      return temp;
    }

    const T &operator*() const {
      return m_current->m_value;
    }

    bool operator==(const InOrderIterator &other) const {
      return m_current == other.m_current;
    }

    bool operator!=(const InOrderIterator &other) const {
      return !(*this == other);
    }
  };

  // 获取中序遍历的开始迭代器
  InOrderIterator InOrderBegin() const {
    return InOrderIterator(m_root);
  }
  // 获取中序遍历的结束迭代器
  InOrderIterator InOrderEnd() const {
    return InOrderIterator(nullptr);
  }

  /*****************************************************************

  定义后序遍历迭代器

  *****************************************************************/
  class PostOrderIterator {
  private:
    SeqStack<NodePointer> m_stack;
    NodePointer m_current;

    NodePointer NextNode(NodePointer node) {
      if (!m_stack.GetTop(node)) {
        return nullptr;
      }
      m_stack.Pop();

      NodePointer result = node;

      if (m_stack.GetTop(node)) {     //再取一个结点，也就是当前结点的父节点
        if (node->m_left == result) { //如果当前结点是左子结点

          node = node->m_right;
          while (node) {
            m_stack.Push(node);
            if (node->m_left) {
              node = node->m_left;
            } else {
              node = node->m_right;
            }
          }
        }
      }
      return result;
    }

  public:
    PostOrderIterator(NodePointer node) : m_current(nullptr) {
      while (node) {
        m_stack.Push(node);
        if (node->m_left) {
          node = node->m_left;
        } else {
          node = node->m_right;
        }
      }

      m_current = NextNode(node);
    }

    //前置++操作符
    PostOrderIterator &operator++() {
      m_current = NextNode(m_current);
      return *this;
    }

    //后置++操作符
    PostOrderIterator operator++(int) {
      PostOrderIterator temp = *this;
      m_current = NextIndex(m_current);
      return temp;
    }

    const T &operator*() const {
      return m_current->m_value;
    }

    bool operator==(const PostOrderIterator &other) const {
      return m_current == other.m_current;
    }

    bool operator!=(const PostOrderIterator &other) const {
      return !(*this == other);
    }
  };

  // 获取后序遍历的开始迭代器
  PostOrderIterator PostOrderBegin() const {

    return PostOrderIterator(m_root);
  }
  // 获取中序遍历的结束迭代器
  PostOrderIterator PostOrderEnd() const {
    return PostOrderIterator(nullptr);
  }
};

/////////////////////////////////////////////////////////////////////////////////////////////////////
/*

成员函数的定义

*/
/////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * *****************************************************************
 * @brief : 辅助删除结点函数
 * @tparam T
 * @param  node
 * *****************************************************************
 */
template <typename T>
inline void LinkBinaryTree<T>::HelpDeleteNode(NodePointer node) {
  if (node) {
    HelpDeleteNode(node->m_left);
    HelpDeleteNode(node->m_right);
    delete node;
  }
}

/**
 * *****************************************************************
 * @brief : 辅助计算结点深度
 * @tparam T
 * @param  node
 * @return int
 * *****************************************************************
 */
template <typename T>
inline int LinkBinaryTree<T>::HelpCalculateDepth(NodePointer node) const {
  if (!node) {
    return 0;
  }

  // 递归计算左右子树的深度，取较大的值并加 1
  int left_depth = HelpCalculateDepth(node->m_left);
  int right_depth = HelpCalculateDepth(node->m_right);

  return (left_depth > right_depth ? left_depth : right_depth) + 1;
}

/**
 * *****************************************************************
 * @brief : 辅助计算结点叶子数
 * @tparam T
 * @param  node
 * @return int
 * *****************************************************************
 */
template <typename T>
inline int LinkBinaryTree<T>::HelpCountLeaves(NodePointer node) const {
  // 空节点没有叶子
  if (!node) {
    return 0;
  }

  // 当前节点是叶子节点
  if (node->m_left == nullptr && node->m_right == nullptr) {
    return 1;
  }

  // 递归计算左右子树的叶子节点数，并返回总和
  return HelpCountLeaves(node->m_left) + HelpCountLeaves(node->m_right);
}

/**
 * *****************************************************************
 * @brief : 辅助计算二叉树结点
 * @tparam T
 * @param  Node
 * @return int
 * *****************************************************************
 */
template <typename T>
inline int LinkBinaryTree<T>::HelpCountNodes(NodePointer node) const {
  if (node == nullptr) {
    return 0;
  }

  // 递归求左子树和右子树的节点数，加上当前节点
  return HelpCountNodes(node->m_left) + HelpCountNodes(node->m_right) + 1;
}

/**
 * *****************************************************************
 * @brief : 辅助前序遍历
 * @tparam T
 * @param  node
 * *****************************************************************
 */
template <typename T>
inline void LinkBinaryTree<T>::HelpPreOrderRecursive(NodePointer node) const {
  if (node == nullptr) {
    return;
  }

  cout << node->m_value << "   ";
  HelpPreOrderRecursive(node->m_left);
  HelpPreOrderRecursive(node->m_right);
}

/**
 * *****************************************************************
 * @brief : 辅助中序遍历
 * @tparam T
 * @param  node
 * *****************************************************************
 */
template <typename T>
inline void LinkBinaryTree<T>::HelpInOrderRecursive(NodePointer node) const {
  if (node == nullptr) {
    return;
  }

  HelpInOrderRecursive(node->m_left);
  cout << node->m_value << "   ";
  HelpInOrderRecursive(node->m_right);
}

/**
 * *****************************************************************
 * @brief : 辅助后序遍历
 * @tparam T
 * @param  node
 * *****************************************************************
 */
template <typename T>
inline void LinkBinaryTree<T>::HelpPostOrderRecursive(NodePointer node) const {
  if (node == nullptr) {
    return;
  }
  HelpPostOrderRecursive(node->m_left);
  HelpPostOrderRecursive(node->m_right);
  cout << node->m_value << "   ";
}

/**
 * *****************************************************************
 * @brief : 辅助镜像翻转
 * @tparam T
 * @param  node
 * *****************************************************************
 */
template <typename T>
inline void LinkBinaryTree<T>::HelpMirror(NodePointer node) {
  if (node == nullptr) {
    return;
  }

  // 交换当前节点的左右子树
  NodePointer temp = node->m_left;
  node->m_left = node->m_right;
  node->m_right = temp;

  // 递归翻转左右子树
  HelpMirror(node->m_left);
  HelpMirror(node->m_right);
}

/**
 * *****************************************************************
 * @brief : 辅助转换成顺序存储二叉树
 * @tparam T
 * @param  node
 * @param  index
 * @param  seq_tree
 * *****************************************************************
 */
template <typename T>
inline void LinkBinaryTree<T>::HelpLinkToSequential(NodePointer node, int index, SeqBinaryTree<T> &seq_tree) const {
  if (node == nullptr) {
    return;
  }
  seq_tree.SetNode(index, node->m_value);

  if (node->m_left) {
    HelpLinkToSequential(node->m_left, index * 2 + 1, seq_tree);
  }
  if (node->m_right) {
    HelpLinkToSequential(node->m_right, index * 2 + 2, seq_tree);
  }
}

/**
 * *****************************************************************
 * @brief : Destroy the Link Binary Tree< T>:: Link Binary Tree object
 * @tparam T
 * *****************************************************************
 */
template <typename T>
inline LinkBinaryTree<T>::~LinkBinaryTree() {
  HelpDeleteNode(m_root);
}

/**
 * *****************************************************************
 * @brief : 置空
 * @tparam T
 * *****************************************************************
 */
template <typename T>
inline void LinkBinaryTree<T>::Clear() {
  HelpDeleteNode(m_root);
  m_root = nullptr;
}

/**
 * *****************************************************************
 * @brief : 计算二叉树深度
 * @tparam T
 * @return int
 * *****************************************************************
 */
template <typename T>
inline int LinkBinaryTree<T>::CalculateDepth() const {
  return HelpCalculateDepth(m_root);
}

/**
 * *****************************************************************
 * @brief : 计算二叉树叶子数
 * @tparam T
 * @return int
 * *****************************************************************
 */
template <typename T>
inline int LinkBinaryTree<T>::CountLeaves() const {
  return HelpCountLeaves(m_root);
}

/**
 * *****************************************************************
 * @brief : 计算二叉树的结点数
 * @tparam T
 * @return int
 * *****************************************************************
 */
template <typename T>
inline int LinkBinaryTree<T>::CountNodes() const {
  return HelpCountNodes(m_root);
}

/**
 * *****************************************************************
 * @brief : 是否为空
 * @tparam T
 * @return true
 * @return false
 * *****************************************************************
 */
template <typename T>
inline bool LinkBinaryTree<T>::IsEmpty() const {
  return m_root == nullptr;
}

/**
 * *****************************************************************
 * @brief : 前序遍历，递归
 * @tparam T
 * *****************************************************************
 */
template <typename T>
inline void LinkBinaryTree<T>::PreOrderRecursive() const {
  cout << "\n";
  HelpPreOrderRecursive(m_root);
  cout << "\n";
}

/**
 * *****************************************************************
 * @brief : 中序遍历，递归
 * @tparam T
 * *****************************************************************
 */
template <typename T>
inline void LinkBinaryTree<T>::InOrderRecursive() const {
  cout << "\n";
  HelpInOrderRecursive(m_root);
  cout << "\n";
}

/**
 * *****************************************************************
 * @brief : 后序遍历，递归
 * @tparam T
 * *****************************************************************
 */
template <typename T>
inline void LinkBinaryTree<T>::PostOrderRecursive() const {
  cout << "\n";
  HelpPostOrderRecursive(m_root);
  cout << "\n";
}

/**
 * *****************************************************************
 * @brief : 镜像二叉树
 * @tparam T
 * *****************************************************************
 */
template <typename T>
inline void LinkBinaryTree<T>::Mirror() {
  HelpMirror(m_root);
}

/**
 * *****************************************************************
 * @brief : 转换成顺序存储二叉树
 * @tparam T
 * @param  seq_tree
 * *****************************************************************
 */
template <typename T>
inline void LinkBinaryTree<T>::LinkToSequential(SeqBinaryTree<T> &seq_tree) const {
  HelpLinkToSequential(m_root, 0, seq_tree);
}

/**
 * *****************************************************************
 * @brief : 将顺序存储二叉树转换成二叉链表
 * @tparam T
 * @param  seq_tree
 * *****************************************************************
 */
template <typename T>
inline void LinkBinaryTree<T>::SequentialToLink(const SeqBinaryTree<T> &seq_tree) {
  Clear();
  m_root = HelpSequentialToLink(seq_tree, 0);
}

} // namespace bu_tools

#endif // _LINKBINARYTREE_H_