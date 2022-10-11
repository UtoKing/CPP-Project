#include <iostream>
#include "string"
#include "strMultiply.h"
#include "strAdd.h"
#include "strMinus.h"
#include "strDivision.h"
#include "basicFunction.h"
#include "RPN_convert.h"

using namespace std;

int main() {
//    vector<string> s = {"1", "+", "2"};
    string string1 = "2+cos(3*4+5)";
//    print_vector(convert2RPN(s));
    print_vector(transToRPN(string1));
}
