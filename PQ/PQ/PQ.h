#ifndef _PQ_H_
#define _PQ_H_

template <typename T>
class PQ { //���ȼ�����PQģ����
protected:
	virtual void append(T item) = 0; //���ձȽ���ȷ�������ȼ�����������
	virtual T getMax() = 0; //ȡ�����ȼ���ߵĴ���
	virtual T delMax() = 0; //ɾ�����ȼ���ߵĴ���
}; 

#endif
