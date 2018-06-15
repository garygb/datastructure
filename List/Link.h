#ifndef LINK_H_
#define LINK_H_

template <typename E>
class Link {
public:
	//可以写一个友元类，让他访问私有的element和next吗？ 怎么做？ 
	Link(const E& elemval, Link* nextval = NULL) 
		: element(elemval), next(nextval) {}
	Link(Link* nextval = NULL) : next(nextval) {}
	~Link() {}
	E element;
	Link* next;
};

#endif
