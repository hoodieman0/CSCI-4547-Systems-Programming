#pragma once

#include <vector>
#include "kid.hpp"

class Mom{
private:
	JobTable jobsTable;
	const string kidNames[4] = {"Kid 1", "Kid 2", "Kid 3", "Kid 4"};
	Kid kids[4];
	pthread_t threads[4];
	vector<Job> completedJobs;
	time_t startTime, curTime;

	inline void initializeJobs(){ jobsTable.initialize(); };
public:
	Mom() = default;
	void findComplete();
	void run();
	stringstream print() const;
};

inline ostream& operator<<(ostream& out, const Mom& m){ return out <<m.print().str(); };

static void* kidMain(void* arg){
	Kid* k = (Kid*)arg;
	k->run();
	pthread_exit(NULL);
}
