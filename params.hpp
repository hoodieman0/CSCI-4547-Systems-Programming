/*
CSCI-4547 Systems Programming
params.hpp
Author: Sean Vargas
Created: 13 Feb 2023
Last edited: 13 Feb 2023
*/

#include <fstream>
#include <iostream>
#include <vector>
#include <filesystem>
#include <cstring>

using namespace std;

class Params{
private:
	char* startDir;
	char* outFileName;
	ofstream out;
	vector<string> keywords;
	// Switches: v, h, o, d, c
	bool verbose = false, help = false, fileOutput = false, directorySearch = false, caseInsensitive = false;
public:
	Params(int argc, char* argv[]);
	~Params() { if(!directorySearch) delete[] startDir; }

	void print(ostream& out);
	void usage();
};