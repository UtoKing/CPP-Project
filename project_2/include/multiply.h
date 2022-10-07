//
// Created by UtoKing on 2022/10/7.
//

#ifndef PROJECT_2_MULTIPLY_H
#define PROJECT_2_MULTIPLY_H

#endif //PROJECT_2_MULTIPLY_H

#include "string"

using namespace std;

bool isNumber(const string &s);

bool isScientific(const string &s);

string multiply(const int *a1, const int *a2, long long a1_length, long long a2_length);

string strMultiply(string s1, string s2);

string scientific2Double(const string &s);

string format(string s);
