/**
 * ************************************************************************
 * @filename: unionfind.h
 * 
 * @brief : 并查集
 * 
 * 
 * @author : baiyebzx (baiyebzx1228@gmail.com)
 * @date : 2024-09-23
 * 
 * ************************************************************************
 */

#ifndef _UNIONFIND_H_
#define _UNIONFIND_H_


namespace bu_tools{

/**
 * *****************************************************************
 * @brief : 并查集（Union-Find）类
 * *****************************************************************
 */
class UnionFind {
private:
  int *m_parent; // 存储每个节点的父节点
  int *m_rank;   // 存储每个根节点对应的树的“秩”
  int m_len;

public:
  UnionFind(int n) : m_len(n) {
    m_parent = new int[m_len];
    m_rank = new int[m_len];

    for (int i = 0; i < m_len; ++i) {
      m_parent[i] = i; // 初始时，每个节点的父节点是它自己
      m_rank[i] = 0;
    }
  }

  ~UnionFind() {
    delete[] m_parent;
    delete[] m_rank;
  }

  /**
   * *****************************************************************
   * @brief : 查找元素x所对应的集合的代表，带路径压缩
   * @param  x
   * @return int
   * *****************************************************************
   */
  int Find(int x) {
    if (m_parent[x] != x) {
      m_parent[x] = Find(m_parent[x]); // 路径压缩
    }
    return m_parent[x];
  }

  /**
   * *****************************************************************
   * @brief : 合并元素x和y所在的两个集合
   * @param  x
   * @param  y
   * *****************************************************************
   */
  void Unite(int x, int y) {
    int root_x = Find(x);
    int root_y = Find(y);

    if (root_x != root_y) {
      // 按秩合并
      if (m_rank[root_x] < m_rank[root_y]) {
        m_parent[root_x] = root_y;
      } else if (m_rank[root_x] > m_rank[root_y]) {
        m_parent[root_y] = root_x;
      } else {
        m_parent[root_y] = root_x;
        m_rank[root_x] += 1; // 如果秩相等，选择一个作为根，并增加其秩
      }
    }
  }

  /**
   * *****************************************************************
   * @brief : 检查元素x和元素y是否属于同一个集合
   * @param  x
   * @param  y
   * @return true
   * @return false
   * *****************************************************************
   */
  bool IsConnected(int x, int y) {
    return Find(x) == Find(y);
  }
};

} // namespace bu_tools




#endif // _UNIONFIND_H_