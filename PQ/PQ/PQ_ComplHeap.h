#ifndef _PQ_COMPLHEAP_H_
#define _PQ_COMPLHEAP_H_

#include "..\..\_share\util\util.h"
#include "..\..\List\AList.h"
#include "PQ.h"
#include "PQ_ComplHeap_macro.h" //存放PQ_ComplHeap类使用到的宏指令

template <typename T>
class PQ_ComplHeap : public PQ<T>, public AList<T> {
protected:
//操作接口调用的函数
	//对第i个词条实施上滤操作，i < _listSize， 时间复杂度O（logn）, 返回上滤最终抵达的位置
	//这种先保存结点，最后替换的方法类似于选择排序（赋值次数为x+1(保存)+1(插入)，x为上升的次数）
	//而每次交换的方法类似于冒泡排序（赋值次数为3x）
	Rank percolateUp(Rank i) { 
		T tempItem = _listArray[i]; //保存需要上滤的第i个元素
		while (ParentValid(i)) { //只要i有父亲(尚未抵达堆顶)，则，
			Rank j = Parent(i); //将i之父记作j
			if (lessthan(tempItem, _listArray[j])){ //一旦发现i的父亲大于这个元素，说明rank i就是需要插入元素的位置
				break; //跳出循环
			} else {  //否则
				_listArray[i] = _listArray[j]; //将父节点的值保存到子节点处
			}
			i = j; //并上升一层
		}
		_listArray[i] = tempItem; //将保存的元素插入到最终抵达的位置i（可能是中途跳出了，也可能是i==0）
		return i; //返回上滤最终抵达的位置
	}
	//对前n个词条中的Rank = i的词条实施下滤，i < n, 返回下滤抵达的位置
	Rank percolateDown(Rank n, Rank i) { 
		Rank j; //i及其（至多两个孩子中）
		while (i != (j = ProperParent(_listArray, n, i))) {
			swap(_listArray[i], _listArray[j]);
			i = j;
		}
		return i; //返回下滤抵达的位置
	}
	//Floyd建堆算法（自下而上的下滤各*内部*结点）
	//可理解为子堆的逐层合并，--由以上性质，堆序性必然全局恢复
	//自上而下的上滤算法<=> 时间复杂度O(nlogn) 太慢！
	void heapify(Rank n) { 
		for (int i = LastInternal(n); i >= 0; i++) {
			percolateDown(n, i); //下滤各内部结点
		}
	} 
public:
//构造析构
	PQ_ComplHeap() { } //默认构造
	PQ_ComplHeap(T* A, Rank n) { copyFrom(A, 0, n); heapify(n); } //批量构造 [0, n) size = n
	virtual ~PQ_ComplHeap() { }
//操作接口
	virtual void append(T item) { //按照比较器确定的优先级次序插入词条
		AList<T>::append(item);
		percolateUp(_listSize - 1);
	}
	virtual T getMax() { return _listArray[0]; } //取出优先级最高的词条 O(1)
	virtual T delMax() { //删除优先级最高的词条
		T maxItem = _listArray[0]; //保存最大元素
		_listArray[0] = _listArray[--_listSize]; //摘除堆顶，以末元素替代之
		percolateDown(_listSize, 0); //对新堆实施下滤
		return maxItem; //返回之前备份的最大词条
	}
};

#endif
