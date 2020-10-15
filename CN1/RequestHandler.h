#pragma once
#include "RespHead.h"
#include "ReqHead.h"
#include "Configuration.h"
#include "FileManager.h"
#include "Buffer.h"
#include <string>
using namespace std;
class RequestHandler
{
	Configuration* conf;
	FileManager fm;
public:
	RequestHandler(Configuration& conf);
	Buffer& GetResponse(ReqHead& head);
private:
	Buffer& GetNotFoundPage();

	Buffer& GetHtml(ReqHead& head);
	Buffer& GetPNG(ReqHead& head);
	Buffer& GetJPG(ReqHead& head);
	
	Buffer& GetCss(ReqHead& head);
	Buffer& GetJs(ReqHead& head);

	Buffer& GetPlain(ReqHead& head);
};

