#include "mom.hpp"

void Mom::
findComplete(){
	for (int i = 0; i < 10; i++){
		if (jobsTable.jobs[i].isComplete()){
			completedJobs.push_back(jobsTable.jobs[i]);
			jobsTable.jobs[i] = Job();
		}
	}
}

void Mom::
run(){
	initializeJobs();
	// Initialize kids
}