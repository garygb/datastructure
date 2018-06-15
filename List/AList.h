#ifndef ALISH_H_
#define ALIST_H_
#include <iostream>
#include <cstdlib>
#define DEFAULT_CAPACITY 3 //Ĭ�ϵ�AList��ʼ�����������������޸ĳɸ����ֵ
typedef int Rank; //�ȣ���Ϊ������±� e.g. AList[Rank] 
using std::cout;
using std::endl;

template <typename E>
class AList {
protected:
	int _maxSize;
	int _listSize;
	E*  _listArray;
	 
//sort���� Lower bound for comparison based Alg = O(nlogn)
	//sort���õĽӿ� 
	void swap(E& a, E& b);
	bool bubble(Rank lo, Rank hi); //ɨ�轻��
	Rank bubble_fast(Rank lo, Rank hi); //ɨ�轻��(�Ľ���) 
	void merge(Rank lo, Rank mi, Rank hi); //�鲢 
	Rank partition(Rank lo, Rank hi); //quickSort����㻮�ֺ���
	
	//ð�������㷨(�ȶ��������㷨) ���O(n),�O(n^2) �͵��㷨 
	void bubbleSort(Rank lo, Rank hi); 
	//ð�������㷨(�Ľ��棬�ȶ�)  ���O(n),�O(n^2) �͵��㷨 
	void bubbleSort_fast(Rank lo, Rank hi); 
	//�鲢�����㷨(�ȶ�) ʱ�临�Ӷ�O(nlogn), �ռ临�Ӷ�O(n) 
	void mergeSort(Rank lo, Rank hi);
	//�����Ŀ������� (���ȶ����͵��㷨�� 
	//���ܣ�ʱ�临�Ӷȣ����O(nlogn),�O(n^2) ƽ��O(nlogn)
	void quickSort(Rank lo, Rank hi); 
//	void heapSort(Rank lo, Rank hi);
	
//�ӿڵ��õĲ������� 
	//����������A[lo, hi)Ϊ������������
	void copyFrom(const E* A, Rank lo, Rank hi) { 
		_listArray = new E[_maxSize = 2 * (hi - lo)]; //����ռ䣬��ģ����
		_listSize = 0;
		while (lo < hi) { //A[lo, hi)�ڵ�Ԫ����һ 
			_listArray[_listSize++] = A[lo++]; //������_listArray[0, hi-low) 
		}
	} 
	//�ռ䲻��ʱ���� 
	virtual void expand() { 
		if (_listSize < _maxSize) return; //��δ��Աʱ�������� 
		E* oldListArray = _listArray;
		_listArray = new E[_maxSize <<= 1]; //�����ӱ�
		for (int i = 0; i < _listSize; i++) { //����ԭ��������(EΪ�������ͻ����Ѿ����ع�������"=") 
			_listArray[i] = oldListArray[i];
		} 
		delete[] oldListArray; //�ͷ�ԭ�ռ� 
	}
	//װ�����ӹ�Сʱѹ��������ռ�ռ�
	virtual void shrink() {
		if ( _maxSize < (DEFAULT_CAPACITY << 1) ) return; //����������DEFAULT_CAPACITY����
		if (_listSize << 2 > _maxSize) return; //��25%Ϊ��
		E* oldListArray = _listArray;
		_listArray = new E[_maxSize >>= 1]; //��������
		for (int i = 0; i < _listSize; i++) { //����ԭ�������� 
			_listArray[i] = oldListArray[i];
		} 
		delete[] oldListArray; //�ͷ�ԭ�ռ� 
	}
	
public:
//���캯�� 
	//����һ���ձ� 
	AList (int maxSize = DEFAULT_CAPACITY) { 
		_maxSize = maxSize;
		_listSize = 0;
		_listArray = new E[_maxSize];
	} 
	//����һ���������ΪmaxSize��������listSize��Ԫ��ֵΪelement���б�
	AList(int listSize, E element) : 
		_maxSize(2 * listSize), _listSize(listSize) {;
		_listArray = new E[_maxSize];  
		for (int i = 0; i < listSize; i++) {
			_listArray[i] = element;
		}
	}
	AList(const E* A, Rank n) { copyFrom(A, 0, n); } //�������帴��
	AList(const E* A, Rank lo, Rank hi) { copyFrom(A, lo, hi); } //�������临�� 
	AList( const AList<E>& V ) { copyFrom(V._listArray, 0, V._listSize); } //�������帴��
//	AList( const AList<E>& V, Rank lo, Rank hi ) { 
//		if (0 <= lo && lo < hi && hi <= V._listSize) {
//			copyFrom(V._listArray, lo, hi);
//		} else { 
//			cout << "Invalid copy range." << endl;
//		}
//	} //�������临�� 
//�������� 
	virtual ~AList() { delete[] _listArray; } //��virtual����������ʹ��virtual destructer
	
//�����ӿ� 

//ֻ�����ʽӿ� 
	int length() const { return _listSize; }
	bool empty() const { return !_listSize; }	
	int maxSize () { return _maxSize; }
	bool isSorted() const {
		bool isSorted = true;
		for (int i = 1; i < _listSize; i++) {
			//���ڽ�������ԣ���˵�������� 
			if (_listArray[i-1] > _listArray[i])  isSorted = false; 
		}
		return isSorted;
	}
	//����������������ң��������һ��Ԫ��item��λ�ã�ʧ��ʱ������lo - 1,E����Ϊ���еȵĻ������ͣ��������ز�����"=="��"!="
	Rank find(const E& item, Rank lo, Rank hi) const { 
		if (0 <= lo && lo < hi && hi <= _listSize) {
			Rank r = hi - 1;
			for (; r >= lo; r--) { //�Ӻ���ǰ��˳����� 
				if (item == _listArray[r])
					break;
			}
			return r; //hi = low - 1����ζ����ʧ�ܣ����򷵻�����Ԫ�ص��� 
		} else {
			cout << "Invalid finding range!" << endl;
//			exit(-1);
		}
	} 
	//�����������������
	Rank find(const E& item) const {
		return find(item, 0, _listSize);
	} 
//��д���ʽӿ�
	E& operator[] (Rank r) {
		if (r >= 0 && r <= _listSize) {
			return _listArray[r];
		} else {
			cout << "Invalid rank." << endl; 
//			exit(-1);
		}
	}
	//����"="��������Ա�ʵ��array֮��ĸ�ֵ 
	AList<E>& operator= ( const AList<E>& V ) {
	   	if ( _listArray ) delete [] _listArray; //�ͷ�ԭ������
  		copyFrom ( V._listArray, 0, V._listSize ); //���帴��
   		return *this; //���ص�ǰ��������ã��Ա���ʽ��ֵ
	}
	void clear() {
		delete[] _listArray;
		_listSize = 0;
		_listArray = new E[_maxSize];
	}
	//����Ϊr��λ�ò���Ԫ�أ����ز���Ԫ�ص���(�±�)*��0��ʼ* 
	int insert(Rank r, const E& item) {
		if ( 0 <= r && r <= _listSize) {
			expand();//���б�Ҫ������
			for (int i = _listSize; i > r; i--) { //�Ժ���ǰ�����Ԫ��˳�κ���һ����Ԫ
				_listArray[i] = _listArray[i-1];
			}
			_listArray[r] = item;
			_listSize++; //������Ԫ�ز���������
			return r; //������
		} else {
			cout << "Invalid insertion rank!" << endl;
//			exit(-1);
		}
	}
	//���б��ĩβ��Ԫ�أ����ز���Ԫ�ص���(�±�)*��0��ʼ* 
	virtual Rank append (const E& item) {
		expand();  //���б�Ҫ������ 
		_listArray[_listSize++] = item;
		return (_listSize - 1);
	}
	//ɾ����������[lo, hi)֮�ڵ�Ԫ�أ����ر�ɾ��Ԫ����Ŀ 
	virtual int remove(Rank lo, Rank hi) {
		if (0 <= lo && lo <= hi && hi <= _listSize) {
			if (lo == hi) return 0; //����Ч�ʿ���,���������˻������
			while (hi < _listSize) {
				_listArray[lo++] = _listArray[hi++]; //[hi, _listSize)˳��ǰ��hi-lo����Ԫ 
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
	//����Ԫ��ȥ��,����ɾ��Ԫ�ص���Ŀ O(n^2)
	int deduplicate() {
		int oldSize = _listSize;
		int deleteItems;
		Rank i = 1; //��_listArray[1]��ʼ 
		while (i < _listSize) { //��ǰ�����һ�����Ԫ��_elem[i]
			(find(_listArray[i], 0, i) < 0) ? //����ǰ׺��Ѱ����֮��ͬ�ߣ�����һ����
			i++ : remove(i);  //������ͬ������������̣�����ɾ����ͬ��
		}
		deleteItems = oldSize - _listSize;
		shrink();
		return deleteItems; //ɾ��Ԫ����Ŀ 
	}
//sort
	void sort(Rank lo, Rank hi,int type) { //��[lo, hi)���� 
		switch (type % 4) {
			case 0: bubbleSort(lo, hi); break;
			case 1: bubbleSort_fast(lo, hi); break;
			case 2: mergeSort(lo, hi); break; 
			case 3: quickSort(lo, hi); break;
//			case 4: heapSort(lo, hi); break; 
		}
	}
	void sort(int type) { sort(0, _listSize, type); } //�������� 
	//�������� 
	void unsort(Rank lo, Rank hi) { //�ȸ��������������[lo, hi)
		E* V = _listArray + lo; //��������_elem[lo, hi)������һ����V[0, hi - lo)
		for (Rank i = hi - lo; i > 0; i--) { //�Ժ���ǰ
			//rand(): ͷ�ļ�<cstdlib> 
			swap(V[i-1], V[rand() % i]); //��V[i - 1]��V[0, i)��ĳһԪ���������
		}
	}
	//�������� 
	void unsort() { unsort(0, _listSize); } 
//����
	//���뺯��ָ��
	void traverse(void (*visit)(E&)) {
		for (int i = 0; i < _listSize; i++) {
			visit(_listArray[i]);
		} 
	} 
	//����������أ����Ķ���->�º�����
	//��ͨ�ã��ô���1.����״̬ 2.Ч�ʸ���
//	template <typename VST>
//	void traverse(VST& visit) {
//		for (int i = 0; i < _listSize; i++) {
//			visit(_listSize[i]);
//		}
//	}
};  

#include "sort_implementation.h" 
#endif
