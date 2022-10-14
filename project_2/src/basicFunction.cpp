//
// Created by UtoKing on 2022/10/11.
//

#include "basicFunction.h"
#include "cmath"
#include "string"
#include "iostream"

using namespace std;

string str_sqrt(const string &s) {
    double a = stod(s);
    if (a < 0) {
        cout << "SQRT: Can't calculate square root when the input is less than 0.";
        exit(0);
    }
    a = sqrt(a);
    return to_string(a);

}

string str_sine(const string &s) {
    double a = stod(s);
    a = sin(a);
    return to_string(a);
}

string str_cosine(const string &s) {
    double a = stod(s);
    a = cos(a);
    return to_string(a);
}

string str_exponential(const string &s) {
    double a = stod(s);
    a = exp(a);
    return to_string(a);
}

string str_tangent(const string &s) {
    double a = stod(s);
    if (abs(a - M_PI / 2) <= 1e-6) {
        cout << "TAN: Can't calculate tangent when the input is pi/2.";
        exit(0);
    }
    a = tan(a);
    return to_string(a);
}

string str_cotangent(const string &s) {
    double a = stod(s);
    if (abs(a) <= 1e-6) {
        cout << "COT: Can't calculate cotangent when the input is zero.";
        exit(0);
    }
    a = atan(a);
    return to_string(a);
}

string str_pow(const string &s1, const string &s2) {
    double a1 = stod(s1);
    double a2 = stod(s2);
    double a = pow(a1, a2);
    return to_string(a);
}

string str_log(const string& s) {
    double a = stod(s);
    if (a < 0) {
        cout << "LOG: Can't calculate when the input is less zero.";
        exit(0);
    }
    a = log(a);
    return to_string(a);
}
