#ifndef _BINNODE_H_
#define _BINNODE_H_
#define stature(p) ((p) ? (p)->height : -1)
#define hasLC(x) ((x).lChild)
#define hasRC(x) ((x).rChild)
#define IsRoot(x) ( ! ( (x).parent ) ) 
#define IsLChild(x) ( ! IsRoot(x) && ( &(x) == (x).parent->lChild ) )
#define IsRChild(x) ( ! IsRoot(x) && ( &(x) == (x).parent->rChild ) )
#define FromParentTo(x) /*来自父亲的引用*/ \
   ( IsRoot(x) ? _root : ( IsLChild(x) ? (x).parent->lChild : (x).parent->rChild ) )
#include "..\Stack\LStack.h"
#include "..\Queue\LQueue.h" 
template <typename T>
class BinNode {
public:
	//成员变量 
	T data;
	BinNode<T> *parent, *lChild, *rChild;
	int height;
	//构造析构 
	BinNode() :
    	parent ( NULL ), lChild ( NULL ), rChild ( NULL ), height ( 0 ) { }
 	BinNode ( T e, BinNode<T>* p = NULL, BinNode<T>* lc = NULL, BinNode<T>* rc = NULL, int h = 0 ) :
    	data ( e ), parent ( p ), lChild ( lc ), rChild ( rc ), height ( h ) { }
	//操作接口 
	int size(); //子树规模 
	BinNode<T>* insertAsLC(const T&);
	BinNode<T>* insertAsRC(const T&);
	BinNode<T>* succ(); //(中序遍历意义下)当前节点的直接后继

	void travPre_R(BinNode<T>* x, void (*visit)(T&));    //子树先序遍历 
	void travPre_I1(BinNode<T>* x, void (*visit)(T&));	
	void travPre_I2(BinNode<T>* x, void (*visit)(T&));
	
	void travIn_R(BinNode<T>* x, void (*visit)(T&));    //子树中序遍历 
	void travIn_I(BinNode<T>* x, void (*visit)(T&)); 
	
	void travPost_R(BinNode<T>* x, void (*visit)(T&)); //子树后序遍历 
	void travPost_I(BinNode<T>* x, void (*visit)(T&));
	
	void travLevel(BinNode<T>* x, void (*visit)(T&)); //子树层次遍历 
protected:
	//以下是操作接口才能调用的子函数 
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
int BinNode<T>::size() { //后代总数，即以其为根的子树的规模 
	int s = 1; //计入本身
	if (lChild) s += lChild->size();
	if (rChild) s += rChild->size();
	return s;
}
//(中序遍历意义下)当前节点的直接后继
template <typename T>
BinNode<T>* BinNode<T>::succ() {
	BinNode<T>* x = this; //记录后继的临时变量
	if (this->rChild) { //若有右孩子，则直接后继必在右子树中，具体地就是
		x = this->rChild; //进入右子树 
		while (x->lChild) {  //最靠左（最小）的节点
			x = x->lChild; 
		}
	} else { //否则，直接后继应是“将当前节点包含于其左子树中的最低祖先”，具体地就是
		while(IsRChild(*x)) { //逆向地沿右向分支，不断朝左上方移动
			x = x->parent;
		}
		x = x->parent;  //最后再朝右上方移动一步，即抵达直接后继（如果存在）
	}
	return x;
}

//先序遍历：递归版 
template <typename T> 
void BinNode<T>::travPre_R(BinNode<T>* x, void (*visit)(T&)) {
	if (!x) return;
	visit(x->data);
	travPre_R(x->lChild, visit);
	travPre_R(x->rChild, visit);
} 
//先序遍历：迭代版1
template <typename T>
void BinNode<T>::travPre_I1(BinNode<T>* x, void (*visit)(T&)) {
	LStack<BinNode<T>*> S; //辅助栈 
	if (x) S.push(x);      //根节点入栈 
	while (!S.isEmpty()) { //在栈变空前反复循环 
		x = S.pop(); visit(x->data); //弹出并访问当前节点 
		if (hasRC(*x)) {        //右孩子需要后出，考虑到栈的LIFO特性，需要先将右孩子入栈 
			S.push(x->rChild);
		}
		if (hasLC(*x)) {        
			S.push(x->lChild);
		}
	}   //注意先后次序 
}

template <typename T>
void BinNode<T>::visitAlongLeftBranch(BinNode<T>* x, void (*visit)(T&), LStack<BinNode<T>*> &S) { 
	//访问左侧链（在preorder traverse中用到） 
	while (x) {
		visit(x->data);
		S.push(x->rChild);
		x = x->lChild;
	}
}
//先序遍历：迭代版2
template <typename T>
void BinNode<T>::travPre_I2(BinNode<T>* x, void (*visit)(T&)) {
	LStack<BinNode<T>*> S; //辅助栈 
	while (true) {
		visitAlongLeftBranch(x, visit, S);
		if (S.isEmpty()) break;
		x = S.pop(); 
		//弹出栈顶元素作为下一批的起点，也是遍历的左侧链最后一个元素的右孩子，
		//目的是遍历以这个右孩子为根的子树 
	} 
}
//中序遍历：递归版 
template <typename T> 
void BinNode<T>::travIn_R(BinNode<T>* x, void (*visit)(T&)) {
	if (!x) return;
	travIn_R(x->lChild, visit);
	visit(x->data);
	travIn_R(x->rChild, visit);
} 
//访问左侧链函数（在inorder traverse中用到）
template <typename T>
void BinNode<T>::goAlongLeftBranch(BinNode<T>* x, LStack<BinNode<T>*> &S) { 
	 //分摊O(1),由于对于一棵树来说，所有的访问左侧链的操作中，push的操作次数加起来也就等于元素个数n，
	 //而如中序遍历算法中写的，goAlongLB一共执行n次，因此这个函数的时间复杂度为分摊O(1) --具体见视频教程 
	while (x) {
		S.push(x);
		x = x->lChild;
	}
}

//中序遍历：迭代版 
template <typename T> 
void BinNode<T>::travIn_I(BinNode<T>* x, void (*visit)(T&)) {
	LStack<BinNode<T>*> S;
	while (true) {               //这个while执行n次（visit所有元素） 
		goAlongLeftBranch(x, S); //从当前结点出发，逐批入栈
		if (S.isEmpty()) break;  //直到所有结点处理完毕 
		x = S.pop();             //x的左子树为空或已遍历（等效为空），故可以 
		visit(x->data);          // 访问之 
		x = x->rChild;            //再转向其右子树 （可能为空，但是如果为空，调用goAlongLB函数直接返回，什么也不做） 
	}
} 
//后序遍历：递归版 
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
	while (BinNode<T>* x = S.topValue()) { //自顶向下反复检查栈顶节点 
		if (hasLC(*x)) { //尽可能向左，在此之前 
			if (hasRC(*x)) {   //若有右孩子，则 
				S.push(x->rChild); //优先入栈 
			}
			S.push(x->lChild);    //然后转向左孩子 
		} else {                  //实不得已 
			S.push(x->rChild);    //才转向右孩子 
		}
	}
	S.pop(); //返回之前，弹出栈顶的空节点 
} 
//后序遍历：迭代版 
template <typename T>
void BinNode<T>::travPost_I(BinNode<T>* x, void (*visit)(T&)) {
	LStack<BinNode<T>*> S;
	if (x) S.push(x); //根节点非空首先入栈 
	while (!S.isEmpty()) {
		if (S.topValue() != x->parent) { //栈顶非x之父（则必为其右兄） 
			gotoHLVFL(S); //在x的右子树中，找到HLVFL 
		}
		x = S.pop(); 
		visit(x->data);
	} 
}
//层次遍历 这个算法最好理解，需要加强理解（先序遍历的跌代版1就是这个的queue改为了stack，体会一下为什么要这样）
//为什么很多遍历操作都要用到栈？ 原理和函数递归调用要用到栈是一样的（还没要用到它，先把数据存起来，见教材P79） 
template <typename T>
void BinNode<T>::travLevel(BinNode<T>* x, void (*visit)(T&)) {
	LQueue<BinNode<T>*> Q; //辅助队列
	Q.enqueue(x);          //根节点入队 
	while (!Q.isEmpty()) {  //在队列再次变空前，反复迭代 
		BinNode<T>* x = Q.dequeue(); //取出队首结点 
		visit(x->data);              //访问之 
		if (hasLC(*x)) Q.enqueue(x->lChild); //左孩子入队 
		if (hasRC(*x)) Q.enqueue(x->rChild); //右孩子入队 
	}
}

#endif
