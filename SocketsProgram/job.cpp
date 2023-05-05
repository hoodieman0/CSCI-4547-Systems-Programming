#include "job.hpp"

short Job::jobTotal = 0;

Job::Job(){
    time = rand() % 5 + 1;
	dirtiness = rand() % 5 + 1;
	difficulty = rand() % 5 + 1;
	value = time * (dirtiness + difficulty);
	status = notStarted;
	id = ++jobTotal;
	kid = -1;
}

Job::Job(int name){
    jobTotal = 0;
    
    time = rand() % 5 + 1;
	dirtiness = rand() % 5 + 1;
	difficulty = rand() % 5 + 1;
	value = time * (dirtiness + difficulty);
	status = notStarted;
	id = ++jobTotal;

    kid = name;
}

ostream& Job::print(ostream& out) const{
    out << "Job ID: " << id << endl;
    out << "Job " << id << " Value: " << value << endl;
    out << "Job " << id <<" Kid: " << kid << endl;
    out << "Job " << id <<" Status: " << status << endl;
	return out;
}