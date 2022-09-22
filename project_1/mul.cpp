#include <iostream>
#include <string>
#include <regex>
#include <string.h>

using namespace std;

bool isNumber(string s);
bool isScientific(string s);
int *multiply(int *a1, int *a2, int a1_length, int a2_length);
string del(int *a, int length);
string scientific2Int(string s);
void print_int_array(int *a, int length);

int main(int argc, char *argv[]) {
    if (argc < 3) {
        cout << "Input is not enough" << endl;
        return 0;
    } else if (argc > 3) {
        cout << "Too many inputs!" << endl;
        return 0;
    }

    string s1 = argv[1];
    string s2 = argv[2];

    if (!(isNumber(s1) || isScientific(s1))) {
        cout << "First input is Not a Number or Not Standard!" << endl;
        return 0;
    }

    if (!(isNumber(s2) || isScientific(s2))) {
        cout << "Second input is Not a Number or Not Standard!" << endl;
        return 0;
    }

    if (isScientific(s1)) {
        s1 = scientific2Int(s1);
    }

    if (isScientific(s2)) {
        s2 = scientific2Int(s2);
    }

    int decimal = 0;
    int a1[s1.length()] = {0};
    int a2[s2.length()] = {0};

    int sign = 1;

    for (int i = s1.length() - 1, j = s1.length() - 1; i >= 0; i--) {
        if (s1[i] != '.' && s1[i] != '-') {
            a1[j] = s1[i] - '0';
            j--;
        } else if (s1[i] == '-') {
            sign *= -1;
        } else
            decimal += s1.length() - i - 1;
    }

    for (int i = s2.length() - 1, j = s2.length() - 1; i >= 0; i--) {
        if (s2[i] != '.' && s2[i] != '-') {
            a2[j] = s2[i] - '0';
            j--;
        } else if (s2[i] == '-') {
            sign *= -1;
        } else
            decimal += s2.length() - i - 1;
    }

    int *result = multiply(a1, a2, s1.length(), s2.length());
    string result_str = del(result, s1.length() + s2.length());
    if (decimal > 0)
        result_str.insert(result_str.length() - decimal, ".");

    if (sign == -1)
        result_str.insert(0, "-");

    cout << result_str << endl;

    return 0;
}

bool isNumber(string s) {
    regex r("^[+-]?((\\d+\\.?\\d*)|(\\.\\d+))$");
    return regex_match(s, r);
}

bool isScientific(string s) {
    regex r("^[+-]?(([1-9]\\.?)|([1-9]\\.\\d*))[Ee]([+-]?\\d+)$");
    return regex_match(s, r);
}

int *multiply(int *a1, int *a2, int a1_length, int a2_length) {
    int *result_int = new int[a1_length + a2_length];
    memset(result_int, 0, sizeof(*result_int) * (a1_length + a2_length));

    for (int i = a1_length - 1; i >= 0; i--) {
        int remainder = 0;
        int temp[a2_length + 1] = {0};

        for (int j = a2_length - 1, k = a2_length; j >= 0; j--) {
            int r = a1[i] * a2[j] + remainder;
            temp[k] = r % 10;
            remainder = r / 10;
            k--;
        }
        temp[0] = remainder;

        remainder = 0;
        for (int j = a2_length, k = i + a2_length; j >= 0; j--) {
            int r = result_int[k] + temp[j] + remainder;
            result_int[k] = r % 10;
            remainder = r / 10;
            k--;
        }
    }

    return result_int;
}

string del(int *a, int length) {
    string s;
    int zero_num = 0;
    for (int i = 0; i < length; i++) {
        if (a[i] == 0)
            zero_num += 1;
        else
            break;
    }

    for (int i = zero_num; i < length; i++) {
        string c = to_string(a[i]);
        s.append(c);
    }

    return s;
}

void print_int_array(int *a, int length) {
    for (int i = 0; i < length; i++) {
        cout << a[i];
    }

    cout << endl;
}

string scientific2Int(string s) {
    smatch results;
    regex r("^([+-]?)(([1-9]\\.?)|([1-9]\\.\\d*))[Ee]([+-]?\\d+)$");
    string part1;
    long long part2;

    if (regex_match(s, results, r)) {
        part1 = results[2];
        part2 = stol(results[5]);
    }

    if (part1.find(".") < part1.length()) {
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
