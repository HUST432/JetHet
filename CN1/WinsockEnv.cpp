#include "WinsockEnv.h"
#include <iostream>
#include <winsock2.h>
#include "Console.h"
#pragma comment(lib, "Ws2_32.lib")

using namespace std;


#define MAJORVERSION 2  //Winsock主版本号
#define MINORVERSION 2	//Winsock次版本号

WinsockEnv::WinsockEnv(void)
{
}

WinsockEnv::~WinsockEnv(void)
{
}

void WinsockEnv::Startup() {

	WSADATA wsaData;//用于返回Winsock的环境信息   
	int rtn;		//Winsock初始化函数的返回值
	WORD  wVersionRequested = MAKEWORD(MAJORVERSION, MINORVERSION); //Winsock版本号，高字节次版本，低字节主版本号


	//初始化 winsock
	rtn = WSAStartup(wVersionRequested, &wsaData);

	if (rtn) { //如果返回值不是0，则Winsock初始化失败
		//throw "Winsock startup error!";
		throw(rtn, "Winsock初始化失败!");
	}

	//判断返回的Winsock版本号
	if (LOBYTE(wsaData.wVersion) != MAJORVERSION || HIBYTE(wsaData.wVersion) != MINORVERSION) { //如果版本不对
		WSACleanup();  //清除Winsock
		//throw "Winsock version error!";
		throw(MAJORVERSION, "Winsock版本错误!");
	}
}