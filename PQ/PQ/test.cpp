#include <iostream>
#include "PQ_ComplHeap.h"
using namespace std;

int main() {

	PQ_ComplHeap<int> priQ;
	priQ.append(5);
	priQ.append(3);
	priQ.append(7);
	cout << priQ.getMax() << endl;
	system("pause");
}