#include <iostream>
#include <server.h>
#include <thread>
#include <threadpool.h>

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
    // TODO: need check of task counters and threads counters
    ThreadPool t(2);
    TCPServer::Server server(6000);

    //t.AddTask(server.sendData("Hello"));
    //t.AddTask(server.sendData());
    server.startServer();

    //server.sendData("Hello\n");
    //server.getClients();

    //server.readData();
    return 0;
}