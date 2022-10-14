//
// Created by UtoKing on 2022/10/13.
//

#include "defineVariable.h"
#include "string"
#include "map"
#include "regex"
#include "RPN_convert.h"
#include "calculator.h"

using namespace std;

bool isDefine(const string &s, map<char, string> &m) {
    regex regex1("^([a-zA-Z])=(.+)");
    smatch result;
    bool ret = regex_match(s, result, regex1);
    if (ret) {
        string s1 = result[1];
        string s2 = result[2];
        vector<string> rpn = transToRPN(s2, m);
        s2 = calculator(rpn);
        map<char, string>::iterator n;
        if ((n = m.find(s1[0])) != m.end()) {
            n->second = s2;
        } else {
            m[s1[0]] = s2;
        }
    }
    return ret;
}