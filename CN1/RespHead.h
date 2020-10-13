﻿#pragma once
#include <string>
#include <map>
using namespace std;
class RespHead
{
	string httpVersion;
	int statusCode;
	string status;

	string date;//当前的GMT时间。你可以用setDateHeader来设置这个头以避免转换时间格式的麻烦
	//表示内容长度。只有当浏览器使用持久HTTP连接时才需要这个数据。
	//如果你想要利用持久连接的优势，可以把输出文档写入ByteArrayOutputStram，完成后查看其大小，
	//然后把该值放入Content-Length头，最后通过byteArrayStream.writeTo(response.getOutputStream()发送内容。
	long long int contentLength;
	//表示后面的文档属于什么MIME类型。Servlet默认为text/plain，但通常需要显式地指定为text/html。
	//由于经常要设置Content-Type，因此HttpServletResponse提供了一个专用的方法setContentType。
	string contentType;
	//表示后面的文档属于什么MIME类型。Servlet默认为text/plain，但通常需要显式地指定为text/html。
	//由于经常要设置Content-Type，因此HttpServletResponse提供了一个专用的方法setContentType。
	string contentEncoding;
	string allow;//服务器支持哪些请求方法（如GET、POST等）
	string server;//服务器名字。Servlet一般不设置这个值，而是由Web服务器自己设置。
	//设置和页面关联的Cookie。Servlet不应使用response.setHeader("Set-Cookie", ...)，而是应使用HttpServletResponse提供的专用方法addCookie。参见下文有关Cookie设置的讨论。
	string setCookie;


	string expires;//Expires 应该在什么时候认为文档已经过期，从而不再缓存它
	//文档的最后改动时间。客户可以通过If-Modified-Since请求头提供一个日期，
	//该请求将被视为一个条件GET，只有改动时间迟于指定时间的文档才会返回，
	//否则返回一个304（Not Modified）状态。Last-Modified也可用setDateHeader方法来设置。
	string lastModified;
	//表示客户应当到哪里去提取文档。Location通常不是直接设置的，
	//而是通过HttpServletResponse的sendRedirect方法，该方法同时设置状态代码为302。
	string location;
	//表示浏览器应该在多少时间之后刷新文档，以秒计。除了刷新当前文档之外，
	//你还可以通过setHeader("Refresh", "5; URL=http://host/path")让浏览器读取指定的页面。
	//注意这种功能通常是通过设置HTML页面HEAD区的<META HTTP-EQUIV="Refresh" CONTENT="5;URL=http://host/path">实现，
	//这是因为，自动刷新或重定向对于那些不能使用CGI或Servlet的HTML编写者十分重要。
	//但是，对于Servlet来说，直接设置Refresh头更加方便。注意Refresh的意义是“N秒之后刷新本页面或访问指定页面”，
	//而不是“每隔N秒刷新本页面或访问指定页面”。因此，连续刷新要求每次都发送一个Refresh头，而发送204状态代码则可以阻止浏览器继续刷新，
	//不管是使用Refresh头还是<META HTTP-EQUIV="Refresh" ...>。
	//注意Refresh头不属于HTTP 1.1正式规范的一部分，而是一个扩展，但Netscape和IE都支持它。
	string refresh;

	//WWW-Authenticate 客户应该在Authorization头中提供什么类型的授权信息？
	//在包含401（Unauthorized）状态行的应答中这个头是必需的。
	//例如，response.setHeader("WWW-Authenticate", "BASIC realm=\"executives\"")。
	//注意Servlet一般不进行这方面的处理，而是让Web服务器的专门机制来控制受密码保护页面的访问（例如.htaccess）。
	string wwwAuthenticate;
};

