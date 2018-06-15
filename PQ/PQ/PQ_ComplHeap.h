#ifndef _PQ_COMPLHEAP_H_
#define _PQ_COMPLHEAP_H_

#include "..\..\_share\util\util.h"
#include "..\..\List\AList.h"
#include "PQ.h"
#include "PQ_ComplHeap_macro.h" //���PQ_ComplHeap��ʹ�õ��ĺ�ָ��

template <typename T>
class PQ_ComplHeap : public PQ<T>, public AList<T> {
protected:
//�����ӿڵ��õĺ���
	//�Ե�i������ʵʩ���˲�����i < _listSize�� ʱ�临�Ӷ�O��logn��, �����������յִ��λ��
	//�����ȱ����㣬����滻�ķ���������ѡ�����򣨸�ֵ����Ϊx+1(����)+1(����)��xΪ�����Ĵ�����
	//��ÿ�ν����ķ���������ð�����򣨸�ֵ����Ϊ3x��
	Rank percolateUp(Rank i) { 
		T tempItem = _listArray[i]; //������Ҫ���˵ĵ�i��Ԫ��
		while (ParentValid(i)) { //ֻҪi�и���(��δ�ִ�Ѷ�)����
			Rank j = Parent(i); //��i֮������j
			if (lessthan(tempItem, _listArray[j])){ //һ������i�ĸ��״������Ԫ�أ�˵��rank i������Ҫ����Ԫ�ص�λ��
				break; //����ѭ��
			} else {  //����
				_listArray[i] = _listArray[j]; //�����ڵ��ֵ���浽�ӽڵ㴦
			}
			i = j; //������һ��
		}
		_listArray[i] = tempItem; //�������Ԫ�ز��뵽���յִ��λ��i����������;�����ˣ�Ҳ������i==0��
		return i; //�����������յִ��λ��
	}
	//��ǰn�������е�Rank = i�Ĵ���ʵʩ���ˣ�i < n, �������˵ִ��λ��
	Rank percolateDown(Rank n, Rank i) { 
		Rank j; //i���䣨�������������У�
		while (i != (j = ProperParent(_listArray, n, i))) {
			swap(_listArray[i], _listArray[j]);
			i = j;
		}
		return i; //�������˵ִ��λ��
	}
	//Floyd�����㷨�����¶��ϵ����˸�*�ڲ�*��㣩
	//�����Ϊ�Ӷѵ����ϲ���--���������ʣ������Ա�Ȼȫ�ָֻ�
	//���϶��µ������㷨<=> ʱ�临�Ӷ�O(nlogn) ̫����
	void heapify(Rank n) { 
		for (int i = LastInternal(n); i >= 0; i++) {
			percolateDown(n, i); //���˸��ڲ����
		}
	} 
public:
//��������
	PQ_ComplHeap() { } //Ĭ�Ϲ���
	PQ_ComplHeap(T* A, Rank n) { copyFrom(A, 0, n); heapify(n); } //�������� [0, n) size = n
	virtual ~PQ_ComplHeap() { }
//�����ӿ�
	virtual void append(T item) { //���ձȽ���ȷ�������ȼ�����������
		AList<T>::append(item);
		percolateUp(_listSize - 1);
	}
	virtual T getMax() { return _listArray[0]; } //ȡ�����ȼ���ߵĴ��� O(1)
	virtual T delMax() { //ɾ�����ȼ���ߵĴ���
		T maxItem = _listArray[0]; //�������Ԫ��
		_listArray[0] = _listArray[--_listSize]; //ժ���Ѷ�����ĩԪ�����֮
		percolateDown(_listSize, 0); //���¶�ʵʩ����
		return maxItem; //����֮ǰ���ݵ�������
	}
};

#endif
