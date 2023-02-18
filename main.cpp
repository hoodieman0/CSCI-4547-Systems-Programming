/*
CSCI-4547 Systems Programming
main.cpp
Author: James Mok and Sean Vargas
Created: 13 Feb 2023
Last edited: 18 Feb 2023
*/

#include "tools.hpp"
#include "params.hpp"

using namespace std;

int main(int argc, char* argv[]){
	banner();
	
	Params p(argc, argv);
	p.print(cout);

	bye();
}