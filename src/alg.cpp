// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

int priority(char x) {
  if (x == '(')
    return 0;
  if (x == ')')
    return 1;
  if ((x == '+') || (x == '-'))
    return 2;
  if ((x == '*') || (x == '/'))
    return 3;
  if ((x == '(') || (x == ')'))
    return 0;
  return -1;
}

std::string infixToPostfix(std::string infix) {
  TStack<char, 100> stack;
  std::string postfix = "";
  int index = 0;
  for (char a : infix) {
    bool flag = true;
    if (priority(a) == -1) {
      postfix += a;
      postfix += ' ';
      flag = false;
    }
    if (priority(a) == 0) {
      stack.push(a);
      flag = false;
    }
    if (priority(a) > priority(stack.top())) {
      stack.push(a);
      flag = false;
    }
    if (stack.empty() && priority(a) != -1) {
      stack.push(a);
      flag = false;
    }
    if (flag && a != ')') {
      while (priority(stack.top()) >= priority(a)) {
        postfix += stack.pop();
        postfix += ' ';
      }
      stack.push(a);
    }
    if (a == ')') {
      while (stack.top() != '(') {
        postfix += stack.pop();
        postfix += ' ';
      }
      stack.pop();
    }
    if (index == infix.size() - 1) {
      while (!stack.empty()) {
        postfix += stack.pop();
        if (stack.priority() != -1) postfix += ' ';
      }
    }
    ++index;
  }
  return postfix;
}

int evaluatePostfix(std::string postfix) {
  TStack<int, 100> stack;
  for (char a : postfix) {
    if (a == '+') {
      int tmp = stack.pop();
      tmp = tmp + stack.pop();
      stack.push(tmp);
    }
    if (a == '-') {
      int tmp = stack.pop();
      tmp = stack.pop() - tmp;
      stack.push(tmp);
    }
    if (a == '/') {
      int tmp = stack.pop();
      tmp = stack.pop() / tmp;
      stack.push(tmp);
    }
    if (a == '*') {
      int tmp = stack.pop();
      tmp = tmp * stack.pop();
      stack.push(tmp);
    }
    if (a == ' ') {
      continue;
    }
    if ((a - '0') > 0) {
      int tmp = a - '0';
      stack.push(tmp);
    }
  }
  return stack.top();
}
