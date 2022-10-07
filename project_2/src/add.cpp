//
// Created by UtoKing on 2022/10/7.
//

#include "add.h"
#include "string"
#include "iostream"
#include "numberFunctions.h"
#include <cstring>

using namespace std;

string integerAdd(string s1, string s2);

string add(string s1, string s2) {
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

    string result_str;

    if (decimal2 > decimal1) {
        s1.append(decimal2 - decimal1, '0');
        result_str = integerAdd(s1, s2);
    } else if (decimal1 > decimal2) {
        s2.append(decimal1 - decimal2, '0');
        result_str = integerAdd(s1, s2);
    }

    cout << s1 << " " << s2 << endl;

    result_str = integerAdd(s1, s2);

    result_str.insert(result_str.length() - max(decimal1, decimal2), ".");
    result_str = format(result_str);

    return result_str;
}

string integerAdd(string s1, string s2) {
    int a1[s1.length()];
    int a2[s2.length()];

    int result_length = max(s1.length(), s2.length()) + 1;
    int result_int[result_length];
    memset(result_int, 0, sizeof(*result_int) * result_length);

    for (int i = 0; i < s1.length(); ++i) {
        a1[i] = s1[i] - '0';
    }

    for (int i = 0; i < s2.length(); ++i) {
        a2[i] = s2[i] - '0';
    }

    int remainder = 0;
    for (int i = s1.length() - 1, j = s2.length() - 1, k = result_length - 1; k > 0; k--) {
        int temp = a1[i] + a2[j] + remainder;
        result_int[k] = temp % 10;
        remainder = temp / 10;
        if (i > 0) i--;
        else a1[0] = 0;
        if (j > 0) j--;
        else a2[j] = 0;
    }
    result_int[0] = remainder;

    string result_str;

    for (int i = 0; i < result_length; i++) {
        result_str.append(to_string(result_int[i]));
    }

    return result_str;

}
