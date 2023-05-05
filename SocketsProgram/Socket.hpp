#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <unistd.h>
#include <netdb.h>
#include <sys/poll.h>
#include <arpa/inet.h>

#include "tools.hpp"

typedef struct sockaddr_in  sockInfo;

class Socket {
private:
    int fd = -1;
    sockInfo info = {0};
    char* process;

public:
    Socket(char* process);
    in_port_t port() const { return info.sin_port; }
    in_addr addr() const { return info.sin_addr; }
    int sockfd() const { return fd; }

    void refresh();
    int peer(Socket* pr) const;

    void listen(int port);
    void connect(const char* host, int port);

    ostream& print(ostream& out) const;
};

inline ostream& operator <<(ostream& out, const Socket& sn) {
	return sn.print(out); 
    }

#endif