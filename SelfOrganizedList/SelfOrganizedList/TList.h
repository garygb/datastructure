#ifndef _TLIST_H_
#define _TLIST_H_
#include "..\..\List\AList.h"

//用于保存search返回的信息
class Info {
public:
	int cmpTime;
	bool isFind;
	Info() : cmpTime(0), isFind(false) { }
	Info(int time, bool find) : cmpTime(time), isFind(find) { }
};

//转置法自组织线性表  
template <typename E>
class TList : public AList<E> { 		
public:
	//构造析构
	TList(int maxSize = DEFAULT_CAPACITY) : AList(maxSize) { }
	virtual ~TList() { } //会自动调用父类的析构
 
//操作接口
	//可写访问接口
	//无序向量的区间查找：返回比较的次数和是否找到
	//E可以为可判等的基本类型，或已重载操作符"=="或"!="
	Info search(const E& item, Rank lo, Rank hi) { 
		if (0 <= lo && lo < hi && hi <= _listSize) {
			int count = 0;
			bool isFind = false;
			Rank r = 0;
			for (; r < hi; r++) { //从前向后，顺序查找 
				count++;
				if (item == _listArray[r] && r > 0) {
					swap(_listArray[r], _listArray[r-1]); 
					isFind = true;
					break;
				}
			}
			if (isFind) { //返回比较的次数与是否找到
				Info info(count, true);
				return info;
			} else {
				Info info(count, false);
				return info; 
			}
		} else {
			cout << "Invalid finding range!" << endl;
//			exit(-1);
		}
	} 
	//无序向量的整体查找
	Info search(const E& item) {
		return search(item, 0, _listSize);
	}  

};

#endif