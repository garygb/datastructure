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
	//�������ж����Զ���ı������� 
	binTree.travPost_I(doubleItem);
	cout << "��������£������ӱ�������Ԫ�أ�" << endl; 
	binTree.travPre_I1(print);
	cout << endl; 
	cout << "��������£������ӱ�������Ԫ�أ�" << endl; 
	binTree.travIn_I(print); 
	cout << endl; 
	cout << "��������£������ӱ�������Ԫ�أ�" << endl; 
	binTree.travPost_I(print);
	cout << endl;  
	cout << "��α����£������ӱ�������Ԫ�أ�" << endl; 
	binTree.travLevel(print); 
	cout << endl; 
	return 0;
}
