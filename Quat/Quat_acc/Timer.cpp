#include "Timer.h"
#include <iostream>
#include <iomanip>

Timer::Timer() : elapsedTime(0.0), isRunning(false) {
    // 获取计时器频率
    QueryPerformanceFrequency(&frequency);
}

Timer::~Timer() {
}

void Timer::start() {
    if (!isRunning) {
        QueryPerformanceCounter(&startTime);
        isRunning = true;
    }
}

void Timer::stop() {
    if (isRunning) {
        QueryPerformanceCounter(&endTime);
        // 计算经过时间（秒）
        elapsedTime = static_cast<double>(endTime.QuadPart - startTime.QuadPart) / frequency.QuadPart;
        isRunning = false;
    }
}

double Timer::getElapsedTime() const {
    if (isRunning) {
        LARGE_INTEGER currentTime;
        QueryPerformanceCounter(&currentTime);
        return static_cast<double>(currentTime.QuadPart - startTime.QuadPart) / frequency.QuadPart;
    }
    return elapsedTime;
}

void Timer::reset() {
    elapsedTime = 0.0;
    isRunning = false;
}

void Timer::startSection(const std::string& sectionName) {
    LARGE_INTEGER currentTime;
    QueryPerformanceCounter(&currentTime);
    startTimesMap[sectionName] = currentTime;
}

void Timer::endSection(const std::string& sectionName) {
    auto it = startTimesMap.find(sectionName);
    if (it != startTimesMap.end()) {
        LARGE_INTEGER endTime;
        QueryPerformanceCounter(&endTime);
        double time = static_cast<double>(endTime.QuadPart - it->second.QuadPart) / frequency.QuadPart;
        
        totalTimes[sectionName] += time;
        executionCounts[sectionName]++;
        
        startTimesMap.erase(it);
    }
}

double Timer::getTotalTime(const std::string& sectionName) const {
    auto it = totalTimes.find(sectionName);
    if (it != totalTimes.end()) {
        return it->second;
    }
    return 0.0;
}

long long Timer::getExecutionCount(const std::string& sectionName) const {
    auto it = executionCounts.find(sectionName);
    if (it != executionCounts.end()) {
        return it->second;
    }
    return 0;
}

double Timer::getAverageTime(const std::string& sectionName) const {
    auto countIt = executionCounts.find(sectionName);
    auto timeIt = totalTimes.find(sectionName);
    
    if (countIt != executionCounts.end() && timeIt != totalTimes.end() && countIt->second > 0) {
        return timeIt->second / countIt->second;
    }
    return 0.0;
}

void Timer::printStatistics() const {
    std::cout << "\n=== Time Statistics ===\n";
    std::cout << std::fixed << std::setprecision(6);
    
    for (const auto& pair : totalTimes) {
        const std::string& sectionName = pair.first;
        double totalTime = pair.second;
        long long count = getExecutionCount(sectionName);
        double avgTime = getAverageTime(sectionName);
        
        std::cout << "Position: " << sectionName << std::endl;
        std::cout << "  Total Execution Time: " << totalTime << " seconds" << std::endl;
        std::cout << "  Execution Count: " << count << std::endl;
        std::cout << "  Average Execution Time: " << avgTime << " seconds" << std::endl;
        std::cout << "------------------------\n";
    }
}
