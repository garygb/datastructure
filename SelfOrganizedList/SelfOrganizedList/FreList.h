#ifndef _FRELIST_H_
#define _FRELIST_H_
#include "..\..\List\AList.h"

//ʹ��Ƶ������֯����ʽ�������  
//Least frequently used(LFU) record-replacement algorithm
//ȱ����һ��һ����¼�������˺ܶ�Σ����ܽ����ķ�����ʷ��ô����������һֱ�����Ա��ǰ��
template <typename E>
class FreList : protected AList<E> { 
	//����δ��ȫ��д����AList�����нӿڣ��ص�ʹ�ñ����̳У���ֹuser���ʸ���Ľӿ�������� 
protected:
	int* _fre;
	
//FreList API���õĺ��� 
	//�ռ䲻��ʱ����(�����˶�_fre����Ķ�̬����)
	virtual void expand() { 
		if (_listSize < _maxSize) return; //��δ��Աʱ�������� 
		E* oldListArray = _listArray;
		int* oldFre = _fre; 
		_maxSize <<= 1;
		_listArray = new E[_maxSize]; //�����ӱ�
		_fre = new int[_maxSize];
		for (int i = 0; i < _listSize; i++) { //����ԭ��������(EΪ�������ͻ����Ѿ����ع�������"=") 
			_listArray[i] = oldListArray[i];
			_fre[i] = oldFre[i];
		} 
		delete[] oldListArray; //�ͷ�ԭ�ռ� 
		delete[] oldFre;
	}
	//װ�����ӹ�Сʱѹ��������ռ�ռ�(�����˶�_fre����Ķ�̬����)
	virtual void shrink() {
		if ( _maxSize < (DEFAULT_CAPACITY << 1) ) return; //����������DEFAULT_CAPACITY����
		if (_listSize << 2 > _maxSize) return; //��25%Ϊ��
		E* oldListArray = _listArray;
		int* oldFre = _fre; 
		_maxSize >>= 1;
		_listArray = new E[_maxSize]; //��������
		_fre = new int[_maxSize];
		for (int i = 0; i < _listSize; i++) { //����ԭ�������� 
			_listArray[i] = oldListArray[i];
			_fre[i] = oldFre[i];
		} 
		delete[] oldListArray; //�ͷ�ԭ�ռ� 
		delete[] oldFre;
	}
	
public:
	//�������� 
	FreList(int maxSize = DEFAULT_CAPACITY) : AList(maxSize) {
		_fre = new int[maxSize];
	}
	virtual ~FreList() { delete[] _fre; } //���Զ����ø��������
 
//�����ӿ�
	//ֻ�����ʽӿ�
	int length() const { return AList::length(); }
	bool empty() const { return AList::empty(); }	
	//��д���ʽӿ�
	//����������������ң����ص�һ��Ԫ��item�ڲ���֮ǰ��λ�ã�ʧ��ʱ������-1
	// ���������¼�Ѿ�������ǰ��ļ�¼�ķ�����, ������¼�ͻ������Ա�����ǰ�ƶ�
	//E����Ϊ���еȵĻ������ͣ��������ز�����"=="��"!="
	Rank search(const E& item, Rank lo, Rank hi) { 
		if (0 <= lo && lo < hi && hi <= _listSize) {
			Rank r = 0;
			for (; r < hi; r++) { //��ǰ���˳����� 
				if (item == _listArray[r]) {
					_fre[r]++; //����Ŷ�Ӧ�ķ��ʴ���++ 
					break;
				}
			}
			if (r == hi) { //r = hi����ζ����ʧ�ܷ���-1�����򷵻�����Ԫ���ڲ���ǰ���ȣ����Һ���ܱ��ƶ��� 
				return -1;
			} else {
				E data = _listArray[r]; //������ҵ���Ԫ�غͷ����� 
				int fre =  _fre[r];
				Rank tempr = r - 1; 
				while (tempr >= 0 && _fre[tempr] < fre) { //����ǰһ��Ԫ�ؿ�ʼ�����ν�������С��fre��Ԫ�غͷ���������ƶ�һ�� 
					_listArray[tempr+1] = _listArray[tempr];
					_fre[tempr+1] = _fre[tempr];
					tempr--;
				} //ֱ��temprС��0 ���� �ҵ�tempr��ָ�ķ��������ڵ���fre 
				tempr++; //�����ҵ���Ԫ�غͷ�������Ϣ*����*tempr��ָ��λ�õ�֮��һ�� 
				_listArray[tempr] = data;
				_fre[tempr] = fre; 
				return r; //���ص�һ��Ԫ��item������Ԫ�أ��ڲ���֮ǰ��λ��
			}
		} else {
			cout << "Invalid finding range!" << endl;
//			exit(-1);
		}
	} 
	//�����������������
	Rank search(const E& item) {
		return search(item, 0, _listSize);
	}  
	//���б��ĩβ���Ԫ�أ����ز���Ԫ�ص���(�±�)*��0��ʼ*  
	virtual Rank append (const E& item) {
		expand();  //���б�Ҫ������ 
		_listArray[_listSize] = item;
		_fre[_listSize] = 1;
		_listSize++;
		return (_listSize - 1);
	} 
	//ɾ����������[lo, hi)֮�ڵ�Ԫ�أ����ر�ɾ��Ԫ����Ŀ 
	virtual int remove(Rank lo, Rank hi) {
		if (0 <= lo && lo <= hi && hi <= _listSize) {
			if (lo == hi) return 0; //����Ч�ʿ���,���������˻������
			while (hi < _listSize) {
				_listArray[lo] = _listArray[hi]; //[hi, _listSize)˳��ǰ��hi-lo����Ԫ 
				_fre[lo] = _fre[hi];
				lo++; hi++;
			} 
			_listSize = lo; //���¹�ģ��ֱ�Ӷ���β��[lo, _listSize = hi)������
			shrink(); //���б�Ҫ�������� 
			return hi - lo; //���ر�ɾ��Ԫ�ص���Ŀ 
		} else {
			cout << "Invalid deletion rank!" << endl; 
//			exit(-1);
		}
	}
	//ɾ����Ϊr��Ԫ�أ����ظ�Ԫ�� 
	virtual E remove(Rank r) {
		if (r >= 0 && r <= _listSize) {
			E item = _listArray[r]; //���ݱ�ɾ��Ԫ�� 
			remove(r, r+1); //��Ч������ɾ���㷨��ɾ��[r, r+1)������ 
			return item; //���ر�ɾ��Ԫ��
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