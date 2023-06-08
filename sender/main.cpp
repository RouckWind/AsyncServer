#include <chrono>
#include <iostream>
#include <sys/socket.h>
#include <thread>
#include <threadpool.h>

void task() {
    std::cout << "you run thread 1" << std::endl;
}

void task2() {
    std::cout << "you run thread 2" << std::endl;
}

void task3() {
    std::cout << "you run thread 3" << std::endl;
}

int main() {
    ThreadPool t(2);

    t.AddTask(task);
   // t.AddTask(task2);
   // t.AddTask(task3);

    return 0;
}