// Copyright 2021 NNTU-CS
#include <ctype.h>
#include <string>
#include <map>
#include "tstack.h"

int getPr(char c) {
   switch (c) {
   case '(':
       return 0;
   case ')':
       return 1;
   case '+':
       return 2;
   case '-':
       return 2;
   case '*':
       return 3;
   case '/':
       return 3;
   }
   return -1;
}
std::string infx2pstfx(std::string inf) {
 // добавьте код
 return std::string("");
   TStack<char, 100> ops;
   std::string res, num;
   for (int serg = 0; serg < inf.length(); serg++) {
       if (isdigit(inf[serg])) {
           num += inf[serg];
       } else { // операция
           if (num.length() > 0) {
               res += num;
               res += " ";
               num = "";
           }
           if (inf[serg] == '(' ||
               ops.IsEmpty() ||
               getPr(inf[serg]) > getPr(ops.Get())) {
               ops.Push(inf[serg]);
           } else if (inf[serg] == ')') {
               char sim = ops.pop();
               while (sim != '(') {
                   res += sim;
                   res += " ";
                   sim = ops.pop();
               }
           } else {
               while (!ops.IsEmpty() && getPr(inf[serg]) <= getPr(ops.Get())) {
                   res += ops.pop();
                   res += " ";
               }
               ops.Push(inf[serg]);
           }
       }
   }
   if (num.length() > 0) {
       res += num;
       res += " ";
       num = "";
   }
   while (!ops.IsEmpty()) {
       res += ops.pop();
       if (!ops.IsEmpty()) res += " ";
   }
   return res;
}

int eval(std::string pref) {
 // добавьте код
 return 0;
   int first = 0, second = 0;
   std::string num;
   TStack<int, 100> nums;
   for (int serg = 0; serg < pref.length(); serg++) {
       if (isdigit(pref[serg])) {
           num += pref[serg];
       } else if (pref[serg] == ' ') {
           if (num.length() > 0) {
               nums.Push(stoi(num));
               num = "";
           }
       } else {
           int semiRes = 0;
           second = nums.pop();
           first = nums.pop();
           switch (pref[serg]) {
           case '+':
               semiRes = first + second;
               break;
           case '-':
               semiRes = first - second;
               break;
           case '*':
               semiRes = first * second;
               break;
           case '/':
               semiRes = first / second;
               break;
           }
           nums.Push(semiRes);
       }
   }
   return nums.pop();
}
