#include "../inc/threadpool.h"

#include <cassert>
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


void ThreadPool::AddTask(Task task) {
    m_tasks.add(std::move(task));
}

void ThreadPool::DoWork() {
    while (!m_terminate) {

        auto task = m_tasks.extract();
        if (task == nullptr) {
            assert(m_terminate);
            return;
        }

        try {
            task();
        } catch (std::exception& e) {
            try {
                std::cerr << "Catch exception: " << e.what()  << " on thread: " << std::this_thread::get_id() << std::endl;
            } catch (...) {
                std::cerr << "Catch unknown exception on thread: " << std::this_thread::get_id() << std::endl;
            };
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

ThreadPool::~ThreadPool() {
    m_terminate = true;

    m_tasks.clear();
    for (auto& active_thread : m_threads) {
        if (active_thread.joinable()) {
            active_thread.join();
        }
    }
}
std::unique_ptr<ThreadPool> ThreadPool::create(uint32_t num_of_threads) {
    return std::unique_ptr<ThreadPool>(new ThreadPool(num_of_threads));
}
