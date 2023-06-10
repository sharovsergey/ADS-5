// Copyright 2021 NNTU-CS
#include <iostream>
#include <string>
#include "include/tstack.h"


int priority(char c) {
    if (c == '*' || c == '/')
        return 2;
    else if (c == '+' || c == '-')
        return 1;
    else
        return 0;
}


std::string infx2pstfx(std::string inf) {
    TStack<char, 100> stack;
    std::string post;
    int len = inf.length();

    for (int i = 0; i < len; i++) {
        char symbol = inf[i];

        if (symbol >= '0' && symbol <= '9') {
            post += symbol;
            post += ' ';
        }
        else if (symbol == '(') {
            stack.push(symbol);
        }
        else if (symbol == ')') {
            while (stack.get() != '(') {
                post += stack.get();
                post += ' ';
                stack.pop();
            }
            stack.pop();
        }
        else {
            while (!stack.isEmpty() && priority(stack.get()) >= priority(symbol)) {
                post += stack.get();
                post += ' ';
                stack.pop();
            }
            stack.push(symbol);
        }
    }

    while (!stack.isEmpty()) {
        post += stack.get();
        post += ' ';
        stack.pop();
    }

    return post;
}


int eval(std::string post) {
    TStack<int, 100> stack;
    int len = post.length();

    for (int i = 0; i < len; i++) {
        char symbol = post[i];

        if (symbol >= '0' && symbol <= '9') {
            int num = 0;

            while (symbol >= '0' && symbol <= '9') {
                num = num * 10 + (symbol - '0');
                i++;
                symbol = post[i];
            }

            stack.push(num);
        }
        else if (symbol != ' ') {
            int operand2 = stack.get();
            stack.pop();
            int operand1 = stack.get();
            stack.pop();

            switch (symbol) {
            case '+':
                stack.push(operand1 + operand2);
                break;
            case '-':
                stack.push(operand1 - operand2);
                break;
            case '*':
                stack.push(operand1 * operand2);
                break;
            case '/':
                stack.push(operand1 / operand2);
                break;
            }
        }
    }

    return stack.get();
}

int main() {
    setlocale(LC_ALL, "Russian");
    std::string infixExpression = "(2+2)*2";
    std::string postfixExpression = infx2pstfx(infixExpression);

    std::cout << "Infix выражение: " << infixExpression << std::endl;
    std::cout << "Postfix выражение: " << postfixExpression << std::endl;

    int result = eval(postfixExpression);
    std::cout << "Результат: " << result << std::endl;

    return 0;
}
