#include "polynomial_parser.hpp"

#include <iostream> 
#include <stack> 
#include <string>
#include <cctype>
#include <sstream>
using namespace std;
Polynomial PolynomialParser::compute_polynomial(const std::string& expression, //�����expression����postfix notation��������
	std::map<std::string, Polynomial>& polys) {  
	stack < Polynomial > stack;


	std::stringstream String(expression);
	std::string element;
	while (String >> element) {
		if (element == "+") {
			auto A = stack.top();
			stack.pop();
			auto B = stack.top();
			stack.pop();
			stack.push(A + B);
			
		}
		else if (element == "-") {
			auto A = stack.top();
			stack.pop();
			auto B = stack.top();
			stack.pop();
			stack.push(B-A);
		}
		else if (element == "*") {
			auto A = stack.top();
			stack.pop();
			auto B = stack.top();
			stack.pop();
			stack.push(A * B);
		}
		else {
			stack.push(polys[element]);
		}
	}
	return stack.top();
	//int index = 0;
	//int begin=0;
	//int end;
	//string middle;
	//
	////Polynomial result;
	///*std::stringstream String(expression);
	//std::string element;
	//while (String >> element) {

	//}*/
	//while (index < expression.size()) {
	//	if (expression[index] == ' ') {
	//		end = index - 1;
	//		middle = expression.substr(begin, end - begin + 1);
	//		begin = index + 1;
	//		if (middle == "+") {
	//			auto A = stack.top();
	//			stack.pop();
	//			auto B = stack.top();
	//			stack.pop();
	//			stack.push(A + B);
	//		}
	//		else if (middle == "-") {
	//			auto A = stack.top();
	//			stack.pop();
	//			auto B = stack.top();
	//			stack.pop();
	//			stack.push(B-A);
	//		}
	//		else if (middle == "*") {
	//			auto A = stack.top();
	//			stack.pop();
	//			auto B = stack.top();
	//			stack.pop();
	//			stack.push(A * B);
	//		}
	//		else {
	//			stack.push(polys[middle]);
	//		}
	//		
	//	}
	//	index += 1;
	//}
	//if (expression[index - 1] != ' ') {
	//	if (expression[index - 1] == '+') {
	//		Polynomial A = stack.top();
	//		stack.pop();
	//		Polynomial B = stack.top();
	//		stack.pop();
	//		stack.push(A + B);
	//	}
	//	else if (expression[index - 1] == '-') {
	//		Polynomial A = stack.top();
	//		stack.pop();
	//		Polynomial B = stack.top();
	//		stack.pop();
	//		stack.push(B-A);
	//	}
	//	else if (expression[index - 1] == '*') {
	//		Polynomial A = stack.top();
	//		stack.pop();
	//		Polynomial B = stack.top();
	//		stack.pop();
	//		stack.push(A * B);
	//	}
	//}
	//
	//return stack.top();
}


typedef std::function<double(double)> scalarFct;  //������һ�����������Ĳ�����double���ͣ�����ֵҲ��double����
scalarFct PolynomialParser::compute_lambda(const std::string& expression,  //������صĺ���Ӧ�þ��ǲ�����x��ֵ�ĺ���
	std::map<std::string, Polynomial>& polys) {
	return compute_polynomial(expression, polys);
	//stack < Polynomial > stack;
	//int index = 0;
	//int begin = 0;
	//int end;
	//string middle;

	////Polynomial result;

	//while (index < expression.size()) {
	//	if (expression[index] == ' ') {
	//		end = index - 1;
	//		middle = expression.substr(begin, end - begin + 1);
	//		begin = index + 1;
	//		if (middle == "+") {
	//			Polynomial A = stack.top();
	//			stack.pop();
	//			Polynomial B = stack.top();
	//			stack.pop();
	//			stack.push(A + B);
	//		}
	//		else if (middle == "-") {
	//			Polynomial A = stack.top();
	//			stack.pop();
	//			Polynomial B = stack.top();
	//			stack.pop();
	//			stack.push(A - B);
	//		}
	//		else if (middle == "*") {
	//			Polynomial A = stack.top();
	//			stack.pop();
	//			Polynomial B = stack.top();
	//			stack.pop();
	//			stack.push(A * B);
	//		}
	//		else {
	//			stack.push(polys[middle]);
	//		}

	//	}
	//	index += 1;
	//}
	//if (expression[index - 1] != ' ') {
	//	if (expression[index - 1] == '+') {
	//		Polynomial A = stack.top();
	//		stack.pop();
	//		Polynomial B = stack.top();
	//		stack.pop();
	//		stack.push(A + B);
	//	}
	//	else if (expression[index - 1] == '-') {
	//		Polynomial A = stack.top();
	//		stack.pop();
	//		Polynomial B = stack.top();
	//		stack.pop();
	//		stack.push(A - B);
	//	}
	//	else if (expression[index - 1] == '*') {
	//		Polynomial A = stack.top();
	//		stack.pop();
	//		Polynomial B = stack.top();
	//		stack.pop();
	//		stack.push(A * B);
	//	}
	//}

	//return [&](double x)->double {
	//	return stack.top()(x);
	//};
	
}
