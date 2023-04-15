#include "job.hpp"

using namespace std;

int main(){
	srand(time(NULL));
	Job j;
	cout <<j.status <<endl;
	j.chooseJob("test", 6);
	cout <<j.status <<endl;
	j.announceDone();
	cout <<j.status <<endl;
}