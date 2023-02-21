#include <vector>
#include <iostream>
#include <string>

using namespace std;

class FileID{
private:
	int iNode;
	string pathname, filename;
	vector<string> keywords;
public:
	FileID(string file, int iNum, string path) : filename(file), iNode(iNum), pathname(path.append(file)) {};
	~FileID() = default;
	void print(ostream& out);
	void addKeyword(string word);
};