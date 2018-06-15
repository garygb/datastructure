#ifndef _BST_H_
#define _BST_H_
#include "..\BinTree\BinTree.h"

template <typename T>
class BST : public BinTree<T> {
public:
//操作接口 
	//查找 返回查找到的位置的指针的引用（方便在函数外操作） 
	//调用这个函数而不是searchIn的原因是，外部操作只要穿一个参数就好了，清晰明了（_root和_hot都是内部的变量,外部无需传入） 
	virtual BinNode<T>* & search(const T& e) { //O(h)
		//注意传入的_hot是一个引用，无论search到的元素是一个存在的（指针非NULL）或是一个不存在的（指针为NULL），_hot均指向它的父亲 
		return searchIn(this->_root, e, _hot = NULL); //从根节点启动查找 
	} 
	//插入(可以很好地处理空树的情况) O(h)
	virtual BinNode<T>* insert(const T& e) { 
		BinNode<T>* & x = search(e); //查找目标（副作用是让_hot指向了所要查找目标的父亲） 
		if (!x) { //在x == NULL时才有后续操作，禁止插入雷同元素，在查找失败时才实施插入操作 
			//空树的case，x(绑定_root)，被赋一个根节点BinNode<T>(e, _hot = NULL)
			//其余case，x(绑定查找到的那个(_hot->) lChild或者rChild),被赋一个叶子结点BinNode<T>(e, _hot)
			x = new BinNode<T>(e, _hot); //创建新节点，以_hot为父亲 
			this->_size++; //更新全树规模 
			this->updateHeightAbove(x); //更新历代祖先的高度
		}
		return x; 
	} //无论e是否存在于原树中，返回时总有x->data == e
	//删除 返回成功与否（删除不存在的元素返回false） 
	virtual bool remove(const T& e) {  //O(h)
		BinNode<T>* & x = search(e); //定位目标结点
		if (!x) return false; //确认目标存在(此时_hot为x的父亲)
		removeAt(x, _hot); //分两大类情况实施删除，更新全树规模 
		this->_size--; //更新全树规模 
		this->updateHeightAbove(_hot); //更新_hot及其历代祖先的高度
		return true; 
	} //删除成功与否，由返回值指示 
protected:
	BinNode<T>* _hot; //命中节点的父亲
//	BinNode<T>* connect34( //3 + 4重构 
//		BinNode<T>*, BinNode<T>*, BinNode<T>*,
//		BinNode<T>*, BinNode<T>*, BinNode<T>*, BinNode<T>*);
//	BinNode<T>* rotateAt(BinNode<T>*); //旋转调整
	//操作接口调用的函数
	BinNode<T>* & searchIn(BinNode<T>* & v, //当前(子)树根 
		const T& e, //目标关键码 
		BinNode<T>* & hot) { //记忆热点(函数内部修改它，使它成为查找到结点的父亲)
		if (!v || e == v->data) return v; //足以确定失败或者成功，或者，
		hot = v; //先记下当前（非空）结点
		return searchIn(((e < v->data) ? v->lChild : v->rChild), e, _hot); 
	} //运行时间正比于返回结点v的深度，不超过树高O(h) 
	BinNode<T>* removeAt(BinNode<T>* & x, BinNode<T>* & hot) {
		BinNode<T>* w = x; //实际被摘除的结点，初值同x
		BinNode<T>* succ = NULL; // 实际被删除节点的接替者
		if (!hasLC(*x)) { //若*x的左子树为空(包含左右子树都为空的情况)，则可 
			succ = x = x->rChild; //直接将 *x替换为右子树 
//			succ->parent = w->parent;
		} else if (!hasRC(*x)) { //若*x的右子树为空（此时左子树一定不为空） 
			succ = x = x->lChild; //对称地处理（此时succ != NULL） 
//			succ->parent = w->parent;
		} else { //若x的左右孩子并存 
			w = x->succ(); 
			swap(x->data, w->data); //令*x与其后继*w互换数据 
			BinNode<T>* u = w->parent;
			if (u == x) { //隔离节点*w
				u->rChild = succ = w->rChild;
//				w->rChild->parent = u;
			} else {
				u->lChild = succ = w->rChild;
//				w->rChild->parent = u;
			}
		} 
		//单独处理父亲结点的连接（每种case其实情况相同） 
		hot = w->parent; //记录下被删除结点的父亲
		if (succ) succ->parent = hot; //并将被删除节点的接替者与hot相联
		delete w; //释放被摘除节点
		return succ; //返回接替者
	} //O(h) 
	void swap(T& a, T& b) {
		T temp = a;
		a = b;
		b = temp;
	}
};

#endif
