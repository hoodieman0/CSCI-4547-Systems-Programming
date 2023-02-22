#include "sniff.hpp"

Sniff::
Sniff(Params& p) : parameters(&p){
	firstDir = p.getStartDir();
	pathname = firstDir;

	istringstream s(p.getKeywords());
	string word;
	for (;;){
		s >>word;
		words.push_back(word);
		if (s.eof()) break;
	}

	chdir(firstDir);
}

void Sniff::
oneDir(){
	DIR* currentDir = opendir(getcwd(nullptr, 0));

	int i = closedir(currentDir);
}