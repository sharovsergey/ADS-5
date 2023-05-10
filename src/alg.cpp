// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

using namespace std;

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

Пример использования:

int main() {
    string infix = "3+4*2/(1-5)^2";
    string postfix = infixToPostfix(infix);
    cout << "Postfix: " << postfix << endl;
    int result = evaluatePostfix(postfix);
    cout << "Result: " << result << endl;
    return 0;
}
