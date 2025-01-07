#ifndef PROCESS_STACK_MANAGER_H
#define PROCESS_STACK_MANAGER_H

#include <stack>
#include <string>
#include <iostream>

class ProcessStackManager {
private:
    std::stack<int> processStack; // İşlemleri temsil eden bir yığın

public:
    void push(int processID);    // Yeni işlem ekle
    void pop();                  // Yığından işlem çıkar
    int top() const;             // Yığının tepesindeki işlem
    bool empty() const;          // Yığının boş olup olmadığını kontrol et
    void printStack() const;     // Yığının içeriğini yazdır
};

#endif // PROCESS_STACK_MANAGER_H
