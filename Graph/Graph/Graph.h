#ifndef _GRAPH_H_
#define _GRAPH_H_
#include "..\..\Queue\AQueue.h"

typedef enum {
	UNDISCOVERED, DISCOVERED, VISITED
} VStatus;  //顶点状态 

typedef enum { 
	UNDETERMINED, TREE, CROSS, FORWARD, BACKWARD 
} EStatus; //边在遍历树中所属的类型

template <typename Tv, typename Te>
class Graph {
private:
	/*操作接口调用的函数*/ 
	void reset() { //所有顶点、边的辅助信息复位 
		for (int i = 0; i < n; i++) { //顶点 
			status(i) = UNDISCOVERED;
			dTime(i) = fTime(i) = -1;
			parent(i) = -1;
			priority(i) = INT_MAX;
			for (int j = 0; j < n; j++) { //边 
				if (exists(i, j)) {
					status(i, j) = UNDETERMINED;
				}
			}
		} 	
	}
	//BFS (只适用于单连通的图)
	//所有的status为TREE的边构成图的支撑树
	void BFS(int v, int& clock) { 
	//时间复杂度O(n+e) while循环n轮，每一次while循环中的for循环考虑到遍历搜索一遍所有的邻居看似为O(n),
	//实际由于紧凑结构会在高速缓存中进行，速度大大高于一级缓存，
	//因此与while的比起来可以看做是O(1),里面的操作由于是对所有边都要做一次为O(e),总共O(n+e) 
		AQueue<int> Q;
		status(v) = DISCOVERED;
		Q.enqueue(v);   //初始化操作，当前结点标记为DISCOVERED并入队列 
		while (!Q.isEmpty()) {
			int x = Q.dequeue(); //取出队首顶点 
			dTime(x) = ++clock;
			for (int i = firstNbr(x); i > -1; i = nextNbr(x, i)) { //考察v的每一个邻居 
				if (status(i) == UNDISCOVERED) { //若i尚未被发现 
					status(i) = DISCOVERED;
					Q.enqueue(i); //发现该顶点
					status(x, i) = TREE; parent(i) = x; //引入树边 
				} else { //若i已经被发现（不管是入队未访问还是已经出队并访问完了，只要入队过，就不用再次入队了） 
					status(x, i) = CROSS; //将(x,i)归类为跨边 
				} 
			}
			status(x) = VISITED; //至此,当前顶点访问完毕 
		} //队列变空，BFS结束 
	}
	//DFS(只适用于单连通的图) O(n+e)
	void DFS(int v, int& clock) {
		dTime(v) = ++clock;
		status(v) = DISCOVERED; //发现当前顶点v
		for (int u = firstNbr(v); u > -1; u = nextNbr(v, u)) { //枚举v所有邻居u 
			switch (status(u)) { //视其状态分别处理
				case UNDISCOVERED : //u尚未被发现，意味着支撑树可在此拓展 
					status(v, u) = TREE; 
					parent(u) = v; 
					DFS(u, clock);
					break;
				case DISCOVERED : //u已被发现但尚未访问完毕，应属被后代指向的祖先 
					status(v, u) = BACKWARD; 
					break;
				case VISITED : //u已访问完毕(在有向图中出现)，视其承袭关系为前向边或跨边(Parenthesis Lemma定理)
					status(v, u) = ((dTime(v) < dTime(u)) ? FORWARD : CROSS);
					break; 			 
			} 
		} 
		status(v) = VISITED; 
		fTime(v) = ++clock; //至此，当前顶点v方告访问完毕 
	} 
public:
	int n; //顶点总数 
	int e; //边总数 
	
	/*顶点的操作接口*/ 
	// 顶点的基本操作：查询第i个顶点（0 <= i < n）
	virtual Tv& vertex ( int i ) = 0;
	virtual int inDegree ( int i ) = 0;
	virtual int outDegree ( int i ) = 0;
	virtual int firstNbr ( int i ) = 0;
	virtual int nextNbr ( int i, int j ) = 0;
	virtual VStatus& status ( int i ) = 0;
	virtual int& dTime ( int i ) = 0;
	virtual int& fTime ( int i ) = 0;
	virtual int& parent ( int i ) = 0;
	virtual int& priority ( int i ) = 0;
	//顶点的动态操作(插入、删除) 
	virtual int insert(const Tv& vertex) = 0;
	virtual Tv remove(int i) = 0;
	
	/*边的操作接口*/ 
	//边的确认操作(是否存在这样一条边) 
	virtual bool exists(int i, int j)  = 0;
	//边的基本操作:查询第(i,j)条边的数据、状态、权重 
	virtual Te& edge(int i, int j) = 0;
	virtual EStatus& status(int i, int j) = 0;
	virtual int& weight(int i, int j) = 0;
	//边的动态操作（插入、删除） 
	virtual void insert(const Te& edge, int w, int i, int j) = 0;
	virtual Te remove(int i, int j) = 0; 
	
	/*算法*/
	//bfs (只适用于多连通的图)
	void bfs(int s) { //s为起始顶点 
		reset();
		int clock = 0;
		int v = s;
		//逐一检查所有顶点，一旦遇到尚未发现的顶点，调用BFS算法 
		do {
			if (status(v) == UNDISCOVERED)
				BFS(v, clock);
		} while (s != (v = (++v%n)));
	} 
	//dfs (适用于多连通的图) O(n+e)
	void dfs(int s) { //s为起始顶点 
		reset();
		int clock = 0;
		int v = s;
		do {
			if (status(v) == UNDISCOVERED)
				DFS(v, clock);
		} while (s != (v = (++v) % n) );
	} 
}; 

#endif
 