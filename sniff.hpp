/*
CSCI-4547 Systems Programming
sniff.hpp
Author: James Mok
Created: 18 Feb 2023
Last edited: 18 Feb 2023
*/

#ifndef SNIFF_HPP
#define SNIFF_HPP

#include <vector>
#include "params.hpp"
#include "FileID.hpp"

using namespace std;



class Sniff{
    private:
        Params p();
        char* dir;
        char* pathname;
        vector<string> words;
        vector<FileID> markedFiles;
        struct {
            string name; 
        } dirent;

    public:
        Sniff(int argc, char* argv[]);
        void oneDir();
        FileID oneFile();
};

#endif