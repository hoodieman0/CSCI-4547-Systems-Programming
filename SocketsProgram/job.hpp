#ifndef JOB_HPP
#define JOB_HPP

#include <string>
#include "tools.hpp"
#include "enums.hpp"

using namespace std;

class Job {
    private:
	static short jobTotal;
    short id; 
	short time, dirtiness, difficulty;
	short value;
	short kid;
	jobStat status;

    public: 
    Job();
    Job(int name);
    ostream& print(ostream& out) const;

    // Setters
    void chooseJob(int kidID) { kid = kidID; status = working; }

    // Getters
    jobStat getStatus() const { return status; };
	short getTime() const { return time; };
	short getDirtiness() const { return dirtiness; };
	short getDifficulty() const { return difficulty; };
	int getValue() const { return value; };
	short getID() const { return id; };
    short getKid() const { return kid; }
};

inline ostream& operator<<(ostream& out, const Job& j) { return j.print(out); }

#endif