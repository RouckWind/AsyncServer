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

namespace TCPServer {
    class Server {
        using Socket = int;
        using Listener = int;

        struct Client;

    public:
        void startServer();
        void stopServer();
        bool connect(uint32_t host, uint16_t port);
        void listenSocket();
        void acceptSocket();

    private:
        Socket s_socket;
        Listener s_listener;

        struct sockaddr_in sockaddr;
        std::vector<char> buffer;
        int bytes_read;

        std::set<int> clients;
    };
}  // namespace TCPServer
