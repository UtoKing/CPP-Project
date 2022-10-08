//
// Created by UtoKing on 2022/10/7.
//

#include "numberFunctions.h"

using namespace std;

bool isNumber(const string &s) {
    regex r(R"(^[+-]?((\d+\.?\d*)|(\.\d+))$)");
    return regex_match(s, r);
}

bool isScientific(const string &s) {
    regex r(R"(^[+-]?(([1-9]\.?)|([1-9]\.\d*))[Ee]([+-]?\d+)$)");
    return regex_match(s, r);
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

string vector2String(vector<int> vec) {
    stringstream ss;
    string str;
    copy(vec.begin(), vec.end(), ostream_iterator<int>(ss, ""));
    str = ss.str();
    return str;
}

void print_array(int a[], int a_length) {
    for (int i = 0; i < a_length; ++i) {
        cout << a[i];
    }
    cout << endl;
}
