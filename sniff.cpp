#include "sniff.hpp"

// Sniff constructor
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

// Process one directory
void Sniff::
oneDir(){
	FileID file;
	char* cwd = getcwd(nullptr, 0);
	struct stat* s = new struct stat;
	DIR* currentDir = opendir(cwd);

	// Read and discard first 2 directory entries
	readdir(currentDir);
	readdir(currentDir);

	// Process the directory entries
	for (;;){
		entry = readdir(currentDir);
		if (!entry) break;
		lstat(entry->d_name, s);

		// Check for type of directory entry
		if (S_ISREG(s->st_mode)){
			if (parameters->getSwitch('v')) cout <<entry->d_name <<endl;

			file = oneFile(entry->d_name, s->st_ino, pathname);
			if (file.keywordFound())
				flaggedFiles.push_back(file);
		}
		else if (S_ISDIR(s->st_mode)){
			if (parameters->getSwitch('v')) cout <<entry->d_name <<endl;
		}
	}

	cout <<"Directory processed\n";
	closedir(currentDir);
	free(cwd);
	delete s;
}

// Process a single file
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

// Returns a string equal to the input string with all non-alphabetic characters removed
string Sniff::
stripString(string s){
	string out;

	for (char c : s){
		if (isalpha(c)) out += c;
	}

	return out;
}

// Creates 2 lowercase strings equal to the inputs and returns true if they are the same
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

void Sniff::
run(){
	string current = pathname;
	chdir(current.c_str());
	travel(current);

	for (FileID file : flaggedFiles){
		cout << "\n--------------------" << endl;
		cout << file.getName() << endl;
		file.print(cout);
	}
}

void Sniff::
travel(string pname){
	FileID file;
	char* cwd = getcwd(nullptr, 0);
	struct stat* s = new struct stat;
	DIR* currentDir = opendir(cwd);

	// Read and discard first 2 directory entries
	readdir(currentDir);
	readdir(currentDir);

	// Process the directory entries
	for (;;){
		entry = readdir(currentDir);
		if (!entry) break;
		lstat(entry->d_name, s);

		// Check for type of directory entry
		if (S_ISREG(s->st_mode)){
			if (parameters->getSwitch('v')) cout <<entry->d_name <<endl;

			file = oneFile(entry->d_name, s->st_ino, pname);
			if (file.keywordFound())
				flaggedFiles.push_back(file);
		}
		else if (S_ISDIR(s->st_mode)){
			string dirString = pname + "/" + entry->d_name;
			if (parameters->getSwitch('v')) cout << "Directory: " << dirString <<endl;
			chdir(entry->d_name);
			travel(dirString);
			chdir("..");
		}
	}

	cout <<"Directory processed!\n" << endl;
	closedir(currentDir);
	free(cwd);
	delete s;
}