#include "ReqHead.h"
#include "PreDefinations.h"
#include <fstream>
#include <sstream>
#define CONFINSERT(KEY,VAL) serializeHead.insert(pair<string, string>(KEY, VAL))
#define CONFINSERTV(TEMP,KEY,VAL) ostringstream TEMP;TEMP<<VAL; serializeHead.insert(pair<string, string>(KEY, TEMP.str()))

#define GETCONF(KEY) serializeHead[string(KEY)]
#define GETCONFV(TEMP,KEY,VAL) 	istringstream TEMP(serializeHead[string(KEY)]);TEMP >> VAL
ReqHead::ReqHead(string reqMsg)
{
	/* 在此处添加初始化值 */
	GenerateDefaultReqHead();
	MapReqHead(reqMsg);
	DeserializeReqHead();
}

string ReqHead::GetHeadInfo()
{
	ostringstream ss;
	for (auto iter = serializeHead.begin(); iter != serializeHead.end(); iter++) {
		ss << iter->first << ":" << iter->second << endl;
	}
	return ss.str();
}


void ReqHead::GenerateDefaultReqHead()
{
	/* 若要对值进行初始化 
	 * 在构造函数先对成员进行初始化	
	 * 不要在此处修改
	 */
	CONFINSERT("Method",method);
	CONFINSERT("File",file);
	CONFINSERT("Version",httpVersion);
	CONFINSERT("Host",host);
	CONFINSERT("Connection",connection);
	CONFINSERT("Upgrade-Insecure-Requests",upgradeInsecureRequests);
	CONFINSERT("User-Agent",userAgent);
	CONFINSERT("Sec-Fetch-User",secFetchUser);
	CONFINSERT("Accept",accept);
	CONFINSERT("Sec-Fetch-Site",secFetchSite);
	CONFINSERT("Sec-Fetch-Mode",secFetchMode);
	CONFINSERT("Referer",refer);
	CONFINSERT("Accept-Encoding",acceptEncoding);
	CONFINSERT("Accept-Language",acceptLanguage);
}

void ReqHead::MapReqHead(string context)
{
	istringstream ss(context);
	string line;
	while (getline(ss, line)) {
		preDef.trim(line);
		preDef.trim(line, '\t');
		size_t rp;
		while ((rp = line.find_first_of('\r')) != string::npos)line.erase(rp);
		// #开头为注释
		if (line[0] == '#' || line.empty())continue;
		auto i = line.find_first_of(':');
		if (i == string::npos) {
			//解析头
			auto f1 = line.find_first_of(' ');
			auto f2 = line.find_first_of(' ', f1 + 1);

			string method = line.substr(0, f1);
			preDef.trim(method);
			string file = line.substr(f1 + 1, f2-f1);
			preDef.trim(file);
			string httpVersion = line.substr(f2 + 1);
			preDef.trim(httpVersion);
			serializeHead.insert_or_assign(string("Method"), method);
			serializeHead.insert_or_assign(string("File"), file);
			serializeHead.insert_or_assign(string("Version"), httpVersion);
			continue;
		}
		//如果找到了:符号 则表示是后面的内容
		string key = line.substr(0, i);
		preDef.trim(key);
		preDef.trim(key, '\t');
		string val = line.substr(i + 1);
		preDef.trim(val);
		preDef.trim(val, '\t');
		//printf("---key:%s,val:%s\n", key.c_str(), val.c_str());
		serializeHead.insert_or_assign(key, val);
	}
}

void ReqHead::DeserializeReqHead()
{
	method = GETCONF("Method");
	file = GETCONF("File");
	httpVersion = GETCONF("Version");
	host = GETCONF("Host");
	connection = GETCONF("Connection");
	upgradeInsecureRequests = GETCONF("Upgrade-Insecure-Requests");
	userAgent = GETCONF("User-Agent");
	secFetchUser= GETCONF("Sec-Fetch-User");
	accept = GETCONF("Accept");
	secFetchSite = GETCONF("Sec-Fetch-Site");
	secFetchMode = GETCONF("Sec-Fetch-Mode");
	refer = GETCONF("Referer");
	acceptEncoding = GETCONF("Accept-Encoding");
	acceptLanguage = GETCONF("Accept-Language");
}

