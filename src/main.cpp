#include <iostream>
#include "calculator.h"
int main() {
    std::cout << "Running..." << std::endl;
    Calculator calc;
    calc.run();
    return 0;
}

/*
Sum s;
float num[] = {2,4,1};
float *numPtr = &num[0];
cout << "Result sum: " << s.operate(numPtr,(int) sizeof(num)/sizeof(float)) <<endl;

Multiplication m;
cout << "Result multiplication: " << m.operate(numPtr,(int) sizeof(num)/sizeof(float)) <<endl;

Division d;
cout << "Result division: " << d.operate(numPtr,(int) sizeof(num)/sizeof(float)) <<endl;

Subtraction u;
cout << "Result subtraction: " << u.operate(numPtr,(int) sizeof(num)/sizeof(float)) <<endl;
 */