#include <vector>
#include <string>
#include <sstream>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include "params.hpp"
#include "FileID.hpp"

class Sniff{
private:
	Params* parameters;
	char* firstDir;
	string pathname;
	vector<string> words;
	
	struct dirent* entry;
public:
	vector<FileID> flaggedFiles;

	Sniff(Params& p);
	~Sniff() = default;

	void oneDir();
	FileID oneFile(string name, int iNode, string path);
	string stripString(string s);
	bool caseInsensitiveCompare(string s1, string s2);
};