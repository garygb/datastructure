#include "BST.h"

template <typename T>
BinNode<T>* & BST<T>::search(const T& e) { //����
	return searchIn(this->_root, e, _hot = NULL); //�Ӹ��ڵ��������� 
} 

	template <typename T>
	BinNode<T>* & BST<T>::searchIn(BinNode<T>* v, //��ǰ(��)���� 
		const T& e, //Ŀ��ؼ��� 
		BinNode<T>* & hot) { //�����ȵ�(�����ڲ��޸�����ʹ����Ϊ���ҵ����ĸ���)
		if (!v || e == v->data) return v; //����ȷ��ʧ�ܻ��߳ɹ������ߣ�
		hot = v; //�ȼ��µ�ǰ���ǿգ����
		return searchIn(((e < v->data) ? v->lChild : v->rChild), e, _hot); 
	} //����ʱ�������ڷ��ؽ��v����ȣ�����������O(h) 
