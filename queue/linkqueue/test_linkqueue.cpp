/**
 * ************************************************************************
 * @filename: test_linkqueue.cpp
 * 
 * @brief : 测试非循环链队
 * 
 * 
 * @author : baiyebzx (baiyebzx1228@gmail.com)
 * @date : 2024-08-28
 * 
 * ************************************************************************
 */

#include "linkqueue.h"
#include <iomanip>
#include <iostream>

using std::cout;
using std::cin;
using std::setw;


bu_tools::LinkQueue<int> Q;


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
 * @brief : 打印非循环链队
 * @param  q                
 * *****************************************************************
 */
void ShowLinkQueue(const bu_tools::LinkQueue<int>& q);


/**
 * *****************************************************************
 * @brief : 随机生成一个指定长度的非循环链队
 * @param  len              
 * @param  q                
 * *****************************************************************
 */
void InitLinkQueue(const int len,bu_tools::LinkQueue<int>& q);



/////////////////////////////////////////////////////////////////////////////////////////////////////
/*

主函数

*/
/////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, const char* argv[]) {

  //主菜单操作标号
  int menu01_select = 0;
  //单个操作是否再次执行标号
  char is_continue;

  //随机生成一个非循环链队列
  InitRandomSeed();
  InitLinkQueue(10,Q);


  /*****************************************************************
  
  主循环
  
  *****************************************************************/
  while(true){

    //主菜单
    Menu01();
    //展示当前循环顺序队列
    ShowLinkQueue(Q);

    cout << "\n请选择你要操作的代码<1-9>：";
    cin >> menu01_select;


    if(menu01_select==1){
      /*****************************************************************

      1.进队列（在非循环链队列队尾插入结点）

      *****************************************************************/
      //整个操作的循环
      while (true) {

        // 清空终端屏幕
        cout << "\033[2J\033[1;1H";
        ShowLinkQueue(Q);

        int e;
        cout << "\n请输入你要插入的元素：";
        cin >> e;

        if (Q.EnQueue(e)) {
          cout << "\n入队列后。。。。\n";
          ShowLinkQueue(Q);
        } else {
          cout << "\n队列已满，无法再次入队列！！！\n";
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
    }else if(menu01_select==2){
      /*****************************************************************

      2.出队列（删除非循环链队列队头元素）

      *****************************************************************/
      //整个操作的循环
      while (true) {

        // 清空终端屏幕
        cout << "\033[2J\033[1;1H";
        ShowLinkQueue(Q);

        int e;
        Q.DeQueue(e);

        cout << "\n删除队头元素" << e << "后。。。。\n";
        ShowLinkQueue(Q);

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

      3.读非循环链队列队头的元素到e

      *****************************************************************/
      //整个操作的循环
      while (true) {

        // 清空终端屏幕
        cout << "\033[2J\033[1;1H";
        ShowLinkQueue(Q);

        int e;

        if (Q.GetFront(e)) {
          cout << "\n队头元素为：" << e << "\n";
          ShowLinkQueue(Q);
        } else {
          cout << "\n队列为空，读取错误！！！\n";
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

      4.判断非循环链队列是否为空

      *****************************************************************/
      //整个操作的循环
      while (true) {

        // 清空终端屏幕
        cout << "\033[2J\033[1;1H";
        ShowLinkQueue(Q);

        if (Q.IsEmpty()) {
          cout << "\n队列为空！！！\n";
        } else {
          cout << "\n队列不为空！！！\n";
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

      5.求非循环链队列中元素的个数

      *****************************************************************/
      //整个操作的循环
      while (true) {

        // 清空终端屏幕
        cout << "\033[2J\033[1;1H";
        ShowLinkQueue(Q);

        cout << "\n队列中元素的个数为：" << Q.GetLength() << "\n";

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

      6.把一个非循环链队列赋值给另一个非循环链队列

      *****************************************************************/

      //整个操作的循环
      while (true) {

        // 清空终端屏幕
        cout << "\033[2J\033[1;1H";
        ShowLinkQueue(Q);

        bu_tools::LinkQueue<int> other_Q;
        InitLinkQueue(7, other_Q);

        cout << "\n另一个非循环链队列如下：\n";
        ShowLinkQueue(other_Q);

        Q = other_Q;
        cout << "\n另一个非循环链队列赋值给当前非循环链队列如下：\n";
        ShowLinkQueue(Q);

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

      7.把非循环链队列置空

      *****************************************************************/

      //整个操作的循环
      while (true) {

        // 清空终端屏幕
        cout << "\033[2J\033[1;1H";
        ShowLinkQueue(Q);

        Q.Clear();
        cout << "\n置空后。。。。\n";

        ShowLinkQueue(Q);

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

      8.随机生成非循环链队列

      *****************************************************************/
      //整个操作的循环
      while (true) {

        // 清空终端屏幕
        cout << "\033[2J\033[1;1H";
        ShowLinkQueue(Q);

        InitLinkQueue(7, Q);

        cout << "\n随机生成非循环链队列如下：\n";
        ShowLinkQueue(Q);

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

      9.用已有的非循环链队列初始化另一个新非循环链队列

      *****************************************************************/
      //整个操作的循环
      while (true) {

        // 清空终端屏幕
        cout << "\033[2J\033[1;1H";
        ShowLinkQueue(Q);

        bu_tools::LinkQueue<int> other_Q(Q);

        cout << "\n用当前非循环链队列初始化另一个非循环链队列如下：\n";
        ShowLinkQueue(other_Q);

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
    else{
        break;
    }

    // 清空终端屏幕
    cout << "\033[2J\033[1;1H";
  }

  return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
/*

辅助函数定义

*/
/////////////////////////////////////////////////////////////////////////////////////////////////////

void Menu01(){
  cout << "********** 测 试 非 循 环 链 队 列 操 作 **********\n";
  cout << "      1.进队列（在非循环链队列队尾插入结点）\n";
  cout << "      2.出队列（删除非循环链队列队头元素）\n";
  cout << "      3.读非循环链队列队头的元素到e\n";
  cout << "      4.判断非循环链队列是否为空\n";
  cout << "      5.求非循环链队列中元素的个数\n";
  cout << "      6.把一个非循环链队列赋值给另一个非循环链队列\n";
  cout << "      7.把非循环链队列置空\n";
  cout << "      8.随机生成非循环链队列\n";
  cout << "      9.用已有的非循环链队列初始化另一个新非循环链队列\n";
  cout << "     其他.结束\n";
  cout << "**************************************************\n";
}

void ShowLinkQueue(const bu_tools::LinkQueue<int> &q) {

  if (q.IsEmpty()) {
    cout << "\n队列为空！！！\n";
    return;
  }

  cout << "\n非循环链队列如下：\n";


  int len=q.GetLength();

  //打印队列中的信息
  for (auto it = q.begin(); it != q.end(); ++it) {
    cout << setw(3) << *it << " -> ";
  }
  cout<<*(q.end())<<"\n";

  cout << "  ^";
  for (int i = 0; i < len - 2; ++i) {
    cout << "       ";
  }
  cout << "    ^\n";

  cout << "  |";
  for (int i = 0; i < len - 2; ++i) {
    cout << "       ";
  }
  cout << "    |\n";

  cout << "front";
  for (int i = 0; i < len - 2; ++i) {
    cout << "       ";
  }
  cout << " rear\n";
}

void InitLinkQueue(const int len, bu_tools::LinkQueue<int> &q) {
  if (len <= 0) {
    return;
  }

  if (!q.IsEmpty()) {
    q.Clear();
  }

  for (int i = 0; i < len; ++i) {
    q.EnQueue(GenerateRandomNumber());
  }
}
