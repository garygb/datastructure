#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "AList.h"
using namespace std;

template <typename T>
void print(T& ele) {
	cout << ele << " ";
}

int main() {
	//文件重定向 
	freopen("input1.txt","r",stdin);
//	freopen("input2.txt","r",stdin);
//	freopen("input2.txt","w",stdout);

	clock_t start, finish; //设置起止时钟 
	double duration; //时间间隔（单位:second） 
	srand((unsigned)time(NULL)); //生成随机数种子 
	AList<double> alist;  
	double height;
	//读入数据，存入alist(得益于修改后的AList，可以存储大量数据) 
//	for (int i = 0; i < 2000; i++) { //这些用于改变混乱程度 
//		cin >> height;
//		alist.append(height); 
//	}  
//	while (cin >> height) { 
//		alist.insert(alist.length() - rand() % 2000, height);
//	}
	while(cin >> height) {
		alist.append(height);
	} 
	double buT = 0, bfT = 0, meT = 0, quT = 0; 
	for (int loop = 1; loop <= 5; loop++) {
		cout << "-----------------------------------------" << loop << "th loop-----------------------------------" << endl << endl;
		//1.冒泡排序 
		//开始计时 
		start = clock();
		alist.sort(0); //为了测试而做的接口，事实上真正的sort接口肯定不用传入type参数 
		//结束计时 
		finish = clock();
		//查看排序后结果
//		alist.traverse(print); 	cout << endl; 
		//记录总数 
		cout << "1.--------------------Bubble Sort--------------------" << endl;
		cout << "Total " << alist.length() << " records." << endl; 
		//是否已经有序 
		cout << "Sorted? " << (alist.isSorted() ? "Yes" : "No") << endl;
		//sorting耗时 
		duration = (double)(finish - start) / CLOCKS_PER_SEC;
		buT += duration;
		cout << "Sorting Time = " << duration << "sec" << endl;
		//等概率随机置乱 
		alist.unsort();
		cout << "After unsorting: " << "Sorted? " << (alist.isSorted() ? "Yes" : "No") << endl << endl;
		//2.冒泡排序(改进版) 
		//开始计时 
		start = clock();
		alist.sort(1);
		//结束计时 
		finish = clock();
	//	alist.traverse(print);
		//记录总数 
		cout << "2.-----------------Bubble Sort(fast)-----------------" << endl;
		cout << "Total " << alist.length() << " records." << endl; 
		//是否已经有序 
		cout << "Sorted?" << (alist.isSorted() ? "Yes" : "No") << endl;
		//sorting耗时 
		duration = (double)(finish - start) / CLOCKS_PER_SEC;
		bfT += duration;
		cout << "Sorting Time = " << duration << "sec" << endl;
		//等概率随机置乱 
		alist.unsort(); 
		cout << "After unsorting: " << "Sorted? " << (alist.isSorted() ? "Yes" : "No") << endl << endl;
		
		//3.归并排序 
		//开始计时 
		start = clock();
		alist.sort(2);
		//结束计时 
		finish = clock();
	//	alist.traverse(print);	cout << endl; 
		//记录总数 
		cout << "3.--------------------Merge Sort--------------------" << endl;
		cout << "Total " << alist.length() << " records." << endl; 
		//是否已经有序 
		cout << "Sorted?" << (alist.isSorted() ? "Yes" : "No") << endl;
		//sorting耗时 
		duration = (double)(finish - start) / CLOCKS_PER_SEC;
		meT += duration;
		cout << "Sorting Time = " << duration << "sec" << endl;
		//等概率随机置乱 
		alist.unsort();
		cout << "After unsorting: " << "Sorted? " << (alist.isSorted() ? "Yes" : "No") << endl << endl;
		
		//4.快速排序 
		//开始计时 
		start = clock();
		alist.sort(3);
		//结束计时 
		finish = clock();
	//	alist.traverse(print); 	cout << endl;
		//记录总数 
		cout << "4.--------------------Quick Sort--------------------" << endl;
		cout << "Total " << alist.length() << " records." << endl; 
		//是否已经有序 
		cout << "Sorted?" << (alist.isSorted() ? "Yes" : "No") << endl;
		//sorting耗时 
		duration = (double)(finish - start) / CLOCKS_PER_SEC;
		quT += duration;
		cout << "Sorting Time = " << duration << "sec" << endl;
		//等概率随机置乱 
		alist.unsort();
		cout << "After unsorting: " << "Sorted? " << (alist.isSorted() ? "Yes" : "No") << endl << endl;
	} 
	cout << "-------------------------------Average-----------------------------" << endl;
	printf("BubbleSort\tBubble(fast)\tMergeSort\tQuickSort\t\t\n");
	printf("%.3f\t\t%.3f\t\t%.3f\t\t%.3f\t\t",buT/5.0, bfT/5.0, meT/5.0, quT/5.0);
	return 0; 
} 
