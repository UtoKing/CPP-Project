//
// Created by UtoKing on 2022/10/7.
//

#include "../include/multiply.h"
#include "string"
#include "regex"
#include "iostream"

using namespace std;


string strMultiply(string s1, string s2) {

    if (!(isNumber(s1) || isScientific(s1))) {
        cout << "First input is Not a Number or Not Standard!" << endl;
        return 0;
    }

    if (!(isNumber(s2) || isScientific(s2))) {
        cout << "Second input is Not a Number or Not Standard!" << endl;
        return 0;
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

    if (sign == -1)
        result_str.insert(0, "-");

    return result_str;

}

bool isNumber(const string &s) {
    regex r(R"(^[+-]?((\d+\.?\d*)|(\.\d+))$)");
    return regex_match(s, r);
}

bool isScientific(const string &s) {
    regex r(R"(^[+-]?(([1-9]\.?)|([1-9]\.\d*))[Ee]([+-]?\d+)$)");
    return regex_match(s, r);
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

string scientific2Double(const string &s) {
    smatch results;
    regex r(R"(^([+-]?)(([1-9]\.?)|([1-9]\.\d*))[Ee]([+-]?\d+)$)");
    string part1;
    long long part2 = 0;

    if (regex_match(s, results, r)) {
        part1 = results[2];
        part2 = stol(results[5]);
    }

    if (part1.find('.') < part1.length()) {
        part1.erase(1, 1);
    }

    if (part2 < 0) {
        part1.insert(0, -part2, '0');
        part1.insert(1, ".");
    } else {
        if (part2 >= part1.length()) {
            part1.append(part2 - part1.length() + 1, '0');
        } else {
            part1.insert(part2 + 1, ".");
        }
    }

    if (results[1] == "-")
        part1.insert(0, "-");

    return part1;
}

string format(string s) {
    long long count = 0;
    for (char i: s) {
        if (i == '0')
            count += 1;
        else
            break;
    }
    if (count == s.length()) return "0";

    long long start_0 = 0;
    for (long long i = 0; i < s.length(); i++) {
        if (s[i] == '0' && s[i + 1] != '.') {
            start_0 += 1;
        } else {
            break;
        }
    }
    s.erase(0, start_0);

    if (s.find('.') > s.length())
        return s;
    else {
        long long end_0 = 0;
        for (int64_t i = s.length() - 1; i >= 0; i--) {
            if (s[i] == '0')
                end_0 += 1;
            else
                break;
        }

        s.erase(s.length() - end_0, end_0);

        if (s[s.length() - 1] == '.') s.erase(s.length() - 1, 1);

        return s;
    }
}
