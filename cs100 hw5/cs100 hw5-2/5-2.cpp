#include <cstdlib>
#include <iostream>
#include <cmath>
#include <string>
#include <list>
#include <iomanip>

const double PI = 3.14159;

/***********************************************************************
* Declaration/Definition of the base-class Shape *
***********************************************************************/
class Shape {
public:
    // constructors and destructor
    Shape():area(0),perimeter(0),corner(0){}
    virtual ~Shape(){}
    // Accessors; you should decide which should be virtual or pure virtual.
    virtual double CalculateArea() const=0;
    virtual double CalculatePerimeter() const;
    virtual int NumberCorners() const;

private:
    // member variables;
    double area;
    double perimeter;
    int corner;
};
//这里看看需不需要写上面抽象类里面函数的定义？还是说下面用了虚函数改写了子类里的函数以后就不需要写上面的了？
double Shape::CalculateArea()const {
    return 0;
}
double Shape::CalculatePerimeter()const {
    return 0;
}
int Shape::NumberCorners()const {
    return 0;
}


/***********************************************************************
* Declaration/Definition of the child-classes *
***********************************************************************/
class Rectangle : public Shape //长方形
{
private:
    double height;
    double width;
public:
    virtual double CalculateArea() const;
    virtual double CalculatePerimeter() const ;
    virtual int NumberCorners() const ;
    Rectangle(double size1, double size2) { height = size1; width = size2; }
    virtual~Rectangle() { std::cout << "A Rectangle has been destroyed." << std::endl; }

};// ...
class Square : public Shape { //正方形
private:
    double side_length;
public:
    virtual double CalculateArea() const;
    virtual double CalculatePerimeter() const;
    virtual int NumberCorners() const;
    Square(double size1) { side_length = size1; }
    virtual~Square() { std::cout << "A Square has been destroyed." << std::endl; }

};// ...
class Triangle : public Shape {//直角三角形
private:
    double size_1;
    double size_2;
public:
    virtual double CalculateArea() const;
    virtual double CalculatePerimeter() const;
    virtual int NumberCorners() const;
    Triangle(double size1, double size2) { size_1 = size1; size_2 = size2; }
    virtual~Triangle() { std::cout << "A Triangle has been destroyed." << std::endl; }

}; // ...
class Circle : public Shape {//圆
private:
    double radius;
public:
    virtual double CalculateArea() const;
    virtual double CalculatePerimeter() const;
    virtual int NumberCorners() const;
    Circle(double size1) { radius = size1; }
    virtual~Circle() { std::cout << "A Circle has been destroyed." << std::endl; }

}; // ...

double Rectangle::CalculateArea()const {
    return height * width;
}
double Rectangle::CalculatePerimeter()const {
    return 2 * (height + width);
}
int Rectangle::NumberCorners()const {
    return 4;
}

double Square::CalculateArea()const {
    return side_length*side_length;
}
double Square::CalculatePerimeter()const {
    return 4*side_length;
}
int Square::NumberCorners()const {
    return 4;
}

double Triangle::CalculateArea()const {
    return (size_1*size_2)/2;
}
double Triangle::CalculatePerimeter()const {
    return (size_1+size_2+pow(size_1*size_1+size_2*size_2,0.5));
}
int Triangle::NumberCorners()const {
    return 3;
}

double Circle::CalculateArea()const {
    return PI*radius*radius;
}
double Circle::CalculatePerimeter()const {
    return 2*PI*radius;
}
int Circle::NumberCorners()const {
    return 0;
}

/************************************************************************
* Main Function which is creating/reporting database (do not change!) *
************************************************************************/
int main() {
    //initialize an empty list of shapes
    std::list<Shape*> shapeDatabase;
    //interact with the user: ask the user to enter shapes one by one
    while (1) {
        //print instructions as to how to enter a shape
        std::cout << "Enter a type (Circle, Triangle, Square, or Rectangle) ";
        std::cout << "and one or two size parameters, ";
        std::cout << "separated with blank spaces:\n";
        double size1;
        double size2;
        //check which shape has been requested and store in the database
        std::string shapeType;
        std::cin >> shapeType;
        if (shapeType == std::string("Circle")) {
            std::cin >> size1;
            shapeDatabase.push_back(new Circle(size1));
        }
        else if (shapeType == std::string("Triangle")) {
            std::cin >> size1 >> size2;
            shapeDatabase.push_back(new Triangle(size1, size2));
        }
        else if (shapeType == std::string("Square")) {
            std::cin >> size1;
            shapeDatabase.push_back(new Square(size1));
        }
        else if (shapeType == std::string("Rectangle")) {
            std::cin >> size1 >> size2;
            shapeDatabase.push_back(new Rectangle(size1, size2));
        }
        else {
            std::cout << "Unrecognized shape!!\n";
        }
        //check if the user wants to add more shapes
        std::cout << "Do you want to add more shapes? (Enter Y or N)\n";
        std::string answer;
        std::cin >> answer;
        if (answer != std::string("Y"))
            break;
    }
    //iterate through the list and output the area, perimeter,
    //and number of corners of each entered shape
    std::list<Shape*>::iterator it = shapeDatabase.begin();
    int shapeCounter = 0;
    while (it != shapeDatabase.end()) {
        std::cout << "Properties of shape " << shapeCounter++ << ":\n";
        std::cout << "Area: " << std::setprecision(5) << (*it)->CalculateArea() << "\n";
        std::cout << "Perimeter: " << std::setprecision(5) << (*it)->CalculatePerimeter() << "\n";
        std::cout << "Corners: " << (*it)->NumberCorners() << "\n";
        std::cout << std::endl;
        it++;
    }

    it = shapeDatabase.begin();
    while (it != shapeDatabase.end()) {
        delete (*it);
        it = shapeDatabase.erase(it);
    }

    return 0;
}