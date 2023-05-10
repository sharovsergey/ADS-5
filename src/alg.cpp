// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

using namespace std;

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
int evaluatePostfix(string postfix) {
    stack<int> valStack;

    for (int i = 0; i < postfix.length(); i++) {
        char c = postfix[i];
        if (isdigit(c)) {
            valStack.push(c - '0');
        } else {
            int val2 = valStack.top();
            valStack.pop();
            int val1 = valStack.top();
            valStack.pop();

            switch (c) {
                case '+':
                    valStack.push(val1 + val2);
                    break;
                case '-':
                    valStack.push(val1 - val2);
                    break;
                case '*':
                    valStack.push(val1 * val2);
                    break;
                case '/':
                    valStack.push(val1 / val2);
                    break;
            }
        }
    }

    return valStack.top();
}
