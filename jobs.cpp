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

// Lets other kids know that the current job is done
// Precondition: Job class exists, chooseJob has been run
// Postcondition: Job is completed, done field is set to true
void Job::
announceDone(){
    cout << "Job is done!" << endl;
    // where should I put the done field?
}