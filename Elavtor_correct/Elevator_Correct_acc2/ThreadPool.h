#pragma once

#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <atomic>
#include <stdexcept>

class ThreadPool {
public:


    explicit ThreadPool(size_t threadCount)
        : stopFlag(false)
    {
        if (threadCount == 0)
            throw std::invalid_argument("threadCount must be > 0");

        workers.reserve(threadCount);
        for (size_t i = 0; i < threadCount; ++i) {
            workers.emplace_back([this] {
                workerLoop();
            });
        }
    }

    // 禁止拷贝
    ThreadPool(const ThreadPool&) = delete;
    ThreadPool& operator=(const ThreadPool&) = delete;

    // 允许移动（可选）
    ThreadPool(ThreadPool&&) = delete;
    ThreadPool& operator=(ThreadPool&&) = delete;

    ~ThreadPool() {
        shutdown();
    }

    // 提交任务（最核心接口）
    //template <typename F>
    //void enqueue(F&& task) {
    //    {
    //        std::lock_guard<std::mutex> lock(mutex);
    //        if (stopFlag)
    //            throw std::runtime_error("enqueue on stopped ThreadPool");
    //        tasks.emplace(std::forward<F>(task));
    //    }
    //    cond.notify_one();
    //}

    
    struct Task {
        int priority;
        std::function<void()> func;

        bool operator<(const Task& other) const {
            // priority_queue 是“最大堆”
            return priority < other.priority;
        }
    };

    template <typename F>
    void enqueue(int priority, F&& task) {
        {
            std::lock_guard<std::mutex> lock(mutex);
            if (stopFlag)
                throw std::runtime_error("enqueue on stopped ThreadPool");

            tasks.push(Task{
                priority,
                std::function<void()>(std::forward<F>(task))
            });
        }
        cond.notify_one();
    }

    // 等待所有任务完成（可选）
    void waitIdle() {
        std::unique_lock<std::mutex> lock(mutex);
        idleCond.wait(lock, [this] {
            return tasks.empty() && activeWorkers == 0;
        });
    }

    // 主动关闭（析构时也会调用）
    void shutdown() {
        {
            std::lock_guard<std::mutex> lock(mutex);
            if (stopFlag) return;
            stopFlag = true;
        }
        cond.notify_all();
        for (auto& t : workers) {
            if (t.joinable())
                t.join();
        }
        workers.clear();
    }

private:
    void workerLoop() {
        while (true) {
            std::function<void()> task;

            {
                std::unique_lock<std::mutex> lock(mutex);
                cond.wait(lock, [this] {
                    return stopFlag || !tasks.empty();
                });

                if (stopFlag && tasks.empty())
                    return;

                task = std::move(tasks.top().func);
                tasks.pop();
                ++activeWorkers;
            }

            // 执行任务（不持锁）
            try {
                task();
            } catch (...) {
                // 生产环境可以记录日志
            }

            {
                std::lock_guard<std::mutex> lock(mutex);
                --activeWorkers;
                if (tasks.empty() && activeWorkers == 0) {
                    idleCond.notify_all();
                }
            }
        }
    }

private:
    std::vector<std::thread> workers;
    std::priority_queue<Task> tasks;

    std::mutex mutex;
    std::condition_variable cond;
    std::condition_variable idleCond;

    std::atomic<bool> stopFlag;
    size_t activeWorkers = 0;
};
