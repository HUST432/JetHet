#include "FileManager.h"
#include <fstream>
FileManager::FileManager(string homeDir):homeDir(homeDir)
{
}

long long int FileManager::ReadToEnd(string file, ostringstream& buffer)
{
    string fullPath = homeDir + file;
    ifstream fs;
    fs.open(fullPath, ios::binary|ios::in);
    if (!fs) {
        fs.close();
        return false;
    }
    buffer << fs.rdbuf();
    long long int len = fs.tellg();
    fs.close();
    return len;
}
