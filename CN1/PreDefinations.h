#pragma once
#include <string>
using namespace std;
class PreDefinations {
public:
	static string trim(string& str, char _Ch = ' ') {
		if (str.empty())return str;
		while (str[0] == _Ch)str.erase(str.begin());
		auto iter = str.end() - 1;
		while (iter != str.begin() && *iter == _Ch)str.erase(iter--);
		return str;
	}
};
static PreDefinations preDef;