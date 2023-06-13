#pragma once

#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>

class thSafeQueue {
public:
    using Task = std::function<void()>;

public:
    void add(Task task);
    Task extract();
    void clear();

private:
    std::mutex m_mutex;
    std::queue<Task> m_tasks;
    std::condition_variable m_condition;
};