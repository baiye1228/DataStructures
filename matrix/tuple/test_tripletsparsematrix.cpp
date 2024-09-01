/**
 * ************************************************************************
 * @filename: test_tripletsparsematrix.cpp
 *
 * @brief : 测试稀疏矩阵（三元组）
 *
 *
 * @author : baiyebzx (baiyebzx1228@gmail.com)
 * @date : 2024-08-30
 *
 * ************************************************************************
 */

#include "tripletsparsematrix.h"
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
int GenerateRandomNumber(int min, int max) ;
void ShowMatrixTriplet(const bu_tools::TripletSparseMatrix<int> &matrix);
void InitMatrix(bu_tools::TripletSparseMatrix<int> &matrix);
void ShowMatrix(const bu_tools::TripletSparseMatrix<int> &matrix);

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

  bu_tools::TripletSparseMatrix<int> matrix(init_row, init_col);
  bu_tools::TripletSparseMatrix<int> other_matrix(init_row, init_col);

  //专门接收结果
  bu_tools::TripletSparseMatrix<int> result_matrix(0, 0);

  InitMatrix(matrix);

  /*****************************************************************

  主循环

  *****************************************************************/
  while (true) {

    //主菜单
    Menu01();
    //展示矩阵
    ShowMatrix(matrix);

    cout << "\n请选择你要操作的代码<1-9>：";
    cin >> menu01_select;

    if (menu01_select == 1) {
      /*****************************************************************

      1.求稀疏矩阵的转置矩阵

      *****************************************************************/
      //整个操作的循环
      while (true) {

        // 清空终端屏幕
        cout << "\033[2J\033[1;1H";
        ShowMatrix(matrix);

        matrix.Transpose(other_matrix);
        cout << "\n当前稀疏矩阵的转置矩阵如下：\n";
        ShowMatrix(other_matrix);

        //是否再次进行该操作
        cout << "\n还继续吗？<Y.继续   N.结束>:";
        cin >> is_continue;
        if (is_continue == 'Y' || is_continue == 'y') {
          continue;
        } else {
          break;
        }
      }

    } else if (menu01_select == 2) {
      /*****************************************************************

      2.快速求稀疏矩阵的转置矩阵

      *****************************************************************/
      //整个操作的循环
      while (true) {

        // 清空终端屏幕
        cout << "\033[2J\033[1;1H";
        ShowMatrix(matrix);
        // ShowMatrixTriplet(matrix);

        matrix.TransposeFast(other_matrix);
        cout << "\n当前稀疏矩阵的转置矩阵如下：\n";
        ShowMatrix(other_matrix);
        // ShowMatrixTriplet(other_matrix);

        //是否再次进行该操作
        cout << "\n还继续吗？<Y.继续   N.结束>:";
        cin >> is_continue;
        if (is_continue == 'Y' || is_continue == 'y') {
          continue;
        } else {
          break;
        }
      }
    } else if (menu01_select == 3) {
      /*****************************************************************

      3.稀疏矩阵的赋值运算

      *****************************************************************/
      //整个操作的循环
      while (true) {

        // 清空终端屏幕
        cout << "\033[2J\033[1;1H";
        ShowMatrix(matrix);

        bu_tools::TripletSparseMatrix<int> other_matrix2(GenerateRandomNumber(1, 11), GenerateRandomNumber(1, 11));
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
    } else if (menu01_select == 4) {
      /*****************************************************************

      4.求稀疏矩阵的加法

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
    } else if (menu01_select == 5) {
      /*****************************************************************

      5.求稀疏矩阵的乘法

      *****************************************************************/
      //整个操作的循环
      while (true) {

        // 清空终端屏幕
        cout << "\033[2J\033[1;1H";
        ShowMatrix(matrix);

        bu_tools::TripletSparseMatrix<int> other_matrix2(init_col, init_row);

        InitMatrix(other_matrix2);

        cout << "\n另一个稀疏矩阵如下：\n";
        ShowMatrix(other_matrix2);

        result_matrix = matrix * other_matrix2;
        cout << "\n两个稀疏矩阵的乘积如下：\n";
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
    } else if (menu01_select == 6) {
      /*****************************************************************

      6.显示稀疏矩阵的三元组表示

      *****************************************************************/
      //整个操作的循环
      while (true) {

        // 清空终端屏幕
        cout << "\033[2J\033[1;1H";
        ShowMatrix(matrix);

        ShowMatrixTriplet(matrix);

        //是否再次进行该操作
        cout << "\n还继续吗？<Y.继续   N.结束>:";
        cin >> is_continue;
        if (is_continue == 'Y' || is_continue == 'y') {
          continue;
        } else {
          break;
        }
      }
    } else if (menu01_select == 7) {
      /*****************************************************************

      7.随机生成稀疏矩阵

      *****************************************************************/
      //整个操作的循环
      while (true) {

        // 清空终端屏幕
        cout << "\033[2J\033[1;1H";
        ShowMatrix(matrix);

        bu_tools::TripletSparseMatrix<int> other_matrix2(GenerateRandomNumber(1, 10), GenerateRandomNumber(1, 10));
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
    } else if (menu01_select == 8) {
      /*****************************************************************

      8.用已有的稀疏矩阵初始化一个新矩阵

      *****************************************************************/
      //整个操作的循环
      while (true) {

        // 清空终端屏幕
        cout << "\033[2J\033[1;1H";
        ShowMatrix(matrix);

        bu_tools::TripletSparseMatrix<int> matrix2(matrix);

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
    } else if (menu01_select == 9) {
      /*****************************************************************

      9.输入稀疏矩阵的三元组表

      *****************************************************************/
      //整个操作的循环
      while (true) {

        // 清空终端屏幕
        cout << "\033[2J\033[1;1H";
        int my_rows, my_cols, my_total;
        cout << "\n输入你要构建稀疏矩阵的行数：";
        cin >> my_rows;
        cout << "\n输入你要构建稀疏矩阵的列数：";
        cin >> my_cols;
        cout << "\n输入你要构建稀疏矩阵非零元素的个数：";
        cin >> my_total;

        bu_tools::TripletSparseMatrix<int> matrix2(my_rows, my_cols);

        int my_row, my_col, my_value;
        for (int i = 0; i < my_total; ++i) {
          cout << "\n第" << i + 1 << "个元素：\n";
          cout << "行：";
          cin >> my_row;
          cout << "列：";
          cin >> my_col;
          cout << "值：";
          cin >> my_value;
        }

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
    } else {
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
  cout << "********** 测 试 稀 疏 矩 阵 的 操 作（三元组存储）**********\n";
  cout << "         1.求稀疏矩阵的转置矩阵\n";
  cout << "         2.快速求稀疏矩阵的转置矩阵\n";
  cout << "         3.稀疏矩阵的赋值运算\n";
  cout << "         4.求稀疏矩阵的加法\n";
  cout << "         5.求稀疏矩阵的乘法\n";
  cout << "         6.显示稀疏矩阵的三元组表示\n";
  cout << "         7.随机生成稀疏矩阵\n";
  cout << "         8.用已有的稀疏矩阵初始化一个新矩阵\n";
  cout << "         9.输入稀疏矩阵的三元组表\n";
  cout << "         其他.结束\n";
  cout << "**********************************************************\n";
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
 * @brief : 展示稀疏矩阵，三元组
 * @param  matrix
 * *****************************************************************
 */
void ShowMatrixTriplet(const bu_tools::TripletSparseMatrix<int> &matrix) {
  cout << "\n稀疏矩阵三元组表示如下：\n";

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

/**
 * *****************************************************************
 * @brief : 随机生成一个稀疏矩阵
 * @param  matrix
 * *****************************************************************
 */
void InitMatrix(bu_tools::TripletSparseMatrix<int> &matrix) {
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

/**
 * *****************************************************************
 * @brief : 打印矩阵
 * @param  matrix
 * *****************************************************************
 */
void ShowMatrix(const bu_tools::TripletSparseMatrix<int> &matrix) {
  int rows = matrix.GetRows();
  int cols = matrix.GetCols();

  cout << "\n稀疏矩阵（采用三元组表顺序存储）如下：\n";

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
