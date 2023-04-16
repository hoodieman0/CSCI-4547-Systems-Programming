#include "kid.hpp"

Kid::
Kid(string kidName, JobTable* table) : name(kidName), jobs(table){

}

void Kid::
pickJob(){
	switch (kidMood){
		case lazy:
			lazyJob();
			break;
		case overtired:
			shortJob();
			break;
		case prissy:
			cleanJob();
			break;
		case greedy:
			greedyJob();
			break;
		case cooperative:
			anyJob();
			break;
	}
	cout <<"Complete\n";
}

void Kid::
lazyJob(){
	int jobIndex;
	short compare, difficulty = 6;

	pthread_mutex_lock(&jobs->mtx);
	for (int i = 0; i < 10; i++){
		compare = jobs->jobs[i].getDifficulty();
		if (jobs->jobs[i].getStatus() == notStarted && compare < difficulty){
			jobIndex = i;
			difficulty = compare;
		}
	}

	jobs->jobs[jobIndex].chooseJob(name, jobIndex);
	pthread_mutex_unlock(&jobs->mtx);
}

void Kid::
shortJob(){
	int jobIndex;
	short compare, time = 6;

	pthread_mutex_lock(&jobs->mtx);
	for (int i = 0; i < 10; i++){
		compare = jobs->jobs[i].getTime();
		if (jobs->jobs[i].getStatus() == notStarted && compare < time){
			jobIndex = i;
			time = compare;
		}
	}

	jobs->jobs[jobIndex].chooseJob(name, jobIndex);
	pthread_mutex_unlock(&jobs->mtx);
}

void Kid::
cleanJob(){
	int jobIndex;
	short compare, dirtiness = 6;

	pthread_mutex_lock(&jobs->mtx);
	for (int i = 0; i < 10; i++){
		compare = jobs->jobs[i].getDirtiness();
		if (jobs->jobs[i].getStatus() == notStarted && compare < dirtiness){
			jobIndex = i;
			dirtiness = compare;
		}
	}

	jobs->jobs[jobIndex].chooseJob(name, jobIndex);
	pthread_mutex_unlock(&jobs->mtx);
}

void Kid::
greedyJob(){
	int jobIndex;
	short compare, value = 6;

	pthread_mutex_lock(&jobs->mtx);
	for (int i = 0; i < 10; i++){
		compare = jobs->jobs[i].getValue();
		if (jobs->jobs[i].getStatus() == notStarted && compare < value){
			jobIndex = i;
			value = compare;
		}
	}

	jobs->jobs[jobIndex].chooseJob(name, jobIndex);
	pthread_mutex_unlock(&jobs->mtx);
}

void Kid::
anyJob(){
	int jobIndex;

	pthread_mutex_lock(&jobs->mtx);
	for (int i = 0; i < 10; i++){
		if (jobs->jobs[i].getStatus() == notStarted){
			jobIndex = i;
			break;
		}
	}

	jobs->jobs[jobIndex].chooseJob(name, jobIndex);
	pthread_mutex_unlock(&jobs->mtx);
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

	return ss;
}