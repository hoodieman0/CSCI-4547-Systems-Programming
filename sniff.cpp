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
	FileID file;
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

			file = oneFile(entry->d_name, s->st_ino, pathname);
			if (file.keywordFound())
				flaggedFiles.push_back(file);
		}
	}

	cout <<"Directory processed\n";
	closedir(currentDir);
	delete s;
}

FileID Sniff::
oneFile(string name, int iNode, string path){
	FileID f(name, iNode, path);
	ifstream in(f.getName());
	string input, compare;

	for (;;){
		in >>input;
		compare = stripString(input);

		for (string w : words){
			
			if (parameters->getSwitch('c')){
				if (caseInsensitiveCompare(w, compare)) f.addKeyword(compare);
			} 
			else if (w == compare) 
				f.addKeyword(compare);
		}
		if (in.eof()) break;
	}

	in.close();
	return f;
}

string Sniff::
stripString(string s){
	string out;

	for (char c : s){
		if (isalpha(c)) out += c;
	}

	return out;
}

bool Sniff::
caseInsensitiveCompare(string s1, string s2){
	string string1, string2;
	for (unsigned int i = 0; i < s1.size(); i++){
		string1 += tolower(s1[i]);
	}
	for (unsigned int i = 0; i < s2.size(); i++){
		string2 += tolower(s2[i]);
	}

	return string1 == string2;
}