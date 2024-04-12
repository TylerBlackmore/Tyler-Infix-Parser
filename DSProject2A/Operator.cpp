#include <string>
#include "InfixParser.h"
using namespace std;

/**
 * Function that checks for comparison operators
 * @param input: an equation in string form
 * @return if an operator is found, it separates the 2 sides of the equation, and tests if it is true or false. Otherwise, it moves on to solve class
 */
int operate(const string& input) {
    vector<string> operators = { "<", ">", "<=", ">=", "==", "!=" };
    InfixParser parser;
    for (const string& op : operators) {
        size_t pos = input.find(op);
        if (pos != string::npos) {
            string eqLeft = input.substr(0, pos);
            string eqRight = input.substr(pos + op.length());
            if (op == "<" && parser.solve(eqLeft) < parser.solve(eqRight)) { return 1; }
            if (op == ">" && parser.solve(eqLeft) > parser.solve(eqRight)) { return 1; }
            if (op == "<=" && parser.solve(eqLeft) <= parser.solve(eqRight)) { return 1; }
            if (op == ">=" && parser.solve(eqLeft) >= parser.solve(eqRight)) { return 1; }
            if (op == "==" && parser.solve(eqLeft) == parser.solve(eqRight)) { return 1; }
            if (op == "!=" && parser.solve(eqLeft) != parser.solve(eqRight)) { return 1; }
            return 0;
        }
    }
    return parser.solve(input);
}

/**
 * Function that checks for logical operators
 * @param input: an equation in string form
 * @return if an operator is found, it separates the 2 sides of the equation, and then compares them. Otherwise, it moves on to solve class
 */
int andOr(const string& input) {
    string eqLeft, eqRight;
    size_t pos = input.find("||");
    if (pos != string::npos) {
        eqLeft = input.substr(0, pos);
        eqRight = input.substr(pos + 2);
        if (operate(eqLeft) == 0 && operate(eqRight) == 0) { return 0; }
        else { return 1; }
    }
    pos = input.find("&&");
    if (pos != string::npos) {
        eqLeft = input.substr(0, pos);
        eqRight = input.substr(pos + 2);
        if ((operate(eqLeft) == 0 || operate(eqRight) == 0)) { return 0; }
        else { return 1; }
    }
    return operate(input);
}