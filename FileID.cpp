#include "FileID.hpp"

void FileID::
print(ostream& out){
	for (string s : keywords){
		cout <<s <<endl;
	}
}

// Add word to vector of keywords if it is not already present
void FileID::
addKeyword(string word){
	for (string s : keywords){
		if (s == word) return;
	}
	keywords.push_back(word);
}

// Returns true if any strings are present in the vector of keywords
bool FileID::
keywordFound(){
	if (keywords.size())
		return true;
	else
		return false;
}

const string FileID::
getName(){
	return filename;
}

const string FileID::
getPath(){
	return pathname;
}