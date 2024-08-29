/**
 * ************************************************************************
 * @filename: test_singlylinklist.cpp
 *
 * @brief : 测试非循环单链表
 *
 *
 * @author : baiyebzx (baiyebzx1228@gmail.com)
 * @date : 2024-08-06
 *
 * ************************************************************************
 */

#include "polynomial.h"
#include "singlylinklist.h"
#include <iomanip>
#include <iostream>

using std::cin;
using std::cout;
using std::setw;

bu_tools::SinglyLinkList<int> L;
bu_tools::Polynomial P;

/////////////////////////////////////////////////////////////////////////////////////////////////////
/*

辅助函数

*/
/////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * *****************************************************************
 * @brief : 主菜单
 * *****************************************************************
 */
void Menu01() {
  cout << "************测 试 非 循 环 单 链 表 的 操 作************\n";
  cout << "          1.取非循环单链表的第i个结点\n";
  cout << "          2.在第i个结点之前插入一个数据域为e的结点\n";
  cout << "          3.判断非循环单链表是否为空\n";
  cout << "          4.求非循环单链表中结点个数\n";
  cout << "          5.查找第一个与e满足compare()关系的结点\n";
  cout << "          6.返回某结点前驱的数据域\n";
  cout << "          7.返回某结点后继的数据域\n";
  cout << "          8.删除非循环单链表中数据域为e的第一个结点\n";
  cout << "          9.删除非循环单链表中的重复值\n";
  cout << "         10.非循环单链表的逆置\n";
  cout << "         11.把一个非循环单链表赋值给另一个非循环单链表\n";
  cout << "         12.把非循环单链表置空\n";
  cout << "         13.随机生成非循环单链表\n";
  cout << "         14.用已有的非循环单链表初始化另一个非循环单链表\n";
  cout << "         15.输入非循环单链表\n";
  cout << "         16.多项式的运算(非循环单链表的应用)\n";
  cout << "         其他.结束\n";
  cout << "*******************************************************\n";
}

/**
 * *****************************************************************
 * @brief : 非循环单链表的应用菜单
 * *****************************************************************
 */
void Menu02() {
  cout << "********** 多项式的运算（非循环单链表的应该）**********\n";
  cout << "   16.1  判断多项式是否为空\n";
  cout << "   16.2  把一个多项式赋值给另一个多项式\n";
  cout << "   16.3  两个多项式的加法\n";
  cout << "   16.4  两个多项式的减法\n";
  cout << "   16.5  设置多项式为空多项式\n";
  cout << "   16.6  随机生成多项式\n";
  cout << "   16.7  用已有的多项式初始化另一个多项式\n";
  cout << "   16.8  输入多项式\n";
  cout << "   其他.   结束\n";
  cout << "***************************************************\n";
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
int GenerateRandomNumber01() {
  return rand() % 100;
}

/**
 * *****************************************************************
 * @brief :  生成-100到100之间的随机数
 * @return int
 * *****************************************************************
 */
int GenerateRandomNumber02() {
  // 生成-100到100之间的随机数
  return rand() % 201 - 100;
}

/**
 * *****************************************************************
 * @brief : 生成0-20之间的随机数
 * @return int
 * *****************************************************************
 */
int GenerateRandomNumber03() {
  // 生成-100到100之间的随机数
  return rand() % 20;
}

/**
 * *****************************************************************
 * @brief : 打印非循环单链表
 * @param  L
 * *****************************************************************
 */
void ShowSinglyLinkList(const bu_tools::SinglyLinkList<int> &L) {
  // 定义每行显示的最大元素数量
  const int elementsPerRow = 10;
  // 定义标号和元素的宽度
  const int labelWidth = 7;
  const int numberWidth = 5;

  int len = L.GetLength();
  int e;

  cout << "\n\n非循环单链表为：\n\n";

  for (int i = 0; i < len; i += elementsPerRow) {
    // 打印当前行的标号
    for (int j = i; j < i + elementsPerRow && j < len; ++j) {
      cout << "[" << setw(labelWidth - 2) << j + 1 << "] ";
    }
    cout << "\n";

    // 打印当前行的元素
    for (int j = i; j < i + elementsPerRow && j < len; ++j) {
      L.GetElem(j + 1, e);
      cout << setw(numberWidth - 1) << e << "  ";
      if (j + 1 < len) {
        cout << "->";
      } else {
        cout << "/\\";
      }
    }
    cout << "\n";
  }
}

/**
 * *****************************************************************
 * @brief : 随机生成一个指定长度的非循环单链表
 * @param  len
 * @param  L
 * *****************************************************************
 */
void InitSinglyLinkLIst(const int len, bu_tools::SinglyLinkList<int> &L) {
  if (len <= 0) {
    return;
  }

  for (int i = 0; i < len; ++i) {
    L.Append(GenerateRandomNumber01());
  }
}

/**
 * *****************************************************************
 * @brief : 随机生成多项式
 * @param  P                
 * *****************************************************************
 */
void randomPolynomial(bu_tools::Polynomial &P) {
  int n = GenerateRandomNumber03();

  bu_tools::Term temp_t;
  for (int i = 0; i < n; ++i) {
    temp_t.m_coef = GenerateRandomNumber02();
    temp_t.m_expn = GenerateRandomNumber03();

    P.AddTerm(temp_t);
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
/*

主函数

*/
/////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, const char *argv[]) {

  //随机生成一个15长度的非循环单链表
  InitRandomSeed();
  InitSinglyLinkLIst(15, L);

  /*****************************************************************

  主循环

  *****************************************************************/
  while (true) {

    //主菜单操作标号
    int menu01_select;
    //单个操作是否再次执行标号
    char is_continue;

    //主菜单
    Menu01();
    //展示当前非循环单链表
    ShowSinglyLinkList(L);

    cout << "\n请选择你要操作的代码<1-15>：";
    cin >> menu01_select;

    if (menu01_select == 1) {
      /*****************************************************************

      1.取非循环单链表的第i个结点

      *****************************************************************/

      //整个操作的循环
      while (true) {

        // 清空终端屏幕
        cout << "\033[2J\033[1;1H";
        //展示当前顺序表
        ShowSinglyLinkList(L);

        //输入操作循环
        while (true) {
          int index, e;
          cout << "\n请输入你要取的结点的序号：";
          cin >> index;

          if (!L.GetElem(index, e)) {
            cout << "\n输入的内容存在错误，检查是否越界，重新输入！！！！\n";
            cout << "请在下面重新输入：\n\n";
          } else {
            cout << "\n你要取的非循环单链表的第" << index << "个结点的数据域为：" << e << "\n";
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
    } else if (menu01_select == 2) {
      /*****************************************************************

      2.在第i个结点之前插入一个数据域为e的结点

      *****************************************************************/
      //整个操作的循环
      while (true) {

        // 清空终端屏幕
        cout << "\033[2J\033[1;1H";
        //展示当前顺序表
        ShowSinglyLinkList(L);

        //输入操作循环
        while (true) {
          int index, e;
          cout << "\n请输入你要取的结点的序号：";
          cin >> index;
          cout << "请输入你要插入结点的数据域：";
          cin >> e;

          if (!L.Insert(index, e)) {
            cout << "\n输入的内容存在错误，检查是否越界，重新输入！！！！\n";
            cout << "请在下面重新输入：\n\n";
          } else {
            cout << "\n你已经在第" << index << "个结点插入数据域为 " << e << " 的结点\n";
            ShowSinglyLinkList(L);
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

    } else if (menu01_select == 3) {
      /*****************************************************************

      3.判断非循环单链表是否为空

      *****************************************************************/
      //整个操作的循环
      while (true) {

        // 清空终端屏幕
        cout << "\033[2J\033[1;1H";
        //展示当前顺序表
        ShowSinglyLinkList(L);

        if (L.IsEmpty()) {
          cout << "\n当前非循环单链表为空！！！\n";
        } else {
          cout << "\n当前非循环单链表不为空！！！\n";
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

    } else if (menu01_select == 4) {
      /*****************************************************************

      4.求非循环单链表中结点个数

      *****************************************************************/
      //整个操作的循环
      while (true) {

        // 清空终端屏幕
        cout << "\033[2J\033[1;1H";
        //展示当前顺序表
        ShowSinglyLinkList(L);

        cout << "\n非循环单链表中结点个数：" << L.GetLength() << "\n";

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

      5.查找第一个与e满足compare()关系的结点

      *****************************************************************/

      //整个操作的循环
      while (true) {

        // 清空终端屏幕
        cout << "\033[2J\033[1;1H";
        //展示当前顺序表
        ShowSinglyLinkList(L);

        int e;
        int index; //获取的符合条件的序号

        // equal输入操作
        cout << "\n查找等于某个结点的操作。\n";
        cout << "请输入你想要查找的结点：";
        cin >> e;

        index = L.LocateElem(e, bu_tools::Equal);

        if (index) {
          cout << "数据域等于" << e << "的第一个结点序号为：" << index << "\n";
        } else {
          cout << "没有查找到符合条件的结点序号！！！\n\n";
        }

        // bigger输入操作
        cout << "\n查找大于某个结点的操作。\n";
        cout << "请输入你想要查找的结点：";
        cin >> e;

        index = L.LocateElem(e, bu_tools::Bigger);

        if (index) {
          cout << "数据域大于" << e << "的第一个结点序号为：" << index << "\n";
        } else {
          cout << "没有查找到符合条件的结点序号！！！\n\n";
        }

        // smaller输入操作
        cout << "\n查找小于某个结点的操作。\n";
        cout << "请输入你想要查找的结点：";
        cin >> e;

        index = L.LocateElem(e, bu_tools::Smaller);

        if (index) {
          cout << "数据域小于" << e << "的第一个结点序号为：" << index << "\n";
        } else {
          cout << "没有查找到符合条件的结点序号！！！\n\n";
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
      /*****************************************************************

      6.返回某结点前驱的数据域

      *****************************************************************/

      //整个操作的循环
      while (true) {

        // 清空终端屏幕
        cout << "\033[2J\033[1;1H";
        //展示当前顺序表
        ShowSinglyLinkList(L);

        int e, prior_e;
        cout << "\n请输入你要查找结点的数据域：";
        cin >> e;

        if (L.PriorElem(e, prior_e)) {
          cout << "你想查找" << e << "前驱的数据域为：" << prior_e << "\n";
        } else {
          cout << "没有符合要求的结点！！！\n\n";
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
      /*****************************************************************

      7.返回某结点后继的数据域

      *****************************************************************/
      //整个操作的循环
      while (true) {

        // 清空终端屏幕
        cout << "\033[2J\033[1;1H";
        //展示当前顺序表
        ShowSinglyLinkList(L);

        int e, next_e;
        cout << "\n请输入你要查找结点的数据域：";
        cin >> e;

        if (L.NextElem(e, next_e)) {
          cout << "你想查找" << e << "后继的数据域为：" << next_e << "\n";
        } else {
          cout << "没有符合要求的结点！！！\n\n";
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
      /*****************************************************************

      8.删除非循环单链表中数据域为e的第一个结点

      *****************************************************************/
      //整个操作的循环
      while (true) {

        // 清空终端屏幕
        cout << "\033[2J\033[1;1H";
        //展示当前顺序表
        ShowSinglyLinkList(L);

        int e;
        cout << "\n请输入你想删除结点的数据域：";
        cin >> e;

        if (L.DeleteElem(e)) {
          cout << "\n如下是删除后的非循环单链表：\n";
          ShowSinglyLinkList(L);
        } else {
          cout << "\n没有找到你想删除的结点！！！\n";
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
      /*****************************************************************

      9.删除非循环单链表中的重复值

      *****************************************************************/
      //整个操作的循环
      while (true) {

        // 清空终端屏幕
        cout << "\033[2J\033[1;1H";
        //展示当前顺序表
        ShowSinglyLinkList(L);

        L.DeleteRepeat();
        cout << "\n删除非循环单链表重复值后：\n";
        ShowSinglyLinkList(L);

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
      /*****************************************************************

      10.非循环单链表的逆置

      *****************************************************************/
      //整个操作的循环
      while (true) {

        // 清空终端屏幕
        cout << "\033[2J\033[1;1H";
        //展示当前顺序表
        ShowSinglyLinkList(L);

        L.Reverse();
        cout << "\n非循环单链表逆置后如下：\n";
        ShowSinglyLinkList(L);

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
      /*****************************************************************

      11.把一个非循环单链表赋值给另一个非循环单链表

      *****************************************************************/
      //整个操作的循环
      while (true) {

        // 清空终端屏幕
        cout << "\033[2J\033[1;1H";
        //展示当前顺序表
        ShowSinglyLinkList(L);

        bu_tools::SinglyLinkList<int> other_L;
        InitSinglyLinkLIst(5, other_L);
        cout << "\n另一个非循环单链表如下：\n";
        ShowSinglyLinkList(other_L);

        L = other_L;
        cout << "\n把另一个非循环单链表赋值给当前非循环单链表，当前非循环单链表如下：\n";
        ShowSinglyLinkList(L);

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
      /*****************************************************************

      12.把非循环单链表置空

      *****************************************************************/
      //整个操作的循环
      while (true) {

        // 清空终端屏幕
        cout << "\033[2J\033[1;1H";
        //展示当前顺序表
        ShowSinglyLinkList(L);

        L.Clear();
        cout << "\n当前非循环单链表置空后，结点个数为：" << L.GetLength() << "\n";

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
      /*****************************************************************

      13.随机生成非循环单链表

      *****************************************************************/
      //整个操作的循环
      while (true) {

        // 清空终端屏幕
        cout << "\033[2J\033[1;1H";
        //展示当前顺序表
        ShowSinglyLinkList(L);

        cout << "\n随机生成一个新的非循环单链表。。。\n";
        L.Clear();

        InitSinglyLinkLIst(12, L);

        //展示当前顺序表
        ShowSinglyLinkList(L);

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
      /*****************************************************************

      14.用已有的非循环单链表初始化另一个非循环单链表

      *****************************************************************/
      //整个操作的循环
      while (true) {

        // 清空终端屏幕
        cout << "\033[2J\033[1;1H";
        //展示当前顺序表
        ShowSinglyLinkList(L);

        bu_tools::SinglyLinkList<int> other_L(L);
        cout << "\n当前非循环单链表初始化另一个非循环单链表，另一个非循环单链表如下:\n";
        ShowSinglyLinkList(other_L);

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
      /*****************************************************************

      15.输入非循环单链表

      *****************************************************************/
      //整个操作的循环
      while (true) {

        // 清空终端屏幕
        cout << "\033[2J\033[1;1H";
        //清空当前非循环单链表
        L.Clear();

        int e;
        std::string input;

        int i = 1;
        //输入操作循环
        while (true) {
          cout << "\n请输入第" << i << "个结点的数据(输入不为数字结束)：";
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

        ShowSinglyLinkList(L);

        //是否再次进行该操作
        cout << "\n还继续吗？<Y.继续   N.结束>:";
        cin >> is_continue;
        if (is_continue == 'Y' || is_continue == 'y') {
          continue;
        } else {
          break;
        }
      }
    } else if (menu01_select == 16) {
      /*****************************************************************

      16.多项式的运算(非循环单链表的应用)

      *****************************************************************/
      // 清空终端屏幕
      cout << "\033[2J\033[1;1H";
      //应用菜单操作标号
      int menu02_select;

      randomPolynomial(P);

      /*****************************************************************

      多项式主循环

      *****************************************************************/
      while (true) {

        // 清空终端屏幕
        cout << "\033[2J\033[1;1H";

        //多项式菜单
        Menu02();

        //展示当前多项式

        cout << P;

        cout << "\n请选择你要操作的代码<1-8>:";
        cin >> menu02_select;

        if (menu02_select == 1) {
          /*****************************************************************

          16.1  判断多项式是否为空

          *****************************************************************/
          //整个操作的循环
          while (true) {

            // 清空终端屏幕
            cout << "\033[2J\033[1;1H";
            cout << P;

            if (P.IsEmpty()) {
              cout << "\n当前多项式为空！！！\n";
            } else {
              cout << "\n当前多项式不为空！！！\n";
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

        } else if (menu02_select == 2) {
          /*****************************************************************

          16.2  把一个多项式赋值给另一个多项式

          *****************************************************************/
          //整个操作的循环
          while (true) {

            // 清空终端屏幕
            cout << "\033[2J\033[1;1H";
            cout << P;

            bu_tools::Polynomial other_P;
            randomPolynomial(other_P);
            cout << "\n另一个多项式如下：\n";
            cout << other_P;

            cout << "\n另一个多项式赋值给当前多项式为：\n";
            P = other_P;
            cout << P;

            //是否再次进行该操作
            cout << "\n还继续吗？<Y.继续   N.结束>:";
            cin >> is_continue;
            if (is_continue == 'Y' || is_continue == 'y') {
              continue;
            } else {
              break;
            }
          }

        } else if (menu02_select == 3) {
          /*****************************************************************

          16.3  两个多项式的加法

          *****************************************************************/
          //整个操作的循环
          while (true) {

            // 清空终端屏幕
            cout << "\033[2J\033[1;1H";
            cout << P;

            bu_tools::Polynomial other_P;
            randomPolynomial(other_P);
            cout << "\n另一个多项式如下：\n";
            cout << other_P;

            cout << "\n以上两个多项式相加，和为：\n";
            P = P + other_P;
            cout << P;

            //是否再次进行该操作
            cout << "\n还继续吗？<Y.继续   N.结束>:";
            cin >> is_continue;
            if (is_continue == 'Y' || is_continue == 'y') {
              continue;
            } else {
              break;
            }
          }
        } else if (menu02_select == 4) {
          /*****************************************************************

          16.4  两个多项式的减法

          *****************************************************************/
          //整个操作的循环
          while (true) {

            // 清空终端屏幕
            cout << "\033[2J\033[1;1H";
            cout << P;

            bu_tools::Polynomial other_P;
            randomPolynomial(other_P);
            cout << "\n另一个多项式如下：\n";
            cout << other_P;

            cout << "\n以上两个多项式相减，差为：\n";
            P = P - other_P;
            cout << P;

            //是否再次进行该操作
            cout << "\n还继续吗？<Y.继续   N.结束>:";
            cin >> is_continue;
            if (is_continue == 'Y' || is_continue == 'y') {
              continue;
            } else {
              break;
            }
          }
        } else if (menu02_select == 5) {
          /*****************************************************************

          16.5  设置多项式为空多项式

          *****************************************************************/
          //整个操作的循环
          while (true) {

            // 清空终端屏幕
            cout << "\033[2J\033[1;1H";
            cout << P;

            P.Clear();
            cout << "\n已经将当前多项式设置为空！！！\n";

            cout << P;

            //是否再次进行该操作
            cout << "\n还继续吗？<Y.继续   N.结束>:";
            cin >> is_continue;
            if (is_continue == 'Y' || is_continue == 'y') {
              continue;
            } else {
              break;
            }
          }
        } else if (menu02_select == 6) {
          /*****************************************************************

          16.6  随机生成多项式

          *****************************************************************/
          //整个操作的循环
          while (true) {

            // 清空终端屏幕
            cout << "\033[2J\033[1;1H";
            cout << P;

            P.Clear();

            randomPolynomial(P);

            cout << "\n随机生成多项式(采用非循环单链表)如下：\n";
            cout << P;

            //是否再次进行该操作
            cout << "\n还继续吗？<Y.继续   N.结束>:";
            cin >> is_continue;
            if (is_continue == 'Y' || is_continue == 'y') {
              continue;
            } else {
              break;
            }
          }
        } else if (menu02_select == 7) {
          /*****************************************************************

          16.7  用已有的多项式初始化另一个多项式

          *****************************************************************/
          //整个操作的循环
          while (true) {

            // 清空终端屏幕
            cout << "\033[2J\033[1;1H";
            cout << P;

            bu_tools::Polynomial other_P(P);

            cout << "\n用当前多项式初始化另一个多项式如下：\n";
            cout << other_P;

            //是否再次进行该操作
            cout << "\n还继续吗？<Y.继续   N.结束>:";
            cin >> is_continue;
            if (is_continue == 'Y' || is_continue == 'y') {
              continue;
            } else {
              break;
            }
          }
        } else if (menu02_select == 8) {
          /*****************************************************************

          16.8  输入多项式

          *****************************************************************/
          //整个操作的循环
          while (true) {

            // 清空终端屏幕
            cout << "\033[2J\033[1;1H";
            P.Clear();

            cin >> P;

            cout << P;

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
      }

    } else {
      break;
    }

    // 清空终端屏幕
    cout << "\033[2J\033[1;1H";
  }

  return 0;
}