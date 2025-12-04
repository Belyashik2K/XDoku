//
// Created by belyashik2k on 12/4/25.
//

#ifndef XDOKU_PROFILINGMANAGER_H
#define XDOKU_PROFILINGMANAGER_H

#include <iostream>
#include <chrono>
#include <map>
#include <string>
#include <functional>

struct FunctionStats {
    long long totalTime = 0;
    int callCount = 0;
};

class FunctionTimerManager {
public:
    static FunctionTimerManager& instance() {
        static FunctionTimerManager instance;
        return instance;
    }

    template <typename Func, typename... Args>
    auto track(const std::string& functionName, Func&& func, Args&&... args) {
        auto start = std::chrono::high_resolution_clock::now();  // Засекаем время

        auto result = std::forward<Func>(func)(std::forward<Args>(args)...);

        auto end = std::chrono::high_resolution_clock::now();  // Засекаем время завершения
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

        updateStats(functionName, duration.count());

        return result;
    }

    void updateStats(const std::string& functionName, long long timeTaken) {
        stats[functionName].totalTime += timeTaken;
        stats[functionName].callCount++;
    }

    ~FunctionTimerManager() {
        printf("============= Function Execution Statistics =============\n");
        for (const auto& entry : stats) {
            const auto& functionName = entry.first;
            const auto& stat = entry.second;
            double averageTime = static_cast<double>(stat.totalTime) / stat.callCount;
            std::cout << "| " << std::setw(50) << std::left << functionName
            << " | total: " << std::setw(15) << std::right << stat.totalTime / 1'000'000.0 << "s"
            << " | calls: " << std::setw(10) << std::right << stat.callCount
            << " | avg: " << std::setw(17) << std::right << averageTime / 1'000.0 << "ms |\n";
        }
        printf("=========================================================\n");
    }

private:
    FunctionTimerManager() = default;

    FunctionTimerManager(const FunctionTimerManager&) = delete;
    FunctionTimerManager& operator=(const FunctionTimerManager&) = delete;
    FunctionTimerManager(FunctionTimerManager&&) = delete;
    FunctionTimerManager& operator=(FunctionTimerManager&&) = delete;

    std::map<std::string, FunctionStats> stats;
};

#endif //XDOKU_PROFILINGMANAGER_H