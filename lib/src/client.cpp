#include "../inc/client.h"

namespace TCPClient {

    void Client::errorHandler(int n, const std::string& e_msg) {
        std::cout << strerror(errno) << e_msg << std::endl;
    }

    void Client::createSocket() {
        errorHandler(socket(AF_INET, SOCK_STREAM, 0), " create Socket");

        clientaddr.sin_family = AF_INET;
        clientaddr.sin_port = htons(6000);
        clientaddr.sin_addr.s_addr = htonl(INADDR_ANY);
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


    void Client::closeSocket() {
        close(s_socket);
    }

}


