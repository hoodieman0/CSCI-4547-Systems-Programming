#ifndef MOM_HPP
#define MOM_HPP

#define MAXCLIENTS 10

#include "tools.hpp"
#include "enums.hpp"
#include "JobTable.hpp"
#include "job.hpp"
#include "Socket.hpp"

typedef pollfd toPoll;

// also known as the server
class Mom {
private:
    JobTable table;

    char hostname[242]; // to store name of local host.
    string process;

    //Socket things
    int port;
    Socket server;
    int currentClients = 0;
    toPoll userFDs[MAXCLIENTS + 1];
    toPoll* const welcome = &userFDs[0];
    toPoll* const worker = &userFDs[1];

public:
    Mom(char* process, int port);
    void startServer();
    void startPolling();
    int doWelcome(int welcomeSock, int* nClip, toPoll* worker, const char* greeting);
    int doService(toPoll* p, short id);

    int getPort(int fd);
    void printsockaddr_in(const char* who, sockaddr_in sock);
};

#endif