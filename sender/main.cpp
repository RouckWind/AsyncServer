#include <iostream>
#include <threadpool.h>
#include <thread>

void task() {
    std::cout << "you run thread 1" << std::this_thread::get_id() << std::endl;
}

void task2() {
    std::cout << "you run thread 2" << std::this_thread::get_id() << std::endl;
}

void task3() {
    std::cout << "you run thread 3" << std::this_thread::get_id() << std::endl;
}

void task4() {
    std::cout << "you run thread 4" << std::this_thread::get_id() << std::endl;
}

int main() {
    ThreadPool t(3);

    t.AddTask(task);
    t.AddTask(task2);
    t.AddTask(task3);
    t.AddTask(task4);

    return 0;
}