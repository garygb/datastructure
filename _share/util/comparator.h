#ifndef _COMPARATOR_H_
#define _COMPARATOR_H_

template <typename T>
static bool lessthan(T* a, T* b) { return lessthan(*a, *b); } // less than

template <typename T>
static bool lessthan(T& a, T& b) { return a < b; } //less than

template <typename T> 
static bool eq ( T* a, T* b ) { return eq ( *a, *b ); } //equal

template <typename T> 
static bool eq ( T& a, T& b ) { return a == b; } //equal

#endif  
