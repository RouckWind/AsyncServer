#pragma once

#include "../inc/threadpool.h"

#include <array>
#include <functional>
#include <list>
#include <netinet/in.h>
#include <string>
#include <sys/epoll.h>
#include <sys/socket.h>

namespace TCPServer {
    class Server {
        using Socket = int;

    public:
        Server();

        Server(const Server&) = delete;
        Server(Server&&) noexcept = delete;
        Server operator=(const Server& other) = delete;
        Server operator=(const Server&& other) = delete;
        ~Server();

        int getClients();

    private:
        static void errorHandler(int n, const std::string& e_msg);
        void acceptLoop();
        void sendData(int fd);
        void readData(int fd, int iter);

    private:
        int epollfd{}, nfds{}, buflen{};
        sockaddr_in server{}, client{};
        Socket s_listener, s_client{};

        static const int bufferSize = 100;
        void* buffer[bufferSize];

        epoll_event ep_event{};
        std::array<epoll_event, 1000> events{};

        std::list<int> clients;
    };
}  // namespace TCPServer
