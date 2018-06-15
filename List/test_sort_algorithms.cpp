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
	//�ļ��ض��� 
	freopen("input1.txt","r",stdin);
//	freopen("input2.txt","r",stdin);
//	freopen("input2.txt","w",stdout);

	clock_t start, finish; //������ֹʱ�� 
	double duration; //ʱ��������λ:second�� 
	srand((unsigned)time(NULL)); //������������� 
	AList<double> alist;  
	double height;
	//�������ݣ�����alist(�������޸ĺ��AList�����Դ洢��������) 
//	for (int i = 0; i < 2000; i++) { //��Щ���ڸı���ҳ̶� 
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
		//1.ð������ 
		//��ʼ��ʱ 
		start = clock();
		alist.sort(0); //Ϊ�˲��Զ����Ľӿڣ���ʵ��������sort�ӿڿ϶����ô���type���� 
		//������ʱ 
		finish = clock();
		//�鿴�������
//		alist.traverse(print); 	cout << endl; 
		//��¼���� 
		cout << "1.--------------------Bubble Sort--------------------" << endl;
		cout << "Total " << alist.length() << " records." << endl; 
		//�Ƿ��Ѿ����� 
		cout << "Sorted? " << (alist.isSorted() ? "Yes" : "No") << endl;
		//sorting��ʱ 
		duration = (double)(finish - start) / CLOCKS_PER_SEC;
		buT += duration;
		cout << "Sorting Time = " << duration << "sec" << endl;
		//�ȸ���������� 
		alist.unsort();
		cout << "After unsorting: " << "Sorted? " << (alist.isSorted() ? "Yes" : "No") << endl << endl;
		//2.ð������(�Ľ���) 
		//��ʼ��ʱ 
		start = clock();
		alist.sort(1);
		//������ʱ 
		finish = clock();
	//	alist.traverse(print);
		//��¼���� 
		cout << "2.-----------------Bubble Sort(fast)-----------------" << endl;
		cout << "Total " << alist.length() << " records." << endl; 
		//�Ƿ��Ѿ����� 
		cout << "Sorted?" << (alist.isSorted() ? "Yes" : "No") << endl;
		//sorting��ʱ 
		duration = (double)(finish - start) / CLOCKS_PER_SEC;
		bfT += duration;
		cout << "Sorting Time = " << duration << "sec" << endl;
		//�ȸ���������� 
		alist.unsort(); 
		cout << "After unsorting: " << "Sorted? " << (alist.isSorted() ? "Yes" : "No") << endl << endl;
		
		//3.�鲢���� 
		//��ʼ��ʱ 
		start = clock();
		alist.sort(2);
		//������ʱ 
		finish = clock();
	//	alist.traverse(print);	cout << endl; 
		//��¼���� 
		cout << "3.--------------------Merge Sort--------------------" << endl;
		cout << "Total " << alist.length() << " records." << endl; 
		//�Ƿ��Ѿ����� 
		cout << "Sorted?" << (alist.isSorted() ? "Yes" : "No") << endl;
		//sorting��ʱ 
		duration = (double)(finish - start) / CLOCKS_PER_SEC;
		meT += duration;
		cout << "Sorting Time = " << duration << "sec" << endl;
		//�ȸ���������� 
		alist.unsort();
		cout << "After unsorting: " << "Sorted? " << (alist.isSorted() ? "Yes" : "No") << endl << endl;
		
		//4.�������� 
		//��ʼ��ʱ 
		start = clock();
		alist.sort(3);
		//������ʱ 
		finish = clock();
	//	alist.traverse(print); 	cout << endl;
		//��¼���� 
		cout << "4.--------------------Quick Sort--------------------" << endl;
		cout << "Total " << alist.length() << " records." << endl; 
		//�Ƿ��Ѿ����� 
		cout << "Sorted?" << (alist.isSorted() ? "Yes" : "No") << endl;
		//sorting��ʱ 
		duration = (double)(finish - start) / CLOCKS_PER_SEC;
		quT += duration;
		cout << "Sorting Time = " << duration << "sec" << endl;
		//�ȸ���������� 
		alist.unsort();
		cout << "After unsorting: " << "Sorted? " << (alist.isSorted() ? "Yes" : "No") << endl << endl;
	} 
	cout << "-------------------------------Average-----------------------------" << endl;
	printf("BubbleSort\tBubble(fast)\tMergeSort\tQuickSort\t\t\n");
	printf("%.3f\t\t%.3f\t\t%.3f\t\t%.3f\t\t",buT/5.0, bfT/5.0, meT/5.0, quT/5.0);
	return 0; 
} 
