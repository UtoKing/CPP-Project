#include <iostream>
#include "string"
#include "RPN_convert.h"
#include "calculator.h"
#include "cmath"
#include "defineVariable.h"
#include "map"

using namespace std;

int main() {
    map<char, string> variable;
    while (true) {
        string input;
        getline(cin, input);
        if (input == "#") break;
        else if (isDefine(input, variable)) {
            cout << "Define variable successfully!" << endl;
            continue;
        } else {
            vector<string> rpn = transToRPN(input, variable);
            if (rpn.empty()) {
                cout << "Invalid Input" << endl;
                continue;
            }
            string result = calculator(rpn);
            cout << result << endl;
        }
    }
}
