#include "mom.hpp"

void Mom::
findComplete(){
	pthread_mutex_lock(&jobsTable.mtx);
	for (int i = 0; i < 10; i++){
		if (jobsTable.jobs[i].isComplete()){
			completedJobs.push_back(jobsTable.jobs[i]);
			jobsTable.jobs[i] = Job();
		}
	}
	pthread_mutex_unlock(&jobsTable.mtx);
}

void Mom::
run(){
	initializeJobs();
	// Initialize kids
}