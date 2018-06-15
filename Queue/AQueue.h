#ifndef _AQUEUE_H_ 
#define _AQUEUE_H_
#include <iostream>
using std::cout;
using std::endl;

template <typename E>
class AQueue {
private:
	int maxSize; //ע������õĿռ���maxSize-1 
	int front;
	int rear;
	E* listArray;
	
public:
	//�������� 
	AQueue(int size = 15) : maxSize(size + 1), rear(0), front(1) {
		listArray = new E[maxSize + 1]; //����ѭ�����еĿպ�����ѭ��������Ϊ�˷�ֹ�ƶ����У�
	}
	virtual ~AQueue() {
		delete[] listArray;
	}
	//�����ӿ�
	void clear() {
		rear = 0;
		front = 1;
	}
	void enqueue(const E& item) {
		if ((rear + 2) % maxSize == front) {
			cout << "Queue is full." << endl;
		} else {
			rear = (rear + 1) % maxSize;
			listArray[rear] = item;
		}
	}
	E dequeue() {
		if (length() == 0) {
			cout << "Queue is empty." << endl;
		} else {
			E item = listArray[front];
			front = (front + 1) % maxSize;
			return item;
		}
	}
	const E& frontValue() const {
		if (length() == 0) {
			cout << "Queue is empty." << endl;
		} else {
			return listArray[front];
		}
	} 
	virtual int length() const {
		return (rear + 1 + maxSize - front) % maxSize; 
	}
	bool isEmpty() const {
		return front == (rear + 1);
	}
};

#endif
