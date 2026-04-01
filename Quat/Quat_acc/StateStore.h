
#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <mutex>

using namespace std;

class StateStore {
public:
    // 仿真线程调用（多线程）
    void put(std::string key, std::vector<char>&& data) {
        std::lock_guard<std::mutex> lock(m_);
        store_.emplace(std::move(key), std::move(data));
    }

    // 主线程调用（单线程）
    // 成功只会发生一次
    bool take(const std::string& key, std::vector<char>& out) {
        std::lock_guard<std::mutex> lock(m_);
        auto it = store_.find(key);
        if (it == store_.end())
            return false;

        out = std::move(it->second);
        store_.erase(it);
        return true;
    }

private:
    std::unordered_map<std::string, std::vector<char>> store_;
    std::mutex m_;
};
