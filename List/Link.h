#ifndef LINK_H_
#define LINK_H_

template <typename E>
class Link {
public:
	//����дһ����Ԫ�࣬��������˽�е�element��next�� ��ô���� 
	Link(const E& elemval, Link* nextval = NULL) 
		: element(elemval), next(nextval) {}
	Link(Link* nextval = NULL) : next(nextval) {}
	~Link() {}
	E element;
	Link* next;
};

#endif
