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
	inline const jobStat getStatus(){ return status; };
	inline const short getTime(){ return time; };
	inline const short getDirtiness(){ return dirtiness; };
	inline const short getDifficulty(){ return difficulty; };
	inline const int getValue(){ return value; };
};