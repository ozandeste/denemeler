#include "ProcessStackManager.h"

void ProcessStackManager::push(int processID) {
    processStack.push(processID);
    std::cout << "Process " << processID << " added to the stack.\n";
}

void ProcessStackManager::pop() {
    if (!processStack.empty()) {
        std::cout << "Process " << processStack.top() << " removed from the stack.\n";
        processStack.pop();
    } else {
        std::cout << "Stack is empty. Cannot pop.\n";
    }
}

int ProcessStackManager::top() const {
    if (!processStack.empty()) {
        return processStack.top();
    }
    return -1; // Yığın boşsa -1 döndür
}

bool ProcessStackManager::empty() const {
    return processStack.empty();
}

void ProcessStackManager::printStack() const {
    std::stack<int> tempStack = processStack;
    std::cout << "Current Process Stack: ";
    while (!tempStack.empty()) {
        std::cout << tempStack.top() << " ";
        tempStack.pop();
    }
    std::cout << "\n";
}
