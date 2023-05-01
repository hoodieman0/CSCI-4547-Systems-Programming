#include "job.hpp"

int Job::jobTotal = 0;

Job::Job(){
    time = rand() % 5 + 1;
	dirtiness = rand() % 5 + 1;
	difficulty = rand() % 5 + 1;
	value = time * (dirtiness + difficulty);
	status = notStarted;
	id = ++jobTotal;
}

Job::Job(string name){
    jobTotal = 0;
    
    time = rand() % 5 + 1;
	dirtiness = rand() % 5 + 1;
	difficulty = rand() % 5 + 1;
	value = time * (dirtiness + difficulty);
	status = notStarted;
	id = ++jobTotal;

    kidName = name;
}

void Job::print(){
    cout << "Job ID: " << id << endl;
    cout << "Job " << id << " Value: " << value << endl;
    cout << "Job " << id <<" Kid: " << kidName << endl;
    cout << "Job " << id <<" Status: " << status << endl;
}