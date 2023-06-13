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
        Server(Server&&) = default;
        ~Server();

        void startServer();
        void sendData(const std::string& input);
        void writeData();

        unsigned int getClients() { return clients.size(); };

    private:
        static void errorHandler(int n, std::string e_msg);
        void acceptLoop();
        void waitLoop();

    private:
        Socket s_listener, s_client;

        struct sockaddr_in server, client;
        std::vector<std::string> buffer;
        std::string msg;

        std::set<int> clients;
        short port;

        ThreadPool pool{3};
    };
}  // namespace TCPServer
