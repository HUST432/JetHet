#include "RespHead.h"
#include "Console.h"
#include <sstream>
#define CONFINSERT(KEY,VAL) serializedHead.insert(pair<string, string>(KEY, VAL))
#define CONFINSERTV(TEMP,KEY,VAL) ostringstream TEMP;TEMP<<VAL; serializedHead.insert(pair<string, string>(KEY, TEMP.str()))

#define GETCONF(KEY) serializedHead[string(KEY)]
#define GETCONFV(TEMP,KEY,VAL) 	istringstream TEMP(serializedHead[string(KEY)]);TEMP >> VAL

RespHead::RespHead(int statusCode, string status):contentLength(0),statusCode(statusCode)
{
	httpVersion = "HTTP/1,1";
	this->status = status;
	//this->allow="PUT/GET/DELETE/POST";
	SetCurrentDate();
}

string RespHead::GenerateRespHead()
{
	ostringstream oss;
	oss << httpVersion << " " << statusCode << " " << status << "\r" << endl;
	for (auto iter = serializedHead.begin(); iter != serializedHead.end(); iter++) {
		auto p = *iter;
		oss << p.first << ":" << p.second << "\r" << endl;
	}
	for (auto iter = appendedHead.begin(); iter != appendedHead.end(); iter++) {
		auto p = *iter;
		oss << p.first << ":" << p.second << "\r" << endl;
	}
	oss << "\r" << endl;
	console.Warning(oss.str());
	return oss.str();
}

void RespHead::SetAcceptRanges(string range)
{
	this->acceptRanges = range;
	CONFINSERT("Accept-Ranges",range);
}

void RespHead::SetServer(string server)
{
	this->server = server;
	CONFINSERT("Server", server);
}

void RespHead::SetHttpVersion(string ver)
{
	this->httpVersion = ver;
}

void RespHead::SetConnection(string conn)
{
	this->connection = conn;
	CONFINSERT("Connection", conn);
}

void RespHead::SetContentType(string type)
{
	CONFINSERT("Content-Type", type);
}

void RespHead::SetContentType(string type,string charset)
{
	ostringstream oss;
	oss <<type << ";charset=" << charset;
	contentType = type;
	CONFINSERT("Content-Type", oss.str());
}

void RespHead::SetContentLength(unsigned long int msgLen)
{
	contentLength = msgLen;
	CONFINSERTV(p1, "Content-Length",msgLen);
}

void RespHead::SetContentEncoding(string encoding)
{
	contentEncoding = encoding;
	CONFINSERT("Content-Encoding", encoding);
}

void RespHead::SetAge(long age)
{
	this->age = age;
	CONFINSERTV(p1, "Age", age);
}

void RespHead::AddHeader(pair<string, string> newHeader)
{
	appendedHead.push_back(newHeader);
}
#include<time.h>
void RespHead::SetCurrentDate()
{
	time_t rawTime;
	struct tm* timeInfo;
	char szTemp[30] = { 0 };
	time(&rawTime);
	timeInfo = gmtime(&rawTime);
	char buffer[128];
	strftime(buffer, 128, "%a, %d %b %Y %H:%M:%S GMT", timeInfo);
	
	date = buffer;
	CONFINSERT("Date", date);
}

