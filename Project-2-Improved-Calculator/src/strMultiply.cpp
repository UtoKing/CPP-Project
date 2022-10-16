//
// Created by UtoKing on 2022/10/7.
//

#include "strMultiply.h"

using namespace std;

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

    decimal = decimal1 + decimal2;

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

    vector<int> result_vector = integerMultiply(a1, a2);
    if (result_vector.empty()) result_vector.push_back(0);

    string result_str = vector2String(result_vector);
    if (decimal > 0)
        result_str.insert(result_str.length() - decimal, ".");
    result_str = format(result_str);

    if (sign == -1) result_str.insert(0, "-");

    return result_str;

}

vector<int> integerMultiply(vector<int> &a1, vector<int> &a2) {
    int a1_length = a1.size();
    int a2_length = a2.size();
    int *result_int = new int[a1_length + a2_length];
    memset(result_int, 0, sizeof(*result_int) * (a1_length + a2_length));

    for (long long i = a1_length - 1; i >= 0; i--) {
        int remainder = 0;
        int temp[a2_length + 1];
        memset(temp, 0, sizeof(*temp) * (1 + a2_length));

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

    vector<int> result_vector(result_int, result_int + a1_length + a2_length);

    result_vector = format(result_vector);

    return result_vector;
}
