#include "params.hpp"
#include "FileID.hpp"
#include "tools.hpp"
#include "sniff.hpp"

using namespace std;

int main(int argc, char* argv[]){
	banner();
	Params p(argc, argv);
	Sniff s(p);
	s.run();
}