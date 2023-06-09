// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_


#include <string>
template<typename T, int size>
class TStack {
// добавьте код стека
private:
T arr[100];
int serg;


public:
TStack() :serg(-1) {}
void push(T value) {
if (isFull()) {
throw std::string("Stack is full");
} else {
arr[++serg] = value;
}
}
const T& pop() {
if (isEmpty()) {
throw std::string("Stack is empty");
} else {
return arr[serg--];
}
}
bool isEmpty()const {
return serg == -1;
}
bool isFull()const {
return serg == size - 1;
}
const T& get()const {
return arr[serg];
}
};


#endif
 // INCLUDE_TSTACK_H_
