/*
CSCI-4547 Systems Programming
sniff.cpp
Author: James Mok
Created: 20 Feb 2023
Last edited: 20 Feb 2023
*/

#include "sniff.hpp"

// Constructs sniff class
// Precondition: valid program arguments
// Postcondition: params object is created
Sniff::
Sniff(int argc, char* argv[]){
    string argList(argv[1]);
    string word;
    cout << argList << endl;
    istringstream stream(argList);

    for(;;){
        stream >> word;
        cout << word << endl;
        if (stream.eof()) break;
    }
}

