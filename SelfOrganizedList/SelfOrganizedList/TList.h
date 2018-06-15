#ifndef _TLIST_H_
#define _TLIST_H_
#include "..\..\List\AList.h"

//���ڱ���search���ص���Ϣ
class Info {
public:
	int cmpTime;
	bool isFind;
	Info() : cmpTime(0), isFind(false) { }
	Info(int time, bool find) : cmpTime(time), isFind(find) { }
};

//ת�÷�����֯���Ա�  
template <typename E>
class TList : public AList<E> { 		
public:
	//��������
	TList(int maxSize = DEFAULT_CAPACITY) : AList(maxSize) { }
	virtual ~TList() { } //���Զ����ø��������
 
//�����ӿ�
	//��д���ʽӿ�
	//����������������ң����رȽϵĴ������Ƿ��ҵ�
	//E����Ϊ���еȵĻ������ͣ��������ز�����"=="��"!="
	Info search(const E& item, Rank lo, Rank hi) { 
		if (0 <= lo && lo < hi && hi <= _listSize) {
			int count = 0;
			bool isFind = false;
			Rank r = 0;
			for (; r < hi; r++) { //��ǰ���˳����� 
				count++;
				if (item == _listArray[r] && r > 0) {
					swap(_listArray[r], _listArray[r-1]); 
					isFind = true;
					break;
				}
			}
			if (isFind) { //���رȽϵĴ������Ƿ��ҵ�
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
	//�����������������
	Info search(const E& item) {
		return search(item, 0, _listSize);
	}  

};

#endif