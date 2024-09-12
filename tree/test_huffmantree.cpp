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

#include<iostream>
#include "huffmantree.h"


using std::cout;
using std::cin;

bu_tools::HuffmanItem<char,int> items[4];




int main(int argc, const char* argv[]) {

  char data[] = {'A', 'B', 'C', 'D'};
  int weights[] = {8, 6, 3, 5};

  for(int i=0;i<4;++i){
    items[i].m_data=data[i];
    items[i].m_weight=weights[i];
  }

  bu_tools::HuffmanTree<char,int> huffmantree(items,4);

  huffmantree.PrintHuffmanCodes();



  return 0;
}