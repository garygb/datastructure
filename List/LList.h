#ifndef LLIST_H_
#define LLIST_H_
#include "Link.h"

template <typename E>
class LList {
protected:
	Link<E>* head;
	Link<E>* tail;
	Link<E>* curr;
	int size;
	//Intialization helper method
	void init() {
		curr = head = tail = new Link<E>;
		size = 0; 
	}
	//clean the linklist
	void removeall() {
		while (head != NULL) {
			curr = head;
			head = head->next;
			delete curr;
		}
	}
	
public:
	//构造析构 
	LList() { init(); }
	virtual ~LList() { removeall(); }
	//操作接口 
	virtual E& operator[] (int rank) {
		moveToPos(rank);
		return curr->next->element;
	}
	virtual void print() const {
		for (Link<E>* p = head->next; p != NULL; p = p->next) {
			cout << p->element << " ";
		}
		cout << endl;
	}
	virtual void clear() {
		removeall();
		init();
	}
	//Insert an element at the current location.
	virtual void insert (const E& item) {
		curr->next = new Link<E>(item, curr->next);
		if (tail == curr) {
			tail = curr->next;
		}
		size++;
	}
	//Append an element at the end of the list.
	virtual void append(const E& item) {
		tail->next = new Link<E>(item, NULL);
		tail = tail->next;
		size++;
	}
	//Remove and return the CURRENT element(return : the element that was removed)
	virtual E remove() {
		if (curr->next != NULL) {
			E item = curr->next->element;
			Link<E>* p = curr->next;
			curr->next = p->next;
			if (tail == p) {
				tail = curr;
			}
			delete p;
			size--;
			return  item;
		} else{
			cout << "No element!" << endl;
		}
	}
	//Set the current position to the start of the list.
	virtual void moveToStart() { curr = head; } 
	//Set the current position to the end of the list.
	virtual void moveToEnd() { curr = tail; } 
	//Move the current one step left.
	//NO CHANGE IF ALREADY AT BEGINNING.
	virtual void prev() {
		if (curr != head){
			Link<E>* p = head;
			while (p->next != curr) {
				p = p->next;
			} 
			curr = p;
		}
	}
	//Move the current ont step right.
	//NO CHANGE IF ALREADY AT END.
	virtual void next() {
		if (curr != tail) {
			curr = curr->next;
		}
	}
	//Return: The number of elements in the list.
	virtual int length() const { return size; }	
	//Return: The position of current position.
	virtual int currPos() const {
		Link<E>* p = head;
		int i = 0;
		for (; p != curr; i++) {
			p = p->next;
		}
		return i;
	}
	//Set current position.
	virtual void moveToPos(int pos) {
		if ((pos>=0) || (pos<=size)) {
			curr = head;
			for (int i = 0; i < pos; i++){
				curr = curr->next;
			}
		} else {
			cout << "Position out of range." << endl;
		}
	}
	
	//Return: The current element.
	virtual const E& getValue() const {
		if (curr->next != NULL) {
			return curr->next->element;
		} else {
			cout << "No value." << endl;
		}
	}
	
	//Inflate the array.
//	virtual void inflate (int moreSize) = 0;
	
	virtual bool find (const E& item) const {
		bool flag = false;
		for (Link<E>* p = head; p != NULL; p = p->next) {
			if (p->element == item)
				flag = true;
		}
		return flag;
	}
	//前后倒置
	virtual void reverse() {
		if (head->next == NULL || head->next->next == NULL){
			return;
		} else {
			Link<E>* current = head->next;
			Link<E>* pnext = current->next;
			Link<E>* prev = NULL;
			
			current->next = NULL;

			if (!pnext) {
				pnext->next = current;
				current = pnext;
			}
			while (pnext) {
				prev = pnext->next;
				pnext->next = current;
				current = pnext;
				pnext = prev;
			} 
			
			head->next = current;
		}
	}
};


#endif
