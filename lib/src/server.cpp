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
    void Server::errorHandler(int n, std::string e_msg) {
        std::cout << strerror(errno) << e_msg << std::endl;
    }

    void Server::startServer() {
        errorHandler(s_listener = socket(AF_INET, SOCK_STREAM, 0), "start Server");

        server.sin_family = AF_INET;
        server.sin_port = htons(port);
        server.sin_addr.s_addr = htonl(INADDR_ANY);

        errorHandler(bind(s_listener, (struct sockaddr*)&server, sizeof(server)), " bind");

        //pool.AddTask([this] { acceptLoop(); });
        //pool.AddTask([this] { waitLoop(); });
    }

    void Server::acceptLoop() {
        fd_set readset;
        FD_ZERO(&readset);
        FD_SET(s_listener, &readset);

        for (auto it = clients.begin(); it != clients.end(); it++) {
            FD_SET(*it, &readset);
        }

        timeval timeout;
        timeout.tv_sec = 5;
        timeout.tv_usec = 0;

        //int mx = std::max(s_listener, *std::max_element(clients.begin(), clients.end()));
        //errorHandler(select(mx+1, &readset, NULL, NULL, &timeout));

        int len = sizeof(client);
        errorHandler(s_client = accept(s_listener, (struct sockaddr*)&client, reinterpret_cast<socklen_t*>(&len)), " accept");

        //int sock = accept(s_listener, NULL, NULL);
        //errorHandler(FD_ISSET(s_listener, &readset));

        //fcntl(sock, F_SETFL, O_NONBLOCK);

        //clients.insert(sock);

        //pool.AddTask([this] { acceptLoop(); });
    }

    void Server::sendData(const std::string& input) {
        msg.append(input);
        send(s_client, msg.data(), msg.size(), 0);
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
