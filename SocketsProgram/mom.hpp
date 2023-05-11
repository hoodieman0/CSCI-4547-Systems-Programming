#ifndef MOM_HPP
#define MOM_HPP

#define MAXCLIENTS 3
#define TIMERMAX 21
#include <vector>

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
    vector<Job> completedJobs; // keep track of all completed jobs

    char hostname[242]; // to store name of local host.
    string process; // used to print the executable name

    //timer stuff
    time_t startTime = 0;
    time_t curTime = 0;

    // Socket things
    int port; // what port the welcome socket is on
    Socket server; // Socket class creation

    int currentClients = 0;
    int totalClients = 0;

    toPoll userFDs[MAXCLIENTS + 1];
    toPoll* const welcome = &userFDs[0]; // welcome socket polling info
    toPoll* const worker = &userFDs[1]; // start of client polling info

public:
    Mom(char* process, int port);
    void startServer();
    void startPolling();
    int doWelcome(int welcomeSock, int* nClip, toPoll* worker, const char* greeting);
    int doService(toPoll* p, short id);
    
    // paired with function isTimerFinished()
    void startTimer() { startTime = time(NULL); }

    // startTimer() must be run before isTimerFinished() is called
    bool isTimerFinished() { curTime = time(NULL); return (curTime - startTime >= TIMERMAX) ? true : false; }

    int getPort(int fd);
    void printsockaddr_in(const char* who, sockaddr_in sock);

    void countAllowance();
};

#endif