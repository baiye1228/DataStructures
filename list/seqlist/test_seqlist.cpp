/**
 * ************************************************************************
 * @filename: test_seqlist.cpp
 *
 * @brief : 测试顺序表
 *
 *
 * @author : baiyebzx (baiyebzx1228@gmail.com)
 * @date : 2024-08-06
 *
 * ************************************************************************
 */

#include "myseqlist.h"
#include "seqlist.h"
#include <cctype>
#include <cstdlib>
#include <ctime>
#include <iostream>

using std::cin;
using std::cout;

bu_tools::MySeqList L;

/****************************************************************************************************

外部函数

****************************************************************************************************/

/**
 * *****************************************************************
 * @brief : 主菜单
 * *****************************************************************
 */
void Menu01() {
  cout << "\n*************** 测 试 顺 序 表 操 作 ***************\n";
  cout << "         1.在第i个元素之前插入一个元素\n";
  cout << "         2.判断顺序表是否为空\n";
  cout << "         3.求顺序表中元素的个数\n";
  cout << "         4.取第i个元素\n";
  cout << "         5.查找第i个某元素满足compare()关系元素的符号\n";
  cout << "         6.返回某元素的前驱\n";
  cout << "         7.返回某元素的后继\n";
  cout << "         8.删除第i个元素\n";
  cout << "         9.把一个顺序表赋值给另一个顺序表\n";
  cout << "        10.把顺序表置空\n";
  cout << "        11.随机生成顺序表(元素值为0到99之间的整数)\n";
  cout << "        12.用已有的顺序表初始化另一个顺序表\n";
  cout << "        13.输入顺序表\n";
  cout << "        14.两个顺序表并交差运算\n";
  cout << "        15.学生信息管理(顺序表的应用)\n";
  cout << "       其他.结束\n";
  cout << "****************************************************\n";
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
int GenerateRandomNumber() {
  return rand() % 100;
}

/**
 * *****************************************************************
 * @brief : 包装顺序表输出
 * @param  L
 * *****************************************************************
 */
void ShowSeqList(const bu_tools::MySeqList &L) {
  cout << "\n当前顺序表有" << L.GetLength() << "个元素，分别为：\n";
  L.Show();
}

/**
 * *****************************************************************
 * @brief : 随机生成一个指定长度的顺序表
 * @param  len
 * @param  L
 * *****************************************************************
 */
void InitSeqList(const int len, bu_tools::MySeqList &L) {

  if (len <= 0) {
    return;
  }

  for (int i = 0; i < len; ++i) {
    L.Append(GenerateRandomNumber());
  }
}

/****************************************************************************************************

主函数

****************************************************************************************************/
int main(int argc, const char *argv[]) {

  //主菜单操作标号
  int menu01_select = 0;
  //单个操作是否再次执行标号
  char is_continue;

  //随机生成一个15长度的顺序表
  InitRandomSeed();
  InitSeqList(15, L);

  //主循环
  while (true) {

    //主菜单
    Menu01();
    //展示当前顺序表
    ShowSeqList(L);

    cout << "\n请选择你要操作的代码<1-15>：";
    cin >> menu01_select;

    if (menu01_select == 1) {

      /****************************************************************************************************

      1.在第i个元素之前插入一个元素

      ****************************************************************************************************/

      //整个操作的循环
      while (true) {

        // 清空终端屏幕
        cout << "\033[2J\033[1;1H";
        //展示当前顺序表
        ShowSeqList(L);

        //输入操作循环
        while (true) {
          int index = 0;
          cout << "请输入插入位置的序号：";
          cin >> index;

          int elem;
          cout << "请输入你要插入的元素值：";
          cin >> elem;

          if (!L.Insert(index, elem)) {
            cout << "输入的内容存在错误，重点检查是否越界，重新输入！！！！\n";
            cout << "请在下面重新输入：\n\n";
          } else {
            break;
          }
        }
        //展示当前顺序表
        ShowSeqList(L);

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
      /****************************************************************************************************

      2.判断顺序表是否为空\n";

      ****************************************************************************************************/

      //整个操作的循环
      while (true) {

        // 清空终端屏幕
        cout << "\033[2J\033[1;1H";
        //展示当前顺序表
        ShowSeqList(L);

        if (L.IsEmpty()) {
          cout << "\n\n当前顺序表为空！！！\n";
        } else {
          cout << "\n\n当前顺序表不为空！！！\n";
        }

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
      /****************************************************************************************************

      3.求顺序表中元素的个数

      ****************************************************************************************************/
      //整个操作的循环
      while (true) {

        // 清空终端屏幕
        cout << "\033[2J\033[1;1H";
        //展示当前顺序表
        ShowSeqList(L);

        cout << "\n顺序表元素的个数为：" << L.GetLength() << "\n";

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
      /****************************************************************************************************

      4.取第i个元素

      ****************************************************************************************************/
      //整个操作的循环
      while (true) {

        // 清空终端屏幕
        cout << "\033[2J\033[1;1H";
        //展示当前顺序表
        ShowSeqList(L);

        //输入操作循环
        while (true) {
          int index, elem;
          cout << "\n请输入你想取的元素的序号<1--" << L.GetLength() << ">:";
          cin >> index;

          if (!L.GetElem(index, elem)) {
            cout << "\n输入的内容存在错误，检查是否越界，重新输入！！！！\n";
            cout << "请在下面重新输入：\n\n";
          } else {
            cout << "\n你想取的第" << index << "个元素的值为：" << elem << "\n";
            break;
          }
        }

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
      /****************************************************************************************************

      5.查找第i个某元素满足compare()关系元素的符号

      ****************************************************************************************************/
      //整个操作的循环
      while (true) {

        // 清空终端屏幕
        cout << "\033[2J\033[1;1H";
        //展示当前顺序表
        ShowSeqList(L);

        int elem;
        int index; //获取的符合条件的序号

        // equal输入操作
        cout << "\n查找等于某个元素的操作。\n";
        cout << "请输入你想要查找的元素：";
        cin >> elem;

        index = L.LocateElem(elem, bu_tools::Equal);

        if (index) {
          cout << "你想要查找的第一个等于" << elem << "的元素的序号为：" << index << "\n";
        } else {
          cout << "没有查找到符合条件的元素序号！！！\n\n";
        }

        // bigger输入操作
        cout << "\n查找大于某个元素的操作。\n";
        cout << "请输入你想要查找的元素：";
        cin >> elem;

        index = L.LocateElem(elem, bu_tools::Bigger);

        if (index) {
          cout << "你想要查找的第一个大于" << elem << "的元素的序号为：" << index << "\n";
        } else {
          cout << "没有查找到符合条件的元素序号！！！\n\n";
        }

        // smaller输入操作
        cout << "\n查找小于某个元素的操作。\n";
        cout << "请输入你想要查找的元素：";
        cin >> elem;

        index = L.LocateElem(elem, bu_tools::Smaller);

        if (index) {
          cout << "你想要查找的第一个小于" << elem << "的元素的序号为：" << index << "\n";
        } else {
          cout << "没有查找到符合条件的元素序号！！！\n\n";
        }

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
      /****************************************************************************************************

      6.返回某元素的前驱

      ****************************************************************************************************/
      //整个操作的循环
      while (true) {

        // 清空终端屏幕
        cout << "\033[2J\033[1;1H";
        //展示当前顺序表
        ShowSeqList(L);

        int e, prior_e;
        cout << "\n请输入你要查找其前驱的元素：";
        cin >> e;

        if (L.PriorElem(e, prior_e)) {
          cout << "你想查找的元素" << e << "的前驱为：" << prior_e << "\n";
        } else {
          cout << "没有符合要求的元素！！！\n\n";
        }

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
      /****************************************************************************************************

      7.返回某元素的后继

      ****************************************************************************************************/
      //整个操作的循环
      while (true) {

        // 清空终端屏幕
        cout << "\033[2J\033[1;1H";
        //展示当前顺序表
        ShowSeqList(L);

        int e, next_e;
        cout << "\n请输入你要查找其后继的元素：";
        cin >> e;

        if (L.NextElem(e, next_e)) {
          cout << "你想查找的元素" << e << "的后继为：" << next_e << "\n";
        } else {
          cout << "没有符合要求的元素！！！\n\n";
        }

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
      /****************************************************************************************************

      8.删除第i个元素

      ****************************************************************************************************/

      //整个操作的循环
      while (true) {

        // 清空终端屏幕
        cout << "\033[2J\033[1;1H";
        //展示当前顺序表
        ShowSeqList(L);

        int index;
        int e;

        //输入操作循环
        while (true) {
          cout << "\n请输入你想删除元素的序号<1--" << L.GetLength() << ">:";
          cin >> index;

          if (L.DeleteElem(index, e)) {
            cout << "\n你想删除的第" << index << "个元素的值为：" << e << "\n";
            //展示当前顺序表
            ShowSeqList(L);
            break;
          } else {
            cout << "\n输入的序号越界！！！请重新输入！！！\n\n";
          }
        }

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
      /****************************************************************************************************

      9.把一个顺序表赋值给另一个顺序表

      ****************************************************************************************************/
      //整个操作的循环
      while (true) {

        // 清空终端屏幕
        cout << "\033[2J\033[1;1H";
        //展示当前顺序表
        ShowSeqList(L);

        bu_tools::MySeqList temp_L;
        //生成一个长度为3的顺序表
        InitSeqList(3, temp_L);

        cout << "\n另一个顺序表赋值给当前顺序表如下：\n";
        L = temp_L;

        //展示当前顺序表
        ShowSeqList(L);

        //是否再次进行该操作
        cout << "\n还继续吗？<Y.继续   N.结束>:";
        cin >> is_continue;
        if (is_continue == 'Y' || is_continue == 'y') {
          continue;
        } else {
          break;
        }
      }
    } else if (menu01_select == 10) {
      /****************************************************************************************************

      10.把顺序表置空

      ****************************************************************************************************/
      //整个操作的循环
      while (true) {

        // 清空终端屏幕
        cout << "\033[2J\033[1;1H";
        //展示当前顺序表
        ShowSeqList(L);

        L.Clear();

        cout << "\n当前顺序表置空后，元素的个数为：" << L.GetLength() << "\n";

        //是否再次进行该操作
        cout << "\n还继续吗？<Y.继续   N.结束>:";
        cin >> is_continue;
        if (is_continue == 'Y' || is_continue == 'y') {
          continue;
        } else {
          break;
        }
      }
    } else if (menu01_select == 11) {
      /****************************************************************************************************

      11.随机生成顺序表(元素值为0到99之间的整数)

      ****************************************************************************************************/
      //整个操作的循环
      while (true) {

        // 清空终端屏幕
        cout << "\033[2J\033[1;1H";
        //展示当前顺序表
        ShowSeqList(L);

        cout << "\n随机生成一个新的顺序表。。。\n";
        L.Clear();

        InitSeqList(15, L);

        //展示当前顺序表
        ShowSeqList(L);

        //是否再次进行该操作
        cout << "\n还继续吗？<Y.继续   N.结束>:";
        cin >> is_continue;
        if (is_continue == 'Y' || is_continue == 'y') {
          continue;
        } else {
          break;
        }
      }

    } else if (menu01_select == 12) {
      /****************************************************************************************************

      12.用已有的顺序表初始化另一个顺序表

      ****************************************************************************************************/
      //整个操作的循环
      while (true) {

        // 清空终端屏幕
        cout << "\033[2J\033[1;1H";
        //展示当前顺序表
        ShowSeqList(L);

        bu_tools::MySeqList temp_L(L);

        cout << "\n当前顺序表初始化另一个顺序表为：\n";

        //展示当前顺序表
        ShowSeqList(temp_L);

        //是否再次进行该操作
        cout << "\n还继续吗？<Y.继续   N.结束>:";
        cin >> is_continue;
        if (is_continue == 'Y' || is_continue == 'y') {
          continue;
        } else {
          break;
        }
      }

    } else if (menu01_select == 13) {
      //整个操作的循环
      while (true) {

        // 清空终端屏幕
        cout << "\033[2J\033[1;1H";
        //清空预先准备的顺序表
        L.Clear();

        int e;
        std::string input;

        int i = 1;
        //输入操作循环
        while (true) {
          cout << "\n请输入第" << i << "个元素(输入不为数字结束)：";
          cin >> input;

          bool is_num = true;
          for (auto c : input) {
            if (!std::isdigit(c)) {
              is_num = false;
              break;
            }
          }

          if (!is_num) {
            break;
          }

          e = std::stoi(input);
          L.Append(e);
          ++i;
        }

        cout << "\n你输入的顺序表如下：\n";
        //展示当前顺序表
        ShowSeqList(L);

        //是否再次进行该操作
        cout << "\n还继续吗？<Y.继续   N.结束>:";
        cin >> is_continue;
        if (is_continue == 'Y' || is_continue == 'y') {
          continue;
        } else {
          break;
        }
      }
    } else if (menu01_select == 14) {
      /****************************************************************************************************

      14.两个顺序表并交差运算

      ****************************************************************************************************/
      //整个操作的循环
      while (true) {

        // 清空终端屏幕
        cout << "\033[2J\033[1;1H";
        //展示当前顺序表
        ShowSeqList(L);

        bu_tools::MySeqList other_L, result_L;

        InitSeqList(5, other_L);

        cout << "\n另一个顺序表如下：\n";
        ShowSeqList(other_L);

        //全部排好序
        L.BubbleSort();
        other_L.BubbleSort();

        cout << "\n\n排序后当前顺序表：\n";
        ShowSeqList(L);
        cout << "\n\n排序后另一个顺序表：\n";
        ShowSeqList(other_L);

        //并集
        L.UnionSet(other_L, result_L);
        cout << "\n并集为：\n";
        ShowSeqList(result_L);

        //交集
        L.IntersectSet(other_L, result_L);
        cout << "\n交集为：\n";
        ShowSeqList(result_L);

        //差集
        L.DifferenceSet(other_L, result_L);
        cout << "\n差集为：\n";
        ShowSeqList(result_L);

        //是否再次进行该操作
        cout << "\n还继续吗？<Y.继续   N.结束>:";
        cin >> is_continue;
        if (is_continue == 'Y' || is_continue == 'y') {
          continue;
        } else {
          break;
        }
      }
    } else if (menu01_select == 15) {
      /****************************************************************************************************

      15.学生信息管理(顺序表的应用)

      ****************************************************************************************************/
    } else {
      break;
    }

    // 清空终端屏幕
    cout << "\033[2J\033[1;1H";
  }

  return 0;
}