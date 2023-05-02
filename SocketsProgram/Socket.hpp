#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <unistd.h>
#include <netdb.h>
#include <sys/poll.h>
#include <arpa/inet.h>

#include "tools.hpp"

class Socket {
private:
    int fd = -1;
    sockaddr_in info = {0};

public:
    Socket();
    in_port_t port() const { return info.sin_port; }
    in_addr addr() const { return info.sin_addr; }
    int sockfd() const { return fd; }

    void refresh();
    int peer(Socket* pr) const;

    void listen(int port);
    void connect(const char* host, int port);

    ostream& print(ostream& out) const;
};

#endif