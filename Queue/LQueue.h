#ifndef _LQUEUE_H_
#define _LQUEUE_H_
#include <iostream>
#include "Link.h"
using std::cout;
using std::endl;

template <typename E>
class LQueue {
private:
	Link<E>* front;
	Link<E>* rear;
	int size;
	
public:
	//��������
	//Ϊ�������������Ԫ�ص�ʱ�򣬴���һ��ͷ��㣬��ʼ��ʱfront��rear��ָ�����ͷ��� 
	LQueue() {
		front = rear = new Link<E>();
		size = 0; 
	}
	virtual ~LQueue() {
		clear();
		delete front; //ɾ��ͷ��� 
	}
	//�����ӿ�
	void clear() {
		while (front->next) {
			Link<E>* oldFront = front;
			front = front->next;
			delete oldFront;
		}
		size = 0;
	} 
	void enqueue(const E& item) {
		Link<E>* oldRear = rear;
		rear = new Link<E>(item);
		oldRear->next = rear;
		size++; 
	}
	E dequeue() {
		if (size == 0) {
			cout << "Queue is empty." << endl;
		} else {
			Link<E>* oldFront = front;
//			E item = oldFront->element;
			front = front->next;
			delete oldFront;
			size--; 
			return front->element;
		}
	}
	const E& frontValue() const {
		if (size == 0) {
			cout << "Queue is empty." << endl; 
		} else {
			return front->next->element;
		}
	} 
	virtual int length() const {
		return size;
	}
	bool isEmpty() const {
		return !size;
	} 
};	

#endif
