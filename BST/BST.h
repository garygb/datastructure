#ifndef _BST_H_
#define _BST_H_
#include "..\BinTree\BinTree.h"

template <typename T>
class BST : public BinTree<T> {
public:
//�����ӿ� 
	//���� ���ز��ҵ���λ�õ�ָ������ã������ں���������� 
	//�����������������searchIn��ԭ���ǣ��ⲿ����ֻҪ��һ�������ͺ��ˣ��������ˣ�_root��_hot�����ڲ��ı���,�ⲿ���贫�룩 
	virtual BinNode<T>* & search(const T& e) { //O(h)
		//ע�⴫���_hot��һ�����ã�����search����Ԫ����һ�����ڵģ�ָ���NULL������һ�������ڵģ�ָ��ΪNULL����_hot��ָ�����ĸ��� 
		return searchIn(this->_root, e, _hot = NULL); //�Ӹ��ڵ��������� 
	} 
	//����(���Ժܺõش�����������) O(h)
	virtual BinNode<T>* insert(const T& e) { 
		BinNode<T>* & x = search(e); //����Ŀ�꣨����������_hotָ������Ҫ����Ŀ��ĸ��ף� 
		if (!x) { //��x == NULLʱ���к�����������ֹ������ͬԪ�أ��ڲ���ʧ��ʱ��ʵʩ������� 
			//������case��x(��_root)������һ�����ڵ�BinNode<T>(e, _hot = NULL)
			//����case��x(�󶨲��ҵ����Ǹ�(_hot->) lChild����rChild),����һ��Ҷ�ӽ��BinNode<T>(e, _hot)
			x = new BinNode<T>(e, _hot); //�����½ڵ㣬��_hotΪ���� 
			this->_size++; //����ȫ����ģ 
			this->updateHeightAbove(x); //�����������ȵĸ߶�
		}
		return x; 
	} //����e�Ƿ������ԭ���У�����ʱ����x->data == e
	//ɾ�� ���سɹ����ɾ�������ڵ�Ԫ�ط���false�� 
	virtual bool remove(const T& e) {  //O(h)
		BinNode<T>* & x = search(e); //��λĿ����
		if (!x) return false; //ȷ��Ŀ�����(��ʱ_hotΪx�ĸ���)
		removeAt(x, _hot); //�����������ʵʩɾ��������ȫ����ģ 
		this->_size--; //����ȫ����ģ 
		this->updateHeightAbove(_hot); //����_hot�����������ȵĸ߶�
		return true; 
	} //ɾ���ɹ�����ɷ���ֵָʾ 
protected:
	BinNode<T>* _hot; //���нڵ�ĸ���
//	BinNode<T>* connect34( //3 + 4�ع� 
//		BinNode<T>*, BinNode<T>*, BinNode<T>*,
//		BinNode<T>*, BinNode<T>*, BinNode<T>*, BinNode<T>*);
//	BinNode<T>* rotateAt(BinNode<T>*); //��ת����
	//�����ӿڵ��õĺ���
	BinNode<T>* & searchIn(BinNode<T>* & v, //��ǰ(��)���� 
		const T& e, //Ŀ��ؼ��� 
		BinNode<T>* & hot) { //�����ȵ�(�����ڲ��޸�����ʹ����Ϊ���ҵ����ĸ���)
		if (!v || e == v->data) return v; //����ȷ��ʧ�ܻ��߳ɹ������ߣ�
		hot = v; //�ȼ��µ�ǰ���ǿգ����
		return searchIn(((e < v->data) ? v->lChild : v->rChild), e, _hot); 
	} //����ʱ�������ڷ��ؽ��v����ȣ�����������O(h) 
	BinNode<T>* removeAt(BinNode<T>* & x, BinNode<T>* & hot) {
		BinNode<T>* w = x; //ʵ�ʱ�ժ���Ľ�㣬��ֵͬx
		BinNode<T>* succ = NULL; // ʵ�ʱ�ɾ���ڵ�Ľ�����
		if (!hasLC(*x)) { //��*x��������Ϊ��(��������������Ϊ�յ����)����� 
			succ = x = x->rChild; //ֱ�ӽ� *x�滻Ϊ������ 
//			succ->parent = w->parent;
		} else if (!hasRC(*x)) { //��*x��������Ϊ�գ���ʱ������һ����Ϊ�գ� 
			succ = x = x->lChild; //�ԳƵش�����ʱsucc != NULL�� 
//			succ->parent = w->parent;
		} else { //��x�����Һ��Ӳ��� 
			w = x->succ(); 
			swap(x->data, w->data); //��*x������*w�������� 
			BinNode<T>* u = w->parent;
			if (u == x) { //����ڵ�*w
				u->rChild = succ = w->rChild;
//				w->rChild->parent = u;
			} else {
				u->lChild = succ = w->rChild;
//				w->rChild->parent = u;
			}
		} 
		//���������׽������ӣ�ÿ��case��ʵ�����ͬ�� 
		hot = w->parent; //��¼�±�ɾ�����ĸ���
		if (succ) succ->parent = hot; //������ɾ���ڵ�Ľ�������hot����
		delete w; //�ͷű�ժ���ڵ�
		return succ; //���ؽ�����
	} //O(h) 
	void swap(T& a, T& b) {
		T temp = a;
		a = b;
		b = temp;
	}
};

#endif
