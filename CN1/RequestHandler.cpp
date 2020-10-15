#include "RequestHandler.h"

#include "FileManager.h"
#include "PreDefinations.h"
#include "Console.h"
#include <sstream>
RequestHandler::RequestHandler(Configuration& conf):fm(conf),conf(&conf)
{
}

Buffer& RequestHandler::GetResponse(ReqHead& head)
{

	//对于RESTful的GET请求
	if (head.method == "GET") {
		//如果接受的file为/
		if (head.file == "/")head.file = conf->homePage;
		size_t akpos = 0;
		if ((akpos=head.file.find('?')) != string::npos) {
			head.file=head.file.substr(0, akpos);
		}
		if (preDef.endwith(head.file, ".html"))return GetHtml(head);
		if (preDef.endwith(head.file, ".htm"))return GetHtml(head);
		
		if (preDef.endwith(head.file, ".jpg"))return GetJPG(head);
		if (preDef.endwith(head.file, ".jpeg"))return GetJPG(head);

		if (preDef.endwith(head.file, ".png"))return GetPNG(head);

		if (preDef.endwith(head.file, ".css"))return GetCss(head);
		if (preDef.endwith(head.file, ".js"))return GetJs(head);
		return GetPlain(head);
	}
	return GetNotFoundPage();
}

Buffer& RequestHandler::GetNotFoundPage()
{
	console.Warning("客户端访问了不存在的位置" );
	Buffer* b = new Buffer();
	unsigned long len = 0;
	try {
		len = fm.ReadToEnd(conf->notFoundPage, *b);
	}
	catch (FileNotFoundException e) {
		console.Warning("404网站未配置"+e.Get());
		RespHead rsp(404, STATUS_NOTFOUND);
		rsp.SetServer(conf->server);
		rsp.SetHttpVersion(conf->httpVersion);
		rsp.SetConnection(conf->GetConnection(conf->notFoundPage));
		rsp.SetContentType(TYPE_HTML, conf->GetEncoding(conf->notFoundPage));
		rsp.SetContentLength(0);
		b = new Buffer(rsp.GenerateRespHead());
		return *b;
	}
	RespHead rsp(404, STATUS_NOTFOUND);
	rsp.SetServer(conf->server);
	rsp.SetHttpVersion(conf->httpVersion);
	rsp.SetConnection(CONN_CLOSE);
	rsp.SetContentType(TYPE_HTML, conf->GetEncoding(conf->notFoundPage));
	rsp.SetContentLength(b->length());
	//rsp.SetContentEncoding(ENCODING_GZIP);
	b->InsertFront(Buffer(rsp.GenerateRespHead()));
	return *b;
}

Buffer& RequestHandler::GetHtml(ReqHead& head)
{
	Buffer* b=new Buffer();
	unsigned long len=0;
	try {
		len = fm.ReadToEnd(head.file, *b);
	}
	catch (FileNotFoundException e) {

		return GetNotFoundPage();
	}
	RespHead rsp(200, STATUS_OK);
	rsp.SetServer(conf->server);
	rsp.SetHttpVersion(conf->httpVersion);
	rsp.SetConnection(conf->GetConnection(head.file));
	rsp.SetContentType(TYPE_HTML, conf->GetEncoding(head.file));
	rsp.SetContentLength(b->length());
	//rsp.SetContentEncoding(ENCODING_GZIP);
	b->InsertFront(Buffer(rsp.GenerateRespHead()));
	return *b;
}

Buffer& RequestHandler::GetPNG(ReqHead& head)
{
	Buffer* b = new Buffer();
	unsigned long len = 0;
	try {
		len = fm.ReadToEnd(head.file, *b);
	}
	catch (FileNotFoundException e) {

		return GetNotFoundPage();
	}
	RespHead rsp(200, STATUS_OK);
	rsp.SetServer(conf->server);
	rsp.SetHttpVersion(conf->httpVersion);
	rsp.SetConnection(conf->GetConnection(head.file));
	rsp.SetAcceptRanges(ACCEPT_BYTES);
	rsp.SetContentType(TYPE_PNG);
	rsp.SetContentLength(b->length());
	//rsp.SetContentEncoding(ENCODING_GZIP);
	b->InsertFront(Buffer(rsp.GenerateRespHead()));
	return *b;
}

Buffer& RequestHandler::GetJPG(ReqHead& head)
{
	Buffer* b = new Buffer();
	unsigned long len = 0;
	try {
		len = fm.ReadToEnd(head.file, *b);
	}
	catch (FileNotFoundException e) {

		return GetNotFoundPage();
	}
	RespHead rsp(200, STATUS_OK);
	rsp.SetServer(conf->server);
	rsp.SetHttpVersion(conf->httpVersion);
	rsp.SetConnection(conf->GetConnection(head.file));
	rsp.SetAcceptRanges(ACCEPT_BYTES);
	rsp.SetContentType(TYPE_JPEG);
	rsp.SetContentLength(b->length());
	//rsp.SetContentEncoding(ENCODING_GZIP);
	b->InsertFront(Buffer(rsp.GenerateRespHead()));
	return *b;
}

Buffer& RequestHandler::GetCss(ReqHead& head)
{
	Buffer* b = new Buffer();
	unsigned long len = 0;
	try {
		len = fm.ReadToEnd(head.file, *b);
	}
	catch (FileNotFoundException e) {

		return GetNotFoundPage();
	}
	RespHead rsp(200, STATUS_OK);
	rsp.SetServer(conf->server);
	rsp.SetHttpVersion(conf->httpVersion);
	rsp.SetConnection(conf->GetConnection(head.file));
	rsp.SetContentType(TYPE_CSS, conf->GetEncoding(head.file));
	rsp.SetContentLength(b->length());
	//rsp.SetContentEncoding(ENCODING_GZIP);
	b->InsertFront(Buffer(rsp.GenerateRespHead()));
	return *b;
}

Buffer& RequestHandler::GetJs(ReqHead& head)
{
	Buffer* b = new Buffer();
	unsigned long len = 0;
	try {
		len = fm.ReadToEnd(head.file, *b);
	}
	catch (FileNotFoundException e) {

		return GetNotFoundPage();
	}
	RespHead rsp(200, STATUS_OK);
	rsp.SetServer(conf->server);
	rsp.SetHttpVersion(conf->httpVersion);
	rsp.SetConnection(conf->GetConnection(head.file));
	rsp.SetContentType(TYPE_JS, conf->GetEncoding(head.file));
	rsp.SetContentLength(b->length());
	//rsp.SetContentEncoding(ENCODING_GZIP);
	b->InsertFront(Buffer(rsp.GenerateRespHead()));
	return *b;
}

Buffer& RequestHandler::GetPlain(ReqHead& head)
{
	Buffer* b = new Buffer();
	unsigned long len = 0;
	try {
		len = fm.ReadToEnd(head.file, *b);
	}
	catch (FileNotFoundException e) {

		return GetNotFoundPage();
	}
	RespHead rsp(200, STATUS_OK);
	rsp.SetServer(conf->server);
	rsp.SetHttpVersion(conf->httpVersion);
	rsp.SetConnection(conf->GetConnection(head.file));
	rsp.SetContentType(TYPE_PLAIN, conf->GetEncoding(head.file));
	rsp.SetContentLength(b->length());
	//rsp.SetContentEncoding(ENCODING_GZIP);
	b->InsertFront(Buffer(rsp.GenerateRespHead()));
	return *b;
}

