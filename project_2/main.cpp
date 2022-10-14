#include <iostream>
#include "string"
#include "RPN_convert.h"
#include "calculator.h"
#include "cmath"
#include "defineVariable.h"
#include "map"

using namespace std;

int main(int argc, char *argv[]) {
    int precision = 20;
    if (argc == 2)
        stoi(argv[1]) <= 0 ? precision = 20 : precision = stoi(argv[1]);

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
            string result = calculator(rpn, precision);
            if (result.empty()) continue;
            cout << result << endl;
        }
    }
}
