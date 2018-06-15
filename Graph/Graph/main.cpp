#include <iostream>
#include "GraphMatrix.h" 

int main(int argc, char** argv) {
	
	//基于邻接表实现的graph，BFS和DFS的时间复杂度为O（n+e），整个graph的空间复杂度为O（n^2）
	//支持无向图和有向图，支持带权图
	//支持边和顶点的插入删除
	//支持非连通图的搜索
	//基于顺序表AList实现（在书本的基础上增强了动态性，可以自动伸缩长度，增加了构造的方式，重载了[]和=运算符）

	GraphMatrix<char, int> graph; //char-顶点数据类型 int-边数据类型
	//插入顶点（序号按照插入的先后顺序排序）
	graph.insert('a'); //序号为0
	graph.insert('b'); //序号为1
	graph.insert('c');
	graph.insert('d');
	//插入边：data, weight, from, to
	graph.insert(1, 1, 0, 1); 
	graph.insert(1, 1, 0, 2);
	graph.insert(1, 1, 0, 3);
	graph.insert(1, 1, 1, 3);
	graph.insert(1, 1, 2, 3);
	cout << "# of vertexes: " << graph.n << endl;
	cout << "# of edges: " << graph.e << endl;
	//我写的BFS和DFS并不支持对应的操作器（要用的时候临时加就好了），因此无法将搜索过程直观地打印出来
	//但是搜索前后每个顶点的状态是会改变的
	//搜索前，输出各顶点状态： 0-UNDISCOVERED 1-DISCOVERED 2-VISITED
	cout << "Status of each vertex before BFS/DFS: 0-UNDISCOVERED 1-DISCOVERED 2-VISITED" << endl;
	for(int i = 0; i < 4; i++) { 
		cout << graph.status(i) << " ";
	}
	cout << endl;
	//dfs支持单连通的图，也支持多连通的图（注释掉一些顶点试试）
	graph.dfs(1); //从序号为1的顶点开始搜索（实际上从哪个点开始搜索都是可以的，可以改掉1试试）
//	graph.bfs(2); //bfs接口
	//搜索前，输出各顶点状态。若输出的全部为2（VISITED）,可说明搜索遍了所有顶点
	cout << "Status of each vertex after BFS/DFS: 0-UNDISCOVERED 1-DISCOVERED 2-VISITED" << endl;
	for(int i = 0; i < 4; i++) {
		cout << graph.status(i) << " ";
	}
	cout << endl;
	//顶点和边支持的一些其他静态和动态操作
	cout << "Data in vertex(3): " << graph.vertex(3) << endl;
	cout << "Exists a edge between vertex 0 and 1 ?" 
		 << (graph.exists(0,1) ? "Yes" : "No") << endl;
	cout << "Indegree(0): " << graph.inDegree(0) << endl;
	cout << "Outdegree(0): " << graph.outDegree(0) << endl;
	//删除边（0,1）
	cout << "Removing edge(0, 1),return data of edge(0, 1): " << graph.remove(0,1) << endl;
	cout << "After remove edge(0,1):" << endl;
	cout << "# of vertexes: " << graph.n << endl;
	cout << "# of edges: " << graph.e << endl;
	cout << "Exists a edge between vertex 0 and 1 ?" 
		 << (graph.exists(0,1) ? "Yes" : "No") << endl;
	//删除编号为1的顶点（注意，在删除顶点后，所有之后的顶点序号均前1位）
	cout << "Removing vertex(1),return data of vertex(1): " << graph.remove(1) << endl;
	cout << "After remove vertex(1):" << endl;
	cout << "# of vertexes: " << graph.n << endl;

	system("pause");
	return 0;
}