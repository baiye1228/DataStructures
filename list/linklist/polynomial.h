/**
 * ************************************************************************
 * @filename: polynomial.h
 *
 * @brief : 非循环单链表应用：多项式
 *
 *
 * @author : baiyebzx (baiyebzx1228@gmail.com)
 * @date : 2024-08-11
 *
 * ************************************************************************
 */

#ifndef _POLYNOMIAL_H_
#define _POLYNOMIAL_H_

#include "singlylinklist.h"
#include <iostream>

using std::cin;
using std::cout;
using std::istream;
using std::ostream;

namespace bu_tools {

/**
 * *****************************************************************
 * @brief : 多项式项
 * *****************************************************************
 */
class Term {

public:
  double m_coef; //多项式系数
  int m_expn;    //多项式项的系数

public:
  friend ostream &operator<<(ostream &out, const Term &t);
  friend istream &operator>>(istream &in, Term &t);
};

/**
 * *****************************************************************
 * @brief : 多项式类
 * *****************************************************************
 */
class Polynomial : public SinglyLinkList<Term> {

public:
  Polynomial() {}
  Polynomial(const Polynomial &other_P);

  void AddTerm(const Term &t);
  Polynomial operator+(const Polynomial &other_p);
  Polynomial operator-(const Polynomial &other_p);

  void Read(istream &in);
  void Display(ostream &out) const;

  friend istream &operator>>(istream &in, Polynomial &p);
  friend ostream &operator<<(ostream &out, const Polynomial &p);
};

} // namespace bu_tools

#endif // _POLYNOMIAL_H_