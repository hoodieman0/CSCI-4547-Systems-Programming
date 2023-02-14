#include <getopt.h>
#include "params.hpp"

Params::Params(int argc, char* argv[]){
	int ch;

	const option longOpts[] = {
		{"verbose", no_argument, nullptr, 'v'},
		{"dir", required_argument, nullptr, 'd'},
		{"help", no_argument, nullptr, 'h'},
		{nullptr, no_argument, nullptr, 0}
	};

	for(;;){
		ch = getopt_long(argc, argv, "o:d:vhc", longOpts, nullptr);

		if (ch == -1) break;
		switch (ch){
			case 'o':
				fileOutput = true;
				outFileName = optarg;
				out.open(outFileName, ios::out);
				break;
			case 'd':
				directorySearch = true;
				startDir = optarg;
				break;
			case 'v':
				verbose = true;
				break;
			case 'h':
				help = true;
				break;
			case 'c':
				caseInsensitive = true;
				break;
			default:
				usage();
				break;
		}
	}
	for (optx = optind; optx < argc; optx++){
		cout <<"Arguement " <<argv[optx] <<endl;
		out <<"Arguement " <<argv[optx] <<endl;
	}
}

void Params::print(){
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

void Params::usage(){
	cout <<"Usage: sniff [-v||--verbose] [-h ||--help] [-o filename] [-d||--dir directory] [-c] string" << endl;
}