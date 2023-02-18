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
// Postcondition: sends class data to "ostream& out"
void FileID::
print(ostream& out){
    out << "iNode Number: " << iNode << "\t | Path: " << pathname << endl;
}

// Adds a new word for the class to find in the file
// Precondition: valid FileID object
// Postcondition: 'keywords" is updated with "word"
void FileID::
addKeyword(string word){
    for(int idx = 0; idx < keywords.size(); idx++){
        if (keywords[idx] == word){ return; }
    }
    keywords.push_back(word);
}