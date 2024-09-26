/**
 * ************************************************************************
 * @filename: adjlistgraph.h
 *
 * @brief : 图（邻接表）
 *
 *
 * @author : baiyebzx (baiyebzx1228@gmail.com)
 * @date : 2024-09-22
 *
 * ************************************************************************
 */

#ifndef _ADJLISTGRAPH_H_
#define _ADJLISTGRAPH_H_

#include"../queue/seqqueue/seqqueue.h"
#include <cassert>
#include <limits>
#include "../matrix/tuple/tripletsparsematrix.h"
#include"../tree/priorityqueue.h"
#include"unionfind.h"

namespace bu_tools {

/**
 * *****************************************************************
 * @brief : 图（邻接表
 * @tparam T 顶点
 * @tparam E 权值
 * *****************************************************************
 */
template <typename T, typename E>
class AdjLsitgraph {
  /*****************************************************************

  内部嵌套存储边信息的类

  *****************************************************************/
private:
  class Edge {
  public:
    int m_vertex_row;
    int m_vertex_col;
    E m_weight;

    Edge(int row, int col, E weight) : m_vertex_row(row), m_vertex_col(col), m_weight(weight) {}

    Edge() {
      m_vertex_row = -1;
      m_vertex_col = -1;
      m_weight = E();
    }

    // 重载小于运算符用于排序
    bool operator<(const Edge &other) const {
      return m_weight < other.m_weight;
    }

    bool operator>(const Edge &other) const {
      return m_weight > other.m_weight;
    }

    bool operator!=(const Edge &other) const {
      if ((m_vertex_row == other.m_vertex_row && m_vertex_col == other.m_vertex_col && m_weight == other.m_weight) ||
          (m_vertex_row == other.m_vertex_col && m_vertex_col == other.m_vertex_row && m_weight == other.m_weight)) {
        return false;
      }
      return true;
    }
  };

  /*****************************************************************

  邻接表的链表结点结构

  *****************************************************************/
private:
  class AdjListNode {
  public:
    int m_dest; // 目标顶点在顶点数组中的索引
    E m_weight; // 边的权值
    AdjListNode *m_next;

    AdjListNode() {
      m_dest = -1;
      m_weight = E();
      m_next = nullptr;
    }
    AdjListNode(int dest, const E &weight) : m_dest(dest), m_weight(weight), m_next(nullptr) {}
  };

  /*****************************************************************

  顶点元素结构

  *****************************************************************/
private:
  class Vertex {
  public:
    T m_data;                // 顶点存储的数据
    AdjListNode *m_adj_list; // 邻接表的头指针

    Vertex() {
      m_data = T();
      m_adj_list = nullptr;
    }

    Vertex(const T &data) : m_data(data), m_adj_list(nullptr) {}
  };

  /*****************************************************************

  数据域

  *****************************************************************/

protected:
  bool m_is_directed;    // 图的类型：有向图/无向图
  int m_vertex_count;    // 顶点数量
  int m_vertex_capacity; //顶点数组容量
  int m_edge_count;      // 边或弧的数量
  Vertex *m_vertexs;     //顶点数组

  /*****************************************************************

  成员函数的声明

  *****************************************************************/

private:
  void ResizeVertexs();
  void HelpDepthFirstSearch(int vertex, void (*visit)(const T &vertex), bool *visited) const;
  void HelpBreadthFirstSearch(int start_vertex, void (*visit)(const T &vertex), bool *visited) const;
  void HelpFloyd(E **distance, int **path) const;

public:
  AdjLsitgraph(bool is_directed, int capacity = 10) : m_is_directed(is_directed), m_vertex_count(0),
                                                      m_edge_count(0), m_vertex_capacity(capacity) {
    m_vertexs = new Vertex[m_vertex_capacity];
  }
  virtual ~AdjLsitgraph();

  // 顶点相关操作
  int GetVertexCount() const;                        // 获取顶点数量
  bool InsertVertex(const T &vertex);                // 插入顶点
  bool RemoveVertex(const T &vertex);                // 删除顶点
  int GetVertexIndex(const T &vertex) const;         // 获取顶点的索引
  bool GetVertexByIndex(int index, T &vertex) const; // 根据索引获取顶点

  // 边或弧相关操作
  bool InsertEdge(int src, int dest, const E &weight);    // 插入边或弧
  bool RemoveEdge(int src, int dest);                     // 删除边或弧
  bool IsEdgeExist(int src, int dest) const;              // 判断边或弧是否存在
  bool GetEdgeWeight(int src, int dest, E &weight) const; // 获取边或弧的权值
  bool SetEdgeWeight(int src, int dest, const E &weight); // 设置边或弧的权值

  // 图的遍历
  void DepthFirstSearch(int start_vertex, void (*visit)(const T &vertex)) const;   // 深度优先遍历
  void BreadthFirstSearch(int start_vertex, void (*visit)(const T &vertex)) const; // 广度优先遍历

  // 最短路径算法
  void Dijkstra(int start_vertex, E *distance) const; // Dijkstra 算法
  void Floyd(E **distance, int **path) const;                    // Floyd 算法

  // // 拓扑排序
  bool TopologicalSort(T *sorted_vertices) const; // 拓扑排序

  // // 最小生成树算法:其实两个最小生成树算法，最终目的还是得到一个能够连通所有顶点，且边的总权值最小的边的集合
  void Prim(int start_vertex, TripletSparseMatrix<E>& matrix) const; // Prim 算法
  void Kruskal(TripletSparseMatrix<E> &matrix) const;        // Kruskal 算法

  // // 图的度数相关操作
  int GetInDegree(int vertex) const;  // 获取顶点的入度
  int GetOutDegree(int vertex) const; // 获取顶点的出度

  // 清空图
  void Clear(); // 清空图中的所有顶点和边
};

/////////////////////////////////////////////////////////////////////////////////////////////////////
/*

成员函数的定义

*/
/////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * *****************************************************************
 * @brief : 扩容，只在顶点放满的情况下
 * @tparam T
 * @tparam E
 * *****************************************************************
 */
template <typename T, typename E>
inline void AdjLsitgraph<T, E>::ResizeVertexs() {
  m_vertex_capacity *= 2;
  Vertex *new_base = new Vertex[m_vertex_capacity];

  for (int i = 0; i < m_vertex_count; ++i) {
    new_base[i].m_data = m_vertexs[i].m_data;
    new_base[i].m_adj_list = m_vertexs[i].m_adj_list;
    m_vertexs[i].m_adj_list = nullptr;
  }

  delete[] m_vertexs;
  m_vertexs = new_base;
}

/**
 * *****************************************************************
 * @brief : 辅助深度优先搜索
 * @tparam T
 * @tparam E
 * @param  vertex
 * @param  visit
 * @param  visited
 * *****************************************************************
 */
template <typename T, typename E>
inline void AdjLsitgraph<T, E>::HelpDepthFirstSearch(int vertex, void (*visit)(const T &vertex), bool *visited) const {
  // 标记当前顶点为已访问
  visited[vertex] = true;

  // 调用传入的访问函数
  visit(m_vertexs[vertex].m_data);

  // 遍历当前顶点的邻接表
  AdjListNode *current = m_vertexs[vertex].m_adj_list;
  while(current!=nullptr){
    if(!visited[current->m_dest]){
      HelpDepthFirstSearch(current->m_dest,visit,visited);
    }
    current=current->m_next;
  }
}

/**
 * *****************************************************************
 * @brief : 辅助广度优先搜索
 * @tparam T
 * @tparam E
 * @param  start_vertex
 * @param  visit
 * @param  visited
 * *****************************************************************
 */
template <typename T, typename E>
inline void AdjLsitgraph<T, E>::HelpBreadthFirstSearch(int start_vertex, void (*visit)(const T &vertex), bool *visited) const {
  // 创建队列并将起始顶点入队
  SeqQueue<int> vertex_queue(m_vertex_count);
  vertex_queue.EnQueue(start_vertex);
  visited[start_vertex] = true;

  // 开始广度优先遍历
  while (!vertex_queue.IsEmpty()) {
    // 访问队列头部的顶点
    int current_vertex;
    vertex_queue.GetFront(current_vertex);
    vertex_queue.DeQueue();

    // 调用传入的访问函数
    visit(m_vertexs[current_vertex].m_data);

    // 遍历当前顶点的邻接表
    AdjListNode *current = m_vertexs[current_vertex].m_adj_list;
    while (current != nullptr) {
      if (!visited[current->m_dest]) {
        visited[current->m_dest] = true; // 标记为已访问
        vertex_queue.EnQueue(current->m_dest);        // 入队
      }
      current = current->m_next;
    }
  }
}

/**
 * *****************************************************************
 * @brief : 辅助Floyd 算法，初始化两个矩阵
 * @tparam T
 * @tparam E
 * @param  distance
 * @param  path
 * *****************************************************************
 */
template <typename T, typename E>
inline void AdjLsitgraph<T, E>::HelpFloyd(E **distance, int **path) const {
  // 初始化距离矩阵和路径矩阵
  // distance[i][j] 表示顶点 i 到顶点 j 的最短路径长度
  // path[i][j] 表示从顶点 i 到顶点 j 的路径上，j 的前驱顶点
  for (int i = 0; i < m_vertex_count; ++i) {
    for (int j = 0; j < m_vertex_count; ++j) {
      if (i == j) {
        distance[i][j] = 0; // 自己到自己，距离为 0
        path[i][j] = -1;    // 自己到自己，无前驱顶点
      } else if (IsEdgeExist(i, j)) {

        GetEdgeWeight(i, j, distance[i][j]); // 如果存在边，设置为边的权值
        path[i][j] = i;                      // j 的前驱为 i

      } else {
        distance[i][j] = std::numeric_limits<E>::max(); // 不存在边，设置为无穷大
        path[i][j] = -1;                                // 不存在路径，设置为 -1
      }
    }
  }
}

/**
 * *****************************************************************
 * @brief : Destroy the Adj Lsitgraph< T,  E>:: Adj Lsitgraph object
 * @tparam T
 * @tparam E
 * *****************************************************************
 */
template <typename T, typename E>
inline AdjLsitgraph<T, E>::~AdjLsitgraph() {
  Clear();
}

/**
 * *****************************************************************
 * @brief : 获取顶点数量
 * @tparam T
 * @tparam E
 * @return int
 * *****************************************************************
 */
template <typename T, typename E>
inline int AdjLsitgraph<T, E>::GetVertexCount() const {
  return m_vertex_count;
}

/**
 * *****************************************************************
 * @brief : 插入顶点
 * @tparam T
 * @tparam E
 * @param  vertex
 * @return true
 * @return false
 * *****************************************************************
 */
template <typename T, typename E>
inline bool AdjLsitgraph<T, E>::InsertVertex(const T &vertex) {
  // 检查顶点是否已存在
  for (int i = 0; i < m_vertex_count; ++i) {
    if (m_vertexs[i].m_data == vertex) {
      return false; // 顶点已存在，插入失败
    }
  }

  // 检查是否超过了当前的顶点容量
  if (m_vertex_count == m_vertex_capacity) {
    ResizeVertexs();
  }

  // 插入新的顶点
  m_vertexs[m_vertex_count].m_data = vertex;
  m_vertexs[m_vertex_count].m_adj_list = nullptr; // 初始化邻接表为空
  ++m_vertex_count;                               // 更新顶点数量

  return true; // 插入成功
}

/**
 * *****************************************************************
 * @brief : 删除顶点，影响整体结构
 * @tparam T
 * @tparam E
 * @param  vertex
 * @return true
 * @return false
 * *****************************************************************
 */
template <typename T, typename E>
inline bool AdjLsitgraph<T, E>::RemoveVertex(const T &vertex) {
  // 查找顶点索引
  int vertex_index = GetVertexIndex(vertex);
  if (vertex_index == -1) {
    return false; // 顶点不存在，删除失败
  }

  // 删除该顶点的邻接表
  AdjListNode *adj_node = m_vertexs[vertex_index].m_adj_list;
  while (adj_node != nullptr) {
    AdjListNode *temp = adj_node;
    adj_node = adj_node->m_next;
    delete temp;
    m_edge_count--; // 更新边的数量
  }
  m_vertexs[vertex_index].m_adj_list = nullptr;

  // 删除其他顶点指向该顶点的边
  for (int i = 0; i < m_vertex_count; ++i) {
    if (i != vertex_index) {
      AdjListNode *prev = nullptr;
      AdjListNode *current = m_vertexs[i].m_adj_list;

      while (current != nullptr) {
        if (current->m_dest == vertex_index) { //指向删除的顶点位置
          if (prev == nullptr) {
            m_vertexs[i].m_adj_list = current->m_next;
          } else {
            prev->m_next = current->m_next;
          }
          delete current;
          m_edge_count--; // 更新边的数量
          break;
        }
        prev = current;
        current = current->m_next;
      }
    }
  }

  // 移动顶点数组，填补删除顶点的位置
  for (int i = vertex_index; i < m_vertex_count - 1; ++i) {
    m_vertexs[i] = m_vertexs[i + 1]; // 移动顶点
  }

  // 更新顶点数量
  m_vertex_count--;

  return true; // 删除成功
}

/**
 * *****************************************************************
 * @brief : 获取顶点的索引
 * @tparam T
 * @tparam E
 * @param  vertex
 * @return int 如果是-1，则不存在这个索引
 * *****************************************************************
 */
template <typename T, typename E>
inline int AdjLsitgraph<T, E>::GetVertexIndex(const T &vertex) const {
  // 查找顶点的索引
  int index = -1;
  for (int i = 0; i < m_vertex_count; ++i) {
    if (m_vertexs[i].m_data == vertex) {
      index = i;
      break;
    }
  }

  return index;
}

/**
 * *****************************************************************
 * @brief : 根据索引获取顶点
 * @tparam T
 * @tparam E
 * @param  index 0开始
 * @param  vertex
 * @return true
 * @return false
 * *****************************************************************
 */
template <typename T, typename E>
inline bool AdjLsitgraph<T, E>::GetVertexByIndex(int index, T &vertex) const {
  if (index < 0 || index > m_vertex_count) {
    vertex = T();
    return false;
  }

  vertex = m_vertexs[index].m_data;
  return true;
}

/**
 * *****************************************************************
 * @brief :
 * @tparam T
 * @tparam E
 * @param  vertex1
 * @param  vertex2
 * @param  weight
 * @return true
 * @return false
 * *****************************************************************
 */
template <typename T, typename E>
inline bool AdjLsitgraph<T, E>::InsertEdge(int src, int dest, const E &weight) {
  // 检查源和目标顶点的有效性
  if (src < 0 || src >= m_vertex_count || dest < 0 || dest >= m_vertex_count) {
    return false;
  }

  // 创建新的邻接表节点
  AdjListNode *new_node = new AdjListNode(dest, weight);
  
  // 将新节点插入到源顶点的邻接表中
  new_node->m_next = m_vertexs[src].m_adj_list;
  m_vertexs[src].m_adj_list = new_node;
  

  // 如果是无向图，还需要插入反向边
  if (!m_is_directed) {
    AdjListNode *reverse_node = new AdjListNode(src, weight);
    reverse_node->m_next = m_vertexs[dest].m_adj_list;
    m_vertexs[dest].m_adj_list = reverse_node;

    // 增加边的计数
    m_edge_count++;
  }

  // 增加边的计数
  m_edge_count++;
  return true;
}

/**
 * *****************************************************************
 * @brief : 删除边或弧
 * @tparam T
 * @tparam E
 * @param  src
 * @param  dest
 * @return true
 * @return false
 * *****************************************************************
 */
template <typename T, typename E>
inline bool AdjLsitgraph<T, E>::RemoveEdge(int src, int dest) {
  // 检查源和目标顶点的有效性
  if (src < 0 || src >= m_vertex_count || dest < 0 || dest >= m_vertex_count) {
    return false;
  }

  // 从源顶点的邻接表中删除目标顶点
  AdjListNode *current = m_vertexs[src].m_adj_list;
  AdjListNode *previous = nullptr;

  while (current != nullptr) {
    if (current->m_dest == dest) {
      if (previous == nullptr) {
        // 删除的是头结点
        m_vertexs[src].m_adj_list = current->m_next;
      } else {
        // 删除的是中间或尾部节点
        previous->m_next = current->m_next;
      }
      delete current;
      break; // 找到并删除后退出
    }
    previous = current;
    current = current->m_next;
  }

  // 如果是无向图，还需要在目标顶点的邻接表中删除反向边
  if (!m_is_directed) {
    current = m_vertexs[dest].m_adj_list;
    previous = nullptr;

    while (current != nullptr) {
      if (current->m_dest == src) {
        if (previous == nullptr) {
          // 删除的是头结点
          m_vertexs[dest].m_adj_list = current->m_next;
        } else {
          // 删除的是中间或尾部节点
          previous->m_next = current->m_next;
        }
        delete current;
        break; // 找到并删除后退出
      }
      previous = current;
      current = current->m_next;
    }
  }

  // 减少边的计数
  m_edge_count--;

  return true;
}

/**
 * *****************************************************************
 * @brief : 判断边或弧是否存在
 * @tparam T
 * @tparam E
 * @param  src
 * @param  dest
 * @return true
 * @return false
 * *****************************************************************
 */
template <typename T, typename E>
inline bool AdjLsitgraph<T, E>::IsEdgeExist(int src, int dest) const {
  // 检查源和目标顶点的有效性
  if (src < 0 || src >= m_vertex_count || dest < 0 || dest >= m_vertex_count) {
    return false;
  }

  // 遍历源顶点的邻接表，查找目标顶点
  AdjListNode *current = m_vertexs[src].m_adj_list;
  while (current != nullptr) {
    if (current->m_dest == dest) {
      return true; // 找到边或弧
    }
    current = current->m_next;
  }

  // 如果是有向图，且未找到，则返回false
  return false;
}

/**
 * *****************************************************************
 * @brief : 获取边或弧的权值
 * @tparam T
 * @tparam E
 * @param  src
 * @param  dest
 * @param  weight
 * @return true
 * @return false
 * *****************************************************************
 */
template <typename T, typename E>
inline bool AdjLsitgraph<T, E>::GetEdgeWeight(int src, int dest, E &weight) const {
  // 检查源和目标顶点的有效性
  if (src < 0 || src >= m_vertex_count || dest < 0 || dest >= m_vertex_count) {
    weight = E();
    return false;
  }

  // 遍历源顶点的邻接表，查找目标顶点
  AdjListNode *current = m_vertexs[src].m_adj_list;
  while (current != nullptr) {
    if (current->m_dest == dest) {
      weight = current->m_weight;
      return true; // 找到边或弧，返回权值
    }
    current = current->m_next;
  }

  //没找到
  return false;
}

/**
 * *****************************************************************
 * @brief : 设置边或弧的权值
 * @tparam T
 * @tparam E
 * @param  src
 * @param  dest
 * @param  weight
 * @return true
 * @return false
 * *****************************************************************
 */
template <typename T, typename E>
inline bool AdjLsitgraph<T, E>::SetEdgeWeight(int src, int dest, const E &weight) {
  // 检查源和目标顶点的有效性
  if (src < 0 || src >= m_vertex_count || dest < 0 || dest >= m_vertex_count) {
    return false;
  }

  // 遍历源顶点的邻接表，查找目标顶点
  AdjListNode *current = m_vertexs[src].m_adj_list;
  while (current != nullptr) {
    if (current->m_dest == dest) {
      current->m_weight = weight; // 找到边或弧，设置新的权值
      return true;
    }
    current = current->m_next;
  }

  //无向图遍历目标顶点的邻接表，查找源顶点

  if (!m_is_directed) {
    current = m_vertexs[dest].m_adj_list;
    while (current != nullptr) {
      if (current->m_dest == src) {
        current->m_weight = weight; // 找到边或弧，设置新的权值
        return true;
      }
      current = current->m_next;
    }
  }
}

/**
 * *****************************************************************
 * @brief : 深度优先遍历
 * @tparam T
 * @tparam E
 * @param  start_vertex
 * @param  visit 自定义处理顶点的函数
 * *****************************************************************
 */
template <typename T, typename E>
inline void AdjLsitgraph<T, E>::DepthFirstSearch(int start_vertex, void (*visit)(const T &vertex)) const {
  // 检查起始顶点是否合法
  if (start_vertex < 0 || start_vertex >= m_vertex_count) {
    return; // 非法的起始顶点
  }

  // 创建一个访问标记数组，初始化为 false，表示所有顶点均未被访问
  bool *visited = new bool[m_vertex_count];
  for (int i = 0; i < m_vertex_count; ++i) {
    visited[i] = false;
  }

  HelpDepthFirstSearch(start_vertex, visit, visited);

  delete [] visited;
}

/**
 * *****************************************************************
 * @brief : 广度优先遍历
 * @tparam T
 * @tparam E
 * @param  start_vertex
 * @param  visit  自定义处理顶点的函数
 * *****************************************************************
 */
template <typename T, typename E>
inline void AdjLsitgraph<T, E>::BreadthFirstSearch(int start_vertex, void (*visit)(const T &vertex)) const {
  // 检查起始顶点是否合法
  if (start_vertex < 0 || start_vertex >= m_vertex_count) {
    return; // 非法的起始顶点
  }

  // 创建一个访问标记数组，初始化为 false，表示所有顶点均未被访问
  bool *visited = new bool[m_vertex_count];
  for (int i = 0; i < m_vertex_count; ++i) {
    visited[i] = false;
  }

  // 遍历所有顶点，以确保每个连通分量的顶点都能被访问
  for (int v = start_vertex; v < m_vertex_count; ++v) {
    // 如果当前顶点尚未被访问，执行广度优先遍历
    if (!visited[v]) {
      HelpBreadthFirstSearch(v, visit, visited);
    }
  }

  for (int v = 0; v < start_vertex; ++v) {
    // 如果当前顶点尚未被访问，执行广度优先遍历
    if (!visited[v]) {
      HelpBreadthFirstSearch(v, visit, visited);
    }
  }

  // 释放动态分配的数组内存
  delete[] visited;
}

/**
 * *****************************************************************
 * @brief : Dijkstra 算法：用于在加权图中计算从起点顶点到其余顶点的最短路径
 * @tparam T
 * @tparam E
 * @param  start_vertex 起始顶点的索引
 * @param  distance 保存从起点到各顶点的最短距离
 * *****************************************************************
 */
template <typename T, typename E>
inline void AdjLsitgraph<T, E>::Dijkstra(int start_vertex, E *distance) const {
  const E INF = std::numeric_limits<E>::max(); // 用于表示无穷大的值
  // 检查起始顶点的有效性
  if (start_vertex < 0 || start_vertex >= m_vertex_count) {
    delete [] distance;
    distance=nullptr;
    return;
  }

  // 初始化distance
  bool *visited = new bool[m_vertex_count]; // 访问标记数组
  for (int i = 0; i < m_vertex_count; i++) {
    distance[i] = INF; // 所有顶点的初始距离设为无穷大
    visited[i]=false;
  }

  distance[start_vertex] = 0; // 起点到自身的距离为0

  // Dijkstra 算法核心
  for (int i = 0; i < m_vertex_count; ++i) {
    // 选择未访问顶点中距离最小的顶点
    int u = -1;
    E min_distance = INF;
    for (int j = 0; j < m_vertex_count; j++) {
      if (!visited[j] && distance[j] < min_distance) {
        u = j;
        min_distance = distance[j];
      }
    }

    if (u == -1) {
      break; // 若未找到可更新的顶点，退出
    }

    visited[u] = true; // 标记该顶点已处理

    // 更新与顶点 u 相邻的顶点的距离
    for (int v = 0; v < m_vertex_count; v++) {
      //判断两个顶点是否有通路
      E temp;
      if (!visited[v] && GetEdgeWeight(u, v, temp)) {
        
        E new_dist = distance[u] + temp;
        if (new_dist < distance[v]) {
          distance[v] = new_dist; // 更新顶点 v 的最短距离
        }
      }
    }
  }

  delete[] visited; // 释放内存
}

/**
 * *****************************************************************
 * @brief : Floyd 算法
 * @tparam T
 * @tparam E
 * @param  distance
 * @param  path
 * *****************************************************************
 */
template <typename T, typename E>
inline void AdjLsitgraph<T, E>::Floyd(E **distance, int **path) const {
  HelpFloyd(distance, path); // 初始化矩阵

  // 开始 Floyd 核心算法
  // k 是中间顶点的索引，通过顶点 k 来更新 i 到 j 的最短路径
  for (int k = 0; k < m_vertex_count; ++k) {
    for (int i = 0; i < m_vertex_count; ++i) {
      for (int j = 0; j < m_vertex_count; ++j) {
        // 判断经过顶点 k 是否能找到更短的路径
        if (distance[i][k] != std::numeric_limits<E>::max() &&
            distance[k][j] != std::numeric_limits<E>::max() &&
            distance[i][k] + distance[k][j] < distance[i][j]) {
          distance[i][j] = distance[i][k] + distance[k][j]; // 更新最短路径长度
          path[i][j] = path[k][j];                          // 更新路径：i 到 j 的前驱改为通过 k 的路径
        }
      }
    }
  }
}

/**
 * *****************************************************************
 * @brief : 拓扑排序
 * @tparam T
 * @tparam E
 * @param  sorted_vertices
 * @return true
 * @return false
 * *****************************************************************
 */
template <typename T, typename E>
inline bool AdjLsitgraph<T, E>::TopologicalSort(T *sorted_vertices) const {
  if (!m_is_directed) {
    delete[] sorted_vertices;
    sorted_vertices = nullptr;
    return false;
  }

  // 用于存储每个顶点的入度
  int *in_degrees = new int[m_vertex_count];
  for (int i = 0; i < m_vertex_count; ++i) {
    in_degrees[i] = GetInDegree(i); // 获取每个顶点的入度
  }

  bu_tools::SeqQueue<int> zero_in_degree_queue; // 存放入度为0的顶点索引

  // 将所有入度为0的顶点加入队列
  for (int i = 0; i < m_vertex_count; ++i) {
    if (in_degrees[i] == 0) {
      zero_in_degree_queue.EnQueue(i);
    }
  }

  int sorted_index = 0; // 记录排序后的顶点索引

  while (!zero_in_degree_queue.IsEmpty()) {
    int vertex;
    zero_in_degree_queue.DeQueue(vertex); // 取出入度为0的顶点

    // 将当前顶点加入到拓扑排序结果中
    sorted_vertices[sorted_index++] = m_vertexs[vertex].m_data;

    // 更新相邻顶点的入度
    for (int i = 0; i < m_vertex_count; ++i) {
      if (IsEdgeExist(vertex, i)) { // 如果存在从vertex到i的边
        in_degrees[i]--;            // 减少相邻顶点的入度

        if (in_degrees[i] == 0) {
          zero_in_degree_queue.EnQueue(i); // 入度为0的顶点加入队列
        }
      }
    }
  }

  delete[] in_degrees; // 释放内存

  // 如果排序后的顶点数量小于图的顶点数量，说明存在环，无法进行拓扑排序
  if (sorted_index < m_vertex_count) {
    return false; // 有环，拓扑排序失败
  }

  return true; // 拓扑排序成功
}

/**
 * *****************************************************************
 * @brief : Prim 算法
 * @tparam T
 * @tparam E
 * @param  start_vertex
 * @param  matrix 存储最小生成树的边集合
 * *****************************************************************
 */
template <typename T, typename E>
inline void AdjLsitgraph<T, E>::Prim(int start_vertex, TripletSparseMatrix<E> &matrix) const {
  if (start_vertex < 0 || start_vertex >= m_vertex_count) {
    return;
  }

  E* distance=new E[m_vertex_count];
  int* path=new int[m_vertex_count];

  const E INF = std::numeric_limits<E>::max(); // 定义无穷大
  bool *in_tree = new bool[m_vertex_count];    // 标记顶点是否在最小生成树中

  for (int i = 0; i < m_vertex_count; ++i) {
    distance[i] = INF;  // 初始化所有顶点的最短距离为无穷大
    path[i] = -1;       // 初始化前驱顶点为 -1
    in_tree[i] = false; // 初始时没有顶点在树中
  }

  distance[start_vertex] = 0; // 起点的距离为 0

  for (int i = 0; i < m_vertex_count; ++i) {
    int u = -1;
    E min_dist = INF;

    // 找到不在树中且距离最小的顶点
    for (int j = 0; j < m_vertex_count; ++j) {
      if (!in_tree[j] && distance[j] < min_dist) {
        u = j;
        min_dist = distance[j];
      }
    }

    if (u == -1) {
      break; // 如果无法找到这样的顶点，说明图不连通
    }

    in_tree[u] = true; // 将该顶点加入最小生成树

    // 更新相邻顶点的距离
    for (int v = 0; v < m_vertex_count; ++v) {
      if (!in_tree[v] && IsEdgeExist(u, v)) { // 检查u到v是否存在边
        E weight;
        GetEdgeWeight(u, v, weight); // 获取边的权重
        if (weight < distance[v]) {  // 如果找到更短的路径
          distance[v] = weight;      // 更新最短距离
          path[v] = u;               // 记录前驱顶点
        }
      }
    }
  }

  for(int i=1;i<m_vertex_count;++i){
    if(path[i]!=-1){
      matrix.Insert(path[i],i,distance[i]);
    }
  }

  delete [] path;
  delete [] distance;
  delete [] in_tree;
}

/**
 * *****************************************************************
 * @brief : Kruskal 算法
 * @tparam T
 * @tparam E
 * @param  matrix 存储最小生成树的边集合
 * *****************************************************************
 */
template <typename T, typename E>
inline void AdjLsitgraph<T, E>::Kruskal(TripletSparseMatrix<E> &matrix) const {
  //将所有的边放入优先队列中
  PriorityQueue<Edge> edges;
  AdjListNode* current=nullptr;
  for(int i=0;i<m_vertex_count;++i){
    current=m_vertexs[i].m_adj_list;
    while(current){
      Edge edge(i,current->m_dest,current->m_weight);
      edges.Push(edge);
      current=current->m_next;
    }
  }

  //初始化并查集
  UnionFind uf(m_vertex_count);

  // Kruskal算法核心逻辑
  while (!edges.IsEmpty()) {

    Edge edge;
    edges.Pop(edge);

    if (!uf.IsConnected(edge.m_vertex_row, edge.m_vertex_col)) {
      // 如果这条边的两个顶点不在同一个集合中，加入最小生成树
      matrix.Insert(edge.m_vertex_row, edge.m_vertex_col, edge.m_weight);

      uf.Unite(edge.m_vertex_row, edge.m_vertex_col);
    }

    if (matrix.GetTolal() == m_vertex_count - 1) {
      break;
    }
  }
}

/**
 * *****************************************************************
 * @brief : 顶点入度
 * @tparam T
 * @tparam E
 * @param  vertex
 * @return int
 * *****************************************************************
 */
template <typename T, typename E>
inline int AdjLsitgraph<T, E>::GetInDegree(int vertex) const {
  if (vertex < 0 || vertex >= m_vertex_count || !m_is_directed) {
    return -1;
  }

  int in_degree = 0; // 用于记录顶点的入度

  // 遍历邻接矩阵的每一行，检查是否有边指向该顶点
  for (int i = 0; i < m_vertex_count; ++i) {
    if (IsEdgeExist(i, vertex)) { // 如果从顶点i到目标顶点vertex存在边
      in_degree++;
    }
  }

  return in_degree; // 返回入度
}

/**
 * *****************************************************************
 * @brief : 顶点出度
 * @tparam T
 * @tparam E
 * @param  vertex
 * @return int
 * *****************************************************************
 */
template <typename T, typename E>
inline int AdjLsitgraph<T, E>::GetOutDegree(int vertex) const {
  if (vertex < 0 || vertex >= m_vertex_count || !m_is_directed) {
    return -1;
  }

  int out_degree = 0; // 用于记录顶点的出度

  // 遍历邻接矩阵的第 vertex 行，检查从该顶点出发的边
  for (int i = 0; i < m_vertex_count; ++i) {
    if (IsEdgeExist(vertex, i)) { // 如果从顶点vertex到顶点i存在边
      out_degree++;
    }
  }

  return out_degree; // 返回出度
}

/**
 * *****************************************************************
 * @brief : 置空
 * @tparam T
 * @tparam E
 * *****************************************************************
 */

template <typename T, typename E>
inline void AdjLsitgraph<T, E>::Clear() {
  //避免重复置空
  if (!m_vertexs) {
    // 遍历每个顶点
    for (int i = 0; i < m_vertex_count; ++i) {
      // 获取当前顶点的邻接表头指针
      AdjListNode *adj_node = m_vertexs[i].m_adj_list;
      // 逐个删除邻接表中的边结点
      while (adj_node != nullptr) {
        AdjListNode *temp = adj_node;
        adj_node = adj_node->m_next;
        delete temp;
      }
      // 将顶点的邻接表头指针置空
      m_vertexs[i].m_adj_list = nullptr;
    }

    // 删除顶点数组
    delete[] m_vertexs;
    m_vertexs = nullptr;

    // 重置顶点和边的计数
    m_vertex_count = 0;
    m_edge_count = 0;
  }
}

} // namespace bu_tools

#endif // _ADJLISTGRAPH_H_