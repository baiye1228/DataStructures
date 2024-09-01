/**
 * ************************************************************************
 * @filename: test_crosssparsematrix.cpp
 *
 * @brief : 测试稀疏矩阵（十字链表）
 *
 *
 * @author : baiyebzx (baiyebzx1228@gmail.com)
 * @date : 2024-09-01
 *
 * ************************************************************************
 */

#include "crosssparsematrix.h"
#include <iomanip>
#include <iostream>

using std::cin;
using std::cout;
using std::setw;

/////////////////////////////////////////////////////////////////////////////////////////////////////
/*

辅助函数

*/
/////////////////////////////////////////////////////////////////////////////////////////////////////

void Menu01();
void InitRandomSeed();
int GenerateRandomNumber(int min, int max);
void ShowMatrix(const bu_tools::CrossSparseMatrix<int> &matrix);
void InitMatrix(bu_tools::CrossSparseMatrix<int> &matrix);

/////////////////////////////////////////////////////////////////////////////////////////////////////
/*

主函数

*/
/////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, const char *argv[]) {

  //主菜单操作标号
  int menu01_select = 0;
  //单个操作是否再次执行标号
  char is_continue;

  InitRandomSeed();
  int init_row = GenerateRandomNumber(1, 10);
  int init_col = GenerateRandomNumber(1, 10);

  bu_tools::CrossSparseMatrix<int> matrix(init_row, init_col);
  bu_tools::CrossSparseMatrix<int> other_matrix(init_row, init_col);

  //专门接收结果
  bu_tools::CrossSparseMatrix<int> result_matrix(0, 0);

  InitMatrix(matrix);

  /*****************************************************************

  主循环

  *****************************************************************/

  while (true) {

    //主菜单
    Menu01();
    //展示矩阵
    ShowMatrix(matrix);

    cout << "\n请选择你要操作的代码<1-4>：";
    cin >> menu01_select;

    if (menu01_select == 1) {
      /*****************************************************************

      1.稀疏矩阵的赋值运算

      *****************************************************************/
      //整个操作的循环
      while (true) {

        // 清空终端屏幕
        cout << "\033[2J\033[1;1H";
        ShowMatrix(matrix);

        bu_tools::CrossSparseMatrix<int> other_matrix2(GenerateRandomNumber(1, 11), GenerateRandomNumber(1, 11));
        InitMatrix(other_matrix2);

        cout << "\n另一个稀疏矩阵如下：\n";
        ShowMatrix(other_matrix2);

        matrix = other_matrix2;
        cout << "\n另一个稀疏矩阵赋值给当前矩阵为：\n";
        ShowMatrix(matrix);

        //是否再次进行该操作
        cout << "\n还继续吗？<Y.继续   N.结束>:";
        cin >> is_continue;
        if (is_continue == 'Y' || is_continue == 'y') {
          continue;
        } else {
          break;
        }
      }

    } else if(menu01_select==2){
      /*****************************************************************

      2.求稀疏矩阵的加法

      *****************************************************************/
      //整个操作的循环
      while (true) {

        // 清空终端屏幕
        cout << "\033[2J\033[1;1H";
        ShowMatrix(matrix);

        InitMatrix(other_matrix);

        cout << "\n另一个稀疏矩阵如下：\n";
        ShowMatrix(other_matrix);

        result_matrix = matrix + other_matrix;
        cout << "\n两个稀疏矩阵相加的和如下：\n";
        ShowMatrix(result_matrix);

        //是否再次进行该操作
        cout << "\n还继续吗？<Y.继续   N.结束>:";
        cin >> is_continue;
        if (is_continue == 'Y' || is_continue == 'y') {
          continue;
        } else {
          break;
        }
      }
    }else if(menu01_select==3){
      /*****************************************************************

      3.随机生成稀疏矩阵

      *****************************************************************/
      //整个操作的循环
      while (true) {

        // 清空终端屏幕
        cout << "\033[2J\033[1;1H";
        ShowMatrix(matrix);

        bu_tools::CrossSparseMatrix<int> other_matrix2(GenerateRandomNumber(1, 10), GenerateRandomNumber(1, 10));
        InitMatrix(other_matrix2);

        matrix = other_matrix2;

        cout << "\n新的稀疏矩阵如下：\n";
        ShowMatrix(matrix);

        //是否再次进行该操作
        cout << "\n还继续吗？<Y.继续   N.结束>:";
        cin >> is_continue;
        if (is_continue == 'Y' || is_continue == 'y') {
          continue;
        } else {
          break;
        }
      }

    }else if(menu01_select==4){
      /*****************************************************************

      4.用已有的稀疏矩阵初始化一个新矩阵

      *****************************************************************/
      //整个操作的循环
      while (true) {

        // 清空终端屏幕
        cout << "\033[2J\033[1;1H";
        ShowMatrix(matrix);

        bu_tools::CrossSparseMatrix<int> matrix2(matrix);

        cout << "\n当前稀疏矩阵初始化另一个稀疏矩阵如下：\n";
        ShowMatrix(matrix2);

        //是否再次进行该操作
        cout << "\n还继续吗？<Y.继续   N.结束>:";
        cin >> is_continue;
        if (is_continue == 'Y' || is_continue == 'y') {
          continue;
        } else {
          break;
        }
      }
    }
    else {
      break;
    }

    // 清空终端屏幕
    cout << "\033[2J\033[1;1H";
  }

  return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
/*

辅助函数的定义

*/
/////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * *****************************************************************
 * @brief : 主菜单
 * *****************************************************************
 */
void Menu01() {
  cout << "********** 测 试 稀 疏 矩 阵 的 操 作（十字链表存储）**********\n";
  cout << "         1.稀疏矩阵的赋值运算\n";
  cout << "         2.求稀疏矩阵的加法\n";
  cout << "         3.随机生成稀疏矩阵\n";
  cout << "         4.用已有的稀疏矩阵初始化一个新矩阵\n";
  cout << "         其他.结束\n";
  cout << "*************************************************************\n";
}

/**
 * *****************************************************************
 * @brief : 初始化随机数种子
 * *****************************************************************
 */
void InitRandomSeed() {
  srand(static_cast<unsigned>(time(0)));
}

/**
 * *****************************************************************
 * @brief : 生成0到99之间的随机数
 * @return int
 * *****************************************************************
 */
int GenerateRandomNumber(int min, int max) {
  return min + rand() % (max - min + 1);
}

/**
 * *****************************************************************
 * @brief : 展示整个矩阵
 * @param  matrix
 * *****************************************************************
 */
void ShowMatrix(const bu_tools::CrossSparseMatrix<int> &matrix) {
  int rows = matrix.GetRows();
  int cols = matrix.GetCols();

  cout << "\n稀疏矩阵（采用十字链表存储）如下：\n";

  //列标号
  cout << "       ";
  for (int i = 0; i < cols; ++i) {
    cout << " [" << setw(2) << i << "]  ";
  }
  cout << "\n";

  for (int i = 0; i < rows; ++i) {
    cout << " [" << setw(3) << i << "]  ";

    int e;
    for (int j = 0; j < cols; ++j) {

      if (!matrix.GetValue(i, j, e)) {
        e = 0;
      }

      cout << setw(3) << e << "    ";
    }
    cout << "\n";
  }
}

/**
 * *****************************************************************
 * @brief : 随机生成一个稀疏矩阵
 * @param  matrix
 * *****************************************************************
 */
void InitMatrix(bu_tools::CrossSparseMatrix<int> &matrix) {
  if (!matrix.IsEmpty()) {
    matrix.Clear();
  }

  int rows = matrix.GetRows();
  int cols = matrix.GetCols();

  int total;
  if (rows * cols <= 15) {
    total = GenerateRandomNumber(1, rows * cols);
  } else {
    total = GenerateRandomNumber(1, rows * cols / 2);
  }

  for (int i = 0; i < total; ++i) {
    matrix.Insert(GenerateRandomNumber(0, rows - 1), GenerateRandomNumber(0, cols - 1), GenerateRandomNumber(1, 100));
  }
}
