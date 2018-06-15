#include <iostream>
#include "BinNode.h"
#include "BinTree.h"
using namespace std;

template <typename T>
void print(T ele) {
	cout << ele << " ";
}
template <typename T>
void doubleItem(T ele) {
	ele = 2 * ele; 
}

int main(int argc, char** argv) {
	BinTree<int> binTree;
	binTree.insertAsRoot(1);
	BinNode<int>* lc = binTree.insertAsLC(binTree.root(), 2);
	BinNode<int>* rc = binTree.insertAsRC(binTree.root(), 3);
	binTree.insertAsLC(lc, 4);
	binTree.insertAsRC(lc, 5);
	binTree.insertAsLC(rc, 6);
	binTree.insertAsRC(rc, 7);
	//可以自行定制自定义的遍历操作 
	binTree.travPost_I(doubleItem);
	cout << "先序遍历下，经过加倍操作的元素：" << endl; 
	binTree.travPre_I1(print);
	cout << endl; 
	cout << "中序遍历下，经过加倍操作的元素：" << endl; 
	binTree.travIn_I(print); 
	cout << endl; 
	cout << "后序遍历下，经过加倍操作的元素：" << endl; 
	binTree.travPost_I(print);
	cout << endl;  
	cout << "层次遍历下，经过加倍操作的元素：" << endl; 
	binTree.travLevel(print); 
	cout << endl; 
	return 0;
}
