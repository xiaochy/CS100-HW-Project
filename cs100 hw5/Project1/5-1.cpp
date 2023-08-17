
// DO NOT MODIFY THE CODE BELOW
#include <cstddef>
#include<iostream>;
using namespace std;
class Array {
public:
    Array();
    explicit Array(std::size_t n);
    explicit Array(int* begin, int* end);
    Array(const Array& other);
    Array& operator=(const Array& other);
    ~Array();
    int& at(std::size_t n);
    const int& at(std::size_t n) const;
    std::size_t size() const;
    bool empty() const;
    void clear();
    Array slice(std::size_t l, std::size_t r, std::size_t s = 1) const;
private:
    std::size_t m_size;
    int* m_data;
};

// YOUR CODE STARTS HERE

Array::Array() {
    m_data = NULL;
    m_size = 0;
}

Array::Array(std::size_t n) {
    if (n > 0) {
        m_size = n;
        m_data = new int[n];
        int i;
        for (i = 0; i < n; i++) {
            m_data[i] = i;
        }
    }
    else {
        m_data = NULL;
        m_size = 0;
    }
}

Array::Array(int* begin, int* end) {//begin指的是指向数组第一个元素的指针
    int j;
    if ((end - begin) > 0) {
        m_size = end - begin;
        m_data = new int[m_size];
        for (j = 0; j < m_size; j++) {
            m_data[j] = *(begin + j);
        }
    }
    else {
        m_data = NULL;
        m_size = 0;
    }
}

Array::Array(const Array& other) {  //这里的m_data只被create了，没有被initialize
    int k;
    m_size = other.m_size;
    m_data = new int[m_size];
    for (k = 0; k < m_size; k++) {   //这里会不会涉及到两个数组长度不相同的问题？
        m_data[k] = other.m_data[k];
    }
}

Array& Array::operator=(const Array& other) {//这里的m_data已经被initialize了   如果数组元素个数不等，是否不能直接赋值？
    int k;

    if (this->m_size != other.m_size) {
        delete[] m_data;
        m_data = NULL;
        m_data = new int[other.m_size];
        m_size = other.m_size;
        for (k = 0; k < m_size; k++) {   //这里会不会涉及到两个数组长度不相同的问题？
            m_data[k] = other.m_data[k];
        }
    }
    else {
        for (k = 0; k < m_size; k++) {   //这里会不会涉及到两个数组长度不相同的问题？
            m_data[k] = other.m_data[k];
        }
    }
    return *this;
}

Array::~Array() {
    if (m_data != NULL) {
        delete[]m_data;
        m_data = NULL;
    }


}

int& Array::at(std::size_t n) {
    if (n >= 0 && m_data != NULL) {
        return m_data[n];
    }

}

const int& Array::at(std::size_t n) const {
    if (n >= 0 && m_data != NULL) {
        return m_data[n];
    }

}

std::size_t Array::size() const {
    return m_size;
}

bool Array::empty() const {
    if (m_data == NULL) {
        return true;
    }
    else {
        return false;
    }
}

void Array::clear() {
    if (m_data != NULL) {
        delete[] m_data;
        m_data = NULL;
        m_size = 0;
    }
}

Array Array::slice(std::size_t l, std::size_t r, std::size_t s) const {
    int k;
    Array local;
    if (l < r) {
        int count = 1;

        while (1) {
            if ((l + s * count) < r) {
                count += 1;
            }
            else {
                break;
            }
        }
        int* a = new int[count];
        for (k = 0; k < count; k++) {
            a[k] = m_data[l + k * s];
        }


        local.m_data = new int[count];
        for (k = 0; k < count; k++) {
            local.m_data[k] = a[k];
            cout << local.m_data[k] << endl;
        }

        local.m_size = count;
        delete[] a;
        return local;
    }
    else if (l >= r) {
        local.m_data = NULL;
        local.m_size = 0;
        return local;
    }


}
// YOUR CODE ENDS HERE

int main() {
    // You can test your implementation here, but we will replace the main function on OJ.
    Array p(5);
    
 
    
    Array X;
   
    return 0;
}



if (other.m_cols == m_rows && other.m_rows != m_cols) {
    Matrix local = Matrix(other.m_rows, m_cols);
    for (int i = 0; i < other.m_rows; i++) {
        for (int j = 0; j < m_cols; j++) {
            for (int k = 0; k < m_rows; k++) {
                local.m_matrix[i][j] += other.m_matrix[i][k] * m_matrix[k][j];
            }
        }
    }
    return local;
}
else if (other.m_rows == m_cols && other.m_cols != m_rows) {
    Matrix local = Matrix(m_rows, other.m_cols);
    for (int i = 0; i < m_rows; i++) {
        for (int j = 0; j < other.m_cols; j++) {
            for (int k = 0; k < m_cols; k++) {
                local.m_matrix[i][j] += m_matrix[i][k] * other.m_matrix[k][j];
            }
        }
    }
    return local;
}
else if (other.m_rows == m_cols && other.m_cols == m_rows) {
    Matrix local = Matrix(m_rows, m_rows);
    for (int i = 0; i < m_rows; i++) {
        for (int j = 0; j < m_rows; j++) {
            for (int k = 0; k < m_cols; k++) {
                local.m_matrix[i][j] += m_matrix[i][k] * other.m_matrix[k][j];
            }
        }
    }
    return local;
}