//
// Created by UtoKing on 2022/10/7.
//

#include "strAdd.h"

using namespace std;

string strAdd(string s1, string s2) {
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

    vector<int> a1, a2;

    for (char i: s1) {
        a1.push_back(i - '0');
    }

    for (char i: s2) {
        a2.push_back(i - '0');
    }

    vector<int> result_vector = integerAdd(a1, a2);

    string result_str = vector2String(result_vector);
    result_str.insert(result_str.length() - max(decimal1, decimal2), ".");
    result_str = format(result_str);

    return result_str;
}

vector<int> integerAdd(vector<int> a1, vector<int> a2) {

    vector<int> result_int;

    int length = max(a1.size(), a2.size());

    int remainder = 0;
    for (int i = a1.size() - 1, j = a2.size() - 1, k = 0; k < length; k++) {
        int temp = a1[i] + a2[j] + remainder;
        result_int.insert(result_int.begin(), temp % 10);
        remainder = temp / 10;
        if (i > 0) i--;
        else a1[0] = 0;
        if (j > 0) j--;
        else a2[0] = 0;
    }
    result_int.insert(result_int.begin(), remainder);

    return result_int;

}
