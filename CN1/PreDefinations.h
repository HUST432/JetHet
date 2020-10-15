#pragma once
#include <string>
#include <vector>
using namespace std;
class PreDefinations {
public:
	///去除字符串两边字符
	static string trim(string& str, char _Ch = ' ') {
		if (str.empty())return str;
		while (str[0] == _Ch)str.erase(str.begin());

		if (str.empty())return str;

		auto iter = str.end() - 1;
		while (iter != str.begin() && *iter == _Ch)str.erase(iter--);
		return str;
	}
	///转换字符串为小写
	static string& toLowerCase(string& tgt);
	///检查字符串结尾
	static bool endwith(const string& str, string end) {
		if (str.empty()) {
			if (end.empty())return true;
			return false;
		}
		if (str.length() < end.length())return false;
		auto ns=str.substr(str.length() - end.length());
		toLowerCase(ns);
		toLowerCase(end);
		if (ns == end)return true;
		return false;
	}
	///分离字符串
	static vector<string> split(const string& str,char _Ch) {
		vector<string> arr;
		if (str.empty()) { arr.push_back(""); return arr; }
		size_t i = 0, j = 0;
		while ((j = str.find(_Ch, i)) != string::npos) {
			arr.push_back(str.substr(i, j-i));
			i = j+1;
		}
		arr.push_back(str.substr(i));
		return arr;
	}
};
static PreDefinations preDef;

class Exception {
public:
	virtual string Get() {
		return string("执行过程中发生异常");
	}
};
class FileNotFoundException:Exception{
private:
	string fileName;
public:
	FileNotFoundException(string file) :fileName(file) {};
	virtual string Get()override {
		return string("错误:文件无法找到 目标文件:" + fileName);
	}
};