#include "../inc/threadSafeQueue.h"

using Task = thSafeQueue::Task;

void thSafeQueue::add(Task task) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_tasks.emplace(task);
    m_condition.notify_one();
}

Task thSafeQueue::extract() {
    Task task = nullptr;
    std::unique_lock<std::mutex> lock(m_mutex);

    m_condition.wait(lock, [this] {
        return !m_tasks.empty();
    });
    if (!m_tasks.empty()) {
        task = m_tasks.front();
        m_tasks.pop();
    }
    return task;
}
void thSafeQueue::clear() {
    std::lock_guard<std::mutex> lock(m_mutex);
    std::queue<Task> empty;
    std::swap(m_tasks, empty);
    m_condition.notify_all();
}
