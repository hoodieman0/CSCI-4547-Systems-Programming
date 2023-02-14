#include <getopt.h>
#include "params.hpp"

// Constructs params class
// Precondition: valid program arguments
// Postcondition: params object is created
Params::
Params(int argc, char* argv[]){
	int ch, optx;

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
			default:
				usage();
				break;
		}
	}

	// Ending Arguments
	cout << "Ending Arguments: ";
	for (optx = optind; optx < argc; optx++){
		cout <<argv[optx] << " ";
	}
}

// Prints the all the data members of the params class
// Precondition: valid Params class
// Postcondition: none
void Params::
print(){
	if (fileOutput){
		out <<"Start at: " <<(directorySearch ? startDir : "Current directory") <<"\n";
		out <<"Output file name: " <<outFileName <<"\n";
		out <<"Verbose? " <<(verbose ? "Yes" : "No") <<"\n";
		out <<"Ignore case? " <<(caseInsensitive ? "Yes" : "No") <<"\n";
	}
	else {
		cout <<"Start at: " <<(directorySearch ? startDir : "Current directory") <<"\n";
		cout <<"No output file\n";
		cout <<"Verbose? " <<(verbose ? "Yes" : "No") <<"\n";
		cout <<"Ignore case? " <<(caseInsensitive ? "Yes" : "No") <<"\n";
	}
}

// Prints a Unix usage statement on how to execute the command
// Precondition: none
// Postcondition: none
void Params::
usage(){
	cout <<"Usage: sniff [-v||--verbose] [-h ||--help] [-o filename] [-d||--dir directory] [-c] string" << endl;
}