//#include <cstddef>
//#include<vector>
//#include<iostream>
//#include<cmath>;
//using namespace std;
//typedef std::size_t Index;
//typedef double Scalar;
//
//class Matrix {
//public:
//    typedef double Scalar;
//    typedef std::size_t Index;
//
//    Matrix();
//    explicit Matrix(Index rows, Index cols);
//    Matrix(const Matrix& other);
//    Matrix& operator=(const Matrix& other);
//    ~Matrix();
//    Index rows() const;
//    Index cols() const;
//    Scalar& at(Index r, Index c);
//    const Scalar& at(Index r, Index c) const;
//    Matrix operator+(const Matrix& other) const;
//    Matrix operator-(const Matrix& other) const;
//    Matrix operator*(const Matrix& other) const;
//    Matrix transpose() const;
//    Matrix block(Index r, Index c, Index p, Index q) const; // Block of size p x q, starting at (r,c)
//    Scalar trace() const; // For square matrix
//    Scalar determinant() const; // For square matrix
//
//    Index m_rows;
//    Index m_cols;
//    vector< vector<Scalar> > m_matrix;
//
//private:
//    
//    //Matrix deter(Matrix& other,Index column);
//    Scalar determinant(Matrix& other,Index size)const;
//    void submatrix(Matrix A, Matrix& other, int p, int q, int n)const;
//};
//
//Matrix::Matrix(Index rows, Index cols) :m_rows(rows),m_cols(cols), m_matrix(rows, vector<Scalar>(cols, 0)) { //这里必须使用初始化列表！！！！！！
//    
//    //vector<vector<Scalar>> m_matrix(m_rows, vector<Scalar>(m_cols, 0));
//  
//}
//
//Matrix::Matrix(const Matrix& other):m_rows(other.m_rows),m_cols(other.m_cols),m_matrix(other.m_rows,vector<Scalar>(other.m_cols,0)) {
//   
//    for (int i = 0; i < m_rows; i++) {
//        for (int j = 0; j < m_cols; j++) {
//            m_matrix[i][j] = other.m_matrix[i][j];
//        }
//    }
//}
//
//Matrix& Matrix::operator=(const Matrix& other) {
//    if (this->m_rows != other.m_rows || this->m_cols != other.m_cols) {
//        m_matrix.clear();
//        m_rows = other.m_rows;
//        m_cols = other.m_cols;                                                 //下面语句不能只写右边！！！右边的方法是定义！要赋给左值才行！
//        m_matrix = vector<vector<Scalar>>(m_rows, vector<Scalar>(m_cols, 0));//有时间再试试resize的用法，先循环外层再循环内层
//        //m_matrix.resize(m_rows,0);
//       /* m_matrix.resize(other.m_rows);
//        for (int i = 0; i < other.m_rows; i++) {
//            m_matrix[i].resize(other.m_cols,0);
//        }*/
//        for (int i = 0; i < m_rows; i++) {
//            for (int j = 0; j < m_cols; j++) {
//                m_matrix[i][j] = 0;
//            }
//        }
//        for (int i = 0; i < m_rows; i++) {
//            for (int j = 0; j < m_cols; j++) {
//                m_matrix[i][j] = other.m_matrix[i][j];
//            }
//        }
//    }
//    
//    else {
//        for (int i = 0; i < m_rows; i++) {
//            for (int j = 0; j < m_cols; j++) {
//                m_matrix[i][j] = other.m_matrix[i][j];
//            }
//        }
//    }
//    return *this;
//}
//
//Matrix::~Matrix() {
//    //m_matrix.clear();
//}
//
//Index Matrix:: rows() const {
//    return m_rows;
//}
//
//Index Matrix::cols() const {
//    return m_cols;
//}
//
//Scalar& Matrix::at(Index r, Index c) {
//    return m_matrix[r][c];
//}
//
//const Scalar& Matrix::at(Index r, Index c) const {
//    return m_matrix[r][c];
//}
//
//
//Matrix Matrix::operator+(const Matrix& other) const {
//    Matrix local = Matrix(m_rows,m_cols);
//    for (int i = 0; i < m_rows; i++) {
//        for (int j = 0; j < m_cols; j++) {
//            local.m_matrix[i][j] = m_matrix[i][j] + other.m_matrix[i][j];
//        }
//    }
//    return local;
//}
//
//Matrix Matrix::operator-(const Matrix& other) const {
//    Matrix local = Matrix(m_rows, m_cols);
//    for (int i = 0; i < m_rows; i++) {
//        for (int j = 0; j < m_cols; j++) {
//            local.m_matrix[i][j] = m_matrix[i][j] - other.m_matrix[i][j];  //这里做减法的顺序有要求吗？
//        }
//    }
//    return local;
//}
//
//Matrix Matrix::operator*(const Matrix& other) const {
//    Matrix local = Matrix(m_rows, other.m_cols);
//    for (int i = 0; i < m_rows; i++) {
//        for (int j = 0; j < other.m_cols; j++) {
//            for (int k = 0; k < m_cols; k++) {
//                local.m_matrix[i][j] += m_matrix[i][k] * other.m_matrix[k][j];
//            }
//        }
//    }
//    return local;
//   
//}
//
//Matrix Matrix::transpose() const {
//    Matrix local=Matrix(m_cols,m_rows);    
//    for (int i = 0; i < m_cols; i++) {
//        for (int j = 0; j < m_rows; j++) {
//            local.m_matrix[i][j] =m_matrix[j][i];
//        }
//    }
//    return local;
//
//}
//
//Matrix Matrix::block(Index r, Index c, Index p, Index q) const {
//    Matrix local = Matrix(p, q);
//    for (int i = 0; i < p; i++) {
//        for (int j = 0; j < q; j++) {
//            local.m_matrix[i][j] = m_matrix[r+i][c+j];
//        }
//    }
//    return local;
//}
//
//Scalar Matrix::trace() const {
//    Scalar trace = 0;
//    for (int i = 0; i < m_rows; i++) {
//        trace += m_matrix[i][i];
//    }
//    return trace;
//}
//
//Scalar Matrix::determinant() const {
//    Matrix temp = Matrix(m_rows, m_cols);
//    for (int i = 0; i < m_rows; i++) {
//        for (int j = 0; j < m_cols; j++) {
//            temp.m_matrix[i][j] = m_matrix[i][j];
//        }
//    }
//    return determinant(temp, m_rows);
//}
//
//
//
//Scalar Matrix::determinant(Matrix& other,Index size) const{
//   
//    if(size == 1) {
//        return other.m_matrix[0][0];
//    }
//   
//    else {      //按第一行展开
//       
//        Scalar sum = 0;
//        Matrix middle = Matrix(size-1 , size-1);
//       
//        for (int i = 0; i < size; i++) {
//            submatrix(other, middle, 0, i,size);
//            sum += pow(-1, i) * other.m_matrix[0][i] * determinant(middle,size - 1);
//        }
//        return sum;
//    }
//}
////现在就是要构造出这个submatrix
//void Matrix::submatrix(Matrix A, Matrix& other, int p, int q, int n) const{  //p和q表示去掉的一行一列的索引，n表示A.m_matrix的行列数，other.m_matrix的行列数为n-1
//    int k = 0;
//    int h = 0;
//    for (int i = 0; i < n; i++) {
//        for (int j = 0; j < n; j++) {
//            if (i != p && j != q) {
//                other.m_matrix[k][h] = A.m_matrix[i][j];
//                h++;
//                if (h == n - 1) {
//                    h = 0;
//                    k++;
//                }
//            }
//        }
//    }
//}
//
//int main() {
//    Matrix A = Matrix(3,3);
//    A.m_matrix[0][0] = 1;
//    A.m_matrix[0][1] = 0;
//    A.m_matrix[0][2] = 0;
//    A.m_matrix[1][0] = 0;
//    A.m_matrix[1][1] = 2;
//    A.m_matrix[1][2] = 0;
//    A.m_matrix[2][0] = 0;
//    A.m_matrix[2][1] = 0;
//    A.m_matrix[2][2] = 3;
//   
//
//    cout << A.determinant() << endl;  //deteminant求解有问题
//    //cout << A.trace() << endl;
//
//}

#include <algorithm>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;
// This class is quite simple with only some getters and setters.
// Finish the definitions of these functions first.
class Grade {
public:
	// This constructor initializes the members with the parameters.
	Grade();
	Grade(const std::string& name, int number, double grade);
	~Grade();
	std::string getName() const;
	void setName(const std::string& name);
	int getNumber() const;
	void setNumber(int number);
	double getGrade() const;
	void setGrade(double grade);

private:
	std::string m_name;
	int m_number;
	double m_grade;
};

Grade::Grade(const std::string& name, int number, double grade) :m_name(name), m_number(number), m_grade(grade) {

}
Grade::Grade() : m_number(0), m_grade(0) {//?

}

Grade::~Grade() {

}
string Grade::getName()const {
	return this->m_name;
}

void Grade::setName(const std::string& name) {
	this->m_name = name;
}

int Grade::getNumber()const {
	return this->m_number;
}

void Grade::setNumber(int number) {
	this->m_number = number;
}

double Grade::getGrade()const {
	return this->m_grade;
}

void Grade::setGrade(double grade) {
	this->m_grade = grade;
}

struct NameComparator {
	bool operator()(const Grade& a, const Grade& b) const; //需要重载
};

struct NumberComparator {
	bool operator()(const Grade& a, const Grade& b) const;
};

struct GradeComparator {
	bool operator()(const Grade& a, const Grade& b) const;
};



class Gradesheet {
	friend std::ostream& operator<<(std::ostream& os, const Gradesheet& sheet);

public:
	Gradesheet();
	//Gradesheet(const Grade& grade);
	~Gradesheet();
	std::size_t size() const;
	double average() const;
	bool addGrade(const Grade& grade);
	double findByName(const std::string& name) const;
	double findByNumber(int number) const;
	Grade& operator[](std::size_t i);
	const Grade& operator[](std::size_t i) const;
	void sortByName();
	void sortByNumber();
	void sortByGrade();

private:
	std::vector<Grade> m_grades;
	std::size_t m_records_num;
};

Gradesheet::Gradesheet() :m_grades(0), m_records_num(0) {//这里是创建一个空的vector 0表示size?

}



Gradesheet::~Gradesheet() {

}

std::size_t Gradesheet::size()const {
	return m_records_num;
}

double Gradesheet::average() const {
	double sum = 0;
	for (int i = 0; i < m_records_num; i++) {
		sum += m_grades[i].getGrade();
	}
	double average = sum / m_records_num;
	return average;
}

bool Gradesheet::addGrade(const Grade& grade) {
	int is_in_vector = 0;
	for (int j = 0; j < m_records_num; j++) {
		if (m_grades[j].getName() == grade.getName()) {
			is_in_vector = 1;
			break;
		}
	}
	if (is_in_vector == 1) {
		return false;
	}
	else {
		m_grades.emplace_back(grade);
		m_records_num += 1;
		return true;
	}
}

double Gradesheet::findByName(const std::string& name) const {
	int is_in_vector = 0;
	for (int j = 0; j < m_records_num; j++) {
		if (m_grades[j].getName() == name) {
			is_in_vector = 1;
			return m_grades[j].getGrade();
			break;
		}
	}
	if (is_in_vector == 0) {
		return -1;
	}
}

double Gradesheet::findByNumber(int number) const {
	int is_in_vector = 0;
	for (int j = 0; j < m_records_num; j++) {
		if (m_grades[j].getNumber() == number) {
			is_in_vector = 1;
			return m_grades[j].getGrade();
			break;
		}
	}
	if (is_in_vector == 0) {
		return -1;
	}
}

Grade& Gradesheet::operator[](std::size_t i) {
	return m_grades[i];
}

const Grade& Gradesheet::operator[](std::size_t i)const {
	return m_grades[i];
}

ostream& operator<<(std::ostream& os, const Gradesheet& sheet) {
	cout << "/------------------------------\\" << endl;
	cout << endl;
	cout << "|Name      Number    Grade     |" << endl;
	cout << endl;
	cout << "|------------------------------|" << endl;
	cout << endl;
	for (int i = 0; i < sheet.size(); i++) {  //打一行人名 打一行空行
		cout << "|";
		os.width(10); os << left << sheet[i].getName();
		os.width(10); os << left << sheet[i].getNumber();
		os.width(10); os << fixed;  os << left << setprecision(3) << sheet[i].getGrade();
		cout << "|" << endl;
		cout << endl;
	}
	cout << "\\------------------------------/" << endl;
}

bool NameComparator::operator()(const Grade& a, const Grade& b) const {
	return(int(a.getName()[0]) < int(b.getName()[0]));
}

bool NumberComparator::operator()(const Grade& a, const Grade& b) const {
	return(a.getNumber() < b.getNumber());
}

bool GradeComparator::operator()(const Grade& a, const Grade& b) const {
	return(a.getGrade() > b.getGrade());
}

void Gradesheet::sortByName() {
	sort(m_grades.begin(), m_grades.begin() + m_records_num, NameComparator());
}

void Gradesheet::sortByNumber() {
	sort(m_grades.begin(), m_grades.begin() + m_records_num, NumberComparator());
}

void Gradesheet::sortByGrade() {
	sort(m_grades.begin(), m_grades.begin() + m_records_num, GradeComparator());
}

int main() {
	Gradesheet sheet;
	sheet.addGrade(Grade("Bob", 1, 95));
	sheet.addGrade(Grade("Carl", 2, 100));
	sheet.addGrade(Grade("Alex", 3, 90));
	sheet.sortByGrade();
	std::cout << "size == " << sheet.size() << "\n" << sheet;
	return 0;
}
