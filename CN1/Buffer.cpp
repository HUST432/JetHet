#include "Buffer.h"
#include <sstream>
Buffer::Buffer():buf(0),size(0)
{
}

Buffer::Buffer(const char* buf, unsigned long int size):buf(new char[size]),size(size-1)
{
	size_t i = 0;
	for (i = 0; i < size-1; i++)this->buf[i] = buf[i];
	this->buf[i] = '\0';
}

Buffer::Buffer(string buf):size((unsigned long int)buf.size()),buf(new char[buf.size()+1])
{
	auto sf = buf.c_str();
	for (size_t i = 0; i < size; i++)this->buf[i] =sf[i];
	buf[size] = '\0';
}

Buffer::~Buffer()
{
	if (size > 0)delete[] buf;
}

Buffer& Buffer::operator+(const Buffer& buffer)
{
	unsigned long int ns = size + buffer.size;
	auto nsp = new char[size+buffer.size+1];
	unsigned long i = 0;
	for (i = 0; i < size; i++)nsp[i] = buf[i];
	unsigned long j = 0;
	for ( j = 0; j < buffer.size; j++)nsp[i + j] = buffer.buf[j];
	nsp[i + j] = '\0';
	size = ns;
	delete[] buf;
	buf = nsp;
	
	return *this;
}

unsigned long Buffer::length()
{
	return size;
}

char Buffer::operator[](unsigned long index)
{
	if (index >= size)return '\0';
	return buf[index];
}

Buffer::operator string()
{
	ostringstream oss;
	oss << std::hex;
	//for (unsigned long i = 0; i < sz; i++)oss <<"\\x"<<(unsigned)(unsigned char)buf[i]<<",";
	//for (unsigned long i = 0; i < size; i++)oss << buf[i];
	return oss.str();
}

void Buffer::InsertFront(Buffer&& buffer)
{
	unsigned long int ns = size + buffer.size;
	auto nsp = new char[size + buffer.size+1];
	unsigned long i = 0;
	for (i = 0; i < buffer.size; i++)nsp[i] = buffer.buf[i];
	unsigned long j = 0;
	for ( j = 0; j <size; j++)nsp[i + j] =buf[j];
	nsp[i + j] = '\0';
	size = ns;
	delete[] buf;
	buf = nsp;
	
}
