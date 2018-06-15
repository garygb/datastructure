#ifndef _LSTACK_H_
#define _LSTACK_H_
#include <iostream>
#include "Link.h"
using std::cout;
using std::endl;

template <typename E>
class LStack {
private:
	Link<E>* top;
	int size;
public:
	LStack() {
		top = NULL; 
		size = 0;
	}
	virtual ~LStack() {
		clear();
	}
	void clear() {
		while (top != NULL) {
			Link<E>* temp = top;
			top = top->next;
			delete temp;
		}
		size = 0;
	}
	void push(const E& item) {
		top = new Link<E>(item, top);
		size++;
	}
	E pop() {
		if (top == NULL) {
			cout << "Stack is empty." << endl;
		} else {
			E item = top->element;
			Link<E>* temp = top;
			top = top->next;
			delete temp;
			size--;
			return item;
		}
	}
	const E& topValue() {
		if (top == NULL) {
			cout << "Stack is empty." << endl;
		} else {
			return top->element;
		}
	}
	int length() const {
		 return size;
	}
	bool isEmpty() const {
		return (!size);
	}
}; 

#endif 
