#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "Server.h"
#include "WinsockEnv.h"

#include <sstream>
#pragma region Public Functions
Server::Server(string address, u_short port,int recvBufferCapacity):
	address(address), port(port), blockMode(1), loopPeriod({0,500000}),
	socketSignaledNumber(0),maxConnections(SOMAXCONN),
	interaction(NULL),recvBufferCapacity(recvBufferCapacity),
	addr(),name(),rfds(),wfds(),tcpSock(0)
{
	recvBuffer = new char[recvBufferCapacity];
	conns = new list<SOCKET>();
	errs = new list<SOCKET>();
	clientAddrs = new map<SOCKET, string>();
}

Server::Server(Configuration& conf):
	address(conf.address), port(conf.port), blockMode(conf.blockMode), loopPeriod({0,0}),
	socketSignaledNumber(0),maxConnections(conf.maxConnections),
	interaction(NULL),recvBufferCapacity(conf.recvBufferCapacity),
	addr(),name(),rfds(),wfds(),tcpSock(0)
{
	loopPeriod.tv_sec = (long)conf.loopPeriod;
	loopPeriod.tv_usec =(long) ((conf.loopPeriod - loopPeriod.tv_sec) * 1000000);
	recvBuffer = new char[recvBufferCapacity];
	conns = new list<SOCKET>();
	errs = new list<SOCKET>();
	clientAddrs = new map<SOCKET, string>();
}

Server::~Server()
{
	delete[] recvBuffer;
	delete conns;
	delete errs;
	delete clientAddrs;
	Close();
}

void Server::StartUp()
{
	//输出初始化设置
	if (interaction) {
		stringstream& ss = *new stringstream();
		ss << "\nAddress:" << address << endl <<
			"Port:" << port << endl <<
			"Receive Buffer:" << recvBufferCapacity << endl <<
			"Block Mode:" << blockMode << endl <<
			"Loop Period:" << (loopPeriod.tv_sec + (loopPeriod.tv_usec / 1000000.0f)) << endl <<
			"Max Connections:" << maxConnections << endl;
		interaction->onInitialize(ss.str());
	}

	WinsockEnv::Startup();

	Socket();

	Bind();
}

void Server::Listen()
{
	int nRC=listen(tcpSock, maxConnections);
	if (nRC==SOCKET_ERROR) {
		closesocket(tcpSock);
		WSACleanup();
		int errorCode=WSAGetLastError();
		if (interaction)interaction->onListenFailed(errorCode);
		//console.Throw(errorCode, msg);
	}
}

void Server::Connect()
{
	int nRC = connect(tcpSock, (LPSOCKADDR)&addr, sizeof(addr));
	if (nRC==SOCKET_ERROR) {
		int errorCode = WSAGetLastError();
		string msg = "Connect Failed! Error Code:";
		msg += errorCode;
		throw (const char*)msg.c_str();
	}
}

int Server::Send(char* buf, int len)
{
	int s = send(tcpSock, buf, len, 0);
	return s;
}

int Server::Recv(char* buf, int len)
{
	int s = recv(tcpSock, buf, len, 0);
	return s;
}

int Server::SendTo(const char* buf, int len,const sockaddr* to, int tolen)
{
	int s = sendto(tcpSock, buf, len, 0,to,tolen);
	return s;
}

int Server::RevFrom(char* buf, int len, sockaddr* from, int* fromlen)
{
	int s = recvfrom(tcpSock, buf, len, 0, from, fromlen);
	return 0;
}

void Server::PostMsg(string msg)
{
	for (auto iter = conns->begin(); iter != conns->end(); iter++)
		if (FD_ISSET(*iter, &wfds))SendMsg(*iter, msg);
}

void Server::SendMsg(SOCKET client, string s)
{
	auto iter=find(errs->begin(), errs->end(), client);
	if (iter != errs->end())return;
	int nRC = send(client, s.c_str(), s.length(), 0);
	if (nRC == SOCKET_ERROR) {
		//console.Error("Send Message Failed!");
		//console.Log(GetClientAddress(client) + " has lost the connection");
		AddErrSession(client);
		if (interaction)interaction->onConnectionFailed(client);
	}
}

void Server::SendBuffer(SOCKET client, const char* buf, size_t size)
{
	auto iter = find(errs->begin(), errs->end(), client);
	if (iter != errs->end())return;
	int nRC = send(client, buf,size, 0);
	if (nRC == SOCKET_ERROR) {
		//console.Error("Send Message Failed!");
		//console.Log(GetClientAddress(client) + " has lost the connection");
		AddErrSession(client);
		if (interaction)interaction->onConnectionFailed(client);
	}
}

void Server::SetInteraction(Interaction* interaction)
{
	interaction->SetServer(this);
	this->interaction = interaction;
}

void Server::Loop()
{
	SetBlockMode(tcpSock);

	while (true) {
		//移除conns中关闭的会话
		RemoveErrSessions();
		//在监听到退出循环的事件后退出循环
		if (interaction != 0)
			if (interaction->InterruptLoopEvent()) {
				Close();
				break;
			}
		//将缓冲区设为0
		FD_ZERO(&rfds);
		FD_ZERO(&wfds);
		//把sock加入rfds 等待用户连接
		FD_SET(tcpSock, &rfds);
		//等待用户数据
		for (auto iter = conns->begin(); iter != conns->end(); iter++) {
			FD_SET(*iter, &rfds);
			FD_SET(*iter, &wfds);
		}
		//select函数返回有可读或可写的socket的总数，保存   最后一个参数设定等待时间，如为NULL则为阻塞模式

		socketSignaledNumber = select(0, &rfds, &wfds, NULL, &loopPeriod);
		if (socketSignaledNumber == SOCKET_ERROR)throw "select() Failed";
		RevRequest();

		RevMessage();
	}
}

void Server::CloseSocket(SOCKET client)
{
	if (client != INVALID_SOCKET) {
		//closesocket(client);
		AddErrSession(client);
	}
}

void Server::Close()
{
	closesocket(tcpSock);
	//closesocket(udpSock);
}

string Server::GetClientAddress(SOCKET s)
{
	string clientAddress; //clientAddress是个空字符串
	sockaddr_in clientAddr;
	int nameLen, rtn;

	nameLen = sizeof(clientAddr);
	rtn = getsockname(s, (LPSOCKADDR)&clientAddr, &nameLen);
	if (rtn != SOCKET_ERROR) {
		clientAddress += inet_ntoa(clientAddr.sin_addr);
		
	}

	return clientAddress;
}

string Server::GetClientAddressOffline(SOCKET s)
{
	auto iter = clientAddrs->find(s);
	if (iter != clientAddrs->end())
		return (*iter).second;
	return string("");
}
#pragma endregion

#pragma region Private Functions
void Server::Socket()
{
	//udpSock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	tcpSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.S_un.S_addr = inet_addr(address.c_str());
	
}

void Server::Bind()
{
	int nRC = bind(tcpSock, (LPSOCKADDR)&addr, sizeof(addr));
	if (nRC == SOCKET_ERROR) {
		closesocket(tcpSock);
		WSACleanup();
		throw "绑定地址失败!"; 
	}
}

void Server::Accept(sockaddr_in &addr,int &nAddrLen)
{
	SOCKET s = accept(tcpSock, (LPSOCKADDR)&addr, &nAddrLen);
	if (s == INVALID_SOCKET) {
		int errorCode = WSAGetLastError();
		if (interaction)interaction->onAcceptClientFailed(s,errorCode);
		return;
	}
	SetBlockMode(s);
	AddSession(s);
	//char opt = 1;
	//setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
	string nameAddr = GetClientAddress(s);
	//console.Log("Accept Address:"+nameAddr);
	// ADD INTO MAP
	clientAddrs->insert(map<SOCKET, string>::value_type(s, nameAddr));
	// ADD RECEIVE MESSAGE
	if (interaction)interaction->onAcceptClient(s);
		//StartNewHandlerThread()

}

void Server::AddSession(SOCKET session)
{
	if (session != INVALID_SOCKET)conns->push_back(session);
}

void Server::AddErrSession(SOCKET session)
{
	if (session != INVALID_SOCKET)
	{
		auto iter=find(errs->begin(), errs->end(), session);
		if (iter != errs->end())return;
		errs->push_back(session);
	}
}

void Server::RemoveErrSessions()
{
	for (auto iter = errs->begin(); iter != errs->end(); iter++) {
		if (*iter == INVALID_SOCKET)continue;
		//移除失效的会话
		auto err = find(conns->begin(), conns->end(), *iter);
		if (err != conns->end()) { 
			//closesocket(*err);
			conns->erase(err); 
		}
	}
	errs->clear();
}

void Server::RevRequest()
{
	//客户端IP
	sockaddr_in clientAddr;
	int addrLen = sizeof(clientAddr);
	if (socketSignaledNumber <= 0)return;
	if (FD_ISSET(tcpSock, &rfds)) {
		socketSignaledNumber--;
		Accept(clientAddr,addrLen);
	}
}

void Server::RevMessage()
{
	if (socketSignaledNumber <= 0)return;
	for (auto iter = conns->begin(); iter != conns->end(); iter++) 
		if (FD_ISSET(*iter, &rfds))
			RevMessage(*iter);
}

void Server::RevMessage(SOCKET client)
{
	int received = recv(client, recvBuffer, recvBufferCapacity, 0);
	if (received == SOCKET_ERROR || received == 0) {
		AddErrSession(client);
		if (interaction)interaction->onConnectionFailed(client);
		return;
	}
	//成功收到消息
	recvBuffer[received] = '\0';
	if (interaction)interaction->onReceiveMessage(client, string(recvBuffer));
	memset(recvBuffer, '\0', recvBufferCapacity);
}

void Server::SetBlockMode(SOCKET s)
{
	int nRC = ioctlsocket(s, FIONBIO, &blockMode);
	if (nRC == SOCKET_ERROR)throw "ioctlsocket() Failed!";
}



#pragma endregion

Server::Interaction::Interaction()
{
	server =nullptr ;
}


