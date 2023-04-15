#include "job.hpp"
#include "sharedData.hpp"

using namespace std;

int main(){
	srand(time(NULL));
	long i = 5;
	kidMain((void*)i);
}
