#pragma once

#include <vector>
#include <signal.h>
#include "jobTable.hpp"

class Kid{
private:
	string name;
	mood kidMood;
	vector<Job> completedJobs;
	JobTable* jobs;

	Job* lazyJob();
	Job* shortJob();
	Job* cleanJob();
	Job* greedyJob();
	Job* anyJob();
	static void signalHandler(int sig){ if (sig == SIGQUIT) quitflag = true; };
public:
	Kid() = default;
	Kid(string kidName, JobTable* table);
	void run();
	Job* pickJob();
	stringstream print() const;
	inline void chooseMood(){ kidMood = (mood)(rand() % 5); };
};

inline ostream& operator<<(ostream& out, const Kid& k) { return out <<k.print().str(); }
