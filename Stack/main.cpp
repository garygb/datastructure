#include <iostream>
#include "AStack.h" 
#include "LStack.h"

int main(int argc, char** argv) {
	
	AStack<int> astack;
	astack.push(0);
	astack.push(1);
	astack.push(2);
	cout << astack.topValue() << endl;
	cout << astack.pop() << " ";
	cout << astack.pop() << " ";
	cout << astack.pop() << endl; 
	
	astack.pop();
	LStack<double> lstack; 
	lstack.push(0);
//	lstack.pop(); 
	lstack.push(1);
	lstack.push(2);
	cout << lstack.topValue() << endl;
	cout << lstack.pop() << " ";
	cout << lstack.pop() << " ";
	cout << lstack.pop() << endl; 
	
	lstack.pop();
	
	return 0;
}
