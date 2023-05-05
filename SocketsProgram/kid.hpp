#ifndef KID_HPP
#define KID_HPP

#include <vector>
#include <signal.h>
#include "jobTable.hpp"

class Kid{
private:
	int name;
	mood kidMood;
	vector<Job> completedJobs;
	JobTable* jobs;

	Job* lazyJob();
	Job* shortJob();
	Job* cleanJob();
	Job* greedyJob();
	Job* anyJob();
public:
	Kid() = default;
	Kid(int kidID);
	int getID() const { return name; }
	mood getMood() const { return kidMood; }
	void run();
	void setTable(JobTable* table) { jobs = table;}
	Job* pickJob();
	stringstream print() const;
	inline void chooseMood(){ kidMood = (mood)(rand() % 5); };
};

inline ostream& operator<<(ostream& out, const Kid& k) { return out <<k.print().str(); }

#endif