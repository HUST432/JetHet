#pragma once
#include<string>
using namespace std;
class Buffer
{
public:
	char* buf;
	unsigned long int size;
public:
	Buffer();
	Buffer(const char* buf,unsigned long int size);
	Buffer(string buf);
	~Buffer();
	Buffer& operator + (const Buffer& buffer);
	/// <summary>
	/// 
	/// </summary>
	/// <returns>返回size+1 包括\0</returns>
	unsigned long length();
	char operator [](unsigned long index);
	explicit operator string();
	void InsertFront(Buffer&& buffer );
};
