#ifndef _PQ_H_
#define _PQ_H_

template <typename T>
class PQ { //优先级队列PQ模板类
protected:
	virtual void append(T item) = 0; //按照比较器确定的优先级次序插入词条
	virtual T getMax() = 0; //取出优先级最高的词条
	virtual T delMax() = 0; //删除优先级最高的词条
}; 

#endif
