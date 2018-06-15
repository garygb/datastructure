#include <iostream>
#include "AQueue.h"
#include "LQueue.h" 

int main(int argc, char** argv) {
	cout << "AQueue:" << endl;
	AQueue<int> aqueue(2);
	cout << "Empty? " << (aqueue.isEmpty() ? "Yes" : "No") << endl;
	aqueue.enqueue(5);
	aqueue.enqueue(3);
	cout << "Empty? " << (aqueue.isEmpty() ? "Yes" : "No") << endl;
	cout << aqueue.dequeue() << endl;
	cout << aqueue.frontValue() << endl;
	cout << aqueue.length() << endl;
	aqueue.enqueue(4);
	cout << endl;
	cout << "LQueue:" << endl;
	LQueue<int> lqueue;
	cout << "Empty? " << (lqueue.isEmpty() ? "Yes" : "No") << endl;
	lqueue.enqueue(5);
	lqueue.enqueue(3);
	cout << "Empty? " << (lqueue.isEmpty() ? "Yes" : "No") << endl;
	cout << lqueue.dequeue() << endl;
	cout << lqueue.frontValue() << endl;
	cout << lqueue.length() << endl;
	lqueue.enqueue(4);
  
	return 0;
}
