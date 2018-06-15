#ifndef PQ_COMPLHEAP_MACRO_H_
#define PQ_COMPLHEAP_MACRO_H_

//������д��n����ʾ����Ķѵ�size��ʵ�ʶѵ�size���Ա�������Ϊ���ԶԶѵ�һ���ֽ��в���)
//i����������Ľ����ȣ�����ʵ�������飩
//PQ�������������ָ��
#define Parent(i) (((i) - 1) >> 1) //PQ[i]�ĸ��ڵ㣨floor((i-1)/2)��i����������
#define LChild(i) (((i) << 1) + 1) //PQ[i]������
#define RChild(i) (((i) + 1) << 1) //PQ[i]���Һ���
#define LastInternal(n)   Parent( n - 1 ) //���һ���ڲ��ڵ㣨��ĩ�ڵ�ĸ��ף�
#define ParentValid(i) ((i) > 0)  //�ж�PQ[i]�Ƿ��и���
#define InHeap(n, i) ((i) >= 0 && (i) < (n)) //�ж�PQ[i]�Ƿ�Ϸ�
#define LChildValid(n, i) InHeap(n, LChild(i)) //�ж�PQ[i]�Ƿ���һ�����󣩺���
#define RChildValid(n, i) InHeap(n, RChild(i)) //�ж�PQ[i]�Ƿ�����������
#define Bigger(PQ, i, j) (lessthan(PQ[i], PQ[j]) ? j : i) //������ֵ�ϴ��ߵ���
#define ProperParent(PQ, n, i) /*��ֵΪ����(����)�����е�����ߵ���*/\
		(RChildValid(n, i) ? Bigger(PQ, (Bigger(PQ, i, LChild(i))), RChild(i)) \
						   : (LChildValid(n, i) ? Bigger(PQ, i, LChild(i)) : i)) 
 //PQ[i]���������ӣ���������������ߵ���
 //PQ[i]��һ�����ӣ���������������ߵ���
 //PQ[i]�޺��ӣ�����i /*���ʱ���ڵ����ȣ���˿ɱ��ⲻ��Ҫ�Ľ���*/



#endif
