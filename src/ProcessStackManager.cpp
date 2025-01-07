#include "ProcessStackManager.h"

void ProcessStackManager::push(int processID) {
    processStack.push(processID);
}

void ProcessStackManager::pop() {
    if (!processStack.empty()) {
        processStack.pop();
    } else {
        std::cout << "Yığın boş, pop işlemi yapılamaz!" << std::endl;
    }
}

int ProcessStackManager::top() const {
    if (!processStack.empty()) {
        return processStack.top();
    } else {
        std::cerr << "Yığın boş!" << std::endl;
        return -1;
    }
}

bool ProcessStackManager::empty() const {
    return processStack.empty();
}

void ProcessStackManager::printStack() const {
    std::stack<int> tempStack = processStack;
    while (!tempStack.empty()) {
        std::cout << tempStack.top() << " ";
        tempStack.pop();
    }
    std::cout << std::endl;
}
