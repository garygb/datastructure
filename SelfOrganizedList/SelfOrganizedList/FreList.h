#ifndef _FRELIST_H_
#define _FRELIST_H_
#include "..\..\List\AList.h"

//使用频率自组织启发式规则的类  
//Least frequently used(LFU) record-replacement algorithm
//缺点是一旦一条记录被访问了很多次，不管将来的访问历史怎么样，他都会一直在线性表的前面
template <typename E>
class FreList : protected AList<E> { 
	//由于未完全重写父类AList的所有接口，特地使用保护继承，防止user访问父类的接口引起错误 
protected:
	int* _fre;
	
//FreList API调用的函数 
	//空间不足时扩容(增加了对_fre数组的动态扩容)
	virtual void expand() { 
		if (_listSize < _maxSize) return; //尚未满员时不必扩容 
		E* oldListArray = _listArray;
		int* oldFre = _fre; 
		_maxSize <<= 1;
		_listArray = new E[_maxSize]; //容量加倍
		_fre = new int[_maxSize];
		for (int i = 0; i < _listSize; i++) { //复制原向量内容(E为基本类型或者已经重载过操作符"=") 
			_listArray[i] = oldListArray[i];
			_fre[i] = oldFre[i];
		} 
		delete[] oldListArray; //释放原空间 
		delete[] oldFre;
	}
	//装填因子过小时压缩向量所占空间(增加了对_fre数组的动态缩容)
	virtual void shrink() {
		if ( _maxSize < (DEFAULT_CAPACITY << 1) ) return; //不致收缩到DEFAULT_CAPACITY以下
		if (_listSize << 2 > _maxSize) return; //以25%为界
		E* oldListArray = _listArray;
		int* oldFre = _fre; 
		_maxSize >>= 1;
		_listArray = new E[_maxSize]; //容量减半
		_fre = new int[_maxSize];
		for (int i = 0; i < _listSize; i++) { //复制原向量内容 
			_listArray[i] = oldListArray[i];
			_fre[i] = oldFre[i];
		} 
		delete[] oldListArray; //释放原空间 
		delete[] oldFre;
	}
	
public:
	//构造析构 
	FreList(int maxSize = DEFAULT_CAPACITY) : AList(maxSize) {
		_fre = new int[maxSize];
	}
	virtual ~FreList() { delete[] _fre; } //会自动调用父类的析构
 
//操作接口
	//只读访问接口
	int length() const { return AList::length(); }
	bool empty() const { return AList::empty(); }	
	//可写访问接口
	//无序向量的区间查找：返回第一个元素item在查找之前的位置；失败时，返回-1
	// 如果这条记录已经大于它前面的记录的访问数, 这条记录就会在线性表中向前移动
	//E可以为可判等的基本类型，或已重载操作符"=="或"!="
	Rank search(const E& item, Rank lo, Rank hi) { 
		if (0 <= lo && lo < hi && hi <= _listSize) {
			Rank r = 0;
			for (; r < hi; r++) { //从前向后，顺序查找 
				if (item == _listArray[r]) {
					_fre[r]++; //该序号对应的访问次数++ 
					break;
				}
			}
			if (r == hi) { //r = hi则意味查找失败返回-1，否则返回命中元素在查找前的秩（查找后可能被移动） 
				return -1;
			} else {
				E data = _listArray[r]; //保存查找到的元素和访问数 
				int fre =  _fre[r];
				Rank tempr = r - 1; 
				while (tempr >= 0 && _fre[tempr] < fre) { //从其前一个元素开始，依次将访问数小于fre的元素和访问数向后移动一格 
					_listArray[tempr+1] = _listArray[tempr];
					_fre[tempr+1] = _fre[tempr];
					tempr--;
				} //直到tempr小于0 或者 找到tempr所指的访问数大于等于fre 
				tempr++; //将查找到的元素和访问数信息*插入*tempr所指向位置的之后一格 
				_listArray[tempr] = data;
				_fre[tempr] = fre; 
				return r; //返回第一个元素item（查找元素）在查找之前的位置
			}
		} else {
			cout << "Invalid finding range!" << endl;
//			exit(-1);
		}
	} 
	//无序向量的整体查找
	Rank search(const E& item) {
		return search(item, 0, _listSize);
	}  
	//在列表的末尾添加元素，返回插入元素的秩(下标)*从0开始*  
	virtual Rank append (const E& item) {
		expand();  //如有必要，扩容 
		_listArray[_listSize] = item;
		_fre[_listSize] = 1;
		_listSize++;
		return (_listSize - 1);
	} 
	//删除在在区间[lo, hi)之内的元素，返回被删除元素数目 
	virtual int remove(Rank lo, Rank hi) {
		if (0 <= lo && lo <= hi && hi <= _listSize) {
			if (lo == hi) return 0; //处于效率考虑,单独考虑退化的情况
			while (hi < _listSize) {
				_listArray[lo] = _listArray[hi]; //[hi, _listSize)顺次前移hi-lo个单元 
				_fre[lo] = _fre[hi];
				lo++; hi++;
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
	void traverse(void (*visit)(E&)) {
		AList::traverse(visit);
	} 
//	template <typename VST>
//	void traverse(VST& visit) {
//		AList::traverse(visit);
//	}
};


#endif