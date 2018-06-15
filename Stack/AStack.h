#ifndef _STACK_H_
#define _STACK_H_
#include <iostream>
using std::cout; 
using std::endl;

template <typename E>
class AStack {
private:
	int maxSize; //max size of stack
	int top;     //index for top element
	E* listArray; //array holding stack elements
	
public:
	//构造析构 
	AStack(int size = 15) {
		maxSize = size;
		top = 0;
		listArray = new E[size];
	}
	virtual ~AStack() {
		delete[] listArray;
	} 
	//操作接口 
	void clear() {
		top = 0;
	}
	void push (const E & item) {
		if (top == maxSize) {
			cout << "Stack is full." << endl;
		} else {
		listArray[top++] = item;
		}
	}
	E pop() {
		if (top == 0) {
			cout << "Stack is empty." << endl;
		} else {
			return listArray[--top];
		}
	}
	const E& topValue() const {
		if (top == 0) {
			cout << "Stack is empty." << endl;
		}  else {
			return listArray[top-1];
		}
	}
	int length() const {
		return top;
	}
	bool isEmpty() const {
		return (!top);
	}
}; 

#endif 
