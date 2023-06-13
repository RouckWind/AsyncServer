#pragma once

#include "../inc/threadpool.h"

#include <functional>
#include <netinet/in.h>
#include <set>
#include <string>
#include <sys/socket.h>
#include <vector>

namespace TCPServer {
    class Server {
        using Socket = int;

    public:
        explicit Server(short _port)
            : s_client{}
            , s_listener{}
            , server{}
            , client{}
            , msg{}
            , buffer{}
            , port{_port} {};

        Server(const Server&) = delete;
        Server(const Server&&) = delete;
        ~Server();

        void serverStart();
        unsigned int getClients();
        std::function<void()> sendData(const std::string& input);
        void writeData();


    private:
        static auto errorHandler();
        void acceptLoop();
        void waitLoop();

    private:
        Socket s_listener, s_client;

        struct sockaddr_in server, client;
        std::vector<std::string> buffer;
        std::string msg;

        std::set<int> clients;
        short port;

        ThreadPool pool{ 3 };
    };
}  // namespace TCPServer
