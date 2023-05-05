#ifndef JOBTABLE_HPP
#define JOBTABLE_HPP

#include "job.hpp"

class JobTable {
    public: 
    Job jobs[10];

    JobTable() { 
        for(int i = 0; i < 10; i ++){
		    jobs[i] = Job();
	    }
    }
    void chooseJob(short jobID, short kidID){

    }
};

#endif