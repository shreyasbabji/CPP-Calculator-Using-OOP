#ifndef CALCULATOR_H_
#define CALCULATOR_H_
#include <iostream>
#include<string>
#include<cmath>

using namespace std;
class Calculator
{
public:
    // Constructors
    Calculator();
    // Destructor
    ~Calculator();
    void expression(Calculator& cal);
    double term(Calculator& cal) throw(string,double);
    double factor(Calculator& cal);
    double result(Calculator& cal) throw(string);
    friend istream& operator >>(istream& instr, Calculator& cal);

private:
    double operand_one, operand_two;
    double resVal;
    char symbol;
    string message;
};

#endif
