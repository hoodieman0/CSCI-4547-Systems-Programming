#include "tools.hpp"
#include "enums.hpp"

#pragma once

class Job{
private:
	short time, dirtiness, difficulty;
	int value;
	string kidName;
	jobStat status;
public:
	Job();
	void chooseJob(string name, int jobNumber);
	void announceDone();
};