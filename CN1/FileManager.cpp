#include "FileManager.h"
#include "PreDefinations.h"
#include "Buffer.h"
#include <fstream>
FileManager::FileManager(Configuration& conf):homeDir(conf.homeDir),conf(&conf)
{
}

unsigned long int FileManager::ReadToEnd(string file, Buffer& buffer)
{
    string fullPath = homeDir + file;
    ifstream fs;
    fs.open(fullPath, ios::binary|ios::in);
    if (!fs) {
        fs.close();
        throw FileNotFoundException(fullPath);
    }
    fs.seekg(0, std::ios::end);
    unsigned long len =(unsigned long) fs.tellg()+1;
    fs.seekg(0, std::ios::beg);
    char* buf = new char[len];
    fs.read(buf, len);
    buffer =buffer+Buffer(buf,len);
    delete[] buf;
    fs.close();
    return len;
}
