#include <vector>
#include <iostream>
#include <string>

#pragma once

using namespace std;

class FileID{
private:
	string filename;
	int iNode;
	string pathname;
	vector<string> keywords;
public:
	FileID() = default;
	FileID(string file, int iNum, string path) : filename(file), iNode(iNum), pathname(path.append(file)) {};
	~FileID() = default;

	void print(ostream& out);
	void addKeyword(string word);
	bool keywordFound();
	const string getName();
};