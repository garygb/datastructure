#define max(x,y) ((x)>(y) ? x : y)  
#include "BinNode.h" 

template <typename T>
class BinTree {
protected:
	//��Ա���� 
	int _size; //��������ģ 
	BinNode<T>* _root; //���ڵ�
	//�ڲ��������� 
	virtual int updateHeight(BinNode<T>* x) { //���½ڵ�x�ĸ߶�
		return x->height = 1 + max(stature(x->lChild), stature(x->rChild));
	}
	void updateHeightAbove(BinNode<T>* x) {  //����x�������ȵĸ߶�
		while (x) {   //���Ż���һ���߶�δ�䣬������ֹ 
			int originalHeight = x->height;
			if(originalHeight == updateHeight(x) ) {
				return;
			}
			x = x->parent;
		}
	} //O(n = depth(x))
	static int removeAt ( BinNode<T>* x ) { //assert: xΪ�������еĺϷ�λ��
   		if ( !x ) return 0; //�ݹ��������
  		int n = 1 + removeAt ( x->lChild ) + removeAt ( x->rChild ); //�ݹ��ͷ���������
  		delete x; 
		return n; //�ͷű�ժ���ڵ㣬������ɾ���ڵ�����
	}
public: 
	//��������
	BinTree() : _size ( 0 ), _root ( NULL ) { } //���캯��
	virtual ~BinTree() { if ( _size > 0 ) remove ( _root ); } //�������� 
	//�����ӿ�
	int& size() { return _size; }
	bool isEmpty() { return !_root; }
	BinNode<T>* &root() { return _root; }
	//�ڵ���� 
	//������ڵ�
	BinNode<T>* insertAsRoot ( const T& e ) {
		_size = 1; 
		return _root = new BinNode<T> ( e ); //��e�������ڵ����յĶ�����
	} 
	//e��Ϊx�����ӣ�ԭ�ޣ�����
	BinNode<T>* insertAsRC(BinNode<T>* x, const T& e) {
	//	return x->rChild = new BinNode(e, this); --��������д����Ϊ��BinNode�������Ѿ��������insertAsRC������ 
		_size++;
		x->insertAsRC(e); 
		updateHeightAbove(x);
		return x->rChild;
	}
	//e��Ϊx���Һ��ӣ�ԭ�ޣ�����
	BinNode<T>* insertAsLC (BinNode<T>* x, const T& e) {
		_size++;
		x->insertAsLC(e);
		updateHeightAbove(x);
		return x->lChild;
	}
	//�������� 
	//S��Ϊx����������
	BinNode<T>* attachAsRC(BinNode<T>* x, BinTree<T>* &S) { //��BinTree��Ķ����ָ��ȡ���õ�ԭ���ǣ���Ҫ����������ֵ���޸ģ� 
		if (x->rChild = S->_root) {
			x->rChild->parent = x;
		} 
		_size += S->size;
		updateHeightAbove(x);
		delete S; //����S 
		S = NULL; //��SΪNULL���ͷſռ� 
		return x; //���ؽ���λ�� 
	}
	//T��Ϊx����������
	BinNode<T>* attachAsLC(BinNode<T>* x, BinTree<T>* &S) {
		if (x->lChild = S->_root) {  //->ǰ��ȷ���Ƿ�һ����ΪNULL����һ��Ҫ��������if��ȷ����ȫ�� 
			x->lChild->parent = x;
		}
		_size += S->_size;
		updateHeightAbove(x);
		delete S;
		S = NULL;
		return x; 
	}
	//ɾ����������λ��x���Ľڵ㼰���������ر�ɾ���ڵ����ֵ
	int remove(BinNode<T>* x) {
		FromParentTo(*x) = NULL;  //�ж����Ը��ڵ��ָ��
		updateHeightAbove(x->parent);  // �������ȸ߶ȣ�����ڵ��಻�䣩 
		int n = removeAt(x);
		_size -= n;
		return n; //���ر�ɾ���ڵ����� 
	}
	//������x�ӵ�ǰ����ժ����������ת��Ϊһ�ö�������
	BinNode<T>* secede(BinNode<T>* x) {
		FromParentTo(*x) = NULL;
		updateHeightAbove(x->parent);
		//���¶Է��������������װ
		BinTree<T>* S = new BinTree<T>(); //�������� 
		S->_root = x;
		S->parent = NULL;
		S->_size = x->size();
		_size -= S->_size;
		return S; //���ط�װ������� 
	}
	//����
   	void travPre_R(void (*visit)(T&)) {  //�������_�ݹ�� 
		if ( _root ) _root->travPre_R ( _root, visit ); 
	} 
	void travPre_I1(void (*visit)(T&)) {  //�������_������1 
		if (_root) _root->travPre_I1(_root, visit);
	}
	void travPre_I2(void (*visit)(T&)) {  //�������_������2
		if (_root) _root->travPre_I2(_root, visit);
	}
   	void travIn_R(void (*visit)(T&)) {   //�������_�ݹ�� 
   		if (_root) _root->travIn_R(_root, visit);
	}
	void travIn_I(void (*visit)(T&)) {   //�������_������ 
   		if (_root) _root->travIn_I(_root, visit);
	}	
	void travPost_R(void (*visit)(T&)) { //�������_�ݹ�� 
		if (_root) _root->travPost_R(_root, visit);
	}
	void travPost_I(void (*visit)(T&)) { //�������_������ 
		if (_root) _root->travPost_I(_root, visit);
	}
	void travLevel(void (*visit)(T&)) { //��α���_������ 
		if (_root) _root->travLevel(_root, visit);
	}
};

