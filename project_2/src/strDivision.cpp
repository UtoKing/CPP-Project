//
// Created by UtoKing on 2022/10/8.
//

#include "strDivision.h"
#include "strMultiply.h"
#include "numberFunctions.h"
#include "strMinus.h"
#include "cmath"

using namespace std;

vector<int> integerDivision(vector<int> &a1, vector<int> &a2, int precision);

string strDivision(string s1, string s2, int precision) {
    /**
     * @brief return the result of s1 / s2.
     * @param s1 the dividend or the numerator.
     * @param s2 the divisor of the denominator.
     * @param precision the precision you want, default is 20.
     * @return the result of s1 / s2.
     *
     * Perform the division operation and return a string with precision you want.
     */

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
        decimal1 = s1.length() - n - 1;
    }
    if ((n = s2.find('.')) != string::npos) {
        decimal2 = s2.length() - n - 1;
    }

    string multiplier = "1";
    if (decimal2 > decimal1) multiplier.append(decimal2, '0');
    else multiplier.append(decimal1, '0');

    s1 = strMultiply(s1, multiplier);
    s2 = strMultiply(s2, multiplier);

    vector<int> a1;
    vector<int> a2;

    int sign = 1;

    for (char i: s1) {
        if (i == '-') sign *= -1;
        else if (i != '+') {
            a1.push_back(i - '0');
        }
    }

    for (char i: s2) {
        if (i == '-') sign *= -1;
        else if (i != '+') {
            a2.push_back(i - '0');
        }
    }

    string result_str = vector2String(integerDivision(a1, a2, precision));

    if (result_str[0] == '0') result_str.insert(1, ".");
    result_str = format(result_str);
    if (sign == -1) result_str.insert(0, "-");

    return result_str;
}

vector<int> integerDivision(vector<int> &a1, vector<int> &a2, int precision) {
    vector<int> result;
    vector<int> divisor;
    int index = 0;
    while (!compare(divisor, a2)) {
        if (index < a1.size()) {
            divisor.push_back(a1[index]);
        } else {
            divisor.push_back(0);
            result.push_back(0);
        }
        index++;
    }

    for (int i = 0; i < precision; ++i) {
        if (compare(divisor, a2)) {
            for (int j = 2; j <= 10; ++j) {
                vector<int> t1 = {j};
                vector<int> t2 = integerMultiply(a2, t1);
                if (!compare(divisor, t2)) {
                    result.push_back(j - 1);
                    t1 = {j - 1};
                    t2 = integerMultiply(a2, t1);
                    divisor = integerMinus(divisor, t2);
                    break;
                }
            }
            if (divisor.empty() && index >= a1.size()) break;
            if (index < a1.size()) divisor.push_back(a1[index]);
            else divisor.push_back(0);
            index++;
        } else {
            result.push_back(0);
            if (index < a1.size()) divisor.push_back(a1[index]);
            else divisor.push_back(0);
            index++;
        }
    }

    return result;
}


