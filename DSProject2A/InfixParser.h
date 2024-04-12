#ifndef INFIXPARSER_H
#define INFIXPARSER_H
#include <iostream>
#include <stack>
#include <string>
#include <vector>
using namespace std;
class InfixParser {
public:
    int solve(const string& expression);

private:
    bool isOperator(char c);
    int precedence(char op);
    vector<string> tokenize(const string& expression);
    vector<string> infixToPostfix(const vector<string>& infix);
    int evaluatePostfix(const vector<string>& postfix);
};
#endif


