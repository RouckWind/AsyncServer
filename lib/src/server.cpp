#include "../inc/server.h"

#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <string>
#include <unistd.h>

namespace TCPServer {
    void Server::errorHandler(int n, const std::string& e_msg) {
        std::cerr << strerror(n) << e_msg << std::endl;
    }

    Server::Server() {
        //create server socket
        s_listener = socket(AF_INET, SOCK_STREAM, 0);

        // write parameters of server socket
        server.sin_family = AF_INET;
        server.sin_port = htons(6000);
        server.sin_addr.s_addr = htonl(INADDR_ANY);

        //bind local address to socket
        bind(s_listener, reinterpret_cast<sockaddr*>(&server), sizeof(server));

        // start listening connection on socket
        listen(s_listener, 10);

        acceptLoop();
    }

    void Server::acceptLoop() {
        // create epoll for waiting i/o events from connections
        epollfd = epoll_create1(0);

        // add first event
        ep_event.events = EPOLLIN;
        ep_event.data.fd = s_listener;

        epoll_ctl(epollfd, EPOLL_CTL_ADD, s_listener, &ep_event);
        while (true) {
            nfds = epoll_wait(epollfd, events.data(), events.size(), -1);
            auto addrlen = sizeof(server);
            for (int i = 0; i < nfds; ++i) {
                if (events[i].data.fd == s_listener) {
                    // accept incoming connection
                    s_client = accept(s_listener, reinterpret_cast<sockaddr*>(&client), reinterpret_cast<socklen_t*>(&addrlen));

                    //set nonblocking
                    fcntl(s_client, F_SETFL, O_NONBLOCK);

                    ep_event.events = EPOLLIN;
                    ep_event.data.fd = s_client;

                    // add new client to epoll
                    errorHandler(epoll_ctl(epollfd, EPOLL_CTL_ADD, s_client, &ep_event), " epoll_ctl");

                    // add client to clients list
                    clients.push_back(s_client);

                } else {
                    int clientfd = events[i].data.fd;
                    readData(clientfd, i);
                }
            }
        }
    }

    void Server::readData(int fd, int iter) {
        buflen = recv(fd, buffer, bufferSize, 0);
        if (buflen == 0) {
            close(fd);
            epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, &events[iter]);
            clients.pop_back();
        } else {
            sendData(fd);
        }
    }

    void Server::sendData(int fd) {
        buflen = send(fd, buffer, bufferSize, 0);
    }

    Server::~Server() {
        close(s_listener);
        close(s_client);
        close(epollfd);
    }
    int Server::getClients() {
        return clients.size();
    }
}  // namespace TCPServer
