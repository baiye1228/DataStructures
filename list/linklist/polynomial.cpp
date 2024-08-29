
/**
 * ************************************************************************
 * @filename: polynomial.cpp
 *
 * @brief : 多项式成员函数的定义
 *
 *
 * @author : baiyebzx (baiyebzx1228@gmail.com)
 * @date : 2024-08-11
 *
 * ************************************************************************
 */

#include "polynomial.h"
#include "singlylinklist.h"

namespace bu_tools {

ostream &operator<<(ostream &out, const Term &t) {
  if (t.m_coef != 1) {
    out << t.m_coef;
  }
  if (t.m_expn) {
    out << "x^" << t.m_expn;
  }
  return out;
}

istream &operator>>(istream &in, Term &t) {
  cout << "\n系数：";

  while (!(in >> t.m_coef)) {
    cout << "   系数不为零，重新输入！\n";
  }
  cout << "\t    指数：";
  in >> t.m_expn;
  cout << "\n";
  return in;
}

istream &operator>>(istream &in, Polynomial &p) {
  p.Read(in);
  return in;
}

ostream &operator<<(ostream &out, const Polynomial &p) {
  p.Display(out);
  return out;
}

Polynomial::Polynomial(const Polynomial &other_p) {
  *this = other_p;
}

void Polynomial::AddTerm(const Term &t) {
  NodePointer new_node = new Node(t);

  // 如果链表为空或新项指数大于头结点指数，插入到链表头部
  if (m_head == nullptr || m_head->m_data.m_expn < t.m_expn) {
    new_node->m_next = m_head;
    m_head = new_node;
    ++m_len;
  } else {
    NodePointer current = m_head;
    NodePointer prev = nullptr;

    //找到正确的插入位置
    while (current != nullptr && current->m_data.m_expn > t.m_expn) {
      prev = current;
      current = current->m_next;
    }

    // 如果存在相同指数的项，直接相加系数
    if (current != nullptr && current->m_data.m_expn == t.m_expn) {
      current->m_data.m_coef += t.m_coef;
      delete new_node;

      // 如果系数为0，删除该节点
      if (current->m_data.m_coef == 0) {
        if (prev == nullptr) {
          m_head = current->m_next;
        } else {
          prev->m_next = current->m_next;
        }
        delete current;
      }
    } else {
      //插入新的项
      prev->m_next = new_node;
      new_node->m_next = current;
      ++m_len;
    }
  }
}
/**
 * *****************************************************************
 * @brief : 重载加法运算符
 * @param  other_p
 * @return Polynomial
 * *****************************************************************
 */
Polynomial Polynomial::operator+(const Polynomial &other_p) {
  Polynomial result_p;
  Term temp_t;

  NodePointer p1 = this->m_head;
  NodePointer p2 = other_p.m_head;

  while (p1 != nullptr && p2 != nullptr) {
    if (p1->m_data.m_expn > p2->m_data.m_expn) {
      temp_t.m_coef = p1->m_data.m_coef;
      temp_t.m_expn = p1->m_data.m_expn;
      result_p.AddTerm(temp_t);
      p1 = p1->m_next;
    } else if (p1->m_data.m_expn < p2->m_data.m_expn) {
      temp_t.m_coef = p2->m_data.m_coef;
      temp_t.m_expn = p2->m_data.m_expn;
      result_p.AddTerm(temp_t);
      p2 = p2->m_next;
    } else {
      int sumCoef = p1->m_data.m_coef + p2->m_data.m_coef;
      if (sumCoef != 0) {
        temp_t.m_coef = sumCoef;
        temp_t.m_expn = p1->m_data.m_expn;
        result_p.AddTerm(temp_t);
      }
      p1 = p1->m_next;
      p2 = p2->m_next;
    }
  }

  // 处理剩余的项
  while (p1 != nullptr) {
    temp_t.m_coef = p1->m_data.m_coef;
    temp_t.m_expn = p1->m_data.m_expn;
    result_p.AddTerm(temp_t);
    p1 = p1->m_next;
  }
  while (p2 != nullptr) {
    temp_t.m_coef = p2->m_data.m_coef;
    temp_t.m_expn = p2->m_data.m_expn;
    result_p.AddTerm(temp_t);
    p2 = p2->m_next;
  }

  return result_p;
}

/**
 * *****************************************************************
 * @brief : 重载减法运算符
 * @param  other_p
 * @return Polynomial
 * *****************************************************************
 */
Polynomial Polynomial::operator-(const Polynomial &other_p) {
  Polynomial negatedOther;
  Term temp_t;
  NodePointer current = other_p.m_head;

  // 对other多项式的每一项取反
  while (current != nullptr) {
    temp_t.m_coef = -current->m_data.m_coef;
    temp_t.m_expn = current->m_data.m_expn;
    negatedOther.AddTerm(temp_t);
    current = current->m_next;
  }

  // 使用重载的加法运算符将当前多项式与取反后的other相加
  return *this + negatedOther;
}

/**
 * *****************************************************************
 * @brief : 输入多项式
 * @param  in
 * *****************************************************************
 */
void Polynomial::Read(istream &in) {
  Term temp_t;

  char choice;
  int i = 1;

  int n; //需要输入的项数
  this->Clear();

  do {
    cout << "\n第" << i << "项：\n";
    in >> temp_t;
    ++i;

    AddTerm(temp_t);
    cout << "\n是否继续输入下一项？（y/n）：";
    in >> choice;
  } while (choice == 'y' || choice == 'Y');
}

/**
 * *****************************************************************
 * @brief : 打印多项式
 * *****************************************************************
 */
void Polynomial::Display(ostream &out) const {
  NodePointer current = m_head;
  if (!m_head) {
    out << "\n该多项式为空！！！\n";
    return;
  }

  cout << "\n多项式（采用非循环单链表存储）为：\n";
  while (current != nullptr) {
    out << current->m_data;
    current = current->m_next;
    if (current != nullptr && current->m_data.m_coef > 0) {
      out << " + ";
    }
  }
  out << "\n";
}

} // namespace bu_tools
