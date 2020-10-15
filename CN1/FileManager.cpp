#include "FileManager.h"
#include "PreDefinations.h"
#include "Buffer.h"
#include <fstream>
FileManager::FileManager(Configuration& conf):homeDir(conf.homeDir),conf(&conf)
{
}

unsigned long int FileManager::ReadToEnd(string file, Buffer& buffer)
{
    auto loc = locale::global(locale(""));
    string fullPath = homeDir + file;
    fullPath = preDef.UrlDecode(fullPath);
   
    ifstream fs;
    wstring str = preDef.string2wstring(fullPath);
    fs.open(str, ios::binary | ios::in);

    locale::global(loc);
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
