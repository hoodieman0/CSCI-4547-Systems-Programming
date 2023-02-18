/*
CSCI-4547 Systems Programming
FileID.hpp
Author: James Mok
Created: 18 Feb 2023
Last edited: 18 Feb 2023
*/

#ifndef ID_HPP
#define ID_HPP

#include <string>
#include <vector>
#include <iostream>
using namespace std;

class FileID{
    private:
        char* filename;
        int iNode;
        string pathname;
        vector<string> keywords;
    
    public:
        // What is the type being talked about?
        FileID()=delete;
        FileID(char* filename, int type, string path) : 
            filename(filename), iNode(type), pathname(path) {}
        ~FileID()=default;

        void print(ostream& out);
        void addKeyword(string word);
};

#endif