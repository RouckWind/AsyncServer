#pragma once

#include <chrono>
#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

class ThreadPool {
public:
    explicit ThreadPool(uint32_t num_of_threads);

    ~ThreadPool();

    void AddTask(const std::function<void()>& task);
    void test(std::function<void()>);

private:
    void ThreadLoop();

private:
    bool m_terminate;
    std::mutex m_mutex;
    std::condition_variable_any m_condition;
    std::vector<std::thread> m_threads;
    std::queue<std::function<void()>> m_tasks;
};