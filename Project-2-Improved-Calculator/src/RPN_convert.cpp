//
// Created by UtoKing on 2022/10/11.
//

#include <vector>
#include <stack>
#include "RPN_convert.h"
#include "string"
#include "numberFunctions.h"

using namespace std;

vector<string> transToRPN(string s, map<char, string> &variable) {
    vector<string> ans;
    stack<pair<string, int>> op_stack;
    stack<char> brackets;
    map<char, string>::iterator iter;

    int n = s.length();
    for (int i = 0; i < n; i++) {
        if (s[i] >= '0' && s[i] <= '9') {
            string temp;
            while ((s[i] >= '0' && s[i] <= '9') || s[i] == 'e' || s[i] == 'E' || s[i] == '.') {
                temp.push_back(s[i]);
                i++;
            }
            if (isNumber(temp) || isScientific(temp))
                ans.push_back(temp);
            else {
                cout << "Input is not valid!";
                vector<string> empty;
                return empty;
            }
            i--;

        } else if ((iter = variable.find(s[i])) != variable.end()) {
            ans.push_back(iter->second);
        } else if (s[i] == '+' || s[i] == '-') {
            int current_priority = brackets.size() * 10 + 1;
            string temp(1, s[i]);
            pair<string, int> p({temp, current_priority});
            if (i == 0 || s[i - 1] == '(') ans.emplace_back("0");
            if (op_stack.empty()) {
                op_stack.push(p);
            } else {
                pair<string, int> last_node = op_stack.top();
                if (current_priority > last_node.second) {
                    op_stack.push(p);
                } else {
                    while (!op_stack.empty() && current_priority <= op_stack.top().second) {
                        ans.push_back(op_stack.top().first);
                        op_stack.pop();
                    }
                    op_stack.push(p);
                }
            }
        } else if (s[i] == '*' || s[i] == '/') {
            int current_priority = brackets.size() * 10 + 2;
            string temp(1, s[i]);
            pair<string, int> p({temp, current_priority});
            if (op_stack.empty()) {
                op_stack.push(p);
            } else {
                pair<string, int> last_node = op_stack.top();
                if (current_priority > last_node.second) {
                    op_stack.push(p);
                } else {
                    while (!op_stack.empty() && current_priority <= op_stack.top().second) {
                        ans.push_back(op_stack.top().first);
                        op_stack.pop();
                    }
                    op_stack.push(p);
                }
            }
        } else if (s.substr(i, 3) == "sin" || s.substr(i, 3) == "cos" || s.substr(i, 3) == "cot" ||
                   s.substr(i, 3) == "exp" || s.substr(i, 3) == "log" || s.substr(i, 3) == "tan") {
            int current_priority = brackets.size() * 10 + 4;
            string temp = s.substr(i, 3);
            pair<string, int> p({temp, current_priority});
            i += 2;
            if (op_stack.empty()) {
                op_stack.push(p);
            } else {
                pair<string, int> last_node = op_stack.top();
                if (current_priority > last_node.second) {
                    op_stack.push(p);
                } else {
                    while (!op_stack.empty() && current_priority <= op_stack.top().second) {
                        ans.push_back(op_stack.top().first);
                        op_stack.pop();
                    }
                    op_stack.push(p);
                }
            }
        } else if (s.substr(i, 4) == "sqrt") {
            int current_priority = brackets.size() * 10 + 4;
            string temp = s.substr(i, 4);
            pair<string, int> p({temp, current_priority});
            i += 3;
            if (op_stack.empty()) {
                op_stack.push(p);
            } else {
                pair<string, int> last_node = op_stack.top();
                if (current_priority > last_node.second) {
                    op_stack.push(p);
                } else {
                    while (!op_stack.empty() && current_priority <= op_stack.top().second) {
                        ans.push_back(op_stack.top().first);
                        op_stack.pop();
                    }
                    op_stack.push(p);
                }
            }
        } else if (s[i] == '^') {
            int current_priority = brackets.size() * 10 + 3;
            string temp(1, s[i]);
            pair<string, int> p({temp, current_priority});
            if (op_stack.empty()) {
                op_stack.push(p);
            } else {
                pair<string, int> last_node = op_stack.top();
                if (current_priority > last_node.second) {
                    op_stack.push(p);
                } else {
                    while (!op_stack.empty() && current_priority <= op_stack.top().second) {
                        ans.push_back(op_stack.top().first);
                        op_stack.pop();
                    }
                    op_stack.push(p);
                }
            }
        } else if (s[i] == '(') {
            brackets.push(s[i]);
        } else if (s[i] == ')') {
            brackets.pop();
        } else {
            vector<string> empty;
            return empty;
        }
    }

    while (!op_stack.empty()) {
        ans.push_back(op_stack.top().first);
        op_stack.pop();
    }

    return ans;
}

