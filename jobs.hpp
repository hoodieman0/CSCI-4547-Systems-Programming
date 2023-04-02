#ifndef JOBS_HPP
#define JOBS_HPP

#include "tools.hpp"
#include "enums.hpp"

class Job{
private:
    short Q; // time unit, from 1 (short) to 5 (long)
    short P; // pleasant, from 1 (pleasant) to 5 (unpleasant)
    short E; // easy work, from 1 (easy) to 5 (heavy)
    int value = 0; // Q*(P+E)
    string workerName;
    jobStatus status = INCOMPLETE;

public:
    Job();
    void chooseJob(string kidname, int jobNumber);
    void announceDone();

};

#endif