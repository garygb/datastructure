#include <iostream>
#include <fstream>
//#include "FreList.h"
#include "TList.h"
using namespace std;

//template <typename T> 
//class Increase {
//	void operator()(T& item) { item++; }
//};

//template <typename T>
//void increase(FreList<T>& frelist) {
//	frelist.traverse(Increase<T>());
//}

template<typename T>
void print(T& item) {
	cout << item << " ";
}

//������ĺ������������part1��part2��
template<typename T>
void printChinese(T& item) {
	cout << item.part1 << item.part2;
}

//����һ��Chinese�࣬����һ�������ַ������������ֽ���Ϣ��part1+part2��
class Chinese {
public:
	char part1;
	char part2;
	Chinese(char a, char b) : part1(a), part2(b) { }
	Chinese(): part1(0), part2(0) { }
	~Chinese() { }
	bool operator== (const Chinese& ch) const { //�е�����part1��part2�����ʱ���������ֲ���ͬ
		return (part1 == ch.part1) && (part2 == ch.part2);
	}
};

int main() {

//	freopen("input.txt", "r", stdin);
//	freopen("output.txt","w", stdout);
	//����Ƶ������ʽ����֯���Ա�
	//FreList<int> frelist;

	////����0��9��һ��10����
	//for (int i = 0; i < 10; i++) {
	//	frelist.append(i);
	//}
	//frelist.search(5);
	//frelist.search(5);
	//frelist.search(3);
	//frelist.traverse(print);
	//cout << endl;
	//frelist.remove(4,6);
	//frelist.traverse(print);
	//cout << endl;


	//����һ���޲ι����ifstream����
	ifstream input;
	//���ļ�(input.txt�д��ԭʼ���ı���search.txt�д��Ҫ���ҵ����֣������������stdout��)
	input.open("input.txt");
	//����ת��ʽ����֯���Ա�
	TList<Chinese> tlist;
	char part1, part2;
	//���ļ��ж�ȡ���ݣ�2��char���һ�������ַ���
	while (input >> part1 && input >> part2) {
		Chinese ch(part1, part2);
		tlist.append(ch);
	}
	//�ر��ļ�
	input.close();
	//���ԭʼ���ı�
	cout << "The original text:" << endl;
	tlist.traverse(printChinese);
	cout << endl << endl;
	//�򿪲��ҵ��������ڵ��ı��ļ�
	ifstream search("search.txt");
	//����һ��Info��Ķ������ڱ���search�ķ���ֵ(���Ҵ���+�Ƿ��ҵ�)
	Info info;
	while (search >> part1 && search >> part2) {
		Chinese ch(part1, part2);
		info = tlist.search(ch);
		cout << "Searching " << ch.part1 << ch.part2 << " compare time = " << info.cmpTime
			<< " Find ? " << ((info.isFind) ? "Yes" : "No") << endl;
	}
	cout << endl << "Text after searching: " << endl;
	tlist.traverse(printChinese);
	cout << endl << endl;
	system("pause");
	return 0;
} 