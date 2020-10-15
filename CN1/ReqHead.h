#pragma once
#include <string>
#include <map>
using namespace std;
class ReqHead
{

	map<string, string> serializeHead;
public:
	string method;
	string file;
	string httpVersion;
	string host;//初始URL中的主机和端口
	//表示是否需要持久连接。如果Servlet看到这里的值为“Keep - Alive”，
	//或者看到请求使用的是HTTP 1.1（HTTP 1.1默认进行持久连接），
	//它就可以利用持久连接的优点，当页面包含多个元素时（例如Applet，图片），
	//显著地减少下载所需要的时间。
	//要实现这一点，Servlet需要在应答中发送一个Content - Length头，
	//最简单的实现方法是：先把内容写入ByteArrayOutputStream，然后在正式写出内容之前计算它的大小。
	string connection;
	string upgradeInsecureRequests;//接收连接信息
	string userAgent;//浏览器类型，如果Servlet返回的内容与浏览器类型有关则该值非常有用。
	string secFetchUser;//接收连接信息
	string accept;// 浏览器可接受的MIME类型
	string secFetchSite;
	string secFetchMode;
	string refer;//接收请求信息   包含一个URL，用户从该URL代表的页面出发访问当前请求的页面。
	//浏览器能够进行解码的数据编码方式，比如gzip。
	//Servlet能够向支持gzip的浏览器返回经gzip编码的HTML页面。
	//许多情形下这可以减少5到10倍的下载时间。
	string acceptEncoding;
	string acceptLanguage;//浏览器所希望的语言种类，当服务器能够提供一种以上的语言版本时要用到。


	string acceptCharset;//浏览器可接受的字符集
	string authorization;//授权信息，通常出现在对服务器发送的WWW-Authenticate头的应答中。
	string contentLength;//表示请求消息正文的长度
	string cookie;//这是最重要的请求头信息之一
	string from;//请求发送者的email地址，由一些特殊的Web客户程序使用，浏览器不会用到它。
	string ifModifiedSince;//只有当所请求的内容在指定的日期之后又经过修改才返回它，否则返回304“Not Modified”应答。
	string pragma;//指定“no-cache”值表示服务器必须返回一个刷新后的文档，即使它是代理服务器而且已经有了页面的本地拷贝。
	//由某些版本的IE浏览器所发送的非标准的请求头，表示屏幕大小、颜色深度、操作系统和CPU类型。
	string uaPixels;
	string uaColor;
	string uaOs;
	string uaCpu;


public:
	ReqHead(string reqMsg);
	string GetHeadInfo();
private:
	void GenerateDefaultReqHead();
	void MapReqHead(string context);
	void DeserializeReqHead();
};

