#pragma once
#include <fstream>
#include <string>
#include <sstream>
using namespace std;
class FileManager
{
private:
	string homeDir;
public:
	FileManager(string homeDir);
	long long int ReadToEnd(string file, ostringstream& buffer);
};

