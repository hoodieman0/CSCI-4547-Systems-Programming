#include "sharedData.hpp"

class Kid{
private:
	string name;
	mood kidMood;
	vector<Job> completedJobs;
	JobTable* jobs;
public:
	Kid(string kidName, JobTable* table);
	void chooseMood();
	void pickJob();
	void run();
	void print();
};