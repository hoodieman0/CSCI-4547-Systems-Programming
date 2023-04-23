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
	}

	for (int i = 0; i < 4; i++){
		errorCode = pthread_create(&threads[i], NULL, kidMain, (void*)&kids[i]);
		if (errorCode) fatal("Failed to create thread %d, Error code: %d\n", i, errorCode);
	}
	cout <<"Threads created\n";

	startTime = time(NULL);

	sleep(.5);
	for (int i = 0; i < 4; i++){
		errorCode = pthread_kill(threads[i], SIGUSR1);
		if (errorCode) fatal("Failed to sent start signal to thread %d, Error code: %d", i, errorCode);
	}
	cout <<"Start signals sent\n";

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
	cout <<"Quit signals sent\n";

	for (int i = 0; i < 4; i++){
		errorCode = pthread_join(threads[i], NULL);
		if (errorCode) fatal("Error code from pthread_join: %d", errorCode);
	}
	findComplete();

	cout <<"Threads rejoined\n";
	cout <<"Completed Jobs: " <<completedJobs.size() <<endl;
	int kidMoney[4] = {0, 0, 0, 0};
	for (Job j : completedJobs){
		string tempName = j.getName();
		if (tempName == kidNames[0]){
			kidMoney[0] += j.getValue();
		}
		else if (tempName == kidNames[1]){
			kidMoney[1] += j.getValue();
		}	
		else if (tempName == kidNames[2]){
			kidMoney[2] += j.getValue();
		}
		else if (tempName == kidNames[3]){
			kidMoney[3] += j.getValue();
		}
	}
	for (int i = 0; i < 4; i++){
		cout <<kidNames[i] <<" Money: " <<kidMoney[i] <<endl;
	}
}

stringstream Mom::
print() const{
	stringstream ss;

	ss <<"Kids:\n";
	for (int i = 0; i < 4; i++){
		ss <<kids[i] <<endl;
	}

	return ss;
}