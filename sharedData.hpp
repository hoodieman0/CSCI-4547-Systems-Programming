#include <pthread.h>
#include "job.hpp"

#pragma once

class JobTable{
public:
	Job jobs[10];
	pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
	bool quitflag = false;
	void initialize();
};

static void* kidMain(void* arg){
	// Cast arg to Kid and call Kid::run
	return nullptr;
}