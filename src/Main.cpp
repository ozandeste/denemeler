#include "ProcessStackManager.h"
#include "DeadlockManager.h"
#include "config.h"  // Sabit değerler için yeni dosya ekledim

int main() {
    DeadlockManager manager(NUM_PROCESSES, NUM_RESOURCES, false);
    ProcessStackManager processStack;

    for (int i = 0; i < NUM_PROCESSES; ++i) {
        processStack.push(i);
    }

    manager.printSystemState("Başlangıç Sistem Durumu:");

    if (manager.detectDeadlock()) {
        std::cout << "Deadlock tespit edildi!\n";
        manager.resolveDeadlock();
        manager.printSystemState("Deadlock Çözümü Sonrası Sistem Durumu:");
    } else {
        std::cout << "Deadlock tespit edilmedi.\n";
    }

    processStack.printStack();
    return 0;
}
