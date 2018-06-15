#include <iostream>
#include "GraphMatrix.h"
using namespace std;

int main() {
	
	GraphMatrix<char, int> graph;
	int n, e;
	cout << "Please enter the # of city: ";
	cin >> n;
	for (int i = 0; i < n; i++) {
		char city;
		cout << "Please enter the " << i+1 << "th city: ";
		cin >> city;
		graph.insert(city);
	}
	cout << "Please enter  the # of road: ";
	cin >> e;
	for (int i = 0; i < e; i++) {
		int length;
		char from, to;
		cout << "Please enter the length, source and distination of the " << i+1 << "th road: ";
		cin >> length >> from >> to;
		Rank rankFr = graph.find(from);
		Rank rankTo = graph.find(to);
		graph.insert(0, length, rankFr, rankTo);
		graph.insert(0, length, rankTo, rankFr);
	}
	cout << "Please enter the departure city and distination city: ";
	char start, end;
	cin >> start >> end;
	Rank rankSt = graph.find(start);
	Rank rankEn = graph.find(end);

	int count = graph.FindAllPath(rankSt, rankEn);
	if (count == 0) {
		cout << "No path." << endl;
	} else {
		cout << "Total " << count << " paths" << endl;
	}
	system("pause");
	return 0;
} 