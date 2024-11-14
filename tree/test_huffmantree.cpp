/**
 * ************************************************************************
 * @filename: test_huffmantree.cpp
 * 
 * @brief : 测试哈夫曼树
 * 
 * 
 * @author : baiyebzx (baiyebzx1228@gmail.com)
 * @date : 2024-09-12
 * 
 * ************************************************************************
 */

//#include<iostream>
#include "huffmantree.h"







int main(int argc, const char* argv[]) {
  int len=6;

  bu_tools::HuffmanItem<char,int> items[len];

  char data[] = {'A', 'B', 'C', 'D','E','F'};
  int weights[] = {8, 6, 3, 5,9,4};

  for(int i=0;i<len;++i){
    items[i].m_data=data[i];
    items[i].m_weight=weights[i];
  }

  bu_tools::HuffmanTree<char,int> huffmantree(items,len);

  huffmantree.PrintHuffmanCodes();



  return 0;
}