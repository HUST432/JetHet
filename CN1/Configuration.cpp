#include "Configuration.h"
#include "PreDefinations.h"
#include <fstream>
#include <sstream>

#define CONFINSERT(KEY,VAL) serializedConf.insert(pair<string, string>(KEY, VAL))
#define CONFINSERTV(TEMP,KEY,VAL) ostringstream TEMP;TEMP<<VAL; serializedConf.insert(pair<string, string>(KEY, TEMP.str()))

#define GETCONF(KEY) serializedConf[string(KEY)]
#define GETCONFV(TEMP,KEY,VAL) 	istringstream TEMP(serializedConf[string(KEY)]);TEMP >> VAL
Configuration::Configuration()
{
	GenerateDefaultConfiguration();
}

Configuration::Configuration(string file)
{
	GenerateDefaultConfiguration();
	fstream fs;
	fs.open(file,ios::in);
	if (!fs) {
		fs.close();
		GenerateConfgurationFile();
		
		return;
	}
	ostringstream oss;
	oss << fs.rdbuf();
	MapConfiguration(oss.str());
	DeserializeConfiguration();
}

string Configuration::GetConfigurationInfo()
{
	stringstream ss;
	for (auto iter = serializedConf.begin(); iter != serializedConf.end(); iter++) {
		ss << iter->first << ":" << iter->second << endl;
	}
	return ss.str();
}

string Configuration::GetConnection(string file)
{
	auto f = connectionMap.find(file);
	if (f != connectionMap.end())return f->second;
	return connection;
}

string Configuration::GetEncoding(string file)
{
	auto f=encodingsMap.find(file);
	if (f != encodingsMap.end())return f->second;
	return encoding;
}

void Configuration::GenerateDefaultConfiguration()
{
	CONFINSERT("Address", address);
	CONFINSERTV(p1,"Port", port);
	CONFINSERTV(p2, "ReceiveBuffer", recvBufferCapacity);
	CONFINSERTV(p3, "BlockMode", blockMode);
	CONFINSERTV(p4, "LoopPeriod", loopPeriod);
	CONFINSERTV(p5, "MaxConnections", maxConnections);
	CONFINSERT("Server", server);
	CONFINSERT("HttpVersion", httpVersion);

	CONFINSERT( "HomeDir", homeDir);
	CONFINSERT("HomePage", homePage);
	CONFINSERT("NotFoundPage", notFoundPage);

	CONFINSERT("Encoding", encoding);
	CONFINSERT("Encodings", encodings);

	CONFINSERT("Connection", connection);
	CONFINSERT("Connections", connections);
}

void Configuration::GenerateConfgurationFile()
{
	fstream fs;
	fs.open(defaultFileName, ios::out);
	for (auto iter = serializedConf.begin(); iter != serializedConf.end(); iter++) {
		fs << iter->first << ":" << iter->second << endl;
	}
	fs.close();
}

void Configuration::MapConfiguration(string context)
{
	istringstream ss(context);
	string line;
	while (getline(ss, line)) {
		preDef.trim(line);
		preDef.trim(line, '\t');
		// #开头为注释
		if (line[0]=='#'||line.empty())continue;
		auto i = line.find_first_of(':');
		string key = line.substr(0, i);
		preDef.trim(key);
		preDef.trim(key, '\t');
		string val = line.substr(i + 1);
		preDef.trim(val);
		preDef.trim(val, '\t');
		//printf("---key:%s,val:%s\n", key.c_str(), val.c_str());
		serializedConf.insert_or_assign(key, val);
	}
}

void Configuration::DeserializeConfiguration()
{
	address = GETCONF("Address");
	GETCONFV(p1, "Port", port);
	GETCONFV(p2, "ReceiveBuffer", recvBufferCapacity);
	GETCONFV(p3, "BlockMode", blockMode);
	GETCONFV(p4, "LoopPeriod", loopPeriod);
	GETCONFV(p5, "MaxConnections", maxConnections);
	server = GETCONF("Server");
	httpVersion = GETCONF("HttpVersion");

	homeDir = GETCONF("HomeDir");
	homePage = GETCONF("HomePage");
	notFoundPage = GETCONF("NotFoundPage");

	encoding = GETCONF("Encoding");
	encodings = GETCONF("Encodings");

	connection = GETCONF("Connection");
	connections = GETCONF("Connections");
	
	auto gp=preDef.split(encodings, ';');
	for (auto iter = gp.begin(); iter != gp.end(); iter++) {
		if (iter->empty())continue;
		auto side = preDef.split(*iter, '=');
		if (side.size() <= 1)continue;
		encodingsMap.insert_or_assign(side[0], side[1]);
	}

	auto conn = preDef.split(connections, ';');
	for (auto iter = conn.begin(); iter != conn.end(); iter++) {
		if (iter->empty())continue;
		auto side = preDef.split(*iter, '=');
		if (side.size() <= 1)continue;
		connectionMap.insert_or_assign(side[0], side[1]);
	}
}
