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
  void union_set(const MySeqList &other_L, MySeqList &result_L) const;
  void intersect_set(const MySeqList &other_L, MySeqList &result_L) const;
  void difference_set(const MySeqList &other_L, MySeqList &result_L) const;
  void bubble_sort();
  void remove_duplicates();
  void show() const;
};

} // namespace bu_tools

#endif // _MYSEQLIST_H_