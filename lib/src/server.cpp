#include "../inc/server.h"

#include <cerrno>
#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <string>
#include <unistd.h>

namespace TCPServer {
    using Task = std::function<void()>;

    void Server::errorHandler(int n, const std::string& e_msg) {
        std::cerr << strerror(n) << e_msg << std::endl;
    }

    Server::Server() {
        errorHandler(s_listener = socket(AF_INET, SOCK_STREAM, 0), " start Server");

        //fcntl(s_listener, F_SETFL, O_NONBLOCK);

        server.sin_family = AF_INET;
        server.sin_port = htons(6000);
        server.sin_addr.s_addr = htonl(INADDR_ANY);

        errorHandler(bind(s_listener, (struct sockaddr*)&server, sizeof(server)), " bind");
        errorHandler(listen(s_listener, 10), " listen");

        //auto pool = ThreadPool::create(3);

        acceptLoop();
        //sendData("test\n");
        //writeData();

        //pool->AddTask(acceptLoop());
        //pool->AddTask(sendData("test\n"));
        //pool->AddTask(writeData());
    }

    Task Server::acceptLoop() {
        errorHandler(epollfd = epoll_create1(0), " epoll");

        e_event.events = EPOLLIN;
        e_event.data.fd = s_listener;

        errorHandler(epoll_ctl(epollfd, EPOLL_CTL_ADD, s_listener, &e_event), " epoll_ctl");
        while (true) {
            errorHandler(nfds = epoll_wait(epollfd, events, 10, -1), " epoll_wait");
            auto addrlen = sizeof(server);
            for ( int n = 0; n < nfds; ++n) {
                if(events[n].data.fd == s_listener) {
                    s_client = accept(s_listener, reinterpret_cast<sockaddr*>(&client), reinterpret_cast<socklen_t*>(&addrlen));
                    fcntl(s_client, F_SETFL, O_NONBLOCK);
                    epoll_ctl(epollfd, EPOLL_CTL_ADD, s_client, &e_event);
                    clients.push_back(s_client);
                    sendData("Hello\n");
                } else {
                    handleMessage(events[n].data.fd);
                    break;
                }
            }
        }

    }

    Task Server::sendData(const std::string& input) {
        errorHandler(bufferSize = send(s_client, input.data(), input.size(), 0), " send");
    }

    Task Server::writeData() {
        errorHandler(recv(s_client, (void*)buffer.data(), 1024, 0), " write");
    }

    void Server::waitLoop() {
    }

    Server::~Server() {
        std::cout << "destructor" << std::endl;
        close(s_listener);
        close(s_client);
        close(epollfd);
    }

    int Server::handleMessage(int c_fd) {
        char buff[100], mess[100];

        bzero(buff, 100);
        bzero(mess, 100);

        int len = recv(s_client, buff, 100, 0);
        if (len == 0) {
            clients.remove(c_fd);
        } else {
            if(clients.size() == 1) {
                send(s_client, "NO ONE CONNECTED", strlen("NO ONE CONNECTED"), 0);
                return len;
            }
            sprintf(mess, "Client ", c_fd, buff);
            for (int & cl : clients) {
                if (cl != c_fd) {
                    send(cl, mess, 100, 0);
                }
            }
        }
        return len;
    }
}  // namespace TCPServer
