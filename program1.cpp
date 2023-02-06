/*
Authors: Sean Vargas, James Mok
Created On: 2 February 2023
Last Edited: 5 February 2023

A short program meant to take in command line arguments and break down each
passed in argument.

(a) ./P1
(b) ./P1 -o myCommand myMain.c myClass.c
(c) ./P1 w/java bash-3.2 ls -l
(d) ./P1 -au --verbose w/java/ kira:w/java/
(e) ./P1 -i "CSCI 6657" *.html > mytemp.txt
(f) ./P1 *.bak *.log

*/

#include <iostream>
#include <fstream>
#include <getopt.h>

using namespace std;

void usage();

int main(int argc, char* argv[]){
	cout <<"\n~Starting Program1~\n" <<endl;
	ofstream out("P1_VargasMok.txt", ios::out | ios::app);
	
	// see https://man7.org/linux/man-pages/man3/getopt.3.html
	// defines all long switches
	struct option longOpts[] = {
		{"verbose", no_argument, NULL, 'v'}
	};
	
	int ch, code, optx;

	cout <<"-----------------------------------" <<endl;
	out <<"-----------------------------------" <<endl;

	cout <<"Command " <<argv[0] <<endl;
	out <<"Command " <<argv[0] <<endl;

	for (;;){
		ch = getopt_long(argc, argv, "ioaulv", longOpts, &code);

		// All Switches
		if (ch == -1) break;
		switch (ch){
			case 'i':
				cout <<"Switch " <<char(ch) <<" Argument " <<optarg <<endl;
				out <<"Switch " <<char(ch) <<" Argument " <<optarg <<endl;
				break;
			case 'o':
				cout <<"Switch " <<char(ch) <<endl;
				out <<"Switch " <<char(ch) <<endl;
				break;
			case 'q':
				cout <<"Switch " <<char(ch) <<endl;
				out <<"Switch " <<char(ch) <<endl;
				break;
			case 'u':
				cout <<"Switch " <<char(ch) <<endl;
				out <<"Switch " <<char(ch) <<endl;
				break;
			case 'l':
				cout <<"Switch " <<char(ch) <<endl;
				out <<"Switch " <<char(ch) <<endl;
				break;
			case 'v':
				cout <<"Switch " <<char(ch) <<endl;
				out <<"Switch " <<char(ch) <<endl;
				break;
			case 0:
				cout <<"Switch " << longOpts[code].name << endl;
				out <<"Switch " << longOpts[code].name << endl;
				if (optarg != NULL){
					cout << "Argument " << optarg << endl;
					out << "Argument " << optarg << endl;
				}
			default:
				usage();
				break;
		}
	}

	// Ending Arguments
	for (optx = optind; optx < argc; optx++){
		cout <<"Arguement: " <<argv[optx] <<endl;
		out <<"Arguement: " <<argv[optx] <<endl;
	}

	cout <<"\n~End Of Program~\n" <<endl;
}

// Command Line Usage Display
void usage(){
	cout <<"Usage: program1 [-ioaul] [arguments]\n"; 
}
