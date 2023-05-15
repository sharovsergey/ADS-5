// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

using namespace std;


bool isOperator(const char &c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

bool hasLessOrEqualPriority(const char &op1, const char &op2) {
    if ((op1 == '+' || op1 == '-') && (op2 == '*' || op2 == '/')) {
        return true;
    }
    return false;
}


string infixToPostfix(const string &infix) {
    stack<char> s;
    string postfix;

    for (const char &c : infix) {
        if (c == '(') {
            s.push(c);
        } else if (c == ')') {
            while (!s.empty() && s.top() != '(') {
                postfix.push_back(s.top());
                s.pop();
            }
            s.pop();
        } else if (isOperator(c)) {
            while (!s.empty() && s.top() != '(' && hasLessOrEqualPriority(c, s.top())) {
                postfix.push_back(s.top());
                s.pop();
            }
            s.push(c);
        } else {
            postfix.push_back(c);
        }
    }

    while (!s.empty()) {
        postfix.push_back(s.top());
        s.pop();
    }

    return postfix;
}

int main() {
    string infix = "a+b*c-d/e";
    string postfix = infixToPostfix(infix);
    cout << postfix << endl;
    return 0;
}
bool isOperator(const char &c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}
double applyOperator(const double &operand1, const double &operand2, const char &op) {
    if (op == '+') {
        return operand1 + operand2;
    } else if (op == '-') {
        return operand1 - operand2;
    } else if (op == '*') {
        return operand1 * operand2;
    } else if (op == '/') {
        return operand1 / operand2;
    }
    return 0;
}
double evaluatePostfix(const string &postfix) {
    stack<double> s;
    double operand1, operand2;

    for (const char &c : postfix) {
        if (isdigit(c)) {
            s.push((double)(c - '0'));
        } else if (isOperator(c)) {
            operand2 = s.top();
            s.pop();
            operand1 = s.top();
            s.pop();
            s.push(applyOperator(operand1, operand2, c));
        }
    }

    return s.top();
}

int main() {
    string postfix = "abc*+de/-";
    double result = evaluatePostfix(postfix);
    cout << result << endl;
    return 0;
}
