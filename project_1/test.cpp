#include <iostream>
#include <string>
#include <regex>

using namespace std;

bool isScientific(string s);
string scientific2Int(string s);

int main(int argc, char *argv[]) {
    string s = argv[1];
    cout<<scientific2Int(s)<<endl;
}

bool isScientific(string s) {
    regex r("^[+-]?(([1-9]\\.?)|([1-9]\\.\\d*))[Ee]([+-]?\\d+)$");

    bool b = regex_match(s, r);
    return b;
}

string scientific2Int(string s) {
    smatch results;
    regex r("^([+-]?)(([1-9]\\.?)|([1-9]\\.\\d*))[Ee]([+-]?\\d+)$");

    string part1;
    long long part2;

    if (regex_match(s, results, r)) {
        part1 = results[2];
        part2 = stol(results[5]);

    } else
        return "";

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

    if(results[1]=="-")
        part1.insert(0,"-");

    return part1;
}
