#pragma once

#include "../inc/threadSafeQueue.h"

#include <atomic>
#include <functional>
#include <thread>
#include <vector>
#include <memory>

class ThreadPool {
public:
    using Task = std::function<void()>;

    static std::unique_ptr<ThreadPool> create(uint32_t num_of_threads);

    ~ThreadPool();

    void AddTask(Task task);

private:
    void DoWork();

private:
    explicit ThreadPool(uint32_t num_of_threads);

    thSafeQueue m_tasks;
    std::vector<std::thread> m_threads;
    std::atomic_bool m_terminate{false};
};