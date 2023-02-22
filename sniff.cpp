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
	struct stat* s = new struct stat;
	DIR* currentDir = opendir(getcwd(nullptr, 0));

	// Read and discard first 2 directory entries
	readdir(currentDir);
	readdir(currentDir);

	for (;;){
		entry = readdir(currentDir);
		if (!entry) break;
		lstat(entry->d_name, s);

		if (S_ISREG(s->st_mode) || S_ISDIR(s->st_mode)){
			if (parameters->getSwitch('v')) cout <<entry->d_name <<endl;
		}
	}

	closedir(currentDir);
	delete s;
}

FileID Sniff::
oneFile(string name, int iNode, string path){
	FileID f(name, iNode, path);
	ifstream in(f.getName());
	string s;

	for (;;){
		in >>s;
		if (in.eof()) break;

		for (string w : words){
			if (!w.compare(s)) 
				f.addKeyword(s);
		}
	}

	in.close();
}