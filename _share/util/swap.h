#ifndef _SWAP_H_
#define _SWAP_H_

template <typename T>
static bool swap(T& a, T& b) { //������������ 
	T temp(a);
	a = b;
	b = temp;
} 


#endif  
