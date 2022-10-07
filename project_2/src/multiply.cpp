//
// Created by UtoKing on 2022/10/7.
//

#include "multiply.h"
#include "string"
#include "regex"
#include "iostream"
#include "numberFunctions.h"

using namespace std;

string multiply(const int *a1, const int *a2, long long a1_length, long long a2_length);

string strMultiply(string s1, string s2) {

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

    long long decimal = 0;
    int a1[s1.length()];
    int a2[s2.length()];

    int sign = 1;

    for (long long i = s1.length() - 1, j = s1.length() - 1; i >= 0; i--) {
        if (s1[i] != '.' && s1[i] != '-' && s1[i] != '+') {
            a1[j] = s1[i] - '0';
            j--;
        } else if (s1[i] == '-') {
            sign *= -1;
        } else if (s1[i] == '+') {
            continue;
        } else
            decimal += s1.length() - i - 1;
    }

    for (long long i = s2.length() - 1, j = s2.length() - 1; i >= 0; i--) {
        if (s2[i] != '.' && s2[i] != '-' && s2[i] != '+') {
            a2[j] = s2[i] - '0';
            j--;
        } else if (s2[i] == '-') {
            sign *= -1;
        } else if (s2[i] == '+') {
            continue;
        } else
            decimal += s2.length() - i - 1;
    }

    string result_str = multiply(a1, a2, s1.length(), s2.length());

    if (decimal > 0)
        result_str.insert(result_str.length() - decimal, ".");

    result_str = format(result_str);

    if (sign == -1) result_str.insert(0, "-");

    return result_str;

}

string multiply(const int *a1, const int *a2, long long a1_length, long long a2_length) {
    int *result_int = new int[a1_length + a2_length];
    memset(result_int, 0, sizeof(*result_int) * (a1_length + a2_length));

    for (long long i = a1_length - 1; i >= 0; i--) {
        int remainder = 0;
        int temp[a2_length + 1];
        memset(temp, 0, sizeof(*result_int) * (1 + a2_length));

        for (long long j = a2_length - 1, k = a2_length; j >= 0; j--) {
            int r = a1[i] * a2[j] + remainder;
            temp[k] = r % 10;
            remainder = r / 10;
            k--;
        }
        temp[0] = remainder;

        remainder = 0;
        for (long long j = a2_length, k = i + a2_length; j >= 0; j--) {
            int r = result_int[k] + temp[j] + remainder;
            result_int[k] = r % 10;
            remainder = r / 10;
            k--;
        }
    }

    string result_str;

    for (long long i = 0; i < a1_length + a2_length; i++) {
        result_str.append(to_string(result_int[i]));
    }

    return result_str;
}
