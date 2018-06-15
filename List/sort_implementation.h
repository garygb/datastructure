#ifndef _SORT_IMPLEMENTATION_H_
#define _SORT_IMPLEMENTATION_H_
//#include "..\PQ\PQ\PQ_ComplHeap.h"
//ð������
template <typename E>
void AList<E>::swap(E& a, E& b) {
	E temp = a;
	a = b;
	b = temp;
}

template <typename E>
void AList<E>::bubbleSort(Rank lo, Rank hi) { //ð�������㷨(�ȶ��������㷨)
	//������ɨ�轻����ֱ��ȫ��bubble��������sortedΪtrue˵��֮ǰ�ľ������ˣ�while�漴ֹͣ 
	while (!bubble(lo, hi--)) ; 
}

template <typename E> 
bool AList<E>::bubble(Rank lo, Rank hi) {  //ɨ�轻��
	bool sorted = true; //���������־ 
	while (++lo < hi) {
		if (_listArray[lo-1] > _listArray[lo]) {
			sorted = false;
			swap(_listArray[lo-1], _listArray[lo]);
		}
	} 
	return sorted; 
}
//ð�����򣨸Ľ��棩
template <typename E>
void AList<E>::bubbleSort_fast(Rank lo, Rank hi) {
	//���ص�ֵ��Ϊ�����������һ��λ�ã�Ҳ��������һ��bubble֮������������ĩβ֮��һ��λ�õ��ڱ���������ֵ��hi���� 
	while (lo < (hi = bubble_fast(lo, hi))) ;  
}

template <typename E>
Rank AList<E>::bubble_fast(Rank lo, Rank hi) {
	Rank last = lo;
	//��ȫ����ʱ��last == lo,��bubbleSort_fast����ֱ������ѭ�� 
	while (lo++ < hi) {
		if (_listArray[lo-1] > _listArray[lo]) { //�������� 
			last = lo;
			swap(_listArray[lo-1], _listArray[lo]);
		}
	}
	return last;
}

//�����鲢���� 
template <typename E>
void AList<E>::mergeSort(Rank lo, Rank hi) { 
	//base case 
	if (hi - lo < 2) return; //��Ԫ��������Ȼ���򣬷���..
	//recursive case 
	int mi = (lo + hi) / 2; //���е�Ϊ��
	mergeSort(lo, mi); //�ֱ����� 
	mergeSort(mi, hi);
	merge(lo, mi, hi); //�鲢
}

//���������Ĺ鲢
template <typename E> 
void AList<E>::merge(Rank lo, Rank mi, Rank hi) {
	E* A = _listArray + lo; //�ϲ��������A[0, hi-lo) = _listArray[lo,hi)
	int lenB = mi - lo;
	E* B = new E[lenB];  //ǰ������B[0, lb) = _elem[lo, mi)
	for (Rank i = 0; i < lenB; i++) { //����ǰ������ 
		B[i] = A[i];
	}
	int lenC = hi - mi; 
	E* C = _listArray + mi; //��������C[0, lc) = _elem[mi, hi)
	for (Rank i = 0, j = 0, k = 0; (j < lenB) || (k < lenC); ) {
		if ((j < lenB) && (!(k < lenC) || B[j] <= C[k])) A[i++] = B[j++];
		if ((k < lenC) && (!(j < lenB) || C[k] < B[j]))  A[i++] = C[k++];
	}
	delete[] B; //�ͷ���ʱ�ռ�B 
} //�鲢��õ���������������[lo, hi) 

//�����Ŀ������� (���ȶ����͵��㷨�� 
//���ܣ�ʱ�临�Ӷȣ����O(nlogn),�O(n^2) ƽ��O(nlogn)
//��ͬ��divide-and-conquer,mergeSort�ؼ�����"��"��quickSort�ؼ�����"��"�� 
template <typename E>
void AList<E>::quickSort(Rank lo, Rank hi) {
	//base case 
	if (hi - lo < 2) return; //��Ԫ����Ȼ����
	Rank mi = partition(lo, hi-1); //��[lo, hi-1)�ڹ������ 
	quickSort(lo, mi); //��ǰ׺[lo, mi)�ݹ����� 
	quickSort(mi+1, hi); //�Ժ�׺[mi+1, hi)�ݹ����� 
} 

//quickSort����㻮�ֺ���
//�������ҳ�������һ����㣨������Ҳ�ᴴ���һ�������������� 
//ʱ�临�Ӷ�O(n), �ռ临�Ӷ�O(1)(�͵��㷨) 
template <typename E>
Rank AList<E>::partition(Rank lo, Rank hi) {
	E pivot = _listArray[lo]; //��������ѡ����ʱlo���ڱ��������ˣ���λ�ñ�Ϊһ������λ�� 
	while (lo < hi) {
		//��RankΪhi��Ԫ��>=pivot������£�������չ�Ҷ������� 
		while ((lo < hi) && (pivot <= _listArray[hi])) hi--;  
		//ֱ�������㣬��ʱ��RankΪhi��Ԫ��ǡ���������������������
		//hi��Ԫ�ؿ�����lo��(lo�ڿ���ǰ��һ������λ)��hi��Ϊһ������λ�� 
		_listArray[lo] = _listArray[hi]; 
		//�Գ� 
		while ((lo < hi) && (pivot >= _listArray[lo])) lo++;
		_listArray[hi] = _listArray[lo]; 
	}
	//while�˳�ʱ��lo = hi = ����λ���˴���Ϊ�����pivotӦ���ڵ�λ��
	_listArray[lo] = pivot; //�����ݵ�����¼����ǰ��������֮��
	return lo; //��������λ�� 
} 

//template <typename E>
//void AList<E>::heapSort(Rank lo, Rank hi) {
//	PQ_ComplHeap<E> H(_listArray + lo, hi - lo);
//	while (!H.empty()) {
//		_listArray[--hi] = H.delMax();
//	}
//}
#endif
