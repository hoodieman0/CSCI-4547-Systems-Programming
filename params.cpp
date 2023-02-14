#include <getopt.h>
#include "params.hpp"

Params::Params(int argc, char* argv[]){
	int ch;

	const option longOpts[] = {
		{"verbose", no_argument, nullptr, 'v'},
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
				out.open(optarg, ios::out);
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
}

void Params::print(){
	out <<startDir <<"   " <<outFileName;
}

void Params::usage(){
	cout <<"Usage: \n";
}