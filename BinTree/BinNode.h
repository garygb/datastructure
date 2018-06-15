#ifndef _BINNODE_H_
#define _BINNODE_H_
#define stature(p) ((p) ? (p)->height : -1)
#define hasLC(x) ((x).lChild)
#define hasRC(x) ((x).rChild)
#define IsRoot(x) ( ! ( (x).parent ) ) 
#define IsLChild(x) ( ! IsRoot(x) && ( &(x) == (x).parent->lChild ) )
#define IsRChild(x) ( ! IsRoot(x) && ( &(x) == (x).parent->rChild ) )
#define FromParentTo(x) /*���Ը��׵�����*/ \
   ( IsRoot(x) ? _root : ( IsLChild(x) ? (x).parent->lChild : (x).parent->rChild ) )
#include "..\Stack\LStack.h"
#include "..\Queue\LQueue.h" 
template <typename T>
class BinNode {
public:
	//��Ա���� 
	T data;
	BinNode<T> *parent, *lChild, *rChild;
	int height;
	//�������� 
	BinNode() :
    	parent ( NULL ), lChild ( NULL ), rChild ( NULL ), height ( 0 ) { }
 	BinNode ( T e, BinNode<T>* p = NULL, BinNode<T>* lc = NULL, BinNode<T>* rc = NULL, int h = 0 ) :
    	data ( e ), parent ( p ), lChild ( lc ), rChild ( rc ), height ( h ) { }
	//�����ӿ� 
	int size(); //������ģ 
	BinNode<T>* insertAsLC(const T&);
	BinNode<T>* insertAsRC(const T&);
	BinNode<T>* succ(); //(�������������)��ǰ�ڵ��ֱ�Ӻ��

	void travPre_R(BinNode<T>* x, void (*visit)(T&));    //����������� 
	void travPre_I1(BinNode<T>* x, void (*visit)(T&));	
	void travPre_I2(BinNode<T>* x, void (*visit)(T&));
	
	void travIn_R(BinNode<T>* x, void (*visit)(T&));    //����������� 
	void travIn_I(BinNode<T>* x, void (*visit)(T&)); 
	
	void travPost_R(BinNode<T>* x, void (*visit)(T&)); //����������� 
	void travPost_I(BinNode<T>* x, void (*visit)(T&));
	
	void travLevel(BinNode<T>* x, void (*visit)(T&)); //������α��� 
protected:
	//�����ǲ����ӿڲ��ܵ��õ��Ӻ��� 
	void visitAlongLeftBranch(BinNode<T>* x, void (*visit)(T&), LStack<BinNode<T>*> &S);
	void goAlongLeftBranch(BinNode<T>* x, LStack<BinNode<T>*> &S); 
	void gotoHLVFL(LStack<BinNode<T>*> &S); 
};

template <typename T>
BinNode<T>* BinNode<T>::insertAsLC(const T& e) {
	return lChild = new BinNode(e, this);
}

template <typename T>
BinNode<T>* BinNode<T>::insertAsRC(const T& e) {
	return rChild = new BinNode(e, this);
}

template <typename T>
int BinNode<T>::size() { //���������������Ϊ���������Ĺ�ģ 
	int s = 1; //���뱾��
	if (lChild) s += lChild->size();
	if (rChild) s += rChild->size();
	return s;
}
//(�������������)��ǰ�ڵ��ֱ�Ӻ��
template <typename T>
BinNode<T>* BinNode<T>::succ() {
	BinNode<T>* x = this; //��¼��̵���ʱ����
	if (this->rChild) { //�����Һ��ӣ���ֱ�Ӻ�̱����������У�����ؾ���
		x = this->rChild; //���������� 
		while (x->lChild) {  //�����С���Ľڵ�
			x = x->lChild; 
		}
	} else { //����ֱ�Ӻ��Ӧ�ǡ�����ǰ�ڵ���������������е�������ȡ�������ؾ���
		while(IsRChild(*x)) { //������������֧�����ϳ����Ϸ��ƶ�
			x = x->parent;
		}
		x = x->parent;  //����ٳ����Ϸ��ƶ�һ�������ִ�ֱ�Ӻ�̣�������ڣ�
	}
	return x;
}

//����������ݹ�� 
template <typename T> 
void BinNode<T>::travPre_R(BinNode<T>* x, void (*visit)(T&)) {
	if (!x) return;
	visit(x->data);
	travPre_R(x->lChild, visit);
	travPre_R(x->rChild, visit);
} 
//���������������1
template <typename T>
void BinNode<T>::travPre_I1(BinNode<T>* x, void (*visit)(T&)) {
	LStack<BinNode<T>*> S; //����ջ 
	if (x) S.push(x);      //���ڵ���ջ 
	while (!S.isEmpty()) { //��ջ���ǰ����ѭ�� 
		x = S.pop(); visit(x->data); //���������ʵ�ǰ�ڵ� 
		if (hasRC(*x)) {        //�Һ�����Ҫ��������ǵ�ջ��LIFO���ԣ���Ҫ�Ƚ��Һ�����ջ 
			S.push(x->rChild);
		}
		if (hasLC(*x)) {        
			S.push(x->lChild);
		}
	}   //ע���Ⱥ���� 
}

template <typename T>
void BinNode<T>::visitAlongLeftBranch(BinNode<T>* x, void (*visit)(T&), LStack<BinNode<T>*> &S) { 
	//�������������preorder traverse���õ��� 
	while (x) {
		visit(x->data);
		S.push(x->rChild);
		x = x->lChild;
	}
}
//���������������2
template <typename T>
void BinNode<T>::travPre_I2(BinNode<T>* x, void (*visit)(T&)) {
	LStack<BinNode<T>*> S; //����ջ 
	while (true) {
		visitAlongLeftBranch(x, visit, S);
		if (S.isEmpty()) break;
		x = S.pop(); 
		//����ջ��Ԫ����Ϊ��һ������㣬Ҳ�Ǳ�������������һ��Ԫ�ص��Һ��ӣ�
		//Ŀ���Ǳ���������Һ���Ϊ�������� 
	} 
}
//����������ݹ�� 
template <typename T> 
void BinNode<T>::travIn_R(BinNode<T>* x, void (*visit)(T&)) {
	if (!x) return;
	travIn_R(x->lChild, visit);
	visit(x->data);
	travIn_R(x->rChild, visit);
} 
//�����������������inorder traverse���õ���
template <typename T>
void BinNode<T>::goAlongLeftBranch(BinNode<T>* x, LStack<BinNode<T>*> &S) { 
	 //��̯O(1),���ڶ���һ������˵�����еķ���������Ĳ����У�push�Ĳ�������������Ҳ�͵���Ԫ�ظ���n��
	 //������������㷨��д�ģ�goAlongLBһ��ִ��n�Σ�������������ʱ�临�Ӷ�Ϊ��̯O(1) --�������Ƶ�̳� 
	while (x) {
		S.push(x);
		x = x->lChild;
	}
}

//��������������� 
template <typename T> 
void BinNode<T>::travIn_I(BinNode<T>* x, void (*visit)(T&)) {
	LStack<BinNode<T>*> S;
	while (true) {               //���whileִ��n�Σ�visit����Ԫ�أ� 
		goAlongLeftBranch(x, S); //�ӵ�ǰ��������������ջ
		if (S.isEmpty()) break;  //ֱ�����н�㴦����� 
		x = S.pop();             //x��������Ϊ�ջ��ѱ�������ЧΪ�գ����ʿ��� 
		visit(x->data);          // ����֮ 
		x = x->rChild;            //��ת���������� ������Ϊ�գ��������Ϊ�գ�����goAlongLB����ֱ�ӷ��أ�ʲôҲ������ 
	}
} 
//����������ݹ�� 
template <typename T>
void BinNode<T>::travPost_R(BinNode<T>* x, void (*visit)(T&)) {
	if (!x) return;
	travPost_R(x->lChild, visit);
	travPost_R(x->rChild, visit);
	visit(x->data);
}
//highest leaf visible from left(HLVFL)
template <typename T>
void BinNode<T>::gotoHLVFL(LStack<BinNode<T>*> &S) {
	while (BinNode<T>* x = S.topValue()) { //�Զ����·������ջ���ڵ� 
		if (hasLC(*x)) { //�����������ڴ�֮ǰ 
			if (hasRC(*x)) {   //�����Һ��ӣ��� 
				S.push(x->rChild); //������ջ 
			}
			S.push(x->lChild);    //Ȼ��ת������ 
		} else {                  //ʵ������ 
			S.push(x->rChild);    //��ת���Һ��� 
		}
	}
	S.pop(); //����֮ǰ������ջ���Ŀսڵ� 
} 
//��������������� 
template <typename T>
void BinNode<T>::travPost_I(BinNode<T>* x, void (*visit)(T&)) {
	LStack<BinNode<T>*> S;
	if (x) S.push(x); //���ڵ�ǿ�������ջ 
	while (!S.isEmpty()) {
		if (S.topValue() != x->parent) { //ջ����x֮�������Ϊ�����֣� 
			gotoHLVFL(S); //��x���������У��ҵ�HLVFL 
		}
		x = S.pop(); 
		visit(x->data);
	} 
}
//��α��� ����㷨�����⣬��Ҫ��ǿ��⣨��������ĵ�����1���������queue��Ϊ��stack�����һ��ΪʲôҪ������
//Ϊʲô�ܶ����������Ҫ�õ�ջ�� ԭ��ͺ����ݹ����Ҫ�õ�ջ��һ���ģ���ûҪ�õ������Ȱ����ݴ����������̲�P79�� 
template <typename T>
void BinNode<T>::travLevel(BinNode<T>* x, void (*visit)(T&)) {
	LQueue<BinNode<T>*> Q; //��������
	Q.enqueue(x);          //���ڵ���� 
	while (!Q.isEmpty()) {  //�ڶ����ٴα��ǰ���������� 
		BinNode<T>* x = Q.dequeue(); //ȡ�����׽�� 
		visit(x->data);              //����֮ 
		if (hasLC(*x)) Q.enqueue(x->lChild); //������� 
		if (hasRC(*x)) Q.enqueue(x->rChild); //�Һ������ 
	}
}

#endif
