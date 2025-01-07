#include "ProcessStackManager.h"
#include "DeadlockManager.h"

int main() {
    // Rastgele oluşumlar için time parametresi ile çağrı yapılır.
    srand(time(0));

    // Sistem parametreleri
    const int NUM_PROCESSES = 5; // İşlem Adeti
    const int NUM_RESOURCES = 3; // Kaynak Adeti

    // Deadlock yöneticisi
    DeadlockManager manager(NUM_PROCESSES, NUM_RESOURCES, false);
    ProcessStackManager processStack;

    // İşlem yığınına işlemleri ekle
    for (int i = 0; i < NUM_PROCESSES; ++i) {
        processStack.push(i);
    }

    // Sistem durumu yazdır
    manager.printSystemState("Başlangıç Sistem Durumu:");

    // Deadlock tespiti
    if (manager.detectDeadlock()) {
        std::cout << "Deadlock tespit edildi!\n";

        // Deadlock çözümünü yığın ile yönetin
        manager.resolveDeadlock();

        // Sistem durumunu tekrar yazdır
        manager.printSystemState("Deadlock Çözümü Sonrası Sistem Durumu:");
    } else {
        std::cout << "Deadlock tespit edilmedi.\n";
    }

    // İşlem yığınını yazdır
    processStack.printStack();

    return 0;
}
