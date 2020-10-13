#include "NetInteraction.h"
#include "Console.h"
#include "ReqHead.h"
#include <conio.h>
NetInteraction::NetInteraction()
{
	console.Warning("注意:按下回车键(Enter)退出程序....");
	console.Log("----------------------------------------------");
}

void NetInteraction::onInitialize(string str)
{
	console.Log("初始化设置:"+str);
}

bool NetInteraction::InterruptLoopEvent()
{
	if (_kbhit()) {
		auto ch = _getch();
		if (ch == 13)return true;
	}
	return false;
}

void NetInteraction::onListenFailed(int errCode)
{
	string msg = "监听失败!";
	console.Throw(errCode,msg);
}

void NetInteraction::onAcceptClient(SOCKET client)
{

		server->SendMsg(client, "HTTP/1.0 200 OK\r\nContent-Length: 100\r\nContent-Type: text/html; charset=UTF-8\r\n\r\n\
<html>\
<head>\
<title>计网实验</title>\
</head>\
<body>\
<p>hello world </p> \
<img src=\"hust.jpg\"> \
</body>\
</html>");
	server->PostMsg("接收来自了 " + server->GetClientAddress(client)+"的连接");
	console.Log("接收连接来自 "+server->GetClientAddress(client));
}

void NetInteraction::onAcceptClientFailed(SOCKET client,int errCode)
{
	string msg = "接收连接失败!";
	console.Error(errCode, msg);
}

void NetInteraction::onConnectionFailed(SOCKET client)
{
	server->PostMsg(server->GetClientAddressOffline(client) + " 离开了网络");
	console.Log("Address:" + server->GetClientAddressOffline(client) + " 断开了连接");
}

void NetInteraction::onReceiveMessage(SOCKET client, string msg)
{
	console.Log("从" + server->GetClientAddress(client) + "收到了消息\n内容:" + msg);
	ReqHead head(msg);
	console.Warning(head.GetHeadInfo());
	server->PostMsg("来自"+ server->GetClientAddress(client) + "的人发送了消息\n 内容:" + msg);
}
