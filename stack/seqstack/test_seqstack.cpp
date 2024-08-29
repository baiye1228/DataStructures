/**
 * ************************************************************************
 * @filename: test_seqstack.cpp
 *
 * @brief : 测试顺序栈
 *
 *
 * @author : baiyebzx (baiyebzx1228@gmail.com)
 * @date : 2024-08-17
 *
 * ************************************************************************
 */

#include "seqstack.h"
#include <cctype>
#include <cstdlib>
#include <iomanip>
#include <iostream>

using std::cin;
using std::cout;
using std::setw;

bu_tools::SeqStack<int> S(20);

/****************************************************************************************************

辅助函数

****************************************************************************************************/

/**
 * *****************************************************************
 * @brief : 主菜单
 * *****************************************************************
 */
void Menu01();

/**
 * *****************************************************************
 * @brief : 表达式求解菜单
 * *****************************************************************
 */
void Menu02();

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
 * @brief : 打印顺序栈
 * @param  S
 * *****************************************************************
 */
void ShowSeqStack(const bu_tools::SeqStack<int> &S);

/**
 * *****************************************************************
 * @brief : 随机生成指定长度的顺序栈
 * @param  len
 * @param  S
 * *****************************************************************
 */
void InitSeqStack(const int len, bu_tools::SeqStack<int> &S);

/**
 * *****************************************************************
 * @brief : 检查字符是否为操作符
 * @param  c
 * @return true
 * @return false
 * *****************************************************************
 */
bool IsOperator(const char c) {
  return c == '+' || c == '-' || c == '*' || c == '/';
}

/**
 * *****************************************************************
 * @brief : 获取操作符的优先级
 * @param  op
 * @return int
 * *****************************************************************
 */
int Precedence(const char op);

/**
 * *****************************************************************
 * @brief : 中缀表达式转后缀表达式
 * @param  infix
 * @param  postfix
 * *****************************************************************
 */
void InfixToPostfix(const char *infix, char *postfix);

/**
 * *****************************************************************
 * @brief : 执行操作符的计算
 * @param  a
 * @param  b
 * @param  op
 * @return int
 * *****************************************************************
 */
int ApplyOperator(int a, int b, char op);

/**
 * *****************************************************************
 * @brief : 计算逆波兰表达式
 * @param  expression
 * @return int
 * *****************************************************************
 */
int EvaluateRPN(const char *expression);

/****************************************************************************************************

主函数

****************************************************************************************************/
int main(int argc, const char *argv[]) {

  //随机生成一个15长度的顺序表
  InitRandomSeed();
  InitSeqStack(15, S);

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
    //展示当前顺序栈
    ShowSeqStack(S);

    cout << "\n请选择你要操作的代码<1-10>：";
    cin >> menu01_select;

    if (menu01_select == 1) {
      /*****************************************************************

      1.在栈顶压入元素e

      *****************************************************************/
      //整个操作的循环
      while (true) {

        // 清空终端屏幕
        cout << "\033[2J\033[1;1H";
        ShowSeqStack(S);

        int e;
        cout << "\n输入你要压入栈中的元素：";
        cin >> e;

        if (!S.Push(e)) {
          cout << "\n栈中元素已满，请展开其他操作！！！！\n";
        } else {
          cout << "\n压栈后。。。。\n";
          ShowSeqStack(S);
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

      2.弹出栈顶元素到e

      *****************************************************************/
      //整个操作的循环
      while (true) {

        // 清空终端屏幕
        cout << "\033[2J\033[1;1H";
        ShowSeqStack(S);

        int e;
        if (S.Pop(e)) {
          cout << "\n弹出的栈顶元素为：" << e << "\n";
          ShowSeqStack(S);
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
    } else if (menu01_select == 3) {
      /*****************************************************************

      3.读栈顶的元素

      *****************************************************************/
      //整个操作的循环
      while (true) {

        // 清空终端屏幕
        cout << "\033[2J\033[1;1H";
        ShowSeqStack(S);

        int e;
        if (S.GetTop(e)) {
          cout << "\n栈顶元素为：" << e << "\n";
          ShowSeqStack(S);
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
    } else if (menu01_select == 4) {
      /*****************************************************************

      4.判断顺序栈是否为空

      *****************************************************************/
      //整个操作的循环
      while (true) {

        // 清空终端屏幕
        cout << "\033[2J\033[1;1H";
        ShowSeqStack(S);

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
    } else if (menu01_select == 5) {
      /*****************************************************************

      5.求顺序栈中元素的个数

      *****************************************************************/
      //整个操作的循环
      while (true) {

        // 清空终端屏幕
        cout << "\033[2J\033[1;1H";
        ShowSeqStack(S);

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
    } else if (menu01_select == 6) {
      /*****************************************************************

      6.把一个顺序栈赋值给另一个顺序栈

      *****************************************************************/
      //整个操作的循环
      while (true) {

        // 清空终端屏幕
        cout << "\033[2J\033[1;1H";
        ShowSeqStack(S);

        bu_tools::SeqStack<int> other_S;
        InitSeqStack(7, other_S);

        cout << "\n另一个顺序栈如下：\n";
        ShowSeqStack(other_S);

        S = other_S;
        cout << "\n另一个顺序栈赋值给当前顺序栈。。。。\n";
        ShowSeqStack(S);

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

      7.把顺序栈置空

      *****************************************************************/
      //整个操作的循环
      while (true) {

        // 清空终端屏幕
        cout << "\033[2J\033[1;1H";
        ShowSeqStack(S);

        S.Clear();

        cout << "\n置空后。。。\n";
        ShowSeqStack(S);

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

      8.随机生成顺序栈

      *****************************************************************/
      //整个操作的循环
      while (true) {

        // 清空终端屏幕
        cout << "\033[2J\033[1;1H";
        ShowSeqStack(S);

        cout << "\n重新随机生成一个顺序栈。。。。\n";
        InitSeqStack(7, S);

        ShowSeqStack(S);

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

      9.用已有的顺序栈初始化另一个新的顺序栈

      *****************************************************************/
      //整个操作的循环
      while (true) {

        // 清空终端屏幕
        cout << "\033[2J\033[1;1H";
        ShowSeqStack(S);

        bu_tools::SeqStack<int> other_S(S);
        cout << "\n当前顺序栈初始化另一个顺序栈如下：\n";

        ShowSeqStack(other_S);

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

      10.表达式求解（顺序栈的应用）

      *****************************************************************/
      // 清空终端屏幕
      cout << "\033[2J\033[1;1H";
      //应用菜单操作标号
      int menu02_select;

      char infix[]="23-((34-13)*7+6/2)";



      /*****************************************************************
      
      表达式求解主循环
      
      *****************************************************************/
      while(true){

        // 清空终端屏幕
        cout << "\033[2J\033[1;1H";
        //表达式求解菜单
        Menu02();
        cout<<"\n当前中缀表达式为：\n"<<infix<<"\n";

        cout << "\n请选择你要操作的代码<1-3>:";
        cin >> menu02_select;

        if(menu02_select==1){
          /*****************************************************************

          1.中缀表达式转换成后缀表达式

          *****************************************************************/

         while(true){

           // 清空终端屏幕
           cout << "\033[2J\033[1;1H";
           cout << "\n当前中缀表达式为：\n"<< infix << "\n";

           char postfix[100];
           InfixToPostfix(infix,postfix);

           cout<<"\n当前中缀表达式对应的后缀表达式为：\n";
           cout<<postfix<<"\n";

           //是否再次进行该操作
           cout << "\n还继续吗？<Y.继续   N.结束>:";
           cin >> is_continue;
           if (is_continue == 'Y' || is_continue == 'y') {
             continue;
           } else {
             break;
           }
         }



        }else if(menu02_select==2){
          /*****************************************************************

          2.后缀表达式的计算

          *****************************************************************/
          while (true) {

            // 清空终端屏幕
            cout << "\033[2J\033[1;1H";
            cout << "\n当前中缀表达式为：\n"
                 << infix << "\n";

            char postfix[100];
            InfixToPostfix(infix, postfix);

            cout << "\n当前中缀表达式对应的后缀表达式为：\n";
            cout << postfix << "\n";

            int result=EvaluateRPN(postfix);
            cout<<"\n表达式的结果为："<<result<<"\n";

            //是否再次进行该操作
            cout << "\n还继续吗？<Y.继续   N.结束>:";
            cin >> is_continue;
            if (is_continue == 'Y' || is_continue == 'y') {
              continue;
            } else {
              break;
            }
          }


        }else if(menu02_select==3){
          /*****************************************************************

          3.输入中缀表达式

          *****************************************************************/
          while (true) {

            // 清空终端屏幕
            cout << "\033[2J\033[1;1H";
            cout << "\n当前中缀表达式为：\n"
                 << infix << "\n";

            cout<<"\n请输入一个新的中缀表达式：";
            cin>>infix;

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

      

    } else {
      break;
    }

    // 清空终端屏幕
    cout << "\033[2J\033[1;1H";
  }

  return 0;
}

/****************************************************************************************************

辅助函数的定义

****************************************************************************************************/

void Menu01() {
  cout << "********** 测 试 顺 序 栈 操 作 **********\n";
  cout << "      1.在栈顶压入元素e\n";
  cout << "      2.弹出栈顶元素到e\n";
  cout << "      3.读栈顶的元素\n";
  cout << "      4.判断顺序栈是否为空\n";
  cout << "      5.求顺序栈中元素的个数\n";
  cout << "      6.把一个顺序栈赋值给另一个顺序栈\n";
  cout << "      7.把顺序栈置空\n";
  cout << "      8.随机生成顺序栈\n";
  cout << "      9.用已有的顺序栈初始化另一个新的顺序栈\n";
  cout << "     10.表达式求解（顺序栈的应用）\n";
  cout << "    其他.结束\n";
  cout << "******************************************\n";
}
void Menu02() {
  cout << "********** 表达式求解（顺序栈的应用） **********\n";
  cout << "     1.中缀表达式转换成后缀表达式\n";
  cout << "     2.后缀表达式的计算\n";
  cout << "     3.输入中缀表达式\n";
  cout << "    其他.结束\n";
  cout << "**********************************************\n";
}

void ShowSeqStack(const bu_tools::SeqStack<int> &S) {
  if (S.IsEmpty()) {
    cout << "\n栈为空！！！\n";
    return;
  }

  cout << "\n顺序栈如下：\n";
  for(auto it=S.begin();it!=S.end();++it){
    cout<<setw(5)<<*it<<"  ";
  }
  cout << "\n";
  cout << "   ^\n";
  cout << "   |\n";
  cout << "  top\n";
}

void InitSeqStack(const int len, bu_tools::SeqStack<int> &S) {
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

int Precedence(const char op) {
  if (op == '+' || op == '-') {
    return 1;
  }

  if (op == '*' || op == '/') {
    return 2;
  }

  return 0;
}

void InfixToPostfix(const char *infix, char *postfix) {
  bu_tools::SeqStack<char> op_stack; // 操作符栈
  int j = 0;                         // 后缀表达式的索引

  for (int i = 0; infix[i] != '\0'; ++i) {
    char c = infix[i];

    if (isdigit(c)) {
      // 如果是操作数，直接添加到后缀表达式
      postfix[j++] = c;
      if(!isdigit(infix[i+1])){
        postfix[j++]=' ';
      }
    } else if (c == '(') {
      // 如果是左括号，压入栈中
      op_stack.Push(c);
    } else if (c == ')') {
      // 如果是右括号，弹出栈中的元素直到遇到左括号
      char top_e;
      op_stack.GetTop(top_e);
      while (!op_stack.IsEmpty() && top_e != '(') {
        postfix[j++] = top_e;
        postfix[j++] = ' ';
        op_stack.Pop();
        op_stack.GetTop(top_e);
      }
      op_stack.Pop();
    } else if (IsOperator(c)) {
      // 如果是操作符，处理栈中的优先级
      char top_e;
      op_stack.GetTop(top_e);
      while (!op_stack.IsEmpty() && Precedence(top_e) >= Precedence(c)) {
        postfix[j++] = top_e;
        postfix[j++] = ' ';
        op_stack.Pop();
        op_stack.GetTop(top_e);
      }
      op_stack.Push(c);
    }
  }

  // 将栈中剩余的操作符添加到后缀表达式
  while (!op_stack.IsEmpty()) {
    char top_e;
    op_stack.GetTop(top_e);
    postfix[j++] = top_e;
    postfix[j++] = ' ';
    op_stack.Pop();
  }

  postfix[j-1] = '\0';
}

int ApplyOperator(int a, int b, char op) {
  switch (op) {
  case '+':
    return a + b;
  case '-':
    return a - b;
  case '*':
    return a * b;
  case '/':
    return a / b;
  default:
    return 0;
  }
}

int EvaluateRPN(const char *expression) {
  bu_tools::SeqStack<int> operand_stack(20);
  char token[20];
  int token_index = 0;
  int b;
  int a;
  int result;

  for (int i = 0; expression[i] != '\0'; ++i) {
    char c = expression[i];

    if (isdigit(c)) {
      token[token_index++] = c; // 收集数字字符

    } else if (c == ' ' && token_index > 0) {
      token[token_index] = '\0';            // 结束字符串
      operand_stack.Push(std::atoi(token)); // 转换为整数并压入栈
      token_index = 0;                      // 重置token索引
    } else if (IsOperator(c)) {

      operand_stack.GetTop(b);
      operand_stack.Pop();

      operand_stack.GetTop(a);
      operand_stack.Pop();

      result = ApplyOperator(a, b, c);
      operand_stack.Push(result);
    }
  }

  // 处理最后的数字
  if (token_index > 0) {
    token[token_index] = '\0';
    operand_stack.Push(std::atoi(token));
  }

  operand_stack.GetTop(result);

  return result;
}
