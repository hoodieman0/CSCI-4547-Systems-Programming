#include <vector>
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
	vector<FileID> flaggedFiles;
	struct dirent* entry;
public:
	Sniff(Params& p);
	~Sniff() = default;

	void oneDir();
	FileID oneFile(string name, int iNode, string path);
};