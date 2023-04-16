#include "mom.hpp"

void Mom::
findComplete(){
	pthread_mutex_lock(&jobsTable.mtx);
	for (int i = 0; i < 10; i++){
		if (jobsTable.jobs[i].getStatus() == complete){
			completedJobs.push_back(jobsTable.jobs[i]);
			jobsTable.jobs[i] = Job();
		}
	}
	pthread_mutex_unlock(&jobsTable.mtx);
}

void Mom::
run(){
	int errorCode;

	initializeJobs();
	
	// Create kids and add to kid array
	for (int k = 0; k < 4; k++){
		kids[k] = Kid(kidNames[k], &jobsTable);
		kids[k].chooseMood();
	}

	for (int i = 0; i < 4; i++){
		errorCode = pthread_create(&threads[i], NULL, kidMain, (void*)&kids[i]);
		if (errorCode) fatal("Failed to create thread %d, Error code: %d\n", i, errorCode);
	}

	startTime = time(NULL);
}

stringstream Mom::
print() const{
	stringstream ss;

	ss <<"Kids:\n";
	for (int i = 0; i < 4; i++){
		ss <<kids[i] <<"Thread id: " <<threads[i] <<endl;
	}

	return ss;
}