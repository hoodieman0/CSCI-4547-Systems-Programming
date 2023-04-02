#include "jobs.hpp"

// Default Constructor that initializes all variables. Uses rand() to
// randomize the values
// Precondition: None
// Postcondition: Job class is created
Job::
Job(){
    srand(time(nullptr));
    Q = rand() % 5 + 1;
    P = rand() % 5 + 1;
    E = rand() % 5 + 1;
    value = Q * (P + E);
    workerName = "";
}

// Claims the job for the given kid, preventing others from 
// claiming the job
// Precondition: Job class exists, kid class exists
// Postcondition: Job is claimed by kidname
void Job::
chooseJob(string kidname, int jobNumber){
    workerName = kidname;
    // what do I do with jobNumber?
}
