#include <iostream>
#include <string>
#include <cmath>


class Expr_node {
public:
    Expr_node() = default;       //���캯��  =default��ʾ����Ĭ�Ϲ��캯��
    virtual double eval() const = 0;    //���ؼ���Ľ��
    virtual std::string to_string() const = 0; //����һ�����Ӻ����ŵ�ʽ��  ��������string�������ĺ�����ʵ����� ���ö����.�����ǵ��ú��� pop_back() push_back()... 
    virtual ~Expr_node() = default;            //��������   =default��ʾ����Ĭ�Ϲ��캯��
    Expr_node(const Expr_node&) = delete;         //���������������ù�������������Ҳ����Ҫ��
    Expr_node& operator=(const Expr_node&) = delete;
};

//double Expr_node::eval()const {
//    ;
//}
//
//std::string Expr_node::to_string()const {
//    ;
//}

/// ////////////��һ���ֵļ̳�//////////////////////////////////////
class Extra_node : public Expr_node {
protected:
    Expr_node* formula;
    
    virtual double eval() const override;
    virtual std::string to_string() const override;
public:
    virtual ~Extra_node(); //��Ҫ��дһ�£�delete on the pointers
    Extra_node() {}
    Extra_node(Expr_node* form);

};
Extra_node::Extra_node(Expr_node* form):formula(form){}

double Extra_node::eval()const {//��Ϊ����Ҳ��Ҫoverride�ģ������������д
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


Sin_node::Sin_node(Expr_node* form) { formula = form; }   //�ǲ�����Щ���಻��Ҫ���캯����


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


Cos_node::Cos_node(Expr_node* form) { formula = form; }   //�ǲ�����Щ���಻��Ҫ���캯����


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


Tan_node::Tan_node(Expr_node* form) { formula = form; }   //�ǲ�����Щ���಻��Ҫ���캯����


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


Log_node::Log_node(Expr_node* form) { formula = form; }   //�ǲ�����Щ���಻��Ҫ���캯����


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


Exp_node::Exp_node(Expr_node* form) { formula = form; }   //�ǲ�����Щ���಻��Ҫ���캯����


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
    Number_node(double val);//���캯��
    virtual double eval() const override;    //�Ӳ���override����ν��ֻ��Ϊ�����ӿɶ��ԣ���ʾ��д�˸���ĺ���
    virtual std::string to_string() const override;//to convert a double to std::string , we should call the std::to-string function defined in <string>�����ּ�����Ϻ�תΪ�ַ���
public:
    virtual ~Number_node()=default;
};//���to_string������Ҫ����д����Ϊ��ֻ��Ҫ������ת��Ϊ�ַ�����������������Ҫ�Ѿ��������ŵ�

Number_node::Number_node(double val):value(val){}  //���������ֳ�ʼ���б�ķ�ʽ����ʼ��ָ����

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
    Negation_node(Expr_node* oper);//���캯��
    virtual double eval() const override;    
    virtual std::string to_string() const override;
public:
    virtual ~Negation_node(); //��Ҫ��дһ�£�delete on the pointers
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
    virtual ~Binary_node(); //��Ҫ��дһ�£�delete on the pointers
};

Binary_node::Binary_node(Expr_node* lh, Expr_node* rh)  {lhs = lh; rhs = rh; }


double Binary_node::eval()const {//��Ϊ����Ҳ��Ҫoverride�ģ������������д
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

/// ////////////�ڶ����ֵļ̳�//////////////////////////////////////

class Plus_node : public Binary_node {//��һ������ҪЩ����������
   // Expr_node* lhs;
    //Expr_node* rhs;
    
    friend Plus_node* plus_negation(Expr_node*,Expr_node*);
    virtual double eval() const override;   
    virtual std::string to_string() const override;
public:
    Plus_node(Expr_node* lh, Expr_node* rh);
    virtual ~Plus_node()=default;
};

Plus_node::Plus_node(Expr_node* lh, Expr_node* rh) { lhs = lh; rhs = rh; }   //�ǲ�����Щ���಻��Ҫ���캯����


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
    if ((*rhs).eval() != 0) {      //��0Ҫ��Ҫ�ж�
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

/// ///////////////////////������inline����///////////////////////////////////////////////////

inline Number_node* make_number(double value) {  //
    return new Number_node(value);   //return��һ��Number_node�Ķ���
}

inline Negation_node* make_negation(Expr_node* operand) {  //
    return new Negation_node(operand);   //return��һ��Number_node�Ķ���
}

inline Plus_node* make_plus(Expr_node* lhs, Expr_node*rhs) {  //
    return new Plus_node(lhs,rhs);   //return��һ��Number_node�Ķ���
}


inline Minus_node* make_minus(Expr_node* lhs, Expr_node* rhs) {  //
    return new Minus_node(lhs, rhs);   //return��һ��Number_node�Ķ���
}


inline Multiply_node* make_multiply(Expr_node* lhs, Expr_node* rhs) {  //
    return new Multiply_node(lhs, rhs);   //return��һ��Number_node�Ķ���
}


inline Divide_node* make_divide(Expr_node* lhs, Expr_node* rhs) {  //
    return new Divide_node(lhs, rhs);   //return��һ��Number_node�Ķ���
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