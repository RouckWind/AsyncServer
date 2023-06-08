#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <cstddef>
#include <functional>
#include <unistd.h>
#include <fcntl.h>
#include <vector>
#include <string>
#include <set>

namespace TCPServer {
    class Server {
        using Socket = int;
        using Listener = int;

        struct Client;

        void startServer() {
            s_listener = socket(AF_INET, SOCK_STREAM, 0);
            if (s_listener < 0) {
                return;
            }
            fcntl(s_listener, F_SETFL, O_NONBLOCK);
            sockaddr.sin_family = AF_INET;
            sockaddr.sin_port = htons(6000);
            sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
            bind(s_listener, (struct sockaddr*)&sockaddr, sizeof(sockaddr));
        }

        void stopServer(){
            close(s_socket);
        }

        bool connect(uint32_t host, uint16_t port) {
           return true;
        }

        void listenSocket() {
            listen(s_listener, 1);

            fd_set readset;
            FD_ZERO(&readset);
            FD_SET(s_listener, &readset);
        }



        void acceptSocket() {
            s_socket = accept(s_listener, NULL, NULL);

            while (1) {
                bytes_read = recv(s_socket, buffer.data(), buffer.size(), 0);
            }
        }



    private:
        Socket s_socket;
        Listener s_listener;

        struct sockaddr_in sockaddr;
        std::vector<char> buffer;
        int bytes_read;

        std::set<int> clients;

    };
}
