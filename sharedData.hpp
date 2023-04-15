#include <pthread.h>
#include "tools.hpp"
#include "job.hpp"

#pragma once

class JobTable{
private:
	Job jobs[10];
	pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
	bool quitflag = false;
};

static void* kidMain(void* arg){
	// Cast arg to Kid and call Kid::run
}