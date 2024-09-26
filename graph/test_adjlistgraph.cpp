/**
 * ************************************************************************
 * @filename: test_adjlistgraph.cpp
 * 
 * @brief : 测试邻接表图类
 * 
 * 
 * @author : baiyebzx (baiyebzx1228@gmail.com)
 * @date : 2024-09-25
 * 
 * ************************************************************************
 */

#include "../matrix/tuple/tripletsparsematrix.h"
#include "adjlistgraph.h"
#include <iomanip>
#include <iostream>

// using std::cin;
using std::cout;
using std::setw;

void PrintVertex(const char &vertex) {
  cout << vertex << " ";
}

void test_Floyd();
void PrintPath(int start, int end, int **path);
 void test_Dijkstra();
 void test_TopologicalSort();
 void test_Prim();
void test_Kruskal();

/////////////////////////////////////////////////////////////////////////////////////////////////////
/*

主函数

*/
/////////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, const char* argv[]) {
   //test_Dijkstra();
   //test_Floyd();
   //test_TopologicalSort();
  //test_Prim();
   test_Kruskal();

  return 0;
}

void test_Floyd(){
  // 假设我们有一个 4 个顶点的有向图
  int vertex_count = 5;
  bool is_directed = false;

  // 创建图对象
  bu_tools::AdjLsitgraph<char,int> graph(is_directed,vertex_count);

  graph.InsertVertex('A'); // 0
  graph.InsertVertex('B'); // 1
  graph.InsertVertex('C'); // 2
  graph.InsertVertex('D'); // 3
  graph.InsertVertex('E'); // 4

  graph.InsertEdge(0, 1, 10);
  graph.InsertEdge(0, 2, 5);
  graph.InsertEdge(3, 4, 2);
  graph.InsertEdge(2, 4, 3);
  graph.InsertEdge(1, 3, 1);
  graph.InsertEdge(3, 2, 2);

  // 动态分配 distance 和 path 数组
  int **distance = new int *[vertex_count];
  int **path = new int *[vertex_count];
  for (int i = 0; i < vertex_count; ++i) {
    distance[i] = new int[vertex_count];
    path[i] = new int[vertex_count];
  }

  // 调用 Floyd 算法
  graph.Floyd(distance, path);

  // 输出结果
  cout << "最短路径距离矩阵 (distance):\n";
  for (int i = 0; i < vertex_count; ++i) {
    for (int j = 0; j < vertex_count; ++j) {
      if (distance[i][j] == std::numeric_limits<int>::max()) {
        cout << "INF"
             << "\t"; // 无穷大表示没有路径
      } else {
        cout << distance[i][j] << "\t";
      }
    }
    cout << "\n";
  }

  cout << "\n路径矩阵 (path):\n";
  for (int i = 0; i < vertex_count; ++i) {
    for (int j = 0; j < vertex_count; ++j) {
      cout << path[i][j] << "\t";
    }
    cout << "\n";
  }

  // 打印从顶点 0 到顶点 3 的路径
  cout << "\nPath from A to D: ";
  PrintPath(0, 3, path);
  cout << "\n";

  // 释放动态分配的数组
  for (int i = 0; i < vertex_count; ++i) {
    delete[] distance[i];
    delete[] path[i];
  }
  delete[] distance;
  delete[] path;
}

void PrintPath(int start, int end, int **path){
  if (start == end) {
    cout << start << " "; // 输出起点
  } else if (path[start][end] == -1) {
    cout << "No path exists from " << start << " to " << end << "\n";
  } else {
    PrintPath(start, path[start][end], path); // 递归回溯前驱节点
    cout << end << " ";                       // 输出终点
  }
}

void test_Dijkstra(){
  // 假设我们有一个 4 个顶点的有向图
  int vertex_count = 5;
  bool is_directed = false;

  // 创建图对象
  bu_tools::AdjLsitgraph<char, int> graph(is_directed, vertex_count);

  graph.InsertVertex('A'); // 0
  graph.InsertVertex('B'); // 1
  graph.InsertVertex('C'); // 2
  graph.InsertVertex('D'); // 3
  graph.InsertVertex('E'); // 4

  graph.InsertEdge(0, 1, 10);
  graph.InsertEdge(0, 2, 5);
  graph.InsertEdge(3, 4, 2);
  graph.InsertEdge(2, 4, 3);
  graph.InsertEdge(1, 3, 1);
  graph.InsertEdge(3, 2, 2);

  int distance[5];

  graph.Dijkstra(0, distance);

  for (int i = 0; i < 5; i++) {
    char vertex;
    graph.GetVertexByIndex(i, vertex);
    cout << vertex << "  " << distance[i] << "\n";
  }
}

void test_TopologicalSort(){
  // 假设我们有一个 4 个顶点的有向图
  int vertex_count = 5;
  bool is_directed = true;

  // 创建图对象
  bu_tools::AdjLsitgraph<char, int> graph(is_directed, vertex_count);

  graph.InsertVertex('A'); // 0
  graph.InsertVertex('B'); // 1
  graph.InsertVertex('C'); // 2
  graph.InsertVertex('D'); // 3
  graph.InsertVertex('E'); // 4

  graph.InsertEdge(0, 1, 10);
  graph.InsertEdge(0, 2, 5);
  graph.InsertEdge(3, 4, 2);
  graph.InsertEdge(2, 4, 3);
  graph.InsertEdge(1, 3, 1);
  graph.InsertEdge(3, 2, 2);

  char *sorted_vertexs = new char[5];
  graph.TopologicalSort(sorted_vertexs);

  for (int i = 0; i < 5; ++i) {
    cout << sorted_vertexs[i] << " ";
  }
  cout << "\n";

  delete[] sorted_vertexs;
}

void test_Prim(){
  // 假设我们有一个 4 个顶点的有向图
  int vertex_count = 5;
  bool is_directed = false;

  // 创建图对象
  bu_tools::AdjLsitgraph<char, int> graph(is_directed, vertex_count);

  graph.InsertVertex('A'); // 0
  graph.InsertVertex('B'); // 1
  graph.InsertVertex('C'); // 2
  graph.InsertVertex('D'); // 3
  graph.InsertVertex('E'); // 4

  graph.InsertEdge(0, 1, 10);
  graph.InsertEdge(0, 2, 5);
  graph.InsertEdge(3, 4, 2);
  graph.InsertEdge(2, 4, 3);
  graph.InsertEdge(1, 3, 1);
  graph.InsertEdge(3, 2, 2);

  bu_tools::TripletSparseMatrix<int> matrix(vertex_count, vertex_count);

  graph.Prim(0,matrix);

  cout << "       行  "
       << "  列  "
       << " 值\n";
  int index = 0;
  for (auto it = matrix.begin(); it != matrix.end(); ++it) {
    cout << "[" << setw(2) << index << "]";
    cout << setw(5) << it->m_row;
    cout << setw(5) << it->m_col;
    cout << setw(6) << it->m_value;
    cout << "\n";
    ++index;
  }
}

void test_Kruskal(){
  // 假设我们有一个 4 个顶点的有向图
  int vertex_count = 5;
  bool is_directed = true;

  // 创建图对象
  bu_tools::AdjLsitgraph<char, int> graph(is_directed, vertex_count);

  graph.InsertVertex('A'); // 0
  graph.InsertVertex('B'); // 1
  graph.InsertVertex('C'); // 2
  graph.InsertVertex('D'); // 3
  graph.InsertVertex('E'); // 4

  graph.InsertEdge(0, 1, 10);
  graph.InsertEdge(0, 2, 5);
  graph.InsertEdge(3, 4, 2);
  graph.InsertEdge(2, 4, 3);
  graph.InsertEdge(1, 3, 1);
  graph.InsertEdge(3, 2, 2);

  bu_tools::TripletSparseMatrix<int> matrix(vertex_count, vertex_count);

  graph.Kruskal(matrix);

  cout << "       行  "
       << "  列  "
       << " 值\n";
  int index = 0;
  for (auto it = matrix.begin(); it != matrix.end(); ++it) {
    cout << "[" << setw(2) << index << "]";
    cout << setw(5) << it->m_row;
    cout << setw(5) << it->m_col;
    cout << setw(6) << it->m_value;
    cout << "\n";
    ++index;
  }
}