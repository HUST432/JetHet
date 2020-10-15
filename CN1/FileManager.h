#pragma once

#include "Configuration.h"
#include "Buffer.h"
#include <fstream>
#include <string>
#include <sstream>
using namespace std;
class FileManager
{
private:
	string homeDir;
	Configuration* conf;
public:
	FileManager(Configuration& conf);
	unsigned long int ReadToEnd(string file, Buffer& buffer);
};

