#include <iostream>
#include "AList.h" 
using namespace std;

//template <typename T>
//class Increase {
//private:
//	void operator() (T& e) {
//		e++;
//	}
//};
//
//template <typename T>
//void increase(AList<T>& V) {
//	V.traverse(Increase<T>());
//}

template <typename T>
void increase(T& item) {
	item++;
}

int main() {
	
	
	AList<int> alist;
	cout << alist.empty() << endl;
	AList<int> b(10,5);
	cout << b.maxSize() << endl;
	b.append(1);
	cout << b.maxSize() << endl;
	
	cout << b.empty() << endl;
	cout << b.length() << endl;
	b.print();
	b.deduplicate();
	cout << b.maxSize() << endl;
	b.print(); 
	b.append(3);
	b.print();
	b.insert(1,2);
	b.print();
	b.remove(0,2);
	b.print();
	cout << b[1] << endl;
//	b.clear();
	b.print();
	cout << b.maxSize() << endl;
	int a[] = {1,2,3};
//	AList<int> c(b,0,2);
//	c.print();
	AList<int> c;
	AList<int> d(10,5);
	c = d;
	c.print();
	c.traverse(increase);
	c.print();
	return 0;	
}
