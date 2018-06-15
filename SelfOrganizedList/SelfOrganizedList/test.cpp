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

//输出中文函数（依次输出part1与part2）
template<typename T>
void printChinese(T& item) {
	cout << item.part1 << item.part2;
}

//定义一个Chinese类，保存一个中文字符所包含的两字节信息（part1+part2）
class Chinese {
public:
	char part1;
	char part2;
	Chinese(char a, char b) : part1(a), part2(b) { }
	Chinese(): part1(0), part2(0) { }
	~Chinese() { }
	bool operator== (const Chinese& ch) const { //判等器：part1与part2均相等时才两个汉字才相同
		return (part1 == ch.part1) && (part2 == ch.part2);
	}
};

int main() {

//	freopen("input.txt", "r", stdin);
//	freopen("output.txt","w", stdout);
	//定义频率启发式自组织线性表
	//FreList<int> frelist;

	////插入0到9，一共10个数
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


	//定义一个无参构造的ifstream对象
	ifstream input;
	//打开文件(input.txt中存放原始的文本，search.txt中存放要查找的文字，所有输出均在stdout中)
	input.open("input.txt");
	//定义转置式自组织线性表
	TList<Chinese> tlist;
	char part1, part2;
	//从文件中读取数据（2个char组成一个中文字符）
	while (input >> part1 && input >> part2) {
		Chinese ch(part1, part2);
		tlist.append(ch);
	}
	//关闭文件
	input.close();
	//输出原始的文本
	cout << "The original text:" << endl;
	tlist.traverse(printChinese);
	cout << endl << endl;
	//打开查找的文字所在的文本文件
	ifstream search("search.txt");
	//定义一个Info类的对象，用于保存search的返回值(查找次数+是否找到)
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