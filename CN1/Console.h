#pragma once
#include<string>
#include<iostream>
using namespace std;
class Console
{
public:
	static void Error(string err);
	static void Error(int code, string err);
	static void Warning(string warn);
	static void Log(string msg);
	static void Throw(int code, string err);
	static void SendInfo(string msg);
};

static Console console;

