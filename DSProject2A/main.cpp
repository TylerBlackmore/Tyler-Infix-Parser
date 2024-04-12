//Written by Tyler Blackmore
//Unfortunately, not all equations listed on the instructions work. Support for logical and comparison operators is mostly hardcoded to an extent
//logical operators inside parentheses or inside another equation will break the program.
//Perhaps if I used my time better, things would have gone smoother.
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "Operator.cpp"
using namespace std;

int main() {
    //Initializes variables
    ifstream in("input.txt");
    string infix_expression;

    //Reads stuff in
    while (in >> infix_expression) {
        int result = andOr(infix_expression);
        cout << (result) << endl;
    }

    //Closes the file
    in.close();
    return 0;
}

