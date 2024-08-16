/**
 * ************************************************************************
 * @filename: test_doublelinklist.cpp
 * 
 * @brief : 测试循环双链表
 * 
 * 
 * @author : baiyebzx (baiyebzx1228@gmail.com)
 * @date : 2024-08-14
 * 
 * ************************************************************************
 */

#include "doublylinklist.h"
#include <iomanip>
#include <iostream>

using std::cin;
using std::cout;
using std::setw;

bu_tools::DoubleLinkList<int> L;

/****************************************************************************************************

外部函数

****************************************************************************************************/


/**
 * *****************************************************************
 * @brief : 主菜单
 * *****************************************************************
 */
void Menu01(){
    cout<<"********** 测 试 循 环 双 链 表 的 操 作 **********\n";
    cout<<"        1. 取循环双链表第i个结点的数据域\n";
    cout<<"        2. 在第i个结点之前插入一个数据域为e的结点\n";
    cout<<"        3. 判断循环双链表是否为空\n";
    cout<<"        4. 求循环双链表中结点的个数\n";
    cout<<"        5. 返回某结点前驱的数据域\n";
    cout<<"        6. 返回某结点后继的数据域\n";
    cout<<"        7. 删除循环双链表中数据域为e的第一个结点\n";
    cout<<"        8. 把一个循环双链表赋值给另一个循环双链表\n";
    cout<<"        9. 把循环双链表置空\n";
    cout<<"       10. 随机生成循环双链表\n";
    cout<<"       11. 用已有的循环双链表初始化另一个循环双链表\n";
    cout<<"       12. 输入循环双链表\n";
    cout<<"      其他. 结束\n";
    cout<<"**************************************************\n";
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

void InitDoubleLinkList(const int len,bu_tools::DoubleLinkList<int>& L){
  if (len <= 0) {
    return;
  }

  for(int i=0;i<len;++i){
    L.Append(GenerateRandomNumber01());
  }
}


/**
 * *****************************************************************
 * @brief : 
 * @param  L                
 * *****************************************************************
 */
void ShowDoubleLinkList(const bu_tools::DoubleLinkList<int> &L){
  // 定义每行显示的最大元素数量
  const int elementsPerRow = 10;
  // 定义标号和元素的宽度
  const int labelWidth = 7;
  const int numberWidth = 5;

  int len = L.GetLength();
  int e;

  cout << "\n\n循环双链表为：\n\n";

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
      } 
    }
    cout << "\n";
  }
}

/****************************************************************************************************

主函数

****************************************************************************************************/
int main(int argc, const char* argv[]) {

  //随机生成一个15长度的循环双链表
  InitRandomSeed();
  InitDoubleLinkList(15,L);

  
  /*****************************************************************
  
  主循环
  
  *****************************************************************/
 while(true){
   //主菜单操作标号
   int menu01_select;
   //单个操作是否再次执行标号
   char is_continue;

   //主菜单
   Menu01();
   //展示当前循环双链表
   ShowDoubleLinkList(L);

   cout << "\n请选择你要操作的代码<1-15>：";
   cin >> menu01_select;

   if(menu01_select==1){
     /*****************************************************************

     1. 取循环双链表第i个结点的数据域

     *****************************************************************/

     //整个操作的循环
     while (true) {

       // 清空终端屏幕
       cout << "\033[2J\033[1;1H";
       ShowDoubleLinkList(L);

       //输入操作循环
       while (true) {
         int index, e;
         cout << "\n请输入你要取的结点的序号：";
         cin >> index;

         if (!L.GetElem(index, e)) {
           cout << "\n输入的内容存在错误，检查是否越界，重新输入！！！！\n";
           cout << "请在下面重新输入：\n\n";
         } else {
           cout << "\n你要取的循环双链表的第" << index << "个结点的数据域为：" << e << "\n";
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

   }else if(menu01_select==2){
     /*****************************************************************

     2. 在第i个结点之前插入一个数据域为e的结点

     *****************************************************************/
     //整个操作的循环
     while (true) {

       // 清空终端屏幕
       cout << "\033[2J\033[1;1H";
       ShowDoubleLinkList(L);

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
           ShowDoubleLinkList(L);
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

   }else if(menu01_select==3){
     /*****************************************************************

     3. 判断循环双链表是否为空

     *****************************************************************/
     //整个操作的循环
     while (true) {

       // 清空终端屏幕
       cout << "\033[2J\033[1;1H";
       ShowDoubleLinkList(L);

       if (L.IsEmpty()) {
         cout << "\n当前循环双链表为空！！！\n";
       } else {
         cout << "\n当前循环双链表不为空！！！\n";
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

     4. 求循环双链表中结点的个数

     *****************************************************************/
     //整个操作的循环
     while (true) {

       // 清空终端屏幕
       cout << "\033[2J\033[1;1H";
       ShowDoubleLinkList(L);

       cout << "\n循环双链表中结点个数：" << L.GetLength() << "\n";

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

     5. 返回某结点前驱的数据域

     *****************************************************************/
     //整个操作的循环
     while (true) {

       // 清空终端屏幕
       cout << "\033[2J\033[1;1H";
       ShowDoubleLinkList(L);

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
   }else if(menu01_select==6){
     /*****************************************************************

     6. 返回某结点后继的数据域

     *****************************************************************/
     //整个操作的循环
     while (true) {

       // 清空终端屏幕
       cout << "\033[2J\033[1;1H";
       ShowDoubleLinkList(L);

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
   }else if(menu01_select==7){
     /*****************************************************************

     7. 删除循环双链表中数据域为e的第一个结点

     *****************************************************************/
     //整个操作的循环
     while (true) {

       // 清空终端屏幕
       cout << "\033[2J\033[1;1H";
       ShowDoubleLinkList(L);

       int e;
       cout << "\n请输入你想删除结点的数据域：";
       cin >> e;

       if (L.DeleteElem(e)) {
         cout << "\n如下是删除后的非循环单链表：\n";
         ShowDoubleLinkList(L);
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
   }else if(menu01_select==8){
     /*****************************************************************

     8. 把一个循环双链表赋值给另一个循环双链表

     *****************************************************************/
     //整个操作的循环
     while (true) {

       // 清空终端屏幕
       cout << "\033[2J\033[1;1H";
       ShowDoubleLinkList(L);

       bu_tools::DoubleLinkList<int> other_L;
       InitDoubleLinkList(5,other_L);
       cout<<"\n另一个循环双链表如下：\n";
       ShowDoubleLinkList(other_L);

       L=other_L;
       cout << "\n把另一个循环双链表赋值给当前循环双链表，当前循环双链表如下：\n";
       ShowDoubleLinkList(L);

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

     9. 把循环双链表置空

     *****************************************************************/
     //整个操作的循环
     while (true) {

       // 清空终端屏幕
       cout << "\033[2J\033[1;1H";
       ShowDoubleLinkList(L);

       L.Clear();
       cout << "\n当前循环双链表置空后，结点个数为：" << L.GetLength() << "\n";

       //是否再次进行该操作
       cout << "\n还继续吗？<Y.继续   N.结束>:";
       cin >> is_continue;
       if (is_continue == 'Y' || is_continue == 'y') {
         continue;
       } else {
         break;
       }
     }
   }else if(menu01_select==10){
     /*****************************************************************

     10. 随机生成循环双链表

     *****************************************************************/
     //整个操作的循环
     while (true) {

       // 清空终端屏幕
       cout << "\033[2J\033[1;1H";
       ShowDoubleLinkList(L);

       cout << "\n随机生成一个新的循环双链表。。。\n";
       L.Clear();

       InitDoubleLinkList(13,L);

       ShowDoubleLinkList(L);

       //是否再次进行该操作
       cout << "\n还继续吗？<Y.继续   N.结束>:";
       cin >> is_continue;
       if (is_continue == 'Y' || is_continue == 'y') {
         continue;
       } else {
         break;
       }
     }
   }else if(menu01_select==11){
     /*****************************************************************

     11. 用已有的循环双链表初始化另一个循环双链表

     *****************************************************************/
     //整个操作的循环
     while (true) {

       // 清空终端屏幕
       cout << "\033[2J\033[1;1H";
       ShowDoubleLinkList(L);

       bu_tools::DoubleLinkList<int> other_L(L);
       cout << "\n当前非循环单链表初始化另一个非循环单链表，另一个非循环单链表如下:\n";
       ShowDoubleLinkList(other_L);

       //是否再次进行该操作
       cout << "\n还继续吗？<Y.继续   N.结束>:";
       cin >> is_continue;
       if (is_continue == 'Y' || is_continue == 'y') {
         continue;
       } else {
         break;
       }
     }
   }else if(menu01_select==12){
     /*****************************************************************

     12. 输入循环双链表

     *****************************************************************/
     //整个操作的循环
     while (true) {

       // 清空终端屏幕
       cout << "\033[2J\033[1;1H";
       ShowDoubleLinkList(L);

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

       ShowDoubleLinkList(L);

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