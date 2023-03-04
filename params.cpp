#include <getopt.h>
#include "params.hpp"

// Constructs params class
// Precondition: valid program arguments
// Postcondition: params object is created
Params::
Params(int argc, char* argv[]){
	int ch;

	// Long switch equivalents
	const option longOpts[] = {
		{"verbose", no_argument, nullptr, 'v'},
		{"dir", required_argument, nullptr, 'd'},
		{"help", no_argument, nullptr, 'h'},
		{nullptr, no_argument, nullptr, 0}
	};

	// Switch options
	for(;;){
		ch = getopt_long(argc, argv, "o:d:vhc", longOpts, nullptr);

		if (ch == -1) break;
		switch (ch){
			case 'o': // send to file
				fileOutput = true;
				outFileName = optarg;
				out.open(outFileName, ios::out);
				break;
			case 'd': // search from directory
				directorySearch = true;
				startDir = optarg;
				break;
			case 'v': // print processed files/directories to cout
				verbose = true;
				break;
			case 'c': // is inputted string case sensitive
				caseInsensitive = true;
				break;
			case 'h': // print helpful information to run program
				help = true;
				break;
			default:
				usage();
				break;
		}
	}

	// Convert keywords from cstring to string
	if (argv[optind]){
		keywords.assign(argv[optind]);
	}
}

// Prints the all the data members of the params class
// Precondition: valid Params class
// Postcondition: none
void Params::
print(ostream& out){
	out <<"Start at: " <<(directorySearch ? startDir : "Current directory") <<"\n";
	out <<"Output file name: " <<(fileOutput ? outFileName : "No file specified") <<"\n";
	out <<"Verbose? " <<(verbose ? "Yes" : "No") <<"\n";
	out <<"Ignore case? " <<(caseInsensitive ? "Yes" : "No") <<"\n";
}

// Prints a Unix usage statement on how to execute the command
// Precondition: none
// Postcondition: none
void Params::
usage(){
	cout <<"Usage: sniff [-v||--verbose] [-h ||--help] [-o filename] [-d||--dir directory] [-c] 'Words to search for'" << endl;
}


// Returns the starting directory as a cstring
char* Params::
getStartDir(){
	return startDir;
}


// Returns the boolean value for the passed in switch
bool Params::
getSwitch(char s){
	switch (s){
			case 'o': // send to file
				return fileOutput;
				break;
			case 'd': // search from directory
				return directorySearch;
				break;
			case 'v': // print processed files/directories to cout
				return verbose;
				break;
			case 'c': // is inputted string case sensitive
				return caseInsensitive;
				break;
			case 'h': // print helpful information to run program
				return help;
				break;
			default:
				return false;
				break;
		}
}


// returns the keyword string
const string Params::
getKeywords(){
	return keywords;
}