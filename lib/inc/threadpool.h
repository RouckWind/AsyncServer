#pragma once

#include <atomic>
#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

class ThreadPool {
public:
    using Task = std::function<void()>;

    explicit ThreadPool(uint32_t num_of_threads);

    ~ThreadPool();

    void AddTask(Task task);

private:
    void DoWork();

private:
    std::queue<Task> m_tasks;
    std::mutex m_mutex;
    std::condition_variable m_condition;
    std::vector<std::thread> m_threads;

    bool m_terminate{false};
};