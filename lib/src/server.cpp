#include "../inc/server.h"

#include <cerrno>
#include <cstddef>
#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>
#include <algorithm>


namespace TCPServer {
    auto Server::errorHandler() {
        return strerror(errno);
    }

    void Server::serverStart() {
        s_listener = socket(AF_INET, SOCK_STREAM, 0);
        if (s_listener < 0) {
            return;
        }
        server.sin_family = AF_INET;
        server.sin_port = htons(port);
        server.sin_addr.s_addr = htonl(INADDR_ANY);

        if (bind(s_listener, (struct sockaddr*)&server, sizeof(server)) < 0) {
            std::cout << errorHandler() << std::endl;
            return;
        }

        pool.AddTask([this] { acceptLoop(); });
        pool.AddTask([this] { waitLoop(); });
    }

    std::function<void()> Server::sendData(const std::string& input) {
        msg.append(input);
        send(s_client, msg.data(), msg.size(), 0);
    }

    void Server::writeData() {
        recv(s_client, (void*)msg.data(), msg.size(), 0);
        std::cout << msg << std::endl;
    }

    unsigned int Server::getClients() {
        return clients.size();
    }

    Server::~Server() {
        close(s_listener);
        close(s_client);
    }

    void Server::acceptLoop() {
        fd_set readset;
        FD_ZERO(&readset);
        FD_SET(s_listener, &readset);

        for (auto it = clients.begin(); it != clients.end(); it++){
            FD_SET(*it, &readset);
        }

        timeval timeout;
        timeout.tv_sec = 5;
        timeout.tv_usec = 0;

        int mx = std::max(s_listener, *std::max_element(clients.begin(), clients.end()));
        if (select(mx+1, &readset, NULL, NULL, &timeout) <= 0) {
            std::cout << errorHandler() << std::endl;
        };

        int len = sizeof(client);
        s_client = accept(s_listener, (struct sockaddr*)&client, reinterpret_cast<socklen_t*>(&len));

        if (s_client < 0) {
            std::cout << "3 " << errorHandler() << std::endl;
        }

        int sock = accept(s_listener, NULL, NULL);
        if(FD_ISSET(s_listener, &readset)) {
            std::cout << errorHandler() << std::endl;
        }
        fcntl(sock, F_SETFL, O_NONBLOCK);

        clients.insert(sock);


        pool.AddTask([this] { acceptLoop(); });
    }

    void Server::waitLoop() {

    }

}  // namespace TCPServer
