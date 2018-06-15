#ifndef _SORT_IMPLEMENTATION_H_
#define _SORT_IMPLEMENTATION_H_
//#include "..\PQ\PQ\PQ_ComplHeap.h"
//冒泡排序
template <typename E>
void AList<E>::swap(E& a, E& b) {
	E temp = a;
	a = b;
	b = temp;
}

template <typename E>
void AList<E>::bubbleSort(Rank lo, Rank hi) { //冒泡排序算法(稳定的排序算法)
	//逐趟做扫描交换，直至全序，bubble函数返回sorted为true说明之前的均有序了，while随即停止 
	while (!bubble(lo, hi--)) ; 
}

template <typename E> 
bool AList<E>::bubble(Rank lo, Rank hi) {  //扫描交换
	bool sorted = true; //整体有序标志 
	while (++lo < hi) {
		if (_listArray[lo-1] > _listArray[lo]) {
			sorted = false;
			swap(_listArray[lo-1], _listArray[lo]);
		}
	} 
	return sorted; 
}
//冒泡排序（改进版）
template <typename E>
void AList<E>::bubbleSort_fast(Rank lo, Rank hi) {
	//返回的值即为最后发生交换的一个位置，也即完成最后一次bubble之后无序向量的末尾之后一个位置的哨兵，把它赋值给hi即可 
	while (lo < (hi = bubble_fast(lo, hi))) ;  
}

template <typename E>
Rank AList<E>::bubble_fast(Rank lo, Rank hi) {
	Rank last = lo;
	//完全有序时，last == lo,在bubbleSort_fast里面直接跳出循环 
	while (lo++ < hi) {
		if (_listArray[lo-1] > _listArray[lo]) { //若逆序，则 
			last = lo;
			swap(_listArray[lo-1], _listArray[lo]);
		}
	}
	return last;
}

//向量归并排序 
template <typename E>
void AList<E>::mergeSort(Rank lo, Rank hi) { 
	//base case 
	if (hi - lo < 2) return; //单元素区间自然有序，否则..
	//recursive case 
	int mi = (lo + hi) / 2; //以中点为界
	mergeSort(lo, mi); //分别排序 
	mergeSort(mi, hi);
	merge(lo, mi, hi); //归并
}

//有序向量的归并
template <typename E> 
void AList<E>::merge(Rank lo, Rank mi, Rank hi) {
	E* A = _listArray + lo; //合并后的向量A[0, hi-lo) = _listArray[lo,hi)
	int lenB = mi - lo;
	E* B = new E[lenB];  //前子向量B[0, lb) = _elem[lo, mi)
	for (Rank i = 0; i < lenB; i++) { //复制前子向量 
		B[i] = A[i];
	}
	int lenC = hi - mi; 
	E* C = _listArray + mi; //后子向量C[0, lc) = _elem[mi, hi)
	for (Rank i = 0, j = 0, k = 0; (j < lenB) || (k < lenC); ) {
		if ((j < lenB) && (!(k < lenC) || B[j] <= C[k])) A[i++] = B[j++];
		if ((k < lenC) && (!(j < lenB) || C[k] < B[j]))  A[i++] = C[k++];
	}
	delete[] B; //释放临时空间B 
} //归并后得到完整的有序向量[lo, hi) 

//向量的快速排序 (不稳定，就地算法） 
//性能：时间复杂度：最好O(nlogn),最坏O(n^2) 平均O(nlogn)
//（同是divide-and-conquer,mergeSort关键在于"合"，quickSort关键在于"分"） 
template <typename E>
void AList<E>::quickSort(Rank lo, Rank hi) {
	//base case 
	if (hi - lo < 2) return; //单元素自然有序
	Rank mi = partition(lo, hi-1); //在[lo, hi-1)内构造轴点 
	quickSort(lo, mi); //对前缀[lo, mi)递归排序 
	quickSort(mi+1, hi); //对后缀[mi+1, hi)递归排序 
} 

//quickSort的轴点划分函数
//功能是找出函数的一个轴点（不存在也会创造出一个），返回其秩 
//时间复杂度O(n), 空间复杂度O(1)(就地算法) 
template <typename E>
Rank AList<E>::partition(Rank lo, Rank hi) {
	E pivot = _listArray[lo]; //拷贝轴点候选，此时lo由于被拷贝过了，该位置变为一个空闲位置 
	while (lo < hi) {
		//在Rank为hi的元素>=pivot的情况下，向左拓展右端子向量 
		while ((lo < hi) && (pivot <= _listArray[hi])) hi--;  
		//直到不满足，此时的Rank为hi的元素恰好满足左端子向量的条件
		//hi的元素拷贝到lo处(lo在拷贝前是一个空闲位)，hi变为一个空闲位置 
		_listArray[lo] = _listArray[hi]; 
		//对称 
		while ((lo < hi) && (pivot >= _listArray[lo])) lo++;
		_listArray[hi] = _listArray[lo]; 
	}
	//while退出时，lo = hi = 空闲位，此处即为保存的pivot应处于的位置
	_listArray[lo] = pivot; //将备份的轴点记录置于前后子向量之间
	return lo; //返回轴点的位置 
} 

//template <typename E>
//void AList<E>::heapSort(Rank lo, Rank hi) {
//	PQ_ComplHeap<E> H(_listArray + lo, hi - lo);
//	while (!H.empty()) {
//		_listArray[--hi] = H.delMax();
//	}
//}
#endif
