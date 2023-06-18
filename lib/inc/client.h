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

    public:
        Client() = delete;
        explicit Client(const std::string& message);
        ~Client();

    private:
        void errorHandler(int n, const std::string& e_msg);
        void readData();
        void sendData();

    private:
        Socket c_socket;

        sockaddr_in server;

        static const int bufferSize = 100;
        char buffer[bufferSize];

        std::string response;

        std::string message;
    };
}  // namespace TCPServer
