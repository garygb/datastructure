#ifndef _GRAPHMATRIX_H_
#define _GRAPHMATRIX_H_
#include "..\..\List\AList.h" 
#include "Graph.h"

template <typename Tv>
struct Vertex { //顶点对象（并未严格封装） 
	Tv data; //顶点数据 
	int inDegree, outDegree; //入度和出度
	VStatus status;
	int dTime, fTime; //时间标签
	int parent; //在遍历数中的父节点
	int priority; //在遍历树中的优先级（最短通路、极短跨边等）
	Vertex (const Tv& d = (Tv)0) :
		data(d), inDegree(0), outDegree(0), status(UNDISCOVERED), 
		dTime(-1), fTime(-1), priority(INT_MAX) { } 
};

template <typename Te> 
struct Edge { //边对象（为简化起见，并未严格封装）
	Te data; int weight; EStatus status; //数据、权重、类型
	Edge (const Te& d, int w) : 
		data (d), weight (w), status(UNDETERMINED) {} //构造新边 
};

template <typename Tv, typename Te> //顶点类型和边类型 
class GraphMatrix : public Graph<Tv, Te> { //基于向量，以矩阵形式实现的图 
private: 
	AList< Vertex<Tv> > V; //顶点集（一组顶点组成的向量）
	AList< AList< Edge<Te>* > > E;//边集（边组成的二维向量）

public:
	//构造析构 
	GraphMatrix() {
		n = e = 0;
	}
	virtual ~GraphMatrix() {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				delete E[i][j];
			}
 		}
	}
	
	/*顶点的操作接口*/ 
	// 顶点的基本操作：查询第i个顶点（0 <= i < n）
	virtual Tv& vertex ( int i ) { return V[i].data; } //数据
	virtual int inDegree ( int i ) { return V[i].inDegree; } //入度
	virtual int outDegree ( int i ) { return V[i].outDegree; } //出度
	virtual int firstNbr ( int i ) { return nextNbr ( i, n ); } //首个邻接顶点
	virtual int nextNbr ( int i, int j ) {  //相对于顶点j的下一邻接顶点（改用邻接表可提高效率）
		while ( ( -1 < j ) && ( !exists ( i, --j ) ) ); //逆向线性试探(此时已经枚举到j)
		return j; 
	} 
	virtual VStatus& status ( int i ) { return V[i].status; } //状态
	virtual int& dTime ( int i ) { return V[i].dTime; } //时间标签dTime
	virtual int& fTime ( int i ) { return V[i].fTime; } //时间标签fTime
	virtual int& parent ( int i ) { return V[i].parent; } //在遍历树中的父亲
	virtual int& priority ( int i ) { return V[i].priority; } //在遍历树中的优先级数 
	//顶点的动态操作(插入、删除) 
	//顶点插入,返回编号 
	virtual int insert(const Tv& vertex) {
		for (int i = 0; i < n; i++) {
			E[i].append(NULL);
		} 
		n++;
		E.append(AList<Edge<Te>*>(n, NULL));
		return V.append(Vertex<Tv>(vertex));
	}
	//顶点删除，删除顶点及其关联边，返回该顶点信息
	virtual Tv remove(int i) {
		for (int j = 0; j < n; j++) {
			if (exists(i, j)) { //删除所有出边 
				delete E[i][j];
				V[j].inDegree--;
			}
		}
		E.remove(i); n--; // 删除第i行
		Tv vBak = vertex(i); //备份顶点i的信息
		V.remove(i);
		for ( int j = 0; j < n; j++ ) {//所有入边
			if ( Edge<Te> * e = E[j].remove ( i ) ) { 
				delete e; V[j].outDegree--; 
			} //逐条删除
		}
		return vBak; //返回被删除顶点的信息 
	} 
	
	/*边的操作接口*/ 
	//边的确认操作(是否存在这样一条边) 
	virtual bool exists(int i, int j) { //边(i,j)是否存在 (i,j) is valid && (i,j) != NULL
		return (0 <= i) && (i < n) && (0 <= j) && (j < n) && E[i][j] != NULL;
	}
	//边的基本操作:查询第(i,j)条边的数据、状态、权重 
	virtual Te& edge(int i, int j) {
		return E[i][j]->data;
	} 
	virtual EStatus& status(int i, int j) {
		return E[i][j]->status;
	}
	virtual int& weight(int i, int j) {
		return E[i][j]->weight;
	}
	//边的动态操作（插入、删除） 
	//边插入
	virtual void insert(const Te& edge, int w, int i, int j) {
		if (exists(i, j)) return; //忽略原有的边 
		E[i][j] = new Edge<Te>(edge, w);//将新边的信息封装，并让E[i][j]指向这个边 
		e++; //更新边计数 
		V[i].outDegree++; //更新关联顶点i的出度 
		V[j].inDegree++;  //更新关联顶点j的入度 
	} 
	//边删除
	virtual Te remove(int i, int j) {
		Te eBak = edge(i, j); //bak-备份 备份边(i,j)的信息（data） 
		delete E[i][j];
		E[i][j] = NULL; //删除边
		e--;
		V[i].outDegree--;
		V[j].inDegree--; 
		return eBak;
	} 

};

#endif