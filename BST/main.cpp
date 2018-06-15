#include <iostream>
#include "BST.h" 
using namespace std;

template <typename T>
void print(T& e) {
	cout << e << " ";
}

int main() {
	//���в���ʱ�临�Ӷ�O(h) 
	BST<int> bst;
	
	//��BST��֧������BinTree��Ľӿڣ�������ò�����ڵ㣬�������Һ��ӽ�㣩 
	BinNode<int>* root = bst.insertAsRoot(5); 
	BinNode<int>* lc = bst.insertAsLC(root, 3);
	BinNode<int>* rc = bst.insertAsRC(root, 7);
	//search�ӿڷ��ص�ǰֵ���ڽ��ĵ�ַ���������򷵻�NULL 
	cout << "Is 3 in bst? " << (bst.search(3) ? "Yes" : "No") << " Address: " << bst.search(3) << endl;
	cout << "Is 1 in bst? " << (bst.search(1) ? "Yes" : "No") << " Address: " << bst.search(1) << endl;
	//����BST���insert�ӿڣ��������һЩ�����ú������ز�����ĵ�ַ
	//��ʵ����insert�ӿڿ���֧�ֿ����Ĳ��룬�ҾͲ�������~��  
	bst.insert(1);  
	bst.insert(4);
	bst.insert(2);
	//���BST��֧����ͬԪ�أ������ظ�Ԫ�ػᱻ�Զ����ԣ�
	//�������ǿ��Է��ز���Ԫ�ؽ��ĵ�ַ(��ʱ���ܺ�searchһ����) 
	bst.insert(2); 
	bst.insert(6);
	bst.insert(8);
	bst.insert(9);
	//����������»��С������������ 
	bst.travIn_I(print); //BinTree��������������� 
	cout << endl;
	//size�ӿڷ�����Ŀ 
	cout <<"size: " << bst.size() << endl;
	//�����ɾ��Ԫ�� 
	bst.remove(3);
	bst.remove(7);
	bst.remove(1);
	cout << "BST after remove 3, 7, 1: ";
	//print��������Ȼ���������Ҳ���ԣ��������������֧���Զ�������� 
	bst.travIn_I(print); 
	cout << endl;
	return 0;
} 
