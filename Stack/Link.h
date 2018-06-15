#ifndef LINK_H_
#define LINK_H_

template <typename E>
class Link {
public:
	//����дһ����Ԫ�࣬��������˽�е�element��next�� ��ô���� 
	Link(const E& elemval, Link<E>* nextval = NULL) 
		: element(elemval), next(nextval) {}
	Link(Link<E>* nextval = NULL) : next(nextval) {}
	virtual ~Link() {}
	E element;
	Link<E>* next;
};

#endif
