/**
 * ************************************************************************
 * @filename: test_linkstack.cpp
 *
 * @brief : 测试链栈
 *
 *
 * @author : baiyebzx (baiyebzx1228@gmail.com)
 * @date : 2024-08-17
 *
 * ************************************************************************
 */

#include "linkstack.h"
//#include <iomanip>
#include <iostream>

using std::cin;
using std::cout;
//using std::setw;

bu_tools::LinkStack<int> S;

/////////////////////////////////////////////////////////////////////////////////////////////////////
/*

辅助函数

*/
/////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * *****************************************************************
 * @brief : 链栈测试主菜单
 * *****************************************************************
 */
void Menu01();

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
 * @brief : 随机生成指定长度的链栈
 * @param  len
 * @param  S
 * *****************************************************************
 */
void InitLinkStack(const int len, bu_tools::LinkStack<int> &S);

/**
 * *****************************************************************
 * @brief : 打印链栈
 * @param  S
 * *****************************************************************
 */
void ShowLinkStack(const bu_tools::LinkStack<int> &S);

/////////////////////////////////////////////////////////////////////////////////////////////////////
/*

主函数

*/
/////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, const char *argv[]) {
  //随机生成一个15长度的顺序表
  InitRandomSeed();
  InitLinkStack(5, S);

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

    //展示当前链栈
    ShowLinkStack(S);

    cout << "\n请选择你要操作的代码<1-10>：";
    cin >> menu01_select;

    if (menu01_select == 1) {
      /*****************************************************************

      1.在栈顶压入一个数据域为e的结点

      *****************************************************************/
      //整个操作的循环
      while (true) {

        // 清空终端屏幕
        cout << "\033[2J\033[1;1H";
        ShowLinkStack(S);

        int e;
        cout << "\n输入你要压入栈中的元素：";
        cin >> e;

        S.Push(e);
        cout<<"\n压栈后当前链栈如下：\n";
        ShowLinkStack(S);


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

      2.弹出栈顶结点

      *****************************************************************/
      //整个操作的循环
      while (true) {

        // 清空终端屏幕
        cout << "\033[2J\033[1;1H";
        ShowLinkStack(S);

        int e;
        if (S.Pop(e)) {
          cout << "\n弹出的栈顶元素为：" << e << "\n";
          ShowLinkStack(S);
        } else {
          cout << "\n栈空，无法再执行弹栈操作！！！\n";
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
    }else if(menu01_select==3){
      /*****************************************************************

      3.读栈顶结点的数据域

      *****************************************************************/
      //整个操作的循环
      while (true) {

        // 清空终端屏幕
        cout << "\033[2J\033[1;1H";
        ShowLinkStack(S);

        int e;
        if (S.GetTop(e)) {
          cout << "\n栈顶元素为：" << e << "\n";
          ShowLinkStack(S);
        } else {
          cout << "\n栈空，无法再执行弹栈操作！！！\n";
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
    }else if(menu01_select==4){
      /*****************************************************************

      4.判断链栈是否为空

      *****************************************************************/
      //整个操作的循环
      while (true) {

        // 清空终端屏幕
        cout << "\033[2J\033[1;1H";
        ShowLinkStack(S);

        if (S.IsEmpty()) {
          cout << "\n栈为空！！！\n";
        } else {
          cout << "\n栈不为空！！！\n";
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
    }else if(menu01_select==5){
      /*****************************************************************

      5.求链栈中结点个数

      *****************************************************************/
      //整个操作的循环
      while (true) {

        // 清空终端屏幕
        cout << "\033[2J\033[1;1H";
        ShowLinkStack(S);

        cout << "\n当前顺序栈中元素个数：" << S.GetLength() << "\n";

        //是否再次进行该操作
        cout << "\n还继续吗？<Y.继续   N.结束>:";
        cin >> is_continue;
        if (is_continue == 'Y' || is_continue == 'y') {
          continue;
        } else {
          break;
        }
      }
    }else if(menu01_select==6){
      /*****************************************************************

      6.把一个链栈赋值给另一个链栈

      *****************************************************************/
      //整个操作的循环
      while (true) {

        // 清空终端屏幕
        cout << "\033[2J\033[1;1H";
        ShowLinkStack(S);

        bu_tools::LinkStack<int> other_S;
        InitLinkStack(7, other_S);

        cout << "\n另一个链栈如下：\n";
        ShowLinkStack(other_S);

        S = other_S;
        cout << "\n另一个链栈赋值给当前链栈。。。。\n";
        ShowLinkStack(S);

        //是否再次进行该操作
        cout << "\n还继续吗？<Y.继续   N.结束>:";
        cin >> is_continue;
        if (is_continue == 'Y' || is_continue == 'y') {
          continue;
        } else {
          break;
        }
      }
    }else if(menu01_select==7){
      /*****************************************************************

      7.把链栈置空

      *****************************************************************/
      //整个操作的循环
      while (true) {

        // 清空终端屏幕
        cout << "\033[2J\033[1;1H";
        ShowLinkStack(S);

        S.Clear();

        cout << "\n置空后。。。\n";
        ShowLinkStack(S);

        //是否再次进行该操作
        cout << "\n还继续吗？<Y.继续   N.结束>:";
        cin >> is_continue;
        if (is_continue == 'Y' || is_continue == 'y') {
          continue;
        } else {
          break;
        }
      }
    }else if(menu01_select==8){
      /*****************************************************************

      8.随机生成链栈

      *****************************************************************/
      //整个操作的循环
      while (true) {

        // 清空终端屏幕
        cout << "\033[2J\033[1;1H";
        ShowLinkStack(S);

        cout << "\n重新随机生成一个顺序栈。。。。\n";
        InitLinkStack(7,S);

        ShowLinkStack(S);

        //是否再次进行该操作
        cout << "\n还继续吗？<Y.继续   N.结束>:";
        cin >> is_continue;
        if (is_continue == 'Y' || is_continue == 'y') {
          continue;
        } else {
          break;
        }
      }
    }else if(menu01_select==9){
      /*****************************************************************

      9.用已有的链栈初始化另一个链栈

      *****************************************************************/
      //整个操作的循环
      while (true) {

        // 清空终端屏幕
        cout << "\033[2J\033[1;1H";
        ShowLinkStack(S);

        bu_tools::LinkStack<int> other_S(S);
        cout << "\n当前顺序栈初始化另一个顺序栈如下：\n";

        ShowLinkStack(other_S);

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

void Menu01() {
  cout << "********** 测 试 链 栈 的 操 作 **********\n";
  cout << "     1.在栈顶压入一个数据域为e的结点\n";
  cout << "     2.弹出栈顶结点\n";
  cout << "     3.读栈顶结点的数据域\n";
  cout << "     4.判断链栈是否为空\n";
  cout << "     5.求链栈中结点个数\n";
  cout << "     6.把一个链栈赋值给另一个链栈\n";
  cout << "     7.把链栈置空\n";
  cout << "     8.随机生成链栈\n";
  cout << "     9.用已有的链栈初始化另一个链栈\n";
  cout << "    其他.结束\n";
  cout << "*****************************************\n";
}

void InitLinkStack(const int len, bu_tools::LinkStack<int> &S) {
  if (len <= 0) {
    return;
  }
  if (!S.IsEmpty()) {
    S.Clear();
  }

  for (int i = 0; i < len; ++i) {
    S.Push(GenerateRandomNumber());
  }
}

void ShowLinkStack(const bu_tools::LinkStack<int> &S) {
  if (S.IsEmpty()) {
    cout << "\n栈为空！！！\n";
    return;
  }

  cout << "\n链栈如下：\n";
  for(auto it=S.begin();it!=S.end();++it){
    cout << "[" << *it << "] -> ";
  }
  cout << "nullptr\n";
  cout << " ^\n";
  cout << " |\n";
  cout << "top\n";
}
