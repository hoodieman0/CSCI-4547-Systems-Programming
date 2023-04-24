#include "kid.hpp"

Kid::
Kid(string kidName, JobTable* table) : name(kidName), jobs(table){}

void Kid::
run(){
	stringstream output;
	Job* curJob;
	int signo;
	sigset_t signals;

	sigemptyset(&signals);
	sigaddset(&signals, SIGUSR1);
	pthread_sigmask(SIG_BLOCK, &signals, NULL);

	struct sigaction sigAct = {Kid::signalHandler, signals, 0};
	sigaction(SIGQUIT, &sigAct, NULL);

	chooseMood();
	sigwait(&signals, &signo);

	if (signo == SIGUSR1){
		cout <<"SIGUSR1 received\n";
		for (;;){
			pthread_mutex_lock(&jobs->mtx);
			curJob = pickJob();
			pthread_mutex_unlock(&jobs->mtx);
			
			sleep(curJob->getTime());
			if (quitflag) break;
			else{
				pthread_mutex_lock(&jobs->mtx);
				curJob->announceDone();
				completedJobs.push_back(*curJob);
				pthread_mutex_unlock(&jobs->mtx);
			}
		}
	}
	output <<"Quit signal received\n";

	int moneyEarned = 0;
	for (Job j : completedJobs){
		moneyEarned += j.getValue();
	}

	output <<name <<" completed jobs: \n";
	for (long unsigned i = 0; i < completedJobs.size(); i++){
		output <<"Job " <<completedJobs[i].id <<", Value: " <<setw(3) <<completedJobs[i].getValue() <<endl;
	}
	output <<"Total money earned: " <<moneyEarned <<endl;
	cout <<output.str();
}

Job* Kid::
pickJob(){
	switch (kidMood){
		case lazy:
			return lazyJob();
		case overtired:
			return shortJob();
		case prissy:
			return cleanJob();
		case greedy:
			return greedyJob();
		case cooperative:
			return anyJob();
		default:
			return nullptr;
	}
}

Job* Kid::
lazyJob(){
	int jobIndex;
	short compare, difficulty = 6;

	for (int i = 0; i < 10; i++){
		compare = jobs->jobs[i].getDifficulty();
		if (jobs->jobs[i].getStatus() == notStarted && compare < difficulty){
			jobIndex = i;
			difficulty = compare;
		}
	}

	jobs->jobs[jobIndex].chooseJob(name, jobIndex);

	return &jobs->jobs[jobIndex];
}

Job* Kid::
shortJob(){
	int jobIndex;
	short compare, time = 6;

	for (int i = 0; i < 10; i++){
		compare = jobs->jobs[i].getTime();
		if (jobs->jobs[i].getStatus() == notStarted && compare < time){
			jobIndex = i;
			time = compare;
		}
	}

	jobs->jobs[jobIndex].chooseJob(name, jobIndex);

	return &jobs->jobs[jobIndex];
}

Job* Kid::
cleanJob(){
	int jobIndex;
	short compare, dirtiness = 6;

	for (int i = 0; i < 10; i++){
		compare = jobs->jobs[i].getDirtiness();
		if (jobs->jobs[i].getStatus() == notStarted && compare < dirtiness){
			jobIndex = i;
			dirtiness = compare;
		}
	}

	jobs->jobs[jobIndex].chooseJob(name, jobIndex);

	return &jobs->jobs[jobIndex];
}

Job* Kid::
greedyJob(){
	int jobIndex;
	short compare, value = 0;

	for (int i = 0; i < 10; i++){
		compare = jobs->jobs[i].getValue();
		if (jobs->jobs[i].getStatus() == notStarted && compare > value){
			jobIndex = i;
			value = compare;
		}
	}

	jobs->jobs[jobIndex].chooseJob(name, jobIndex);

	return &jobs->jobs[jobIndex];
}

Job* Kid::
anyJob(){
	int jobIndex;

	for (int i = 0; i < 10; i++){
		if (jobs->jobs[i].getStatus() == notStarted){
			jobIndex = i;
			break;
		}
	}

	jobs->jobs[jobIndex].chooseJob(name, jobIndex);

	return &jobs->jobs[jobIndex];
}

stringstream Kid::
print() const{
	stringstream ss;

	ss <<"Kid Name: " <<name <<"\tMood: ";
	switch (kidMood){
		case lazy:
			ss <<setw(12) <<"Lazy ";
			break;
		case prissy:
			ss <<setw(12) <<"Prissy ";
			break;
		case overtired:
			ss <<setw(12) <<"Overtired ";
			break;
		case greedy:
			ss <<setw(12) <<"Greedy ";
			break;
		case cooperative:
			ss <<setw(12) <<"Cooperative ";
			break;
	}
	ss <<"Num jobs: " <<completedJobs.size() <<" ";

	return ss;
}