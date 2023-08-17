#include <cstdlib>
#include <iostream>
#include <cmath>
#include <string>
#include<list>
#include <iomanip>

const double PI = 3.14159;

/***********************************************************************
* Declaration/Definition of the base-class Shape *
***********************************************************************/
class Shape {
public:
    // constructors and destructor
    virtual ~Shape()=0;
    Shape() {
        corner = 0;
        area = 0;
        perimeter = 0;
    }
    // Accessors; you should decide which should be virtual or pure virtual.
    virtual double CalculateArea()const;//我这里把后面的const删掉了，不知道行不行
    virtual double CalculatePerimeter()const;
    virtual int NumberCorners()const;


    // member variables;
    double area;
    double perimeter;
    double corner;
};


/***********************************************************************
* Declaration/Definition of the child-classes *
***********************************************************************/
class Rectangle: public Shape {
public:
    Rectangle(double height, double width);
    virtual double CalculateArea() {
        area = height * width;
    }
    virtual double CalculatePerimeter() {
        perimeter = 2 * (height + width);
    }
    virtual int NumberCorners() {
        corner = 4;
    }
    ~Rectangle() {
        std::cout << "A Rectangle has been destroyed." << "\n";
    }
private:
    double height;
    double width;
};// ...
class Square: public Shape {
public:
    Square(double side_length);
    virtual double CalculateArea() {
        area = side_length*side_length;
    }
    virtual double CalculatePerimeter() {
        perimeter =4*side_length;
    }
    virtual int NumberCorners() {
        corner = 4;
    }
    ~Square() {
        std::cout << "A Square has been destroyed." << "\n";
    }
private:
    double side_length;
}; // ...
class Triangle: public Shape {
public:
    Triangle(double side_1,double side_2);
    virtual double CalculateArea() {
        area = (side_1*side_2)/2;
    }
    virtual double CalculatePerimeter() {
        perimeter = side_1+side_2+pow((side_1*side_1+side_2*side_2), 0.5);
    }
    virtual int NumberCorners() {
        corner = 3;
    }
    ~Triangle() {
        std::cout << "A Triangle has been destroyed." << "\n";
    }
private:
    double side_1;
    double side_2;
}; // ...
class Circle:public Shape {
public:
    Circle(double radius);

 
    virtual double CalculateArea() {
        area = PI*radius*radius;
    }
    virtual double CalculatePerimeter() {
        perimeter = 2 * PI*radius;
    }
    virtual int NumberCorners() {
        corner = 0;
    }
    ~Circle() {
        std::cout << "A Circle has been destroyed." << "\n";
    }
private:
    double radius;
}; // ...

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