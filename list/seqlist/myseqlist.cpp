
/**
 * ************************************************************************
 * @filename: myseqlist.cpp
 *
 * @brief :
 *
 *
 * @author : baiyebzx (baiyebzx1228@gmail.com)
 * @date : 2024-08-05
 *
 * ************************************************************************
 */

#include "myseqlist.h"
#include <iomanip>
#include <iostream>

using std::cout;
using std::setw;

namespace bu_tools {

/**
 * *****************************************************************
 * @brief : 求并集
 * @param  other_L
 * @param  result_L
 * *****************************************************************
 */
void MySeqList::union_set(const MySeqList &other_L, MySeqList &result_L) const {
  int i = 0, j = 0;

  result_L.clear();

  while (i < this->m_n && j < other_L.m_n) {

    if (this->m_elem[i] < other_L.m_elem[j]) {
      result_L.append(this->m_elem[i]);
      ++i;
    } else if (this->m_elem[i] > other_L.m_elem[j]) {
      result_L.append(other_L.m_elem[j]);
      ++j;
    } else {
      result_L.append(this->m_elem[i]);
      ++i;
      ++j;
    }
  }

  while (i < this->m_n) {
    result_L.append(this->m_elem[i]);
    ++i;
  }
  while (j < other_L.m_n) {
    result_L.append(other_L.m_elem[j]);
    ++j;
  }
  //去除重复元素
  result_L.remove_duplicates();
}

/**
 * *****************************************************************
 * @brief : 求交集
 * @param  other_L
 * @param  result_L
 * *****************************************************************
 */
void MySeqList::intersect_set(const MySeqList &other_L, MySeqList &result_L) const {
  int i = 0, j = 0;

  result_L.clear();

  while (i < this->m_n && j < other_L.m_n) {

    if (this->m_elem[i] == other_L.m_elem[j]) {
      // 如果两个元素相等，添加到结果中，并移动两个指针
      result_L.append(this->m_elem[i]);
      ++i;
      ++j;
    } else if (this->m_elem[i] < other_L.m_elem[j]) {
      // 如果第一个元素小于第二个元素，移动第一个数组的指针
      ++i;
    } else {
      // 如果第一个元素大于第二个元素，移动第二个数组的指针
      ++j;
    }
  }

  //去除重复元素
  result_L.remove_duplicates();
}

/**
 * *****************************************************************
 * @brief : 求差集
 * @param  other_L
 * @param  result_L
 * *****************************************************************
 */
void MySeqList::difference_set(const MySeqList &other_L, MySeqList &result_L) const {
  int i = 0, j = 0;

  result_L.clear();

  while (i < this->m_n && j < other_L.m_n) {

    if (this->m_elem[i] < other_L.m_elem[j]) {
      // 如果第一个数组的元素小于第二个数组的元素，添加到结果中
      result_L.append(this->m_elem[i]);
      ++i;
    } else if (this->m_elem[i] > other_L.m_elem[j]) {
      // 如果第一个数组的元素大于第二个数组的元素，移动第二个数组的指针
      ++j;
    } else {
      // 如果两个元素相等，跳过该元素，移动两个指针
      ++i;
      ++j;
    }
  }

  while (i < this->m_n) {
    result_L.append(this->m_elem[i]);
    ++i;
  }

  //去除重复元素
  result_L.remove_duplicates();
}

/**
 * *****************************************************************
 * @brief : 冒泡排序
 * *****************************************************************
 */
void MySeqList::bubble_sort() {
  int n = m_n;
  bool swapped;
  for (int i = 0; i < n - 1; ++i) {
    swapped = false;
    for (int j = 0; j < n - i - 1; ++j) {
      int temp;
      if (m_elem[j] > m_elem[j + 1]) {
        temp = m_elem[j];
        m_elem[j] = m_elem[j + 1];
        m_elem[j + 1] = temp;
        swapped = true;
      }
    }
    // 如果没有发生交换，数组已经有序
    if (!swapped) {
      break;
    }
  }
}

/**
 * *****************************************************************
 * @brief : 去除重复元素
 * *****************************************************************
 */
void MySeqList::remove_duplicates() {
  if (m_n == 0) {
    return; // 如果顺序表为空，则无需操作
  }

  int j = 0; // 用于追踪不重复元素的位置

  for (int i = 1; i < m_n; ++i) {
    if (m_elem[j] != m_elem[i]) {
      m_elem[++j] = m_elem[i]; // 发现不同元素，则将其移动到下一个位置
    }
  }
  m_n = j + 1; // 更新顺序表的大小
}

/**
 * *****************************************************************
 * @brief : 打印
 * *****************************************************************
 */
void MySeqList::show() const {
  // 定义每行显示的最大元素数量
  const int elementsPerRow = 10;
  // 定义标号和元素的宽度
  const int labelWidth = 7;
  const int numberWidth = 5;

  for (int i = 0; i < m_n; i += elementsPerRow) {
    // 打印当前行的标号
    for (int j = i; j < i + elementsPerRow && j < m_n; ++j) {
      cout << "[" << setw(labelWidth - 2) << j + 1 << "] ";
    }
    cout << "\n";

    // 打印当前行的元素
    for (int j = i; j < i + elementsPerRow && j < m_n; ++j) {
      cout << setw(numberWidth) << m_elem[j] << "   ";
    }
    cout << "\n";
  }
}

} // namespace bu_tools
