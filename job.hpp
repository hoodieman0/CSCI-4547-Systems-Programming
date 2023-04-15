#include "tools.hpp"
#include "enums.hpp"

#pragma once

class Job{
private:
	short time, dirtiness, difficulty;
	int value;
	string kidName;
	
public:
	jobStat status;
	Job();
	void chooseJob(string name, int jobNumber);
	void announceDone();
};