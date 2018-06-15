#ifndef _GRAPHMATRIX_H_
#define _GRAPHMATRIX_H_
#include "..\..\List\AList.h" 
#include "Graph.h"

template <typename Tv>
struct Vertex { //������󣨲�δ�ϸ��װ�� 
	Tv data; //�������� 
	int inDegree, outDegree; //��Ⱥͳ���
	VStatus status;
	int dTime, fTime; //ʱ���ǩ
	int parent; //�ڱ������еĸ��ڵ�
	int priority; //�ڱ������е����ȼ������ͨ·�����̿�ߵȣ�
	Vertex (const Tv& d = (Tv)0) :
		data(d), inDegree(0), outDegree(0), status(UNDISCOVERED), 
		dTime(-1), fTime(-1), priority(INT_MAX) { } 
};

template <typename Te> 
struct Edge { //�߶���Ϊ���������δ�ϸ��װ��
	Te data; int weight; EStatus status; //���ݡ�Ȩ�ء�����
	Edge (const Te& d, int w) : 
		data (d), weight (w), status(UNDETERMINED) {} //�����±� 
};

template <typename Tv, typename Te> //�������ͺͱ����� 
class GraphMatrix : public Graph<Tv, Te> { //�����������Ծ�����ʽʵ�ֵ�ͼ 
private: 
	AList< Vertex<Tv> > V; //���㼯��һ�鶥����ɵ�������
	AList< AList< Edge<Te>* > > E;//�߼�������ɵĶ�ά������

public:
	//�������� 
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
	
	/*����Ĳ����ӿ�*/ 
	// ����Ļ�����������ѯ��i�����㣨0 <= i < n��
	virtual Tv& vertex ( int i ) { return V[i].data; } //����
	virtual int inDegree ( int i ) { return V[i].inDegree; } //���
	virtual int outDegree ( int i ) { return V[i].outDegree; } //����
	virtual int firstNbr ( int i ) { return nextNbr ( i, n ); } //�׸��ڽӶ���
	virtual int nextNbr ( int i, int j ) {  //����ڶ���j����һ�ڽӶ��㣨�����ڽӱ�����Ч�ʣ�
		while ( ( -1 < j ) && ( !exists ( i, --j ) ) ); //����������̽(��ʱ�Ѿ�ö�ٵ�j)
		return j; 
	} 
	virtual VStatus& status ( int i ) { return V[i].status; } //״̬
	virtual int& dTime ( int i ) { return V[i].dTime; } //ʱ���ǩdTime
	virtual int& fTime ( int i ) { return V[i].fTime; } //ʱ���ǩfTime
	virtual int& parent ( int i ) { return V[i].parent; } //�ڱ������еĸ���
	virtual int& priority ( int i ) { return V[i].priority; } //�ڱ������е����ȼ��� 
	//����Ķ�̬����(���롢ɾ��) 
	//�������,���ر�� 
	virtual int insert(const Tv& vertex) {
		for (int i = 0; i < n; i++) {
			E[i].append(NULL);
		} 
		n++;
		E.append(AList<Edge<Te>*>(n, NULL));
		return V.append(Vertex<Tv>(vertex));
	}
	//����ɾ����ɾ�����㼰������ߣ����ظö�����Ϣ
	virtual Tv remove(int i) {
		for (int j = 0; j < n; j++) {
			if (exists(i, j)) { //ɾ�����г��� 
				delete E[i][j];
				V[j].inDegree--;
			}
		}
		E.remove(i); n--; // ɾ����i��
		Tv vBak = vertex(i); //���ݶ���i����Ϣ
		V.remove(i);
		for ( int j = 0; j < n; j++ ) {//�������
			if ( Edge<Te> * e = E[j].remove ( i ) ) { 
				delete e; V[j].outDegree--; 
			} //����ɾ��
		}
		return vBak; //���ر�ɾ���������Ϣ 
	} 
	
	/*�ߵĲ����ӿ�*/ 
	//�ߵ�ȷ�ϲ���(�Ƿ��������һ����) 
	virtual bool exists(int i, int j) { //��(i,j)�Ƿ���� (i,j) is valid && (i,j) != NULL
		return (0 <= i) && (i < n) && (0 <= j) && (j < n) && E[i][j] != NULL;
	}
	//�ߵĻ�������:��ѯ��(i,j)���ߵ����ݡ�״̬��Ȩ�� 
	virtual Te& edge(int i, int j) {
		return E[i][j]->data;
	} 
	virtual EStatus& status(int i, int j) {
		return E[i][j]->status;
	}
	virtual int& weight(int i, int j) {
		return E[i][j]->weight;
	}
	//�ߵĶ�̬���������롢ɾ���� 
	//�߲���
	virtual void insert(const Te& edge, int w, int i, int j) {
		if (exists(i, j)) return; //����ԭ�еı� 
		E[i][j] = new Edge<Te>(edge, w);//���±ߵ���Ϣ��װ������E[i][j]ָ������� 
		e++; //���±߼��� 
		V[i].outDegree++; //���¹�������i�ĳ��� 
		V[j].inDegree++;  //���¹�������j����� 
	} 
	//��ɾ��
	virtual Te remove(int i, int j) {
		Te eBak = edge(i, j); //bak-���� ���ݱ�(i,j)����Ϣ��data�� 
		delete E[i][j];
		E[i][j] = NULL; //ɾ����
		e--;
		V[i].outDegree--;
		V[j].inDegree--; 
		return eBak;
	} 

};

#endif