#include "FileID.hpp"

void FileID::
print(ostream& out){
	for (string s : keywords){
		cout <<s <<endl;
	}
}

void FileID::
addKeyword(string word){
	for (string s : keywords){
		if (s == word) return;
	}
	keywords.push_back(word);
}

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