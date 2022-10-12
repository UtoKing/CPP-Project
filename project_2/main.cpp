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
    string string1 = "7+cos(-6)";
    vector<string> rpn = transToRPN(string1);
    string result = calculator(rpn);
    cout << result << endl;
//    cout << 5 + 6 * 7 + exp(pow(2, 2)) * (cos(2 + 3) + log(7));
}
