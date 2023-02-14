#include <fstream>
#include <iostream>

using namespace std;

class Params{
private:
	char* startDir;
	char* outFileName;
	ofstream out;
	// Switches: v, h, o, d, c
	bool verbose, help, fileOutput, directorySearch, caseInsensitive = false;
public:
	Params(int argc, char* argv[]);
	~Params() = default;

	void print();
	void usage();
};