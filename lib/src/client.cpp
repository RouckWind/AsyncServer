#include "../inc/client.h"

namespace TCPClient {

    void Client::errorHandler(int n, const std::string& e_msg) {
        std::cout << strerror(errno) << e_msg << std::endl;
    }

    Client::Client(const std::string& _message) {
        message = _message;
        errorHandler(c_socket = socket(AF_INET, SOCK_STREAM, 0), " create Socket");

        bzero(&server, sizeof(server));

        server.sin_family = AF_INET;
        server.sin_port = htons(6000);
        server.sin_addr.s_addr = htonl(INADDR_ANY);

        errorHandler(connect(c_socket, reinterpret_cast<sockaddr*>(&server), sizeof(server)), " connect");
        sendData();
        readData();
    }

    void Client::readData() {
        recv(c_socket, buffer, bufferSize, 0);

        std::cout << buffer << std::endl;
    }

    void Client::sendData() {
        send(c_socket, message.c_str(), message.size(), 0);
        std::cout << message << std::endl;
    }

    Client::~Client() {
        close(c_socket);
    }
}


