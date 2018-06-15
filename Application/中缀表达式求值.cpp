/*˵����
�˼����������ڼ�������Ӽ��˳������ݲ�������׺���ʽ��֧�����ţ�֧�ֶ�λ����С����
���ʽ�еĿո�ᱻ�Զ����ԡ�
����ԭ��������ջ����׺���ʽת��Ϊ��׺���ʽ�������ú�׺���ʽ��ֵ��
���ɽ�һ������׺���ʽ������һ�ű��ʽ��������Ҳ������ֵ��
���ǵ���׺���ʽ�Ѿ�������ֵ���ʴ˹����ڱ�������δ��ʵ��*/ 
#include <iostream>
#include <string> 
#include <cmath>
#include "../Stack/AStack.h"
using namespace std;

bool isDigit(const char& c) { //�ж��Ƿ������� 
	return (c >= '0') && (c <= '9');
}

bool lower(const char& infixExpr, const char& topValue) { 
//�жϵ�ǰ��ȡ��infixExpression���ź�ջ��Ԫ�ص����ȼ���ǰ�ߵ��ں��ߣ�����true 
//	cout << "infixExpr: " << infixExpr << " topValue: " << topValue << endl; //������ 
	if (topValue == '(') return false;
	else if (infixExpr == '^') return false;
	else if ((infixExpr == '*' || infixExpr == '/') && (topValue == '+' || topValue == '-')) return false;
	else return true;
}

string convert(const string& infixExpr) { //��׺���ʽ->��׺���ʽ 
	AStack<char> S;
	string postfixExpr;
	unsigned i = 0;
	while (i < infixExpr.length()) {
		if (infixExpr[i] == ' ') { //�����ո�ֱ�Ӻ��� 
			i++;
		} if (isDigit(infixExpr[i]) || (infixExpr[i] == '.')) { // ����С��һ����ȡ���ÿո�ֿ���ͬ�����ֺͲ������� 
			while (isDigit(infixExpr[i]) || infixExpr[i] == '.') {
				postfixExpr.append(1, infixExpr[i++]);
			}
			postfixExpr.append(1, ' ');
		} else if (infixExpr[i] == '(') {  // ������ֱ����ջ 
			S.push(infixExpr[i++]);
		} else if (infixExpr[i] == ')') {  // �����ţ���ջ�а�����һ�������ŵ�����Ԫ��ȫpop�� 
			char temp = S.pop();
			while (temp != '(') {
				postfixExpr.append(1,temp);
				postfixExpr.append(1, ' ');
				temp = S.pop();
			}
			i++;
		} else { //���else˵����һ�������� 
			if (S.isEmpty()) { //��ջ�������ֱ����ջ 
				S.push(infixExpr[i++]);
			} else {
				while (!S.isEmpty() && lower(infixExpr[i], S.topValue())) {
					postfixExpr.append(1,S.pop());
					postfixExpr.append(1, ' ');
				}
				S.push(infixExpr[i++]);
			}
		}
	}
	while (!S.isEmpty()) {
		postfixExpr.append(1,S.pop());
		postfixExpr.append(1, ' ');
	}
	return postfixExpr;
}

double evaluate(const string& postfixExpr) { //�����׺���ʽ��ֵ 
	AStack<double> S;
	unsigned i = 0;
	while (i < postfixExpr.length()) {
		if (postfixExpr[i] == ' ') {
			i++;
		} else if (isDigit(postfixExpr[i]) || (postfixExpr[i] == '.')) { // ����С��һ����ȡ 
			double num = 0;
			bool flag = true; //falg������С������Ϊfalse
			double divider = 10.0;
			while (isDigit(postfixExpr[i]) || postfixExpr[i] == '.') {
				if (postfixExpr[i] == '.') {
					flag = false;
				} else if (flag) {
					num = num *10 + (postfixExpr[i] - '0');
				} else {
					num = num + (postfixExpr[i] - '0') / divider;
					divider *= 10;
				}
				i++;
			}
			S.push(num);
		} else { // ��ȡ���ǲ���������� 
			double rOpnd = S.pop();
			double lOpnd = S.pop();
			switch (postfixExpr[i]) {
				case '+':
					S.push(lOpnd + rOpnd);
					break;
				case '-':
					S.push(lOpnd - rOpnd);
					break;
				case '*':
					S.push(lOpnd * rOpnd);
					break; 
				case '/':
					S.push(lOpnd + rOpnd);
					break;
				case '^':
					S.push(pow(lOpnd, rOpnd));
					break;
			}
			i++;
		}
	}
}

int main() {

	string infixExpression;
	cout << "Please enter a valid infix expression:" << endl;
	getline(cin, infixExpression);
	string postfixExpression = convert(infixExpression);
	cout <<"postfix expression: " << postfixExpression << endl;
	cout << "value = " << evaluate(postfixExpression) << endl;
	return 0;
} 
