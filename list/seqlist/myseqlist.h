/**
 * ************************************************************************
 * @filename: myseqlist.h
 *
 * @brief :
 *
 *
 * @author : baiyebzx (baiyebzx1228@gmail.com)
 * @date : 2024-08-05
 *
 * ************************************************************************
 */

#ifndef _MYSEQLIST_H_
#define _MYSEQLIST_H_

#include "seqlist.h"
#include <iostream>

using std::cout;

namespace bu_tools {

class MySeqList : public SeqList<int> {

public:
  void UnionSet(const MySeqList &other_l, MySeqList &result_l) const;
  void IntersectSet(const MySeqList &other_l, MySeqList &result_l) const;
  void DifferenceSet(const MySeqList &other_l, MySeqList &result_l) const;
  void BubbleSort();
  void RemoveDuplicates();
  void Show() const;
};

} // namespace bu_tools

#endif // _MYSEQLIST_H_