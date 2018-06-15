#define max(x,y) ((x)>(y) ? x : y)  
#include "BinNode.h" 

template <typename T>
class BinTree {
protected:
	//成员变量 
	int _size; //二叉树规模 
	BinNode<T>* _root; //根节点
	//内部操作函数 
	virtual int updateHeight(BinNode<T>* x) { //更新节点x的高度
		return x->height = 1 + max(stature(x->lChild), stature(x->rChild));
	}
	void updateHeightAbove(BinNode<T>* x) {  //更新x及其祖先的高度
		while (x) {   //可优化：一旦高度未变，即可终止 
			int originalHeight = x->height;
			if(originalHeight == updateHeight(x) ) {
				return;
			}
			x = x->parent;
		}
	} //O(n = depth(x))
	static int removeAt ( BinNode<T>* x ) { //assert: x为二叉树中的合法位置
   		if ( !x ) return 0; //递归基：空树
  		int n = 1 + removeAt ( x->lChild ) + removeAt ( x->rChild ); //递归释放左、右子树
  		delete x; 
		return n; //释放被摘除节点，并返回删除节点总数
	}
public: 
	//构造析构
	BinTree() : _size ( 0 ), _root ( NULL ) { } //构造函数
	virtual ~BinTree() { if ( _size > 0 ) remove ( _root ); } //析构函数 
	//操作接口
	int& size() { return _size; }
	bool isEmpty() { return !_root; }
	BinNode<T>* &root() { return _root; }
	//节点插入 
	//插入根节点
	BinNode<T>* insertAsRoot ( const T& e ) {
		_size = 1; 
		return _root = new BinNode<T> ( e ); //将e当作根节点插入空的二叉树
	} 
	//e作为x的左孩子（原无）插入
	BinNode<T>* insertAsRC(BinNode<T>* x, const T& e) {
	//	return x->rChild = new BinNode(e, this); --不用这样写，因为在BinNode类里面已经定义过了insertAsRC操作了 
		_size++;
		x->insertAsRC(e); 
		updateHeightAbove(x);
		return x->rChild;
	}
	//e作为x的右孩子（原无）插入
	BinNode<T>* insertAsLC (BinNode<T>* x, const T& e) {
		_size++;
		x->insertAsLC(e);
		updateHeightAbove(x);
		return x->lChild;
	}
	//子树接入 
	//S作为x左子树接入
	BinNode<T>* attachAsRC(BinNode<T>* x, BinTree<T>* &S) { //对BinTree类的对象的指针取引用的原因是，需要拿它来做左值（修改） 
		if (x->rChild = S->_root) {
			x->rChild->parent = x;
		} 
		_size += S->size;
		updateHeightAbove(x);
		delete S; //销毁S 
		S = NULL; //置S为NULL，释放空间 
		return x; //返回接入位置 
	}
	//T作为x右子树接入
	BinNode<T>* attachAsLC(BinNode<T>* x, BinTree<T>* &S) {
		if (x->lChild = S->_root) {  //->前不确定是否一定不为NULL，则一定要把它放在if中确保安全性 
			x->lChild->parent = x;
		}
		_size += S->_size;
		updateHeightAbove(x);
		delete S;
		S = NULL;
		return x; 
	}
	//删除二叉树中位置x处的节点及其后代，返回被删除节点的数值
	int remove(BinNode<T>* x) {
		FromParentTo(*x) = NULL;  //切断来自父节点的指针
		updateHeightAbove(x->parent);  // 更新祖先高度（其余节点亦不变） 
		int n = removeAt(x);
		_size -= n;
		return n; //返回被删除节点总数 
	}
	//将子树x从当前树中摘除，并将其转换为一棵独立子树
	BinNode<T>* secede(BinNode<T>* x) {
		FromParentTo(*x) = NULL;
		updateHeightAbove(x->parent);
		//以下对分离出的子树做封装
		BinTree<T>* S = new BinTree<T>(); //创建空树 
		S->_root = x;
		S->parent = NULL;
		S->_size = x->size();
		_size -= S->_size;
		return S; //返回封装后的子树 
	}
	//遍历
   	void travPre_R(void (*visit)(T&)) {  //先序遍历_递归版 
		if ( _root ) _root->travPre_R ( _root, visit ); 
	} 
	void travPre_I1(void (*visit)(T&)) {  //先序遍历_迭代版1 
		if (_root) _root->travPre_I1(_root, visit);
	}
	void travPre_I2(void (*visit)(T&)) {  //先序遍历_迭代版2
		if (_root) _root->travPre_I2(_root, visit);
	}
   	void travIn_R(void (*visit)(T&)) {   //中序遍历_递归版 
   		if (_root) _root->travIn_R(_root, visit);
	}
	void travIn_I(void (*visit)(T&)) {   //中序遍历_迭代版 
   		if (_root) _root->travIn_I(_root, visit);
	}	
	void travPost_R(void (*visit)(T&)) { //后序遍历_递归版 
		if (_root) _root->travPost_R(_root, visit);
	}
	void travPost_I(void (*visit)(T&)) { //后序遍历_迭代版 
		if (_root) _root->travPost_I(_root, visit);
	}
	void travLevel(void (*visit)(T&)) { //层次遍历_迭代版 
		if (_root) _root->travLevel(_root, visit);
	}
};

