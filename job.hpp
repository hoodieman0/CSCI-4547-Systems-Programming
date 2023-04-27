#pragma once

#include "tools.hpp"
#include "enums.hpp"

class Job{
private:
	static int jobTotal;
	short time, dirtiness, difficulty;
	int value;
	string kidName;
	jobStat status;
public:
	int id;
	Job();
	void chooseJob(string name, int jobNumber);
	void announceDone();
	inline jobStat getStatus() const { return status; };
	inline short getTime() const { return time; };
	inline short getDirtiness() const { return dirtiness; };
	inline short getDifficulty() const { return difficulty; };
	inline int getValue() const { return value; };
	inline string getName() const { return kidName; };
};
