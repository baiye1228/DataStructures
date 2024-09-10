/**
 * ************************************************************************
 * @filename: test_basebinarytree.cpp
 *
 * @brief : 测试二叉树（顺序存储）
 *
 *
 * @author : baiyebzx (baiyebzx1228@gmail.com)
 * @date : 2024-09-08
 *
 * ************************************************************************
 */

#include "linkbinarytree.h"
#include "seqbinarytree.h"
#include <iostream>

using std::cout;
// using std::cin;

int main(int argc, const char *argv[]) {

  bu_tools::SeqBinaryTree<int> seq_tree;
  bu_tools::LinkBinaryTree<int> link_tree;

  seq_tree.SetNode(0, 11);
  seq_tree.SetNode(1, 12);
  seq_tree.SetNode(2, 13);
  seq_tree.SetNode(3, 14);
  seq_tree.SetNode(4,99);
  seq_tree.SetNode(6, 15);
  seq_tree.SetNode(8, 16);
  seq_tree.SetNode(13, 17);

  cout << seq_tree.CalculateDepth() << "\n";
  cout << seq_tree.CountLeaves() << "\n";

  //seq_tree.Mirror();

cout<<"\n顺序存储迭代器：\n";

  for (auto it = seq_tree.PreOrderBegin(); it != seq_tree.PreOrderEnd(); ++it) {
    cout << *it << "   ";
  }
  cout << "\n";

  for (auto it = seq_tree.InOrderBegin(); it != seq_tree.InOrderEnd(); ++it) {
    cout << *it << "   ";
  }
  cout << "\n";

  for (auto it = seq_tree.PostOrderBegin(); it != seq_tree.PostOrderEnd(); ++it) {
    cout << *it << "   ";
  }
  cout << "\n";

link_tree.SequentialToLink(seq_tree);

cout<<"\n二叉链表存储迭代器：\n";

for(auto it=link_tree.PreOrderBegin();it!=link_tree.PreOrderEnd();++it){
  cout<<*it<<"   ";
}

link_tree.PreOrderRecursive();

for(auto it=link_tree.InOrderBegin();it!=link_tree.InOrderEnd();++it){
  cout << *it << "   ";
}

link_tree.InOrderRecursive();

for (auto it = link_tree.PostOrderBegin(); it != link_tree.PostOrderEnd(); ++it) {
  cout << *it << "   ";
}

link_tree.PostOrderRecursive();


return 0;
}