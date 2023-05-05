#ifndef JOB_HPP
#define JOB_HPP

#include <string>
#include "tools.hpp"
#include "enums.hpp"

using namespace std;

class Job {
    private:
	static int jobTotal;
    short id; 
	short time, dirtiness, difficulty;
	short value;
	int kid;
	jobStat status;

    public: 
    Job();
    Job(int name);
    void print();

    // Setters
    void chooseJob(int kidID) { kid = kidID; status = working; }

    // Getters
    jobStat getStatus() const { return status; };
	short getTime() const { return time; };
	short getDirtiness() const { return dirtiness; };
	short getDifficulty() const { return difficulty; };
	int getValue() const { return value; };
	int getID() const { return kid; };
};

#endif