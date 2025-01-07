#include "DeadlockManager.h"

DeadlockManager::DeadlockManager(int numProcesses, int numResources, bool notRandom) {
    state.processCount = numProcesses;
    state.resourceCount = numResources;

    // Vektörleri boyutlandır
    state.allocation.resize(numProcesses, std::vector<int>(numResources));
    state.maximum.resize(numProcesses, std::vector<int>(numResources));
    state.need.resize(numProcesses, std::vector<int>(numResources));
    state.available.resize(numResources);

    initializeState(notRandom);
}

void DeadlockManager::initializeState(bool notRandom) {
    if (notRandom) {
        initializeFixedState();
    } else {
        initializeRandomState();
    }
}

void DeadlockManager::initializeRandomState() {
    srand(time(0));  // Random değerler için farklı başlangıç
    for (int i = 0; i < state.processCount; i++) {
        for (int j = 0; j < state.resourceCount; j++) {
            state.allocation[i][j] = rand() % 5;
            state.maximum[i][j] = state.allocation[i][j] + rand() % 5;
            state.need[i][j] = state.maximum[i][j] - state.allocation[i][j];
        }
    }

    for (int i = 0; i < state.resourceCount; i++) {
        state.available[i] = rand() % 10;
    }
}

void DeadlockManager::initializeFixedState() {
    state.allocation = {
        {1, 1, 0},  // İşlem 0
        {1, 0, 2},  // İşlem 1
        {0, 1, 3},  // İşlem 2
        {2, 0, 0},  // İşlem 3
        {3, 2, 1}   // İşlem 4
    };

    state.maximum = {
        {2, 2, 1},  // İşlem 0
        {3, 2, 3},  // İşlem 1
        {1, 1, 4},  // İşlem 2
        {3, 2, 2},  // İşlem 3
        {4, 3, 3}   // İşlem 4
    };

    // İhtiyaç matrisi otomatik olarak hesaplanabilir
    for (int i = 0; i < state.processCount; i++) {
        for (int j = 0; j < state.resourceCount; j++) {
            state.need[i][j] = state.maximum[i][j] - state.allocation[i][j];
        }
    }

    state.available = {0, 0, 0};  // Mevcut kaynaklar
}

bool DeadlockManager::isProcessFinishable(int processIndex, const std::vector<int>& workingResources) const {
    for (int j = 0; j < state.resourceCount; j++) {
        if (state.need[processIndex][j] > workingResources[j]) {
            return false;
        }
    }
    return true;
}

bool DeadlockManager::needsMoreResources(int process) const {
    for (int j = 0; j < state.resourceCount; j++) {
        if (state.need[process][j] > state.available[j]) {
            return true;
        }
    }
    return false;
}

bool DeadlockManager::detectDeadlock(bool isDoneAlready) {
    std::vector<int> work = state.available;
    std::vector<bool> finished(state.processCount, false);

    while (true) {
        bool progress = false;

        for (int i = 0; i < state.processCount; i++) {
            if (!finished[i] && isProcessFinishable(i, work)) {
                for (int j = 0; j < state.resourceCount; j++) {
                    work[j] += state.allocation[i][j];
                }
                finished[i] = true;
                progress = true;
            }
        }

        if (!progress) {
            return std::any_of(finished.begin(), finished.end(), [](bool v) { return !v; });
        }
    }
}

void DeadlockManager::releaseResources(int processIndex) {
    for (int j = 0; j < state.resourceCount; j++) {
        state.available[j] += state.allocation[processIndex][j];
        state.allocation[processIndex][j] = 0;
        state.need[processIndex][j] = 0;
    }
}

void DeadlockManager::resolveDeadlock() {
    std::vector<std::pair<int, int>> processPriorities;
    for (int i = 0; i < state.processCount; i++) {
        processPriorities.push_back({i, rand() % 100});
    }

    std::sort(processPriorities.begin(), processPriorities.end(),
              [](const auto& a, const auto& b) { return a.second < b.second; });

    for (const auto& [process, priority] : processPriorities) {
        if (needsMoreResources(process)) {
            std::cout << "- İşlem " << process << " sonlandırılıyor (Öncelik: " << priority << ")\n";
            releaseResources(process);
        }
    }
}

void DeadlockManager::printSystemState(const std::string& message) const {
    if (!message.empty()) {
        std::cout << "\n" << message << "\n";
    }

    std::cout << "\nMevcut Kaynaklar:\n";
    for (int val : state.available) {
        std::cout << val << " ";
    }

    std::cout << "\n\nTahsis Matrisi:\n";
    for (const auto& row : state.allocation) {
        for (int val : row) {
            std::cout << val << " ";
        }
        std::cout << "\n";
    }

    std::cout << "\nİhtiyaç Matrisi:\n";
    for (const auto& row : state.need) {
        for (int val : row) {
            std::cout << val << " ";
        }
        std::cout << "\n";
    }
}
