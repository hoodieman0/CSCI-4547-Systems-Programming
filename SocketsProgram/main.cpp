#include "mom.hpp"

using namespace std;

#define PORT 1099

int main(int argc, char* argv[]){
	srand(time(NULL));
	Mom m(argv[0], PORT);
    m.startServer();
	bye();
}

