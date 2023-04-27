#pragma once

#include <pthread.h>
#include "job.hpp"

static bool quitflag = false;

class JobTable{
public:
	Job jobs[10];
	pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
	void initialize();
};
