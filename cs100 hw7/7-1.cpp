//#include <algorithm>
//#include <cstddef>
//#include <iomanip>
//#include <iostream>
//#include <vector>
//using namespace std;
//class Grade {
//public:
//	// This constructor initializes the members with the parameters.
//	Grade(const std::string& name, int number, double grade);
//	Grade();
//	~Grade();
//	std::string getName() const;
//	void setName(const std::string& name);
//	int getNumber() const;
//	void setNumber(int number);
//	double getGrade() const;
//	void setGrade(double grade);
//
//private:
//	std::string m_name;
//	int m_number;
//	double m_grade;
//};
//
//Grade::Grade(const std::string& name, int number, double grade) :m_name(name), m_number(number), m_grade(grade) {
//
//}
//Grade::Grade() :m_name(""), m_number(0), m_grade(0) {
//
//}
//
//Grade::~Grade() {
//
//}
//
//string Grade::getName()const {
//	return this->m_name;
//}
//
//void Grade::setName(const std::string& name) {
//	this->m_name = name;
//}
//
//int Grade::getNumber()const {
//	return this->m_number;
//}
//
//void Grade::setNumber(int number) {
//	this->m_number = number;
//}
//
//double Grade::getGrade()const {
//	return this->m_grade;
//}
//
//void Grade::setGrade(double grade) {
//	this->m_grade = grade;
//}
//
//struct NameComparator {
//	bool operator()(const Grade& a, const Grade& b) const {
//		
//		return a.getName() < b.getName();
//	
//	 
//	}
//};
//
//struct NumberComparator {
//	bool operator()(const Grade& a, const Grade& b) const {
//		
//			return a.getNumber() < b.getNumber();
//		
//	    
//	}
//};
//
//struct GradeComparator {
//	bool operator()(const Grade& a, const Grade& b) const {
//		
//			return(a.getGrade() > b.getGrade());
//		
//		
//	  
//		
//
//
//	}
//};
//
//
//
//class Gradesheet {
//	friend std::ostream& operator<<(std::ostream& os, const Gradesheet& sheet);
//
//public:
//	Gradesheet();
//	//Gradesheet(const Grade& grade);
//	~Gradesheet();
//	std::size_t size() const;
//	double average() const;
//	bool addGrade(const Grade& grade);
//	double findByName(const std::string& name) const;
//	double findByNumber(int number) const;
//	Grade& operator[](std::size_t i);
//	const Grade& operator[](std::size_t i) const;
//	void sortByName();
//	void sortByNumber();
//	void sortByGrade();
//
//private:
//	std::vector<Grade> m_grades;
//	std::size_t m_records_num;
//};
//
//Gradesheet::Gradesheet() :m_grades(0), m_records_num(0) {
//
//}
//
//
//
//Gradesheet::~Gradesheet() {
//
//}
//
//std::size_t Gradesheet::size()const {
//	return m_records_num;
//}
//
//double Gradesheet::average() const {
//	double sum = 0;
//	for (int i = 0; i < m_records_num; i++) {
//		sum += m_grades[i].getGrade();
//	}
//	double average = sum / m_records_num;
//	return average;
//}
//
//bool Gradesheet::addGrade(const Grade& grade) {
//	int is_in_vector = 0;
//	for (int j = 0; j < m_records_num; j++) {
//		if (m_grades[j].getName() == grade.getName() || m_grades[j].getNumber() == grade.getNumber()) {
//			is_in_vector = 1;
//			break;
//		}
//	}
//	if (is_in_vector == 1) {
//		return false;
//	}
//	else {
//		m_grades.emplace_back(grade);
//		m_records_num += 1;
//		return true;
//	}
//}
//double Gradesheet::findByName(const std::string& name) const {
//	int is_in_vector = 0;
//	for (int j = 0; j < m_records_num; j++) {
//		if (m_grades[j].getName() == name) {
//			is_in_vector = 1;
//			return m_grades[j].getGrade();
//			break;
//		}
//	}
//	if (is_in_vector == 0) {
//		return -1;
//	}
//}
//
//double Gradesheet::findByNumber(int number) const {
//	int is_in_vector = 0;
//	for (int j = 0; j < m_records_num; j++) {
//		if (m_grades[j].getNumber() == number) {
//			is_in_vector = 1;
//			return m_grades[j].getGrade();
//			break;
//		}
//	}
//	if (is_in_vector == 0) {
//		return -1;
//	}
//}
//
//Grade& Gradesheet::operator[](std::size_t i) {
//	return m_grades[i];
//}
//
//const Grade& Gradesheet::operator[](std::size_t i)const {
//	return m_grades[i];
//}
//
////bool NameComparator::operator()(const Grade& a, const Grade& b) const { //感觉上应该是name的排序有问题，Bob排在了Blex前面，应该反过来
////	if (a.getName() != b.getName()) {
////		int length = a.getName().length();
////		if (b.getName().length() < length) {
////			length = b.getName().length();
////		}
////		for (int i = 0; i < length; i++) {
////			if (int(a.getName()[i]) < int(b.getName()[i])) {
////				return true;
////			}
////			else if (int(a.getName()[i]) > int(b.getName()[i])) {
////				return false;
////			}
////			else if (int(a.getName()[i]) == int(b.getName()[i])) {
////				continue;
////			}
////		}
////	}
////	else {
////		return true;
////	}
////}
////
////bool NumberComparator::operator()(const Grade& a, const Grade& b) const {
////		return(a.getNumber() < b.getNumber());
////	
////}
////
////bool GradeComparator::operator()(const Grade& a, const Grade& b) const {
////	if (a.getGrade() != b.getGrade()) {
////		return(a.getGrade() > b.getGrade());
////	}
////	else {
////		return true;
////	}
////}
//
//void Gradesheet::sortByName() {
//
//		sort(m_grades.begin(), m_grades.end(), NameComparator());
//}
//
//void Gradesheet::sortByNumber() {
//	
//		sort(m_grades.begin(), m_grades.end(), NumberComparator());
//	
//}
//
//void Gradesheet::sortByGrade() {
//	
//		sort(m_grades.begin(), m_grades.end(), GradeComparator());
//	
//}
//
//ostream& operator<<(std::ostream& os, const Gradesheet& sheet) {
//	os << "/------------------------------\\" << endl;
//
//	os << "|Name      Number    Grade     |" << endl;
//
//	os << "|------------------------------|" << endl;
//
//	for (int i = 0; i < sheet.size(); i++) {
//		os << "|";
//		os.width(10); os << left << sheet[i].getName();
//		os.width(10); os << left << sheet[i].getNumber();
//		os.width(10);  os << left << setprecision(3) << sheet[i].getGrade();
//		os << "|" << endl;
//		
//	}
//	os << "\\------------------------------/" << endl;
//	return os;
//}
//
//int main()
//{
//	Gradesheet sheet;
//	sheet.addGrade(Grade("Bobee", 1, 95));
//	sheet.addGrade(Grade("Alice", 23, 90));
//	sheet.addGrade(Grade("Alex", 2, 100));
//	sheet.addGrade(Grade("Aley", 29, 80));
//	sheet.addGrade(Grade("Alez", 32, 70));
//	sheet.addGrade(Grade("Bobe", 1, 60));
//	sheet.sortByNumber();
//	std::cout << "size == " << sheet.size() << "\n" << sheet;
//	return 0;
//}