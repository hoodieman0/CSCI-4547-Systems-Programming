#include "sharedData.hpp"

void JobTable::
initialize(){
	pthread_mutex_lock(&mtx);
	for(int i = 0; i < 10; i ++){
		jobs[i] = Job();
	}
	pthread_mutex_unlock(&mtx);
}