#include "PreDefinations.h"
#include <algorithm>
#include <windows.h>
string& PreDefinations::toLowerCase(string& tgt)
{
    transform(tgt.begin(), tgt.end(), tgt.begin(), ::tolower);
    return tgt;
}

wstring PreDefinations::string2wstring(string str)
{
    //获取缓冲区大小，并申请空间，缓冲区大小按字符计算  
    int len = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.size(), NULL, 0);
    WCHAR* buffer = new WCHAR[len + 1];
    //多字节编码转换成宽字节编码  
    MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.size(), buffer, len);
    buffer[len] = '\0';             //添加字符串结尾  
    //删除缓冲区并返回值  
    wstring result;
    result.append(buffer);
    delete[] buffer;
    return result;
}

string PreDefinations::wstring2string(wstring wstr)
{

    string result;
    //获取缓冲区大小，并申请空间，缓冲区大小事按字节计算的  
    int len = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), wstr.size(), NULL, 0, NULL, NULL);
    char* buffer = new char[len + 1];
    //宽字节编码转换成多字节编码  
    WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), wstr.size(), buffer, len, NULL, NULL);
    buffer[len] = '\0';
    //删除缓冲区并返回值  
    result.append(buffer);
    delete[] buffer;
    return result;
}
