#include <string>
#include<iostream>
using namespace std;

// REMOVE THIS CLASS WHEN SUBMITTING!!!
class Point {
    double x{ 0 }, y{ 0 };
    std::string label;

public:
    Point(double x0, double y0, const std::string& l = "")
        : x(x0), y(y0), label(l) {}
    Point() = default;
    double get_x() const {
        return x;
    }
    double get_y() const {
        return y;
    }
    std::string get_label() const {
        return label;
    }
    Point& set_x(double x0) {
        x = x0;
        return *this;
    }
    Point& set_y(double y0) {
        y = y0;
        return *this;
    }
    Point& set_label(const std::string& l) {
        label = l;
        return *this;
    }
};

class Point_counted {
    friend class Point_handle;
    Point p;
    unsigned cnt; 
};


class Point_handle {
private:
    Point_counted* ptr;

public:
    Point_handle();
    ~Point_handle();
    Point_handle(const Point_handle& other);
    Point_handle& operator=(const Point_handle& other);
    Point_handle(const Point& other);
    Point_handle(double a, double b, const std::string & ="");
    unsigned ref_count()const;
    double get_x()const;
    double get_y()const;
    string get_label()const;
    Point_handle& set_x(double x0);
    Point_handle& set_y(double y0);
    Point_handle& set_label(const string& l);

};

Point_handle::Point_handle():ptr(new Point_counted) {  //如何在这个构造函数里create一个Point P
    (*ptr).cnt = 1;
    (*ptr).p = Point();
}

Point_handle::Point_handle(const Point& other):ptr(new Point_counted) {  //这里ptr的初始化不要漏！！！！ 
    (*ptr).p = other;                                                                                               
    (*ptr).cnt = 1;
}

Point_handle::Point_handle(double a, double b, const std::string &c):ptr(new Point_counted) {
    
    (*ptr).p = Point(a, b, c);
    (*ptr).cnt = 1;
}

Point_handle::~Point_handle() {
   
        (*ptr).cnt -= 1;
        if (ptr->cnt == 0) {
            delete ptr;
        }
    
}

Point_handle::Point_handle(const Point_handle& other):ptr(other.ptr) {  //这里可能有些问题
    ptr->cnt = 1;
}

Point_handle& Point_handle::operator=(const Point_handle& other) {
    Point_counted* new_ptr = other.ptr;
    ptr->cnt -= 1;
    other.ptr->cnt += 1;
    if (ptr->cnt == 0) {
        delete ptr;
    }
    ptr = new_ptr;
    return *this;

}

unsigned Point_handle::ref_count()const {
    return ptr->cnt;
}

double Point_handle::get_x()const {
    return (*ptr).p.get_x();
}

double Point_handle::get_y()const {
    return (*ptr).p.get_y();
}

string Point_handle::get_label()const {
    return (*ptr).p.get_label();
}

Point_handle& Point_handle::set_x(double x0) {
    if ((*ptr).cnt == 1) {
        (*ptr).p=(*ptr).p.set_x(x0);
        return *this;
    }
    else {
        Point_counted* new_object = new Point_counted;
        (*new_object).cnt = 1;
        (*new_object).p = (*this).ptr->p;
        (*this).ptr->cnt -= 1;
        (*this).ptr = new_object;
        (*this).ptr->p=(*this).ptr->p.set_x(x0);
        return *this;
    }
}

Point_handle& Point_handle::set_y(double y0) {
    if ((*ptr).cnt == 1) {
        (*ptr).p = (*ptr).p.set_y(y0);
        return *this;
    }
    else {
        Point_counted* new_object = new Point_counted;
        (*new_object).cnt = 1;
        (*new_object).p = (*this).ptr->p;
        (*this).ptr->cnt -= 1;
        (*this).ptr = new_object;
        (*this).ptr->p = (*this).ptr->p.set_y(y0);
        return *this;
     
    }
}

Point_handle& Point_handle::set_label(const string& l) {//这里的返回值应该是Point_handle& 不应该是Point& 我们定义Point_handle这个类的作用就是为了将用户与直接调用Point里面的内容分离开来
    if ((*ptr).cnt == 1) {
        (*ptr).p = (*ptr).p.set_label(l);
        return *this;
    }
    else {
        Point_counted* new_object = new Point_counted;
        (*new_object).cnt = 1;
        (*new_object).p = (*this).ptr->p;
        (*this).ptr->cnt -= 1;
        (*this).ptr = new_object;
        (*this).ptr->p = (*this).ptr->p.set_label(l);
        return *this;
       
    }
}

int main()
{
    Point_handle ph1(5, 6, "A"),ph2 = ph1;
    ph2.set_x(7);
    cout << ph2.get_x()<<", "<<ph2.get_y() <<ph2.get_label() << endl;
   
}