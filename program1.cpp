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
