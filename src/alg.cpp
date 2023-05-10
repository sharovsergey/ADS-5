// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

int getPriority(char op) {
    if (op == '+' || op == '-') {
        return 1;
    } else if (op == '*' || op == '/') {
        return 2;
    } else {
        return 0;
    }
}

string infixToPostfix(string infix) {
    stack<char> opStack;
    string postfix = "";

    for (int i = 0; i < infix.length(); i++) {
        char c = infix[i];
        if (isdigit(c)) {
            postfix += c;
        } else if (c == '(') {
            opStack.push(c);
        } else if (c == ')') {
            while (opStack.top() != '(') {
                postfix += opStack.top();
                opStack.pop();
            }
            opStack.pop();
        } else if (c == '+' || c == '-' || c == '*' || c == '/') {
            while (!opStack.empty() && getPriority(opStack.top()) >= getPriority(c)) {
                postfix += opStack.top();
                opStack.pop();
            }
            opStack.push(c);
        }
    }

    while (!opStack.empty()) {
        postfix += opStack.top();
        opStack.pop();
    }

    return postfix;
}
