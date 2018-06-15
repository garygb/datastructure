#include <iostream>
#include "GraphMatrix.h" 

int main(int argc, char** argv) {
	
	//�����ڽӱ�ʵ�ֵ�graph��BFS��DFS��ʱ�临�Ӷ�ΪO��n+e��������graph�Ŀռ临�Ӷ�ΪO��n^2��
	//֧������ͼ������ͼ��֧�ִ�Ȩͼ
	//֧�ֱߺͶ���Ĳ���ɾ��
	//֧�ַ���ͨͼ������
	//����˳���AListʵ�֣����鱾�Ļ�������ǿ�˶�̬�ԣ������Զ��������ȣ������˹���ķ�ʽ��������[]��=�������

	GraphMatrix<char, int> graph; //char-������������ int-����������
	//���붥�㣨��Ű��ղ�����Ⱥ�˳������
	graph.insert('a'); //���Ϊ0
	graph.insert('b'); //���Ϊ1
	graph.insert('c');
	graph.insert('d');
	//����ߣ�data, weight, from, to
	graph.insert(1, 1, 0, 1); 
	graph.insert(1, 1, 0, 2);
	graph.insert(1, 1, 0, 3);
	graph.insert(1, 1, 1, 3);
	graph.insert(1, 1, 2, 3);
	cout << "# of vertexes: " << graph.n << endl;
	cout << "# of edges: " << graph.e << endl;
	//��д��BFS��DFS����֧�ֶ�Ӧ�Ĳ�������Ҫ�õ�ʱ����ʱ�Ӿͺ��ˣ�������޷�����������ֱ�۵ش�ӡ����
	//��������ǰ��ÿ�������״̬�ǻ�ı��
	//����ǰ�����������״̬�� 0-UNDISCOVERED 1-DISCOVERED 2-VISITED
	cout << "Status of each vertex before BFS/DFS: 0-UNDISCOVERED 1-DISCOVERED 2-VISITED" << endl;
	for(int i = 0; i < 4; i++) { 
		cout << graph.status(i) << " ";
	}
	cout << endl;
	//dfs֧�ֵ���ͨ��ͼ��Ҳ֧�ֶ���ͨ��ͼ��ע�͵�һЩ�������ԣ�
	graph.dfs(1); //�����Ϊ1�Ķ��㿪ʼ������ʵ���ϴ��ĸ��㿪ʼ�������ǿ��Եģ����Ըĵ�1���ԣ�
//	graph.bfs(2); //bfs�ӿ�
	//����ǰ�����������״̬���������ȫ��Ϊ2��VISITED��,��˵�������������ж���
	cout << "Status of each vertex after BFS/DFS: 0-UNDISCOVERED 1-DISCOVERED 2-VISITED" << endl;
	for(int i = 0; i < 4; i++) {
		cout << graph.status(i) << " ";
	}
	cout << endl;
	//����ͱ�֧�ֵ�һЩ������̬�Ͷ�̬����
	cout << "Data in vertex(3): " << graph.vertex(3) << endl;
	cout << "Exists a edge between vertex 0 and 1 ?" 
		 << (graph.exists(0,1) ? "Yes" : "No") << endl;
	cout << "Indegree(0): " << graph.inDegree(0) << endl;
	cout << "Outdegree(0): " << graph.outDegree(0) << endl;
	//ɾ���ߣ�0,1��
	cout << "Removing edge(0, 1),return data of edge(0, 1): " << graph.remove(0,1) << endl;
	cout << "After remove edge(0,1):" << endl;
	cout << "# of vertexes: " << graph.n << endl;
	cout << "# of edges: " << graph.e << endl;
	cout << "Exists a edge between vertex 0 and 1 ?" 
		 << (graph.exists(0,1) ? "Yes" : "No") << endl;
	//ɾ�����Ϊ1�Ķ��㣨ע�⣬��ɾ�����������֮��Ķ�����ž�ǰ1λ��
	cout << "Removing vertex(1),return data of vertex(1): " << graph.remove(1) << endl;
	cout << "After remove vertex(1):" << endl;
	cout << "# of vertexes: " << graph.n << endl;

	system("pause");
	return 0;
}