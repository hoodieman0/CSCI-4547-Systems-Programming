#include "kid.hpp"

Kid::
Kid(int kidID) : name(kidID){ chooseMood(); }

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

	jobs->jobs[jobIndex].chooseJob(name);

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

	jobs->jobs[jobIndex].chooseJob(name);

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

	jobs->jobs[jobIndex].chooseJob(name);

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

	jobs->jobs[jobIndex].chooseJob(name);

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

	jobs->jobs[jobIndex].chooseJob(name);

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