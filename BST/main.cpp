#include <iostream>
#include "BST.h" 
using namespace std;

template <typename T>
void print(T& e) {
	cout << e << " ";
}

int main() {
	//所有操作时间复杂度O(h) 
	BST<int> bst;
	
	//该BST类支持所有BinTree类的接口（这里调用插入根节点，插入左右孩子结点） 
	BinNode<int>* root = bst.insertAsRoot(5); 
	BinNode<int>* lc = bst.insertAsLC(root, 3);
	BinNode<int>* rc = bst.insertAsRC(root, 7);
	//search接口返回当前值所在结点的地址，不存在则返回NULL 
	cout << "Is 3 in bst? " << (bst.search(3) ? "Yes" : "No") << " Address: " << bst.search(3) << endl;
	cout << "Is 1 in bst? " << (bst.search(1) ? "Yes" : "No") << " Address: " << bst.search(1) << endl;
	//调用BST类的insert接口，随意插入一些数，该函数返回插入结点的地址
	//（实际上insert接口可以支持空树的插入，我就不测试了~）  
	bst.insert(1);  
	bst.insert(4);
	bst.insert(2);
	//这个BST不支持相同元素，插入重复元素会被自动忽略，
	//不过还是可以返回插入元素结点的地址(此时功能和search一样了) 
	bst.insert(2); 
	bst.insert(6);
	bst.insert(8);
	bst.insert(9);
	//在中序遍历下会从小到大有序排列 
	bst.travIn_I(print); //BinTree中序遍历，迭代版 
	cout << endl;
	//size接口返回数目 
	cout <<"size: " << bst.size() << endl;
	//随意地删除元素 
	bst.remove(3);
	bst.remove(7);
	bst.remove(1);
	cout << "BST after remove 3, 7, 1: ";
	//print出来，当然你想做别的也可以，这个遍历操作是支持自定义操作的 
	bst.travIn_I(print); 
	cout << endl;
	return 0;
} 
