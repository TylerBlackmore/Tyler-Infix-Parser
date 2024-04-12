#include "InfixParser.h"
#include <cmath>
#include <cstdlib>
using namespace std;

/**
 * Function that checks if a char is an arithmetic operator
 * @param c The character to be checked
 * @return True if the character is an operator, false otherwise
 */
bool InfixParser::isOperator(char c) { return c == '+' || c == '-' || c == '*' || c == '%' || c == '/' || c == '^'; }

/**
 * Function that This function determines the precedence of the given operator
 * @param op: the operator whose precedence is to be determined
 * @return the precedence of the operator (higher value = higher precedence)
 */
int InfixParser::precedence(char op) {
    switch (op) {
    case '^':
        return 3;
    case '*':
    case '/':
    case '%':
        return 2;
    case '+':
    case '-':
        return 1;
    default:
        return -1;
    }
}

/**
 * Function that tokenizes the infix expression
 * @param expression: the infix expression to be tokenized
 * @return a vector of strings containing extracted tokens
 */
vector<string> InfixParser::tokenize(const string& expression) {
    vector<string> tokens;
    string token = "";
    for (char c : expression) {
        if (c == ' ')
            continue;
        if (isOperator(c) || c == '(' || c == ')') {
            if (!token.empty()) {
                tokens.push_back(token);
                token = "";
            }
            tokens.push_back(string(1, c));
        }
        else {
            token += c;
        }
    }
    if (!token.empty()) { tokens.push_back(token); }
    return tokens;
}

/**
 * function that converts infix to postfix
 * @param infix: the infix expression to be converted
 * @return a new vector of strings containing the expression in postfix
 */
vector<string> InfixParser::infixToPostfix(const vector<string>& infix) {
    vector<string> postfix;
    stack<string> s;

    for (const string& token : infix) {
        if (isdigit(token[0])) { postfix.push_back(token); }
        else if (token == "(") { s.push(token); }
        else if (token == ")") {
            while (!s.empty() && s.top() != "(") {
                postfix.push_back(s.top());
                s.pop();
            }
            s.pop();
        }
        else {
            while (!s.empty() && precedence(token[0]) <= precedence(s.top()[0])) {
                postfix.push_back(s.top());
                s.pop();
            }
            s.push(token);
        }
    }

    while (!s.empty()) {
        postfix.push_back(s.top());
        s.pop();
    }

    return postfix;
}

/**
 * Function that evaluates the postfix operation
 * @param postfix: the postfix expression being evaluated
 * @return the result of the expression evaluation
 */
int InfixParser::evaluatePostfix(const vector<string>& postfix) {
    stack<int> s;

    for (const string& token : postfix) {
        if (isdigit(token[0])) { s.push(stoi(token)); }
        else {
            int operand2 = s.top();
            s.pop();
            int operand1 = s.top();
            s.pop();
            switch (token[0]) {
            case '+':
                s.push(operand1 + operand2);
                break;
            case '-':
                s.push(operand1 - operand2);
                break;
            case '*':
                s.push(operand1 * operand2);
                break;
            case '/':
                s.push(operand1 / operand2);
                break;
            case '%':
                s.push(operand1 % operand2);
                break;
            case '^':
                s.push(pow(operand1, operand2));
                break;
            }
        }
    }
    return s.top();
}

/**
 * Function that solves the infix expression
 * @param expression: the infix expression to be solved
 * @return the final result.
 */
int InfixParser::solve(const string& expression) {
    vector<string> tokens = tokenize(expression);
    vector<string> postfix = infixToPostfix(tokens);
    return evaluatePostfix(postfix);
}