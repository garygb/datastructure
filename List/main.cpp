#include <iostream>
#include "AList.h"
#include "LList.h" 

int main() {
	//测试基于数组的线性表AList的操作 
	cout << "********************************测试基于数组的线性表AList的操作****************************************" << endl; 
	AList<int> alist;
	alist.append(1);
	alist.append(3);
	alist.append(4);
	alist.append(5); 
//	alist.moveToPos(1);
	alist.insert(2);
	alist.print(); 
	cout << "Length = "<< alist.length() << endl; 
	cout << "Here : " << alist[0] << endl;
	alist[0] = 99;
	alist.print();
	alist.moveToPos(3);
	cout << "Pos = "<< alist.currPos() << endl;
	
	alist.remove();
	cout << "Linked list after remove the (Pos+1)th element:" << endl;
	
	alist.print(); 
	cout << "Is 5 existed in the array list? " << (alist.find(5) ? "Yes" : "No") << endl;
	
	alist.clear();
	cout << "Array list after clear:" << endl;
	alist.print();

	
	//测试基于链表的线性表AList的操作 
	cout << "********************************测试基于链表的线性表LList的操作****************************************" << endl; 
	LList<int> llist;
	
	llist.append(1);
	llist.append(3);
	llist.append(4);
	llist.append(5); 
	llist.moveToPos(1);
	llist.insert(2);
	llist.print(); 
	cout << "Length = "<< llist.length() << endl; 
	cout << "Here : " << llist[0] << endl;
	llist[0] = 99;
	llist.print();
	llist.moveToPos(3);
	cout << "Pos = "<< llist.currPos() << endl;
	
	llist.remove();
	cout << "Linked list after remove the (Pos+1)th element:" << endl;
	llist.print(); 
	
	cout << "Is 5 existed in the array list? " << (llist.find(5) ? "Yes" : "No") << endl;

	cout << "Linked list after invert:" << endl;
	llist.reverse();
	llist.print(); 
	
	llist.clear();
	cout << "Linked list after clear:" << endl;
	llist.print();
	
	return 0;
} 
