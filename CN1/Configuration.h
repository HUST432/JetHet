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
	string server = "HeJiahuiWebServer/1.0";

	string httpVersion = "HTTP/1.1";

	string homeDir="html/";
	string homePage="index.html";
	string notFoundPage="404.html";

	string encoding="utf-8";
	//对于特定文件的编码
	string encodings = "";

	string connection = "Close";
	string connections = "";

	map<string, string> serializedConf;

	map<string, string> encodingsMap;
	map<string, string> connectionMap;
	/// <summary>
	/// 使用new方法在外部空间创建对象 所有需要使用配置的文件均使用指针引用此对象
	/// </summary>
	Configuration();
	/// <summary>
	/// 使用new方法在外部空间创建对象 所有需要使用配置的文件均使用指针引用此对象
	/// </summary>
	Configuration(string file);

	string GetConfigurationInfo();

	string GetConnection(string file);

	string GetEncoding(string file);
private:
	void GenerateDefaultConfiguration();
	void GenerateConfgurationFile();
	void MapConfiguration(string context);
	void DeserializeConfiguration();
};

