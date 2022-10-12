#include <iostream>
#include "string"
#include "strMultiply.h"
#include "strAdd.h"
#include "strMinus.h"
#include "strDivision.h"
#include "basicFunction.h"
#include "RPN_convert.h"
#include "calculator.h"
#include "cmath"

using namespace std;

int main() {
    string string1 = "(-6)*(-7)+0*3-cos((-5)/6)*exp(-1)+log(33*sqrt(2))";
    vector<string> rpn = transToRPN(string1);
    print_vector(rpn);
    string result = calculator(rpn);
    cout << result << endl;
    cout << double(-6.0) * (-7) + 0 * 3 - cos(double(-5) / 6) * exp(-1) + log(33 * sqrt(double (2)));
}
