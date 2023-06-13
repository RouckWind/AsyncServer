#include "../inc/client.h"

namespace TCPClient {

    void Client::createSocket() {
        s_listener = socket(AF_INET, SOCK_STREAM, 0);
        if (s_listener < 0) {
            return;
        }
        fcntl(s_listener, F_SETFL, O_NONBLOCK);
        sockaddr.sin_family = AF_INET;
        sockaddr.sin_port = htons(6000);
        sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    }

    void Client::closeSocket() {
        close(s_socket);
    }

    bool Client::connect(uint32_t host, uint16_t port) {
        return true;
    }

    void Client::readData() {
        while (1) {
            bytes_read = recv(s_socket, buffer.data(), buffer.size(), 0);
        }
    }

    void Client::writeData() {
    }
}


