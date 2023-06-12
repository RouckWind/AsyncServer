#include "../inc/threadpool.h"

#include <iostream>

ThreadPool::ThreadPool(uint32_t num_threads) {
    auto max_threads = std::thread::hardware_concurrency();

    if (num_threads > max_threads) {
        num_threads = max_threads;
        std::cerr << "You got maximum available threads " << num_threads << std::endl;
    }

    m_threads.reserve(num_threads);
    for (unsigned i = 0; i < num_threads; ++i) {
        m_threads.emplace_back(&ThreadPool::DoWork, this);
    }
}

ThreadPool::~ThreadPool() {
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_terminate = true;
    }

    m_condition.notify_all();
    for (auto& active_thread : m_threads) {
        if (active_thread.joinable()) {
            active_thread.join();
        }
    }
}

void ThreadPool::AddTask(Task task) {
    std::unique_lock<std::mutex> lock(m_mutex);
    m_tasks.emplace(std::move(task));
    m_condition.notify_one();
}

void ThreadPool::DoWork() {
    for (;;) {
        Task task;
        {
            std::unique_lock<std::mutex> lock(m_mutex);
            m_condition.wait(lock, [&] {
                return !m_tasks.empty() || m_terminate;
            });

            if (m_terminate && m_tasks.empty()) {
                break;
            }

            task = m_tasks.front();
            m_tasks.pop();
        }
        task();
    }
}