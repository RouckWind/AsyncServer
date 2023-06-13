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
        Server();

        Server(const Server&) = delete;
        Server(Server&&) = default;
        ~Server();

        void startServer();
        void sendData(const std::string& input);
        void writeData();

        unsigned int getClients() { return clients.size(); };
        void setPort(int n) { port = n; };
        int getPort() { return port; }

    private:
        static void errorHandler(int n, const std::string& e_msg);
        void acceptLoop();
        void waitLoop();

    private:
        Socket s_listener, s_client{};

        struct sockaddr_in server{}, client{};
        std::vector<std::string> buffer;
        std::string msg;

        std::set<int> clients;
        int port;

        ThreadPool pool{3};
    };
}  // namespace TCPServer
