/**
 * ************************************************************************
 * @filename: adjmatrixgraph.h
 *
 * @brief : 图（邻接矩阵）
 *
 *
 * @author : baiyebzx (baiyebzx1228@gmail.com)
 * @date : 2024-09-15
 *
 * ************************************************************************
 */

#ifndef _ADJMATRIXGRAPH_H_
#define _ADJMATRIXGRAPH_H_

#include "../matrix/tuple/tripletsparsematrix.h"
#include "../queue/seqqueue/seqqueue.h"
//#include "../tree/huffmantree.h"
#include <limits>
#include "unionfind.h"
#include "../tree/priorityqueue.h"

namespace bu_tools {




/**
 * *****************************************************************
 * @brief :图（邻接矩阵）
 * @tparam T 顶点
 * @tparam E 权值
 * *****************************************************************
 */
template <typename T, typename E>
class AdjMatrixGraph {
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
      if ((m_vertex_row == other.m_vertex_row && m_vertex_col == other.m_vertex_col && m_weight == other.m_weight)||
      (m_vertex_row==other.m_vertex_col&&m_vertex_col==other.m_vertex_row&&m_weight==other.m_weight)){
        return false;
      }
        return true;
    }



  };

  /*****************************************************************

  数据域

  *****************************************************************/
protected:
   bool m_is_directed;                  // 图的种类（true 表示有向图，false 表示无向图）
  int m_vertex_count;                  // 顶点数量
  int m_edge_count;                    // 边或弧的数量
  T *m_vertexs;                        // 顶点数据数组
  TripletSparseMatrix<E> m_adj_matrix; // 邻接矩阵，存储边或弧的权值

  /*****************************************************************

  成员函数的声明

  *****************************************************************/

private:
  void HelpDepthFirstSearch(int vertex, void (*visit)(const T &vertex), bool *visited) const;
  void HelpBreadthFirstSearch(int start_vertex, void (*visit)(const T &vertex), bool *visited) const;
  void HelpFloyd(E **distance, int **path) const;

public:
  AdjMatrixGraph(int vertex_count, bool is_directed) : m_is_directed(is_directed), m_edge_count(0), m_adj_matrix(vertex_count, vertex_count) {

    // 动态分配顶点数组
    m_vertexs = new T[vertex_count];

    //顶点还未插入，所以个数为0
    m_vertex_count = 0;

  }
  AdjMatrixGraph(const AdjMatrixGraph& other);
  virtual ~AdjMatrixGraph();

  // 顶点相关操作
  int GetVertexCount() const;                        // 获取顶点数量
  bool InsertVertex(const T &vertex);                // 插入顶点
  bool RemoveVertex(const T &vertex);                // 删除顶点
  int GetVertexIndex(const T &vertex) const;         // 获取顶点的索引
  bool GetVertexByIndex(int index, T &vertex) const; // 根据索引获取顶点

  // 边或弧相关操作
  bool InsertEdge(int vertex1, int vertex2, const E &weight);    // 插入边或弧
  bool RemoveEdge(int vertex1, int vertex2);                     // 删除边或弧
  bool IsEdgeExist(int vertex1, int vertex2) const;              // 判断边或弧是否存在
  bool GetEdgeWeight(int vertex1, int vertex2, E &weight) const; // 获取边或弧的权值
  bool SetEdgeWeight(int vertex1, int vertex2, const E &weight); // 设置边或弧的权值

  // 图的遍历
  void DepthFirstSearch(int start_vertex, void (*visit)(const T &vertex)) const;   // 深度优先遍历
  void BreadthFirstSearch(int start_vertex, void (*visit)(const T &vertex)) const; // 广度优先遍历

  // 最短路径算法
  void Dijkstra(int start_vertex, E *distance) const; // Dijkstra 算法
  void Floyd(E **distance, int **path) const;                    // Floyd 算法

  // // 拓扑排序
  bool TopologicalSort(T *sorted_vertices) const; // 拓扑排序

  // // 最小生成树算法
  void Prim(int start_vertex, E *distance, int *path) const; // Prim 算法
  void Kruskal(TripletSparseMatrix<E> &matrix) const;        // Kruskal 算法

  // // 显示图的邻接矩阵
  // void PrintAdjMatrix() const; // 输出邻接矩阵

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
 * @brief : 辅助深度优先搜索
 * @tparam T
 * @tparam E
 * @param  vertex
 * @param  visit
 * @param  visited
 * *****************************************************************
 */
template <typename T, typename E>
inline void AdjMatrixGraph<T, E>::HelpDepthFirstSearch(int vertex, void (*visit)(const T &vertex), bool *visited) const {
  // 标记当前顶点为已访问
  visited[vertex] = true;

  // 调用传入的访问函数
  visit(m_vertexs[vertex]);

  // 遍历邻接矩阵中的所有顶点，寻找与当前顶点相连且未被访问的顶点
  for (int i = 0; i < m_vertex_count; ++i) {
    // 如果 vertex 到 i 有边且 i 未被访问
    if (m_adj_matrix.IsNonZeroAt(vertex, i) && !visited[i]) {
      HelpDepthFirstSearch(i, visit, visited);
    }
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
inline void AdjMatrixGraph<T, E>::HelpBreadthFirstSearch(int start_vertex, void (*visit)(const T &vertex), bool *visited) const {
  // 创建队列并将起始顶点入队
  SeqQueue<int> vertex_queue(m_vertex_count);
  vertex_queue.EnQueue(start_vertex);
  visited[start_vertex] = true;

  // 开始广度优先遍历
  while (!vertex_queue.IsEmpty()) {
    int current_vertex;
    vertex_queue.GetFront(current_vertex);
    vertex_queue.DeQueue();

    // 调用传入的访问函数
    visit(m_vertexs[current_vertex]);

    // 遍历所有顶点，寻找与当前顶点相连且未访问的顶点
    for (int i = 0; i < m_vertex_count; ++i) {
      // 如果当前顶点与顶点 i 有边且 i 未被访问
      if (m_adj_matrix.IsNonZeroAt(current_vertex, i) && !visited[i]) {
        vertex_queue.EnQueue(i);
        visited[i] = true;
      }
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
inline void AdjMatrixGraph<T, E>::HelpFloyd(E **distance, int **path) const {
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
 * @brief : Construct a new Adj Matrix Graph< T,  E>:: Adj Matrix Graph object
 * @tparam T 
 * @tparam E 
 * @param  other            
 * *****************************************************************
 */
template <typename T, typename E>
inline AdjMatrixGraph<T, E>::AdjMatrixGraph(const AdjMatrixGraph &other) {
  m_is_directed=other.m_is_directed;
  m_vertex_count=other.m_vertex_count;
  m_edge_count=other.m_edge_count;

  m_vertexs=new T[m_vertex_count];
  for(int i=0;i<m_vertex_count;++i){
    m_vertexs[i]=other.m_vertexs[i];
  }

  m_adj_matrix=other.m_adj_matrix;
}

/**
 * *****************************************************************
 * @brief : Destroy the Adj Matrix Graph< T,  E>:: Adj Matrix Graph object
 * @tparam T 
 * @tparam E 
 * *****************************************************************
 */
template <typename T, typename E>
inline AdjMatrixGraph<T, E>::~AdjMatrixGraph() {
  delete [] m_vertexs;
  m_adj_matrix.Clear();
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
inline int AdjMatrixGraph<T, E>::GetVertexCount() const {
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
inline bool AdjMatrixGraph<T, E>::InsertVertex(const T &vertex) {
  // 检查顶点是否已存在
  for (int i = 0; i < m_vertex_count; ++i) {
    if (m_vertexs[i] == vertex) {
      return false; // 顶点已存在，插入失败
    }
  }

  // 检查是否超过了当前的顶点容量
  if (m_vertex_count >= m_adj_matrix.GetRows()) {
    return false; // 没有空间插入新顶点
  }

  // 插入顶点到顶点数组
  m_vertexs[m_vertex_count] = vertex;

  // 更新顶点数量
  ++m_vertex_count;

  return true; // 插入成功
}

/**
 * *****************************************************************
 * @brief : 删除顶点，影响整体结构，会压缩整个矩阵
 * @tparam T
 * @tparam E
 * @param  vertex
 * @return true
 * @return false
 * *****************************************************************
 */
template <typename T, typename E>
inline bool AdjMatrixGraph<T, E>::RemoveVertex(const T &vertex) {
  int index = GetVertexIndex(vertex);

  // 如果顶点不存在，返回删除失败
  if (index == -1) {
    return false;
  }

  // 删除邻接矩阵中与该顶点相关的边（删除第 index 行和第 index 列）
  for (int i = 0; i < m_vertex_count; ++i) {
    // 移除所有与该顶点相连的边
    RemoveEdge(index, i); // 移除 index 行
    RemoveEdge(i, index); // 移除 index 列
  }

  // 移动顶点数组，将后面的顶点向前移动
  for (int i = index; i < m_vertex_count - 1; ++i) {
    m_vertexs[i] = m_vertexs[i + 1];
  }

  // 在邻接矩阵中，删除第 index 行和列后，将后续行和列向前移动
  //删除行列不影响三元组的排列顺序
  for (auto it = m_adj_matrix.begin(); it != m_adj_matrix.end(); ++it) {
    if (it->m_row > index) {
      --it->m_row;
    }
    if (it->m_col > index) {
      --it->m_col;
    }
  }

  // 更新顶点数量
  --m_vertex_count;
  //更新边和弧的数量
  m_edge_count = m_adj_matrix.GetTolal();

  return true;
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
inline int AdjMatrixGraph<T, E>::GetVertexIndex(const T &vertex) const {
  // 查找顶点的索引
  int index = -1;
  for (int i = 0; i < m_vertex_count; ++i) {
    if (m_vertexs[i] == vertex) {
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
inline bool AdjMatrixGraph<T, E>::GetVertexByIndex(int index, T &vertex) const {
  if (index < 0 || index > m_vertex_count) {
    vertex = T();
    return false;
  }
  vertex = m_vertexs[index];
  return true;
}

/**
 * *****************************************************************
 * @brief : 插入边或弧
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
inline bool AdjMatrixGraph<T, E>::InsertEdge(int vertex1, int vertex2, const E &weight) {
  // 检查顶点索引是否有效
  if (vertex1 < 0 || vertex1 >= m_vertex_count || vertex2 < 0 || vertex2 >= m_vertex_count) {
    return false; // 无效的顶点索引
  }

  // 检查是否已经存在边
  if (IsEdgeExist(vertex1, vertex2)) { // 假设E()为默认无边的状态
    return false;                      // 边已存在
  }

  // 插入边或弧，设置邻接矩阵中的权值
  m_adj_matrix.Insert(vertex1, vertex2, weight);

  // 如果是无向图，则同时插入对称位置的权值
  if (!m_is_directed) {
    m_adj_matrix.Insert(vertex2, vertex1, weight);
    // 更新边的数量
    ++m_edge_count;
  }

  // 更新边的数量
  ++m_edge_count;

  return true; // 插入成功
}

/**
 * *****************************************************************
 * @brief : 删除边或弧
 * @tparam T
 * @tparam E
 * @param  vertex1
 * @param  vertex2
 * @return true
 * @return false
 * *****************************************************************
 */
template <typename T, typename E>
inline bool AdjMatrixGraph<T, E>::RemoveEdge(int vertex1, int vertex2) {
  if (m_adj_matrix.Remove(vertex1, vertex2)) {
    --m_edge_count;
    return true;
  }
  return false;
}

/**
 * *****************************************************************
 * @brief : 判断边或弧是否存在
 * @tparam T
 * @tparam E
 * @param  vertex1
 * @param  vertex2
 * @return true
 * @return false
 * *****************************************************************
 */
template <typename T, typename E>
inline bool AdjMatrixGraph<T, E>::IsEdgeExist(int vertex1, int vertex2) const {
  if (m_adj_matrix.IsNonZeroAt(vertex1, vertex2)) {
    return true;
  }
  return false;
}

/**
 * *****************************************************************
 * @brief : 获取边或弧的权值
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
inline bool AdjMatrixGraph<T, E>::GetEdgeWeight(int vertex1, int vertex2, E &weight) const {
  if (m_adj_matrix.GetValue(vertex1, vertex2, weight)) {
    return true;
  }
  return false;
}

/**
 * *****************************************************************
 * @brief : 设置边或弧的权值
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
inline bool AdjMatrixGraph<T, E>::SetEdgeWeight(int vertex1, int vertex2, const E &weight) {
  if (m_adj_matrix.Insert(vertex1, vertex2, weight)) {
    return true;
  }
  return false;
}

/**
 * *****************************************************************
 * @brief : 深度优先遍历
 * @tparam T
 * @tparam E
 * @param  start_vertex
 * @param  visit            自定义处理顶点的函数
 * *****************************************************************
 */
template <typename T, typename E>
inline void AdjMatrixGraph<T, E>::DepthFirstSearch(int start_vertex, void (*visit)(const T &vertex)) const {
  // 检查起始顶点是否合法
  if (start_vertex < 0 || start_vertex >= m_vertex_count) {
    return; // 非法的起始顶点
  }

  // 创建一个访问标记数组，初始化为 false，表示所有顶点均未被访问
  bool *visited = new bool[m_vertex_count];
  for (int i = 0; i < m_vertex_count; ++i) {
    visited[i] = false;
  }

  // 遍历所有顶点，处理不连通图的情况
  for (int v = start_vertex; v < m_vertex_count; ++v) {
    // 如果顶点 v 尚未被访问，进行一次 DFS
    if (!visited[v]) {
      HelpDepthFirstSearch(v, visit, visited);
    }
  }

  for (int v = 0; v < start_vertex; ++v) {
    // 如果顶点 v 尚未被访问，进行一次 DFS
    if (!visited[v]) {
      HelpDepthFirstSearch(v, visit, visited);
    }
  }

  // 释放动态分配的数组内存
  delete[] visited;
}

/**
 * *****************************************************************
 * @brief : 广度优先遍历
 * @tparam T
 * @tparam E
 * @param  start_vertex
 * @param  visit
 * *****************************************************************
 */
template <typename T, typename E>
inline void AdjMatrixGraph<T, E>::BreadthFirstSearch(int start_vertex, void (*visit)(const T &vertex)) const {
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
 * @param  path 保存最短路径的前驱顶点索引，便于回溯路径
 * *****************************************************************
 */
template <typename T, typename E>
inline void AdjMatrixGraph<T, E>::Dijkstra(int start_vertex, E *distance) const {
  const E INF = std::numeric_limits<E>::max(); // 用于表示无穷大的值

  // 初始化distance
  for (int i = 0; i < m_vertex_count; i++) {
    distance[i] = INF; // 所有顶点的初始距离设为无穷大
  }
  distance[start_vertex] = 0; // 起点到自身的距离为0

  bool *visited = new bool[m_vertex_count]; // 访问标记数组
  for (int i = 0; i < m_vertex_count; i++) {
    visited[i] = false; // 初始化所有顶点未访问
  }

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
 * @brief :Floyd 算法
 * @tparam T
 * @tparam E
 * @param  distance
 * @param  path
 * *****************************************************************
 */
template <typename T, typename E>
inline void AdjMatrixGraph<T, E>::Floyd(E **distance, int **path) const {
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
inline bool AdjMatrixGraph<T, E>::TopologicalSort(T *sorted_vertices) const {

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
    sorted_vertices[sorted_index++] = m_vertexs[vertex];

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
 * @param  distance
 * @param  path
 * *****************************************************************
 */
template <typename T, typename E>
inline void AdjMatrixGraph<T, E>::Prim(int start_vertex, E *distance, int *path) const {
  if (start_vertex < 0 || start_vertex >= m_vertex_count) {
    delete[] distance;
    distance = nullptr;
    delete[] path;
    path = nullptr;
    return;
  }

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

  delete[] in_tree; // 释放内存
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
inline void AdjMatrixGraph<T, E>::Kruskal(TripletSparseMatrix<E> &matrix) const {

  //将所有的边放入优先队列中
  PriorityQueue<Edge> edges;
  for (auto it = m_adj_matrix.begin(); it != m_adj_matrix.end(); ++it) {
    Edge edge(it->m_row,it->m_col,it->m_value);
    // edge.m_vertex_row = it->m_row;
    // edge.m_vertex_col = it->m_col;
    // edge.m_weight = it->m_value;

    edges.Push(edge);
    
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
 * @return int              返回-1说明图是无向图或者给出的序号超出范围
 * *****************************************************************
 */
template <typename T, typename E>
inline int AdjMatrixGraph<T, E>::GetInDegree(int vertex) const {

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
inline int AdjMatrixGraph<T, E>::GetOutDegree(int vertex) const {
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
 * @brief : 清空图中的所有顶点和边
 * @tparam T
 * @tparam E
 * *****************************************************************
 */
template <typename T, typename E>
inline void AdjMatrixGraph<T, E>::Clear() {
  delete[] m_vertexs;
  m_adj_matrix.Clear();
}

} // namespace bu_tools

#endif // _ADJMATRIXGRAPH_H_
