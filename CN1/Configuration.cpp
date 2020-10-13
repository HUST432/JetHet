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

void Configuration::GenerateDefaultConfiguration()
{
	CONFINSERT("Address", address);
	CONFINSERTV(p1,"Port", port);
	CONFINSERTV(p2, "ReceiveBuffer", recvBufferCapacity);
	CONFINSERTV(p3, "BlockMode", blockMode);
	CONFINSERTV(p4, "LoopPeriod", loopPeriod);
	CONFINSERTV(p5, "MaxConnections", maxConnections);

	CONFINSERT( "HomeDir", homeDir);
	CONFINSERT("HomePage", homePage);
	CONFINSERT("NotFoundPage", notFoundPage);


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
		// #¿ªÍ·Îª×¢ÊÍ
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

	homeDir = GETCONF("HomeDir");
	homePage = GETCONF("HomePage");
	notFoundPage = GETCONF("NotFoundPage");
}
