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
	string kidName;
	jobStat status;

    public: 
    Job();
    Job(string name);
    void print();

    // Setters
    void chooseJob(string name) { kidName = name; status = working; }

    // Getters
    jobStat getStatus() const { return status; };
	short getTime() const { return time; };
	short getDirtiness() const { return dirtiness; };
	short getDifficulty() const { return difficulty; };
	int getValue() const { return value; };
	string getName() const { return kidName; };
};

#endif