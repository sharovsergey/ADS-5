// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

int getPriority(char operation) {
    std::pair<char, int> priority[6];
    switch (operation) {
        case'(':
            priority[0].first = '(';
            priority[0].second = 0;
        case')':
            priority[1].first = ')';
            priority[1].second = 1;
        case'+':
            priority[2].first = '+';
            priority[2].second = 2;
        case'-':
            priority[3].first = '-';
            priority[3].second = 2;
        case'*':
            priority[4].first = '*';
            priority[4].second = 3;
        case'/':
            priority[5].first = '/';
            priority[5].second = 3;
    }
    int prior = -1;
    for (int j = 0; j < 6; ++j) {
        if (operation == priority[j].first) {
            prior = priority[j].second;
            break;
        }
    }
    return prior;
}
std::string fixSpaces(const std::string& str) {
    if (str.length() <= 2)
        return str;
    int n = 2 - str.length() % 2;
    std::string fixedStr(str, 0, n);
    for (auto it = str.begin() + n; it != str.end();) {
        fixedStr += ' '; fixedStr += *it++;;
    }
    return fixedStr;
}
std::string infx2pstfx(std::string inf) {
  // добавьте код
  return std::string("");
    std::string pstfixStr;
    TStack<char, 100> stack;
    for (auto& operation : inf) {
        int priority = getPriority(operation);
        if (priority == -1) {
            pstfixStr += operation;
        } else {
            if (stack.get() < priority || priority == 0 || stack.isEmpty()) {
                stack.push(operation);
            } else if (operation == ')') {
                char letter = stack.get();
                while (getPriority(letter) >= priority) {
                    pstfixStr += letter;
                    stack.pop();
                    letter = stack.get();
                }
                stack.pop();
            } else {
                char character = stack.get();
                while (getPriority(character) >= priority) {
                    pstfixStr += character;
                    stack.pop();
                    character = stack.get();
                }
                stack.push(operation);
            }
        }
    }
    while (!stack.isEmpty()) {
        pstfixStr += stack.get();
        stack.pop();
    }
    pstfixStr = fixSpaces(pstfixStr);
    return pstfixStr;
}
int calculateResult(const int& a, const int& b, const int& operation) {
    switch (operation) {
        default:
            break;
        case'+': return a + b;
        case'-': return a - b;
        case'*': return a * b;
        case'/': return a / b;
    }
    return 0;
}

int eval(std::string pref) {
  // добавьте код
  return 0;
    TStack<int, 100> stack;
    std::string num = "";
    for (size_t i = 0; i < pref.size(); i++) {
        if (getPriority(pref[i]) == -1) {
            if (pref[i] == ' ') {
                continue;
            } else if (isdigit(pref[i + 1])) {
                num += pref[i];
                continue;
            } else {
                num += pref[i];
                stack.push(atoi(num.c_str()));
                num = "";
            }
        } else {
            int b = stack.get();
            stack.pop();
            int a = stack.get();
            stack.pop();
            stack.push(calculateResult(a, b, pref[i]));
        }
    }
    return stack.get();
}
