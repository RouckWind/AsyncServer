#include "../inc/server.h"

#include <algorithm>
#include <cerrno>
#include <cstddef>
#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <string>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

namespace TCPServer {
    void Server::errorHandler(int n, const std::string& e_msg) {
        std::cout << strerror(errno) << e_msg << std::endl;
    }

    Server::Server(){
        errorHandler(s_listener = socket(AF_INET, SOCK_STREAM, 0), " start Server");

        //fcntl(s_listener, F_SETFL, O_NONBLOCK);

        server.sin_family = AF_INET;
        server.sin_port = htons(6000);
        server.sin_addr.s_addr = htonl(INADDR_ANY);
        port = server.sin_port;

        errorHandler(bind(s_listener, (struct sockaddr*)&server, sizeof(server)), " bind");

        acceptLoop();
    }

    void Server::acceptLoop() {
        errorHandler(listen(s_listener, 10), " listen");

        fd_set readset;
        FD_ZERO(&readset);
        FD_SET(s_listener, &readset);

        int len = sizeof(client);
        errorHandler(accept(s_listener, NULL, NULL), " accept");
    }

    void Server::sendData(const std::string& input) {
        //msg.append(input);
        errorHandler(send(s_listener, input.data(), input.size(), 0), " send");
    }

    void Server::writeData() {
        recv(s_client, (void*)msg.data(), msg.size(), 0);
        std::cout << msg << std::endl;
    }

    void Server::waitLoop() {
    }

    Server::~Server() {
        close(s_listener);
        close(s_client);
    }

}  // namespace TCPServer
