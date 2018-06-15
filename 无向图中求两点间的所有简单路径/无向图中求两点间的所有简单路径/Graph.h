#ifndef _GRAPH_H_
#define _GRAPH_H_
#include "..\..\Queue\AQueue.h"
#include "..\..\Stack\AStack.h"

typedef enum {
	UNDISCOVERED, DISCOVERED, VISITED
} VStatus;  //����״̬ 

typedef enum { 
	UNDETERMINED, TREE, CROSS, FORWARD, BACKWARD 
} EStatus; //���ڱ�����������������

template <typename Tv, typename Te>
class Graph {
private:
	/*�����ӿڵ��õĺ���*/ 
	void reset() { //���ж��㡢�ߵĸ�����Ϣ��λ 
		for (int i = 0; i < n; i++) { //���� 
			status(i) = UNDISCOVERED;
			dTime(i) = fTime(i) = -1;
			parent(i) = -1;
			priority(i) = INT_MAX;
			for (int j = 0; j < n; j++) { //�� 
				if (exists(i, j)) {
					status(i, j) = UNDETERMINED;
				}
			}
		} 	
	}
	//BFS (ֻ�����ڵ���ͨ��ͼ)
	//���е�statusΪTREE�ı߹���ͼ��֧����
	void BFS(int v, int& clock) { 
	//ʱ�临�Ӷ�O(n+e) whileѭ��n�֣�ÿһ��whileѭ���е�forѭ�����ǵ���������һ�����е��ھӿ���ΪO(n),
	//ʵ�����ڽ��սṹ���ڸ��ٻ����н��У��ٶȴ�����һ�����棬
	//�����while�ı��������Կ�����O(1),����Ĳ��������Ƕ����б߶�Ҫ��һ��ΪO(e),�ܹ�O(n+e) 
		AQueue<int> Q;
		status(v) = DISCOVERED;
		Q.enqueue(v);   //��ʼ����������ǰ�����ΪDISCOVERED������� 
		while (!Q.isEmpty()) {
			int x = Q.dequeue(); //ȡ�����׶��� 
			dTime(x) = ++clock;
			for (int i = firstNbr(x); i > -1; i = nextNbr(x, i)) { //����v��ÿһ���ھ� 
				if (status(i) == UNDISCOVERED) { //��i��δ������ 
					status(i) = DISCOVERED;
					Q.enqueue(i); //���ָö���
					status(x, i) = TREE; parent(i) = x; //�������� 
				} else { //��i�Ѿ������֣����������δ���ʻ����Ѿ����Ӳ��������ˣ�ֻҪ��ӹ����Ͳ����ٴ�����ˣ� 
					status(x, i) = CROSS; //��(x,i)����Ϊ��� 
				} 
			}
			status(x) = VISITED; //����,��ǰ���������� 
		} //���б�գ�BFS���� 
	}
	//DFS(ֻ�����ڵ���ͨ��ͼ) O(n+e)
	void DFS(int v, int& clock) {
		dTime(v) = ++clock;
		status(v) = DISCOVERED; //���ֵ�ǰ����v
		for (int u = firstNbr(v); u > -1; u = nextNbr(v, u)) { //ö��v�����ھ�u 
			switch (status(u)) { //����״̬�ֱ���
				case UNDISCOVERED : //u��δ�����֣���ζ��֧�������ڴ���չ 
					status(v, u) = TREE; 
					parent(u) = v; 
					DFS(u, clock);
					break;
				case DISCOVERED : //u�ѱ����ֵ���δ������ϣ�Ӧ�������ָ������� 
					status(v, u) = BACKWARD; 
					break;
				case VISITED : //u�ѷ������(������ͼ�г���)�������Ϯ��ϵΪǰ��߻���(Parenthesis Lemma����)
					status(v, u) = ((dTime(v) < dTime(u)) ? FORWARD : CROSS);
					break; 			 
			} 
		} 
		status(v) = VISITED; 
		fTime(v) = ++clock; //���ˣ���ǰ����v���������� 
	} 
	//��������·��
	//ע�⵽�����ǵݹ�ص��ô˺��������count���������ڸú����ڲ����𲻵�·�����������õģ����������õķ�ʽ����
	void findAllPath(int fr, int to, bool flag, int& count) { //flagΪ1ʱ�����յ�
//		int totalLen = 0;
		if (fr == to) { //������յ���ͬ�������ֱ�ӷ���
			return;
		} else {
			status(fr) = DISCOVERED; //���ֵ�ǰ����v
			for (int u = firstNbr(fr); u > -1; u = nextNbr(fr, u)) { //ö��v�����ھ�u 
				if (u == to && flag == 1) { //flagΪ1ʱ����֮ǰ�����·����ȫ��ͬ�������ֱ�Ӻ��Ե�
					flag = 0;
					continue;
				}
				if (u == to) { //�����յ㣬ͨ��parent�����������㣬ͨ��һ��stack��������·��
					parent(u) = fr;
					AStack<Tv> S;
					for (int i = u; i != -1; i = parent(i)){
						S.push(vertex(i));
					}
					cout << "path" << ++count << ":";
					while(!S.isEmpty()){
						cout << " " << S.pop();
					}
					cout << endl;
					findAllPath(parent(u), to, 1, count);
				}
				if (status(u) == UNDISCOVERED) { 
					parent(u) = fr; 
					findAllPath(u, to, flag, count);		 
				} 
			} 
			status(fr) = VISITED; 
		}

	} 

public:
	int n; //�������� 
	int e; //������ 
	
	/*����Ĳ����ӿ�*/ 
	// ����Ļ�����������ѯ��i�����㣨0 <= i < n��
	virtual Rank find(const Tv& d) = 0;
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
	//����Ķ�̬����(���롢ɾ��) 
	virtual int insert(const Tv& vertex) = 0;
	virtual Tv remove(int i) = 0;
	
	/*�ߵĲ����ӿ�*/ 
	//�ߵ�ȷ�ϲ���(�Ƿ��������һ����) 
	virtual bool exists(int i, int j)  = 0;
	//�ߵĻ�������:��ѯ��(i,j)���ߵ����ݡ�״̬��Ȩ�� 
	virtual Te& edge(int i, int j) = 0;
	virtual EStatus& status(int i, int j) = 0;
	virtual int& weight(int i, int j) = 0;
	//�ߵĶ�̬���������롢ɾ���� 
	virtual void insert(const Te& edge, int w, int i, int j) = 0;
	virtual Te remove(int i, int j) = 0; 
	
	/*�㷨*/
	//bfs (ֻ�����ڶ���ͨ��ͼ)
	void bfs(int s) { //sΪ��ʼ���� 
		reset();
		int clock = 0;
		int v = s;
		//��һ������ж��㣬һ��������δ���ֵĶ��㣬����BFS�㷨 
		do {
			if (status(v) == UNDISCOVERED)
				BFS(v, clock);
		} while (s != (v = (++v%n)));
	} 
	//dfs (�����ڶ���ͨ��ͼ) O(n+e)
	void dfs(int s) { //sΪ��ʼ���� 
		reset();
		int clock = 0;
		int v = s;
		do {
			if (status(v) == UNDISCOVERED)
				DFS(v, clock);
		} while (s != (v = (++v) % n) );
	} 
	//����·��������
	int FindAllPath(int fr, int to) {
		int count = 0;
		findAllPath(fr, to, 0, count);
		return count;
	}
	
}; 

#endif
 