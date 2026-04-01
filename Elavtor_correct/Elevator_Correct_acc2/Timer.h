#pragma once

#include <windows.h>
#include <string>
#include <unordered_map>

// 计时工具类
class Timer {
private:
    LARGE_INTEGER frequency;      // 计时器频率
    LARGE_INTEGER startTime;      // 开始时间
    LARGE_INTEGER endTime;        // 结束时间
    double elapsedTime;           // 经过时间（秒）
    bool isRunning;               // 是否正在计时

    // 用于统计多个位置的总执行时间
    std::unordered_map<std::string, double> totalTimes;
    std::unordered_map<std::string, LARGE_INTEGER> startTimesMap;
    std::unordered_map<std::string, long long> executionCounts;

public:
    Timer();
    ~Timer();

    // 开始计时
    void start();
    
    // 结束计时
    void stop();
    
    // 获取经过时间（秒）
    double getElapsedTime() const;
    
    // 重置计时器
    void reset();

    // 开始统计特定位置的计时
    void startSection(const std::string& sectionName);
    
    // 结束统计特定位置的计时
    void endSection(const std::string& sectionName);
    
    // 获取特定位置的总执行时间
    double getTotalTime(const std::string& sectionName) const;
    
    // 获取特定位置的执行次数
    long long getExecutionCount(const std::string& sectionName) const;
    
    // 获取特定位置的平均执行时间
    double getAverageTime(const std::string& sectionName) const;
    
    // 输出所有统计信息
    void printStatistics() const;
};
