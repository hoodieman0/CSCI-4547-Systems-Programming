#include <vector>
#include <dirent.h>
#include <sstream>
#include <unistd.h>
#include "params.hpp"
#include "FileID.hpp"

class Sniff{
private:
	Params* parameters;
	char* firstDir;
	string pathname;
	vector<string> words;
	vector<FileID> flaggedFiles;
	struct dirent;
public:
	Sniff(Params& p);
	~Sniff() = default;

	void oneDir();
};