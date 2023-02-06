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

void usage();

int main(int argc, char* argv[]){
	std::ofstream out("P1_VargasMok.txt", std::ios::out | std::ios::app);
	int ch, optx;

	std::cout <<"-----------------------------------" <<std::endl;
	out <<"-----------------------------------" <<std::endl;

	std::cout <<"Command " <<argv[0] <<std::endl;
	out <<"Command " <<argv[0] <<std::endl;

	for (;;){
		ch = getopt(argc, argv, "ioaul");

		if (ch == -1) break;
		switch (ch){
			case 'i':
				std::cout <<"Switch " <<char(ch) <<std::endl;
				out <<"Switch " <<char(ch) <<std::endl;
				break;
			case 'o':
				std::cout <<"Switch " <<char(ch) <<std::endl;
				out <<"Switch " <<char(ch) <<std::endl;
				break;
			case 'q':
				std::cout <<"Switch " <<char(ch) <<std::endl;
				out <<"Switch " <<char(ch) <<std::endl;
				break;
			case 'u':
				std::cout <<"Switch " <<char(ch) <<std::endl;
				out <<"Switch " <<char(ch) <<std::endl;
				break;
			case 'l':
				std::cout <<"Switch " <<char(ch) <<std::endl;
				out <<"Switch " <<char(ch) <<std::endl;
				break;
			default:
				usage();
				break;
		}
	}

	for (optx = optind; optx < argc; optx++){
		std::cout <<"Arguement " <<argv[optx] <<std::endl;
		out <<"Arguement " <<argv[optx] <<std::endl;
	}
}

void usage(){
	std::cout <<"Usage: program1 [-ioaul] [arguments]\n"; 
}
