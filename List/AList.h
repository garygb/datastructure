#ifndef ALISH_H_
#define ALIST_H_
#include <iostream>
#include <cstdlib>
#define DEFAULT_CAPACITY 3 //默认的AList初始容量，可以在这里修改成更大的值
typedef int Rank; //秩，即为数组的下标 e.g. AList[Rank] 
using std::cout;
using std::endl;

template <typename E>
class AList {
protected:
	int _maxSize;
	int _listSize;
	E*  _listArray;
	 
//sort函数 Lower bound for comparison based Alg = O(nlogn)
	//sort调用的接口 
	void swap(E& a, E& b);
	bool bubble(Rank lo, Rank hi); //扫描交换
	Rank bubble_fast(Rank lo, Rank hi); //扫描交换(改进版) 
	void merge(Rank lo, Rank mi, Rank hi); //归并 
	Rank partition(Rank lo, Rank hi); //quickSort的轴点划分函数
	
	//冒泡排序算法(稳定的排序算法) 最好O(n),最坏O(n^2) 就地算法 
	void bubbleSort(Rank lo, Rank hi); 
	//冒泡排序算法(改进版，稳定)  最好O(n),最坏O(n^2) 就地算法 
	void bubbleSort_fast(Rank lo, Rank hi); 
	//归并排序算法(稳定) 时间复杂度O(nlogn), 空间复杂度O(n) 
	void mergeSort(Rank lo, Rank hi);
	//向量的快速排序 (不稳定，就地算法） 
	//性能：时间复杂度：最好O(nlogn),最坏O(n^2) 平均O(nlogn)
	void quickSort(Rank lo, Rank hi); 
//	void heapSort(Rank lo, Rank hi);
	
//接口调用的操作函数 
	//以数组区间A[lo, hi)为蓝本复制向量
	void copyFrom(const E* A, Rank lo, Rank hi) { 
		_listArray = new E[_maxSize = 2 * (hi - lo)]; //分配空间，规模清零
		_listSize = 0;
		while (lo < hi) { //A[lo, hi)内的元素逐一 
			_listArray[_listSize++] = A[lo++]; //复制至_listArray[0, hi-low) 
		}
	} 
	//空间不足时扩容 
	virtual void expand() { 
		if (_listSize < _maxSize) return; //尚未满员时不必扩容 
		E* oldListArray = _listArray;
		_listArray = new E[_maxSize <<= 1]; //容量加倍
		for (int i = 0; i < _listSize; i++) { //复制原向量内容(E为基本类型或者已经重载过操作符"=") 
			_listArray[i] = oldListArray[i];
		} 
		delete[] oldListArray; //释放原空间 
	}
	//装填因子过小时压缩向量所占空间
	virtual void shrink() {
		if ( _maxSize < (DEFAULT_CAPACITY << 1) ) return; //不致收缩到DEFAULT_CAPACITY以下
		if (_listSize << 2 > _maxSize) return; //以25%为界
		E* oldListArray = _listArray;
		_listArray = new E[_maxSize >>= 1]; //容量减半
		for (int i = 0; i < _listSize; i++) { //复制原向量内容 
			_listArray[i] = oldListArray[i];
		} 
		delete[] oldListArray; //释放原空间 
	}
	
public:
//构造函数 
	//创建一个空表 
	AList (int maxSize = DEFAULT_CAPACITY) { 
		_maxSize = maxSize;
		_listSize = 0;
		_listArray = new E[_maxSize];
	} 
	//创建一个最大容量为maxSize，并包含listSize个元素值为element的列表
	AList(int listSize, E element) : 
		_maxSize(2 * listSize), _listSize(listSize) {;
		_listArray = new E[_maxSize];  
		for (int i = 0; i < listSize; i++) {
			_listArray[i] = element;
		}
	}
	AList(const E* A, Rank n) { copyFrom(A, 0, n); } //数组整体复制
	AList(const E* A, Rank lo, Rank hi) { copyFrom(A, lo, hi); } //数组区间复制 
	AList( const AList<E>& V ) { copyFrom(V._listArray, 0, V._listSize); } //向量整体复制
//	AList( const AList<E>& V, Rank lo, Rank hi ) { 
//		if (0 <= lo && lo < hi && hi <= V._listSize) {
//			copyFrom(V._listArray, lo, hi);
//		} else { 
//			cout << "Invalid copy range." << endl;
//		}
//	} //向量区间复制 
//析构函数 
	virtual ~AList() { delete[] _listArray; } //有virtual函数，必须使用virtual destructer
	
//操作接口 

//只读访问接口 
	int length() const { return _listSize; }
	bool empty() const { return !_listSize; }	
	int maxSize () { return _maxSize; }
	bool isSorted() const {
		bool isSorted = true;
		for (int i = 1; i < _listSize; i++) {
			//存在紧邻逆序对，即说明非有序 
			if (_listArray[i-1] > _listArray[i])  isSorted = false; 
		}
		return isSorted;
	}
	//无序向量的区间查找：返回最后一个元素item的位置；失败时，返回lo - 1,E可以为可判等的基本类型，或已重载操作符"=="或"!="
	Rank find(const E& item, Rank lo, Rank hi) const { 
		if (0 <= lo && lo < hi && hi <= _listSize) {
			Rank r = hi - 1;
			for (; r >= lo; r--) { //从后向前，顺序查找 
				if (item == _listArray[r])
					break;
			}
			return r; //hi = low - 1则意味查找失败，否则返回命中元素的秩 
		} else {
			cout << "Invalid finding range!" << endl;
//			exit(-1);
		}
	} 
	//无序向量的整体查找
	Rank find(const E& item) const {
		return find(item, 0, _listSize);
	} 
//可写访问接口
	E& operator[] (Rank r) {
		if (r >= 0 && r <= _listSize) {
			return _listArray[r];
		} else {
			cout << "Invalid rank." << endl; 
//			exit(-1);
		}
	}
	//重载"="运算符，以便实现array之间的赋值 
	AList<E>& operator= ( const AList<E>& V ) {
	   	if ( _listArray ) delete [] _listArray; //释放原有内容
  		copyFrom ( V._listArray, 0, V._listSize ); //整体复制
   		return *this; //返回当前对象的引用，以便链式赋值
	}
	void clear() {
		delete[] _listArray;
		_listSize = 0;
		_listArray = new E[_maxSize];
	}
	//在秩为r的位置插入元素，返回插入元素的秩(下标)*从0开始* 
	int insert(Rank r, const E& item) {
		if ( 0 <= r && r <= _listSize) {
			expand();//若有必要，扩容
			for (int i = _listSize; i > r; i--) { //自后向前，后继元素顺次后移一个单元
				_listArray[i] = _listArray[i-1];
			}
			_listArray[r] = item;
			_listSize++; //置入新元素并更新容量
			return r; //返回秩
		} else {
			cout << "Invalid insertion rank!" << endl;
//			exit(-1);
		}
	}
	//在列表的末尾添元素，返回插入元素的秩(下标)*从0开始* 
	virtual Rank append (const E& item) {
		expand();  //如有必要，扩容 
		_listArray[_listSize++] = item;
		return (_listSize - 1);
	}
	//删除在在区间[lo, hi)之内的元素，返回被删除元素数目 
	virtual int remove(Rank lo, Rank hi) {
		if (0 <= lo && lo <= hi && hi <= _listSize) {
			if (lo == hi) return 0; //处于效率考虑,单独考虑退化的情况
			while (hi < _listSize) {
				_listArray[lo++] = _listArray[hi++]; //[hi, _listSize)顺次前移hi-lo个单元 
			} 
			_listSize = lo; //更新规模，直接丢弃尾部[lo, _listSize = hi)的区间
			shrink(); //若有必要，则缩容 
			return hi - lo; //返回被删除元素的数目 
		} else {
			cout << "Invalid deletion rank!" << endl; 
//			exit(-1);
		}
	}
	//删除秩为r的元素，返回该元素 
	virtual E remove(Rank r) {
		if (r >= 0 && r <= _listSize) {
			E item = _listArray[r]; //备份被删除元素 
			remove(r, r+1); //等效于区间删除算法，删除[r, r+1)的区间 
			return item; //返回被删除元素
		} else {
			cout << "Invalid deletion rank!" << endl; 
//			exit(-1);
		}
	} 
	//无序元素去重,返回删除元素的数目 O(n^2)
	int deduplicate() {
		int oldSize = _listSize;
		int deleteItems;
		Rank i = 1; //从_listArray[1]开始 
		while (i < _listSize) { //自前向后逐一考查各元素_elem[i]
			(find(_listArray[i], 0, i) < 0) ? //在其前缀中寻找与之雷同者（至多一个）
			i++ : remove(i);  //若无雷同则继续考查其后继，否则删除雷同者
		}
		deleteItems = oldSize - _listSize;
		shrink();
		return deleteItems; //删除元素数目 
	}
//sort
	void sort(Rank lo, Rank hi,int type) { //对[lo, hi)排序 
		switch (type % 4) {
			case 0: bubbleSort(lo, hi); break;
			case 1: bubbleSort_fast(lo, hi); break;
			case 2: mergeSort(lo, hi); break; 
			case 3: quickSort(lo, hi); break;
//			case 4: heapSort(lo, hi); break; 
		}
	}
	void sort(int type) { sort(0, _listSize, type); } //整体排序 
	//区间置乱 
	void unsort(Rank lo, Rank hi) { //等概率随机置乱区间[lo, hi)
		E* V = _listArray + lo; //将子向量_elem[lo, hi)视作另一向量V[0, hi - lo)
		for (Rank i = hi - lo; i > 0; i--) { //自后向前
			//rand(): 头文件<cstdlib> 
			swap(V[i-1], V[rand() % i]); //将V[i - 1]与V[0, i)中某一元素随机交换
		}
	}
	//整体置乱 
	void unsort() { unsort(0, _listSize); } 
//遍历
	//传入函数指针
	void traverse(void (*visit)(E&)) {
		for (int i = 0; i < _listSize; i++) {
			visit(_listArray[i]);
		} 
	} 
	//传入对象（重载（）的对象->仿函数）
	//更通用，好处：1.具有状态 2.效率更高
//	template <typename VST>
//	void traverse(VST& visit) {
//		for (int i = 0; i < _listSize; i++) {
//			visit(_listSize[i]);
//		}
//	}
};  

#include "sort_implementation.h" 
#endif
