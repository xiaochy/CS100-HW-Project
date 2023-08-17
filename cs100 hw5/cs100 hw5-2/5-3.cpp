#include <iostream>
#include <string>
#include <cmath>


class Expr_node {
public:
    Expr_node() = default;       //构造函数  =default表示存在默认构造函数
    virtual double eval() const = 0;    //返回计算的结果
    virtual std::string to_string() const = 0; //返回一个被加好括号的式子  就是利用string这个类里的函数来实现输出 适用对象加.的像是调用函数 pop_back() push_back()... 
    virtual ~Expr_node() = default;            //析构函数   =default表示存在默认构造函数
    Expr_node(const Expr_node&) = delete;         //以下两个函数不用管它，在子类中也不需要管
    Expr_node& operator=(const Expr_node&) = delete;
};

//double Expr_node::eval()const {
//    ;
//}
//
//std::string Expr_node::to_string()const {
//    ;
//}

/// ////////////第一部分的继承//////////////////////////////////////
class Extra_node : public Expr_node {
protected:
    Expr_node* formula;
    
    virtual double eval() const override;
    virtual std::string to_string() const override;
public:
    virtual ~Extra_node(); //需要重写一下，delete on the pointers
    Extra_node() {}
    Extra_node(Expr_node* form);

};
Extra_node::Extra_node(Expr_node* form):formula(form){}

double Extra_node::eval()const {//因为后面也是要override的，所以这里随便写
    return ((*formula).eval());
}

std::string Extra_node::to_string()const {
    return std::to_string((*formula).eval());
}


Extra_node::~Extra_node() {
    delete formula;
}

///////////////////////////////////////////////////////////
class Sin_node :public Extra_node {
    friend Sin_node* make_sin(Extra_node*);
    virtual double eval() const override;
    virtual std::string to_string() const override;
public:
    Sin_node(Expr_node* form);
    virtual ~Sin_node() = default;
};


Sin_node::Sin_node(Expr_node* form) { formula = form; }   //是不是这些子类不需要构造函数？


double Sin_node::eval()const {
    return sin((*formula).eval());
}

std::string Sin_node::to_string()const {
    if ((*formula).to_string()[0] != '(') {
        return "sin(" + (*formula).to_string() + ")";
    }
    else {
        return "sin" + (*formula).to_string();
    }
}

/// /////////////////////////////////////////////////////////

class Cos_node :public Extra_node {
    friend Cos_node* make_cos(Extra_node*);
    virtual double eval() const override;
    virtual std::string to_string() const override;
public:
    Cos_node(Expr_node* form);
    virtual ~Cos_node() = default;
};


Cos_node::Cos_node(Expr_node* form) { formula = form; }   //是不是这些子类不需要构造函数？


double Cos_node::eval()const {
    return cos((*formula).eval());
}

std::string Cos_node::to_string()const {
    if ((*formula).to_string()[0] != '(') {
        return "cos(" + (*formula).to_string() + ")";
    }
    else {
        return "cos" + (*formula).to_string();
    }
}

////////////////////////////////////////////////

class Tan_node :public Extra_node {
    friend Tan_node* make_tan(Extra_node*);
    virtual double eval() const override;
    virtual std::string to_string() const override;
public:
    Tan_node(Expr_node* form);
    virtual ~Tan_node() = default;
};


Tan_node::Tan_node(Expr_node* form) { formula = form; }   //是不是这些子类不需要构造函数？


double Tan_node::eval()const {
    return tan((*formula).eval());
}

std::string Tan_node::to_string()const {
    if ((*formula).to_string()[0] != '(') {
        return "tan(" + (*formula).to_string() + ")";
    }
    else {
        return "tan" + (*formula).to_string();
    }
}
/////////////////////////////////////////////////////////////

class Log_node :public Extra_node {
    friend Log_node* make_log(Extra_node*);
    virtual double eval() const override;
    virtual std::string to_string() const override;
public:
    Log_node(Expr_node* form);
    virtual ~Log_node() = default;
};


Log_node::Log_node(Expr_node* form) { formula = form; }   //是不是这些子类不需要构造函数？


double Log_node::eval()const {
    return log((*formula).eval());
}

std::string Log_node::to_string()const {
    if ((*formula).to_string()[0] != '(') {
        return "log(" + (*formula).to_string() + ")";
    }
    else {
        return "log" + (*formula).to_string();
    }
}

/////////////////////////////////////////////////////////

class Exp_node :public Extra_node {
    friend Exp_node* make_exp(Extra_node*);
    virtual double eval() const override;
    virtual std::string to_string() const override;
public:
    Exp_node(Expr_node* form);
    virtual ~Exp_node() = default;
};


Exp_node::Exp_node(Expr_node* form) { formula = form; }   //是不是这些子类不需要构造函数？


double Exp_node::eval()const {
    return exp((*formula).eval());
}

std::string Exp_node::to_string()const {
    if ((*formula).to_string()[0] != '(') {
        return "exp(" + (*formula).to_string() + ")";
    }
    else {
        return "exp" + (*formula).to_string();
    }
}

/// /////////////////////////////////////////////////////

class Number_node : public Expr_node {
    friend Number_node* make_number(double);
    double value;
    Number_node(double val);//构造函数
    virtual double eval() const override;    //加不加override无所谓，只是为了增加可读性，表示重写了父类的函数
    virtual std::string to_string() const override;//to convert a double to std::string , we should call the std::to-string function defined in <string>将数字计算完毕后转为字符串
public:
    virtual ~Number_node()=default;
};//这个to_string函数需要被重写，因为不只是要把数字转换为字符串，最终输出结果是要已经加完括号的

Number_node::Number_node(double val):value(val){}  //可以用这种初始化列表的方式来初始化指针吗？

double Number_node::eval()const {
    return value;
}

std::string Number_node::to_string()const {
    if (value >= 0) {
        return std::to_string(value);
    }
    else if (value < 0) {
        return ("(" + std::to_string(value) + ")");
    }
}


class Negation_node : public Expr_node {
    friend Negation_node* make_negation(Expr_node*);
    Expr_node* operand;
    Negation_node(Expr_node* oper);//构造函数
    virtual double eval() const override;    
    virtual std::string to_string() const override;
public:
    virtual ~Negation_node(); //需要重写一下，delete on the pointers
};

Negation_node::Negation_node(Expr_node* oper) :operand(oper) {}


double Negation_node::eval()const {
    return (-(*operand).eval());
}

std::string Negation_node::to_string()const {
   

        //return ("(" + std::to_string(-(*operand).eval()) + ")");
        return ("(-"  + (*operand).to_string() + ")");
    
}

Negation_node::~Negation_node() {
    //std::cout << "Negation" << std::endl;
    delete operand;
    
}




class Binary_node : public Expr_node {
protected:
    Expr_node* lhs;
    Expr_node* rhs;
    Binary_node(Expr_node* lh, Expr_node* rh);
    Binary_node(){}
    virtual double eval() const override; 
    virtual std::string to_string() const override;
public:
    virtual ~Binary_node(); //需要重写一下，delete on the pointers
};

Binary_node::Binary_node(Expr_node* lh, Expr_node* rh)  {lhs = lh; rhs = rh; }


double Binary_node::eval()const {//因为后面也是要override的，所以这里随便写
    return ((*lhs).eval());
}

std::string Binary_node::to_string()const {
    return std::to_string((*lhs).eval());
}

Binary_node::~Binary_node() {
    //std::cout << "Binary" << std::endl;
    delete lhs;
    delete rhs;
}

/// ////////////第二部分的继承//////////////////////////////////////

class Plus_node : public Binary_node {//这一部分需要些析构函数吗？
   // Expr_node* lhs;
    //Expr_node* rhs;
    
    friend Plus_node* plus_negation(Expr_node*,Expr_node*);
    virtual double eval() const override;   
    virtual std::string to_string() const override;
public:
    Plus_node(Expr_node* lh, Expr_node* rh);
    virtual ~Plus_node()=default;
};

Plus_node::Plus_node(Expr_node* lh, Expr_node* rh) { lhs = lh; rhs = rh; }   //是不是这些子类不需要构造函数？


double Plus_node::eval()const {
    return (*lhs).eval() + (*rhs).eval();
}

std::string Plus_node::to_string()const {
    return ("(" + (*lhs).to_string() + " + " + (*rhs).to_string() + ")");
}

//Plus_node::~Plus_node() {
//    //std::cout << "Plus" << std::endl;
//    delete lhs;
//    delete rhs;
//}

class Minus_node : public Binary_node {
    //Expr_node* lhs;
    //Expr_node* rhs;
    friend Minus_node* minus_negation(Expr_node*, Expr_node*);
    virtual double eval() const override;    
    virtual std::string to_string() const override;
public:
    Minus_node(Expr_node* lh, Expr_node* rh);
    virtual ~Minus_node() = default;
};


Minus_node::Minus_node(Expr_node* lh, Expr_node* rh) { lhs = lh; rhs = rh; }


double Minus_node::eval()const {
    return (*lhs).eval() - (*rhs).eval();
}

std::string Minus_node::to_string()const {
    return ("(" + (*lhs).to_string() + " - " + (*rhs).to_string() + ")");
}

//Minus_node::~Minus_node() {
//    //std::cout << "Minus" << std::endl;
//    delete lhs;
//    delete rhs;
//}

class Multiply_node : public Binary_node {
    //Expr_node* lhs;
    //Expr_node* rhs;
    friend Multiply_node* multiply_negation(Expr_node*, Expr_node*);
    virtual double eval() const override;   
    virtual std::string to_string() const override;
public:
    Multiply_node(Expr_node* lh, Expr_node* rh);
    virtual ~Multiply_node() = default;
};

Multiply_node::Multiply_node(Expr_node* lh, Expr_node* rh) { lhs = lh; rhs = rh; }


double Multiply_node::eval()const {
    return (*lhs).eval() * (*rhs).eval();
}

std::string Multiply_node::to_string()const {
    return ("(" + (*lhs).to_string() + " * " + (*rhs).to_string() + ")");
}


//Multiply_node::~Multiply_node() {
//    //std::cout << "Multiply" << std::endl;
//    delete lhs;
//    delete rhs;
//}

class Divide_node : public Binary_node {
    //Expr_node* lhs;
   // Expr_node* rhs;
    friend Divide_node* divide_negation(Expr_node*, Expr_node*);
    virtual double eval() const override;    
    virtual std::string to_string() const override;
public:
    Divide_node(Expr_node* lh, Expr_node* rh);
    virtual ~Divide_node()=default;
};


Divide_node::Divide_node(Expr_node* lh, Expr_node* rh) { lhs = lh; rhs = rh; }


double Divide_node::eval()const {
    if ((*rhs).eval() != 0) {      //除0要不要判断
        return (*lhs).eval() / (*rhs).eval();
    }
}

std::string Divide_node::to_string()const {
    return ("(" + (*lhs).to_string() + " / " + (*rhs).to_string() + ")");
}


//Divide_node::~Divide_node() {
//    //std::cout << "Divide" << std::endl;
//    delete lhs;
//    delete rhs;
//}

/// ///////////////////////以下是inline部分///////////////////////////////////////////////////

inline Number_node* make_number(double value) {  //
    return new Number_node(value);   //return了一个Number_node的对象
}

inline Negation_node* make_negation(Expr_node* operand) {  //
    return new Negation_node(operand);   //return了一个Number_node的对象
}

inline Plus_node* make_plus(Expr_node* lhs, Expr_node*rhs) {  //
    return new Plus_node(lhs,rhs);   //return了一个Number_node的对象
}


inline Minus_node* make_minus(Expr_node* lhs, Expr_node* rhs) {  //
    return new Minus_node(lhs, rhs);   //return了一个Number_node的对象
}


inline Multiply_node* make_multiply(Expr_node* lhs, Expr_node* rhs) {  //
    return new Multiply_node(lhs, rhs);   //return了一个Number_node的对象
}


inline Divide_node* make_divide(Expr_node* lhs, Expr_node* rhs) {  //
    return new Divide_node(lhs, rhs);   //return了一个Number_node的对象
}

inline Sin_node* make_sin(Expr_node* formula) {
    return new Sin_node(formula);
}

inline Cos_node* make_cos(Expr_node* formula) {
    return new Cos_node(formula);
}

inline Tan_node* make_tan(Expr_node* formula) {
    return new Tan_node(formula);
}

inline Log_node* make_log(Expr_node* formula) {
    return new Log_node(formula);
}

inline Exp_node* make_exp(Expr_node* formula) {
    return new Exp_node(formula);
}

int main() {
    /*Expr_node* expr_tree = make_negation(make_plus(make_number(3), make_number(4)));
    std::cout << expr_tree->eval() << std::endl;
    std::cout << expr_tree->to_string() << std::endl;
    delete expr_tree;*/
   /* Expr_node* expr_tree = make_divide( make_negation(make_number(-2)),make_number(3));
    std::cout << expr_tree->eval() << std::endl;
    std::cout << expr_tree->to_string() << std::endl;
    delete expr_tree;*/
    Expr_node* bonus_tree =
        make_sin(make_cos(make_negation(make_number(-2))));
    std::cout << bonus_tree->eval() << std::endl;
    std::cout << bonus_tree->to_string() << std::endl;
    delete bonus_tree;
    return 0;
}