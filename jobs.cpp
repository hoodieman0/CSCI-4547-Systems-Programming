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

