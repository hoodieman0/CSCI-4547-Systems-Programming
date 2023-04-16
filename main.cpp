#include "mom.hpp"

using namespace std;

int main(){
	srand(time(NULL));
	Mom m;
	Kid k("test", nullptr);
	m.run();
	cout <<m;
	//m.initializeJobs();
	//k.chooseMood();
	//k.pickJob();
}

