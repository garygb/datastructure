/*说明：
此计算器可用于计算包含加减乘除和求幂操作的中缀表达式，支持括号，支持多位数和小数。
表达式中的空格会被自动忽略。
基本原理是利用栈将中缀表达式转换为后缀表达式，再利用后缀表达式求值。
并可进一步将后缀表达式构建成一颗表达式树，这样也利于求值。
考虑到后缀表达式已经易于求值，故此功能在本程序中未被实现*/ 
#include <iostream>
#include <string> 
#include <cmath>
#include "../Stack/AStack.h"
using namespace std;

bool isDigit(const char& c) { //判断是否是数字 
	return (c >= '0') && (c <= '9');
}

bool lower(const char& infixExpr, const char& topValue) { 
//判断当前读取的infixExpression符号和栈顶元素的优先级，前者低于后者，返回true 
//	cout << "infixExpr: " << infixExpr << " topValue: " << topValue << endl; //测试用 
	if (topValue == '(') return false;
	else if (infixExpr == '^') return false;
	else if ((infixExpr == '*' || infixExpr == '/') && (topValue == '+' || topValue == '-')) return false;
	else return true;
}

string convert(const string& infixExpr) { //中缀表达式->后缀表达式 
	AStack<char> S;
	string postfixExpr;
	unsigned i = 0;
	while (i < infixExpr.length()) {
		if (infixExpr[i] == ' ') { //遇到空格直接忽略 
			i++;
		} if (isDigit(infixExpr[i]) || (infixExpr[i] == '.')) { // 数字小数一并读取，用空格分开不同的数字和操作符号 
			while (isDigit(infixExpr[i]) || infixExpr[i] == '.') {
				postfixExpr.append(1, infixExpr[i++]);
			}
			postfixExpr.append(1, ' ');
		} else if (infixExpr[i] == '(') {  // 左括号直接入栈 
			S.push(infixExpr[i++]);
		} else if (infixExpr[i] == ')') {  // 右括号，则将栈中包含第一个左括号的所有元素全pop出 
			char temp = S.pop();
			while (temp != '(') {
				postfixExpr.append(1,temp);
				postfixExpr.append(1, ' ');
				temp = S.pop();
			}
			i++;
		} else { //这个else说明是一个操作符 
			if (S.isEmpty()) { //空栈则操作符直接入栈 
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

double evaluate(const string& postfixExpr) { //计算后缀表达式的值 
	AStack<double> S;
	unsigned i = 0;
	while (i < postfixExpr.length()) {
		if (postfixExpr[i] == ' ') {
			i++;
		} else if (isDigit(postfixExpr[i]) || (postfixExpr[i] == '.')) { // 数字小数一并读取 
			double num = 0;
			bool flag = true; //falg在遇到小数点后变为false
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
		} else { // 读取的是操作符的情况 
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
