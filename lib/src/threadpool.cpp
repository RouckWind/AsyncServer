#include "../inc/threadpool.h"

#include <iostream>

ThreadPool::ThreadPool(uint32_t num_threads) {
    m_terminate = false;
    auto max_threads = std::thread::hardware_concurrency();

    if (num_threads > max_threads) {
        num_threads = max_threads;
        std::cerr << "You got maximum available threads " << num_threads << std::endl;
    }

    //m_threads.reserve(num_threads);
    for (uint32_t i = 0; i < num_threads; ++i) {
        m_threads.emplace_back(&ThreadPool::ThreadLoop, this);
    }
}

ThreadPool::~ThreadPool() {
    m_terminate = true;

    m_condition.notify_all();
    for (auto& active_thread : m_threads) {
        if (active_thread.joinable()) {
            active_thread.join();
        }
    }
}

void ThreadPool::AddTask(const std::function<void()>& task) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_tasks.push(task);
    m_condition.notify_one();
}

void ThreadPool::ThreadLoop() {
    while (!m_terminate) {
        std::function<void()> task;
        {
            std::unique_lock<std::mutex> lock(m_mutex);
            m_condition.wait(lock, [&] {
                return !m_tasks.empty() || m_terminate;
            });
            if (m_terminate) {
                break;
            }

            task = m_tasks.front();
            m_tasks.pop();
        }
        test(task);
    }
}
void ThreadPool::test(std::function<void()>) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << " test" << std::endl;
}
