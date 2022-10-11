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

void print_vector(const vector<string> &a) {
    for (const auto &i: a) cout << i << " ";
    cout << endl;
}

void print_vector(const vector<int> &a) {
    for (const auto &i: a) cout << i << " ";
    cout << endl;
}

vector<int> cutArrs(vector<int> arrs, int begin, int end) {
    vector<int> result;
    result.assign(arrs.begin() + begin, arrs.begin() + end);
    return result;
}

bool compare(vector<int> a1, vector<int> a2) {

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

vector<int> format(vector<int> vec) {
    for (int i = 0; i < vec.size();) {
        if (vec[i] == 0) vec.erase(vec.begin());
        else break;
    }
    return vec;
}
