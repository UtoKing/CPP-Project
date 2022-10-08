#include <iostream>
#include "string"
#include "strMultiply.h"
#include "strAdd.h"
#include "strMinus.h"
#include "strDivision.h"

using namespace std;

int main() {
    string s1 = "123";
    string s2 = "45";
    cout << strDivision(s1, s2);
}
