#pragma once

#include "../inc/threadpool.h"

#include <array>
#include <functional>
#include <netinet/in.h>
#include <string>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <list>

namespace TCPServer {
    class Server {
    public:
        using Task = std::function<void()>;
        using Socket = int;

    public:
        Server();

        Server(const Server&) = delete;
        Server(Server&&) noexcept = default;
        //TODO rule of 5
        ~Server();

        Task sendData(const std::string& input);
        Task writeData();

        [[nodiscard]] unsigned int getClients() { return clients.size(); };
        void setPort(int n) { port = n; };
        [[nodiscard]] int getPort() { return port; }

    private:
        static void errorHandler(int n, const std::string& e_msg);
        Task acceptLoop();
        void waitLoop();

    private:
        Socket s_listener, s_client{};

        sockaddr_in server{}, client{};

        int epollfd, nfds;

        std::string buffer{};

        epoll_event e_event, events[10];
        std::list<int> clients;
        int port;
        int bufferSize;
        int handleMessage(int client);
    };
}  // namespace TCPServer
