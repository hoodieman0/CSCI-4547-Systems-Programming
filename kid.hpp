#include <vector>
#include "jobTable.hpp"

#pragma once

class Kid{
private:
	string name;
	mood kidMood;
	vector<Job> completedJobs;
	JobTable* jobs;
	void lazyJob();
	void shortJob();
	void cleanJob();
	void greedyJob();
	void anyJob();
public:
	Kid() = default;
	Kid(string kidName, JobTable* table);
	inline void chooseMood(){ kidMood = (mood)(rand() % 5); };
	void pickJob();
	void run();
	stringstream print() const;
};

inline ostream& operator<<(ostream& out, const Kid& k) { return out <<k.print().str(); }