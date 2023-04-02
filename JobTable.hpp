#ifndef JOBTABLE_HPP
#define JOBTABLE_HPP

#include "tools.hpp"
#include "jobs.hpp"

class JobTable{
private:
    Job table[10];
    // TODO check this variable syntax
    pthread_mutex_t myMutex = PTHREAD_MUTEX_INITIALIZER;
    bool quitFlag = false;

public:
    JobTable();
};

#endif