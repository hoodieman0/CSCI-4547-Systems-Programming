#include <iostream>
#include <fstream>
#include <getopt.h>

int main(int argc, char* argv[]){
	std::ofstream out("P1_VargasMok.txt", std::ios::out | std::ios::app);
	int ch, optx;

	
	for (;;){
		ch = getopt(argc, argv, "qwerty");

		if (ch == -1) break;
		switch (ch){
			case 'q':
				std::cout <<"Switch " <<char(ch) <<std::endl;
				break;
			case 'w':
				std::cout <<"Switch " <<char(ch) <<std::endl;
				break;
			case 'e':
				std::cout <<"Switch " <<char(ch) <<std::endl;
				break;
			case 'r':
				std::cout <<"Switch " <<char(ch) <<std::endl;
				break;
			case 't':
				std::cout <<"Switch " <<char(ch) <<std::endl;
				break;
			case 'y':
				std::cout <<"Switch " <<char(ch) <<std::endl;
				break; 
		}
	}

	for (optx = optind; optx < argc; optx++){
		std::cout <<"Arguement " <<argv[optx] <<std::endl;
	}
}

