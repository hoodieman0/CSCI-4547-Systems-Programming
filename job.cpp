#include "job.hpp"

int Job::jobTotal = 0;

Job::
Job(){
	time = rand() % 5 + 1;
	dirtiness = rand() % 5 + 1;
	difficulty = rand() % 5 + 1;
	value = time * (dirtiness + difficulty);
	status = notStarted;
	id = ++jobTotal;
}

void Job::
chooseJob(string name, int jobNumber){ 
	kidName = name;
	status = working;
}

void Job::
announceDone(){
	status = complete;
}
