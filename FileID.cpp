/*
CSCI-4547 Systems Programming
FileID.cpp
Author: James Mok
Created: 18 Feb 2023
Last edited: 18 Feb 2023
*/

#include "FileID.hpp"

// Prints the iNode ID and the path to the file
// Precondition: valid FileID object
// Postcondition: sends class data to ostream& out
void FileID::
print(ostream& out){
    out << "iNode Number: " << iNode << "\t | Path: " << pathname << endl;
}

void FileID::addKeyword(string word){

}