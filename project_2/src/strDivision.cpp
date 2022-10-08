//
// Created by UtoKing on 2022/10/8.
//

#include "strDivision.h"
#include "strMultiply.h"
#include "numberFunctions.h"
#include "strMinus.h"

using namespace std;

vector<int> cutArrs(vector<int> &arrs, int begin, int end);

bool compare(vector<int> &a1, vector<int> &a2);

string integerDivision(vector<int> a1, vector<int> a2, int precision);

string strDivision(string s1, string s2, int precision) {
    if (!(isNumber(s1) || isScientific(s1))) {
        return "First input is Not a Number or Not Standard!";
    }

    if (!(isNumber(s2) || isScientific(s2))) {
        return "Second input is Not a Number or Not Standard!";
    }

    if (isScientific(s1)) {
        s1 = scientific2Double(s1);
    }

    if (isScientific(s2)) {
        s2 = scientific2Double(s2);
    }

    int decimal1 = 0;
    int decimal2 = 0;

    int n;
    if ((n = s1.find('.')) != string::npos) {
        s1.erase(n, 1);
        decimal1 = s1.length() - n;
    }
    if ((n = s2.find('.')) != string::npos) {
        s2.erase(n, 1);
        decimal2 = s2.length() - n;
    }

    vector<int> a1;
    vector<int> a2;

    int sign = 1;

    for (char i: s1) {
        if (i == '-') sign *= -1;
        else if (i != '+' && i != '.') {
            a1.push_back(i - '0');
        }
    }

    for (char i: s2) {
        if (i == '-') sign *= -1;
        else if (i != '+' && i != '.') {
            a2.push_back(i - '0');
        }
    }

    cout << integerDivision(a1, a2, precision);

    return " ";
}

string integerDivision(vector<int> a1, vector<int> a2, int precision) {
    vector<int> result;
    int denominator_size = a2.size();
    if (a1.size() < a2.size()) {
        a1.insert(a1.end(), a2.size() - a1.size(), 0);
    }

    vector<int> nominator = cutArrs(a1, 0, denominator_size);
    string denominator = vector2String(a2);

    cout << denominator;

    for (int i = 0; i < precision; ++i) {
        if (compare(nominator, a2)) {
            string s = vector2String(nominator);
            cout << s;
            for (int j = 1; j < 10; ++j) {
                if (strMultiply(s, to_string(j)).compare(denominator) < 0) {
                    result.push_back(j - 1);
                    break;
                }
            }
            string temp = strMinus(s, strMultiply(s, to_string(result[result.size() - 1])));
        }
    }

    return vector2String(result);
}

bool compare(vector<int> &a1, vector<int> &a2) {

    /**
     * @brief compare two integer vectors.
     * @param a1 the first vector
     * @param a2 the second vector
     * @return a bool type
     *
     * This function will compare two integer vectors, and return true if a1 >= a2.
     */

    if (a1.size() > a2.size()) return true;
    else if (a1.size() < a2.size()) return false;

    for (int i = 0; i < a1.size(); ++i) {
        if (a1[i] > a2[i]) return true;
        else if (a1[i] == a2[i]) continue;
        else return false;
    }
    return true;
}

vector<int> cutArrs(vector<int> &arrs, int begin, int end) {
    vector<int> result;
    result.assign(arrs.begin() + begin, arrs.begin() + end);
    return result;
}


