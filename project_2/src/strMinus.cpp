//
// Created by UtoKing on 2022/10/7.
//

#include "strMinus.h"

string strMinus(string s1, string s2) {

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

    if (decimal2 > decimal1) {
        s1.append(decimal2 - decimal1, '0');
    } else if (decimal1 > decimal2) {
        s2.append(decimal1 - decimal2, '0');
    }

    int sign = 1;

    if (s1.length() < s2.length()) {
        swap(s1, s2);
        sign *= -1;
    } else if (s1.length() == s2.length()) {
        for (int i = 0; i < s1.length(); i++) {
            if (s1[i] < s2[i]) {
                swap(s1, s2);
                sign *= -1;
                break;
            } else if (s1[i] > s2[i]) {
                break;
            }
        }
    }

    vector<int> a1, a2;

    for (char i: s1) {
        a1.push_back(i - '0');
    }

    for (char i: s2) {
        a2.push_back(i - '0');
    }

    vector<int> result_vector = integerMinus(a1, a2);
    if (result_vector.empty()) result_vector.push_back(0);

    string result_str = vector2String(result_vector);
    result_str.insert(result_str.length() - max(decimal1, decimal2), ".");
    result_str = format(result_str);

    if (sign == -1) result_str.insert(0, "-");

    return result_str;
}

vector<int> integerMinus(vector<int> &a1, vector<int> &a2) {
    vector<int> result_vector;
    for (int i = a1.size() - 1, j = a2.size() - 1; i >= 0; --i) {
        if (a1[i] >= a2[j]) result_vector.insert(result_vector.begin(), a1[i] - a2[j]);
        else {
            result_vector.insert(result_vector.begin(), a1[i] - a2[j] + 10);
            a1[i - 1] -= 1;
        }
        if (j > 0) j--;
        else a2[0] = 0;
    }

    result_vector = format(result_vector);

    return result_vector;
}
