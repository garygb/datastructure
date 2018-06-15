#include "BST.h"

template <typename T>
BinNode<T>* & BST<T>::search(const T& e) { //查找
	return searchIn(this->_root, e, _hot = NULL); //从根节点启动查找 
} 

	template <typename T>
	BinNode<T>* & BST<T>::searchIn(BinNode<T>* v, //当前(子)树根 
		const T& e, //目标关键码 
		BinNode<T>* & hot) { //记忆热点(函数内部修改它，使它成为查找到结点的父亲)
		if (!v || e == v->data) return v; //足以确定失败或者成功，或者，
		hot = v; //先记下当前（非空）结点
		return searchIn(((e < v->data) ? v->lChild : v->rChild), e, _hot); 
	} //运行时间正比于返回结点v的深度，不超过树高O(h) 
