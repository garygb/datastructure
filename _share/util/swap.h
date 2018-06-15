#ifndef _SWAP_H_
#define _SWAP_H_

template <typename T>
static bool swap(T& a, T& b) { //交换两个对象 
	T temp(a);
	a = b;
	b = temp;
} 


#endif  
