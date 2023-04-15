#include <vector>
#include "sharedData.hpp"
#include "kid.hpp"

#pragma once

class Mom{
private:
	JobTable jobsTable;
	const string kidNames[4];
	pthread_t threads[4];
	vector<Job> completedJobs;
	time_t startTime, curTime;
public:
	Mom() = default;
	inline void initializeJobs(){ jobsTable.initialize(); }
	void findComplete();
	void run();
	void print();
};