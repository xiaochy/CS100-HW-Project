#include "polynomial.hpp"
#include <fstream>
#include <iostream>
#include <cmath>
using namespace std;
int max(int a, int b) {
	if (a >= b) {
		return a;
	}
	else {
		return b;
	}
}

Polynomial::Polynomial() {

}

Polynomial::Polynomial(const std::vector<double>& coeffs):m_coeffs(coeffs) {  

}

Polynomial::Polynomial(std::vector<double>&& coeffs):m_coeffs(move(coeffs)) {  //move constructor

}

Polynomial::Polynomial(std::initializer_list<double> coeffs):m_coeffs(coeffs) {

}

Polynomial::Polynomial(const std::string& path) {
	ifstream file;
	file.open(path);
	double number;
	while (file>>number) {
		m_coeffs.push_back(number);
	}
	file.close();
}






Polynomial::Polynomial(const Polynomial& p) {     //没问题
	m_coeffs = p.m_coeffs;
}

Polynomial::Polynomial(Polynomial&& p) noexcept {
	m_coeffs = move(p.m_coeffs);
}

Polynomial& Polynomial::operator=(const Polynomial& p) {
	if (this == &p) {
		return *this;
	}
	else {
		m_coeffs = p.m_coeffs;
		return *this;
	}
}

Polynomial& Polynomial::operator=(Polynomial&& p) noexcept {
	if (this == &p) {
		return *this;
	}
	else {
		m_coeffs = move(p.m_coeffs);
		return *this;
	}
	
}

Polynomial::~Polynomial() {

}





double& Polynomial::operator[](int index) {  //没问题
	if (index < m_coeffs.size()) {
		return m_coeffs[index];
	}
}

const double& Polynomial::operator[](int index) const { //没问题
	if (index < m_coeffs.size()) {
		return m_coeffs[index];
	}
}

int Polynomial::size() const {    //没问题
	return m_coeffs.size();
}

Polynomial Polynomial:: operator+ (const Polynomial& p) const {
	Polynomial result;
	if (m_coeffs.size() <= p.m_coeffs.size()) {
		for (int i = 0; i < m_coeffs.size(); i++) {
			result.m_coeffs.push_back(m_coeffs[i] + p.m_coeffs[i]);
		}
		for (int j = m_coeffs.size(); j < p.m_coeffs.size(); j++) {
			result.m_coeffs.push_back(p.m_coeffs[j]);
		}
	}
	else {
		for (int i = 0; i < p.m_coeffs.size(); i++) {
			result.m_coeffs.push_back(m_coeffs[i] + p.m_coeffs[i]);
		}
		for (int j = p.m_coeffs.size(); j < m_coeffs.size(); j++) {
			result.m_coeffs.push_back(m_coeffs[j]);
		}
	}
	return result;

	/*Polynomial result;
	vector<double> middle_1 = m_coeffs;
	vector<double> middle_2 = p.m_coeffs;
	int max_length = max(m_coeffs.size(), p.m_coeffs.size());
	if (middle_1.size() < max_length) {
		for (int i = 0; i < max_length - middle_1.size(); i++) {
			middle_1.push_back(0);
		}
	}
	if (middle_2.size() < max_length) {
		for (int i = 0; i < max_length - middle_2.size(); i++) {
			middle_2.push_back(0);
		}
	}
	for (int j = 0; j < max_length; j++) {
		result.m_coeffs.push_back(middle_1[j] + middle_2[j]);
	}
	return result;*/

}

Polynomial& Polynomial::operator+=(const Polynomial& p) {
	if (m_coeffs.size() <= p.m_coeffs.size()) {
		for (int i = 0; i < m_coeffs.size(); i++) {
			m_coeffs[i] += p.m_coeffs[i];
		}
		for (int j = m_coeffs.size(); j < p.m_coeffs.size(); j++) {
			m_coeffs.push_back(p.m_coeffs[j]);
		}
	}
	else {
		for (int i = 0; i < p.m_coeffs.size(); i++) {
			m_coeffs[i] += p.m_coeffs[i];
		}
	}
	return *this;
	/*Polynomial result;
	vector<double> middle_1 = m_coeffs;
	vector<double> middle_2 = p.m_coeffs;
	int max_length = max(m_coeffs.size(), p.m_coeffs.size());
	if (middle_1.size() < max_length) {
		for (int i = 0; i < max_length - middle_1.size(); i++) {
			middle_1.push_back(0);
		}
	}
	if (middle_2.size() < max_length) {
		for (int i = 0; i < max_length - middle_2.size(); i++) {
			middle_2.push_back(0);
		}
	}
	for (int j = 0; j < max_length; j++) {
		result.m_coeffs.push_back(middle_1[j] + middle_2[j]);
	}
	m_coeffs = result.m_coeffs;
	return *this;*/

}

Polynomial Polynomial::operator- (const Polynomial& p) const {
	Polynomial result;
	if (m_coeffs.size() <= p.m_coeffs.size()) {
		for (int i = 0; i < m_coeffs.size(); i++) {
			result.m_coeffs.push_back(m_coeffs[i] - p.m_coeffs[i]);
		}
		for (int j = m_coeffs.size(); j < p.m_coeffs.size(); j++) {
			result.m_coeffs.push_back(-p.m_coeffs[j]);
		}
	}
	else {
		for (int i = 0; i < p.m_coeffs.size(); i++) {
			result.m_coeffs.push_back(m_coeffs[i] - p.m_coeffs[i]);
		}
		for (int j = p.m_coeffs.size(); j < m_coeffs.size(); j++) {
			result.m_coeffs.push_back(m_coeffs[j]);
		}
	}
	return result;
	//Polynomial result;
	//vector<double> middle_1 = m_coeffs;
	//vector<double> middle_2 = p.m_coeffs;
	//int max_length = max(m_coeffs.size(), p.m_coeffs.size());
	//if (middle_1.size() < max_length) {
	//	for (int i = 0; i < max_length - middle_1.size(); i++) {
	//		middle_1.push_back(0);
	//	}
	//}
	//if (middle_2.size() < max_length) {
	//	for (int i = 0; i < max_length - middle_2.size(); i++) {
	//		middle_2.push_back(0);
	//	}
	//}
	//for (int j = 0; j < max_length; j++) {
	//	result.m_coeffs.push_back(middle_1[j] - middle_2[j]);
	//}
	//return result;

}

Polynomial& Polynomial::operator-=(const Polynomial& p) {
	if (m_coeffs.size() <= p.m_coeffs.size()) {
		for (int i = 0; i < m_coeffs.size(); i++) {
			m_coeffs[i] -= p.m_coeffs[i];
		}
		for (int j = m_coeffs.size(); j < p.m_coeffs.size(); j++) {
			m_coeffs.push_back(-p.m_coeffs[j]);
		}
	}
	else {
		for (int i = 0; i < p.m_coeffs.size(); i++) {
			m_coeffs[i] -= p.m_coeffs[i];
		}
	}
	return *this;

	//Polynomial result;
	//vector<double> middle_1 = m_coeffs;
	//vector<double> middle_2 = p.m_coeffs;
	//int max_length = max(m_coeffs.size(), p.m_coeffs.size());
	//if (middle_1.size() < max_length) {
	//	for (int i = 0; i < max_length - middle_1.size(); i++) {
	//		middle_1.push_back(0);
	//	}
	//}
	//if (middle_2.size() < max_length) {
	//	for (int i = 0; i < max_length - middle_2.size(); i++) {
	//		middle_2.push_back(0);
	//	}
	//}
	//for (int j = 0; j < max_length; j++) {
	//	result.m_coeffs.push_back(middle_1[j] - middle_2[j]);
	//}
	//m_coeffs = result.m_coeffs;
	//return *this;

}

Polynomial Polynomial:: operator* (const Polynomial& p) const {
	Polynomial result;
	int max_degree = (m_coeffs.size() - 1) + (p.m_coeffs.size() - 1);
	for (int i = 0; i <= max_degree; i++) {
		result.m_coeffs.push_back(0);
	}

	for (int i = 0; i < m_coeffs.size(); i++) {
		for (int j = 0; j < p.m_coeffs.size(); j++) {
			result[i + j] += m_coeffs[i] * p.m_coeffs[j];
		}
	}
	
	return result;
}

Polynomial Polynomial:: operator* (double factor) const {
	Polynomial result;
	for (int i = 0; i < m_coeffs.size(); i++) {
		result.m_coeffs.push_back(factor * m_coeffs[i]);
	}
	return result;
}

Polynomial& Polynomial::operator*=(const Polynomial& p) {
	Polynomial result;
	int max_degree = (m_coeffs.size() - 1) + (p.m_coeffs.size() - 1);
	for (int i = 0; i <= max_degree; i++) {
		result.m_coeffs.push_back(0);
	}

	for (int i = 0; i < m_coeffs.size(); i++) {
		for (int j = 0; j < p.m_coeffs.size(); j++) {
			result[i + j] += m_coeffs[i] * p.m_coeffs[j];
		}
	}

	m_coeffs = result.m_coeffs;
	return *this;
}



double Polynomial::operator()(double x) const {
	double sum=0;
	for (int i = 0; i < m_coeffs.size(); i++) {
		sum += m_coeffs[i] * pow(x, i);
	}
	return sum;
}
 


