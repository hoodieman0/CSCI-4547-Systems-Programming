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

	sleep(1);
	for (int i = 0; i < 4; i++){
		errorCode = pthread_kill(threads[i], SIGUSR1);
		if (errorCode) fatal("Failed to sent start signal to thread %d, Error code: %d", i, errorCode);
	}

	for(;;){
		sleep(1);
		curTime = time(NULL);
		if (curTime - startTime >= 21) break;

		findComplete();
	}

	for (int i = 0; i < 4; i++){
		errorCode = pthread_kill(threads[i], SIGQUIT);
		if (errorCode) fatal("Failed to sent quit signal to thread %d, Error code: %d", i, errorCode);
	}

	for (int i = 0; i < 4; i++){
		errorCode = pthread_join(threads[i], NULL);
		if (errorCode) fatal("Error code from pthread_join: %d", errorCode);
	}
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