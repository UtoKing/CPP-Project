//
// Created by UtoKing on 2022/10/12.
//

#include "calculator.h"
#include "string"
#include "vector"
#include "stack"
#include "numberFunctions.h"
#include "strAdd.h"
#include "strMinus.h"
#include "strMultiply.h"
#include "strDivision.h"
#include "basicFunction.h"

using namespace std;

string calculator(const vector<string>& vs) {
    stack<string> num;
    for (auto & v : vs) {
        if (isNumber(v)) {
            num.push(v);
        } else if (v == "+" || v == "-" || v == "*" || v == "/" || v == "^") {
            string a2 = num.top();
            num.pop();
            string a1 = num.top();
            num.pop();

            if (v == "+") {
                string r = strAdd(a1, a2);
                num.push(r);
            } else if (v == "-") {
                string r = strMinus(a1, a2);
                num.push(r);
            } else if (v == "*") {
                string r = strMultiply(a1, a2);
                num.push(r);
            } else if (v == "/") {
                string r = strDivision(a1, a2);
                num.push(r);
            } else {
                string r = str_pow(a1, a2);
                num.push(r);
            }
        } else {
            string a = num.top();
            num.pop();
            if (v == "sqrt") {
                string r = str_sqrt(a);
                num.push(r);
            } else if (v == "sin") {
                string r = str_sine(a);
                num.push(r);
            } else if (v == "cos") {
                string r = str_cosine(a);
                num.push(r);
            } else if (v == "tan") {
                string r = str_tangent(a);
                num.push(r);
            } else if (v == "cot") {
                string r = str_cotangent(a);
                num.push(r);
            } else if (v == "exp") {
                string r = str_exponential(a);
                num.push(r);
            } else if (v == "log") {
                string r = str_log(a);
                num.push(r);
            }
        }
    }
    return num.top();
}
