#include <cstddef>
#include <fcntl.h>
#include <functional>
#include <netinet/in.h>
#include <set>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <vector>
#include <iostream>
#include <cstring>

namespace TCPClient {
    class Client {
        using Socket = int;
        using Listener = int;

    public:
        void createSocket();
        bool connect(uint32_t host, uint16_t port);
        void readData();
        void writeData();
        void closeSocket();

    private:
        void errorHandler(int n, const std::string& e_msg);

    private:
        Socket s_socket;
        Listener s_listener;

        struct sockaddr_in clientaddr;
        std::vector<char> buffer;
        int bytes_read;
    };
}  // namespace TCPServer
