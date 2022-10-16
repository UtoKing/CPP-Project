//
// Created by UtoKing on 2022/10/7.
//

#ifndef PROJECT_2_ISNUMBER_H
#define PROJECT_2_ISNUMBER_H

#endif //PROJECT_2_ISNUMBER_H

#include "string"
#include "regex"
#include "iostream"

using namespace std;

bool isNumber(const string &s);

bool isScientific(const string &s);

string scientific2Double(const string &s);

string format(string s);

string vector2String(vector<int> vec);

void print_array(int a[], int a_length);

void print_vector(const vector<string>& a);

void print_vector(const vector<int>& a);

vector<int> cutArrs(vector<int> arrs, int begin, int end);

bool compare(vector<int> a1, vector<int> a2);

vector<int> format(vector<int> vec);
