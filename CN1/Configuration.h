#pragma once

#include <string>
#include <map>
using namespace std;
#define SOMAXCONN 0x7fffffff
class Configuration
{
private:
	const string defaultFileName="default.cfg";
public:
	string address="127.0.0.1";
	int port=1234;
	int recvBufferCapacity=65536;
	int blockMode=1;
	int maxConnections=SOMAXCONN;
	double loopPeriod=0.5;

	string homeDir="html/";
	string homePage="index.html";
	string notFoundPage="404.html";

	map<string, string> serializedConf;

	Configuration();
	Configuration(string file);

	string GetConfigurationInfo();
private:
	void GenerateDefaultConfiguration();
	void GenerateConfgurationFile();
	void MapConfiguration(string context);
	void DeserializeConfiguration();
};

