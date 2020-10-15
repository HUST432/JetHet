#pragma once
#include <WinSock2.h>

#include <string>
#include <map>
#include <list>
#include "Configuration.h"


#pragma comment(lib, "ws2_32")

using namespace std;

class Server
{
public:
	class Interaction {
	protected:
		Server* server;
	public:
		Interaction();
		void SetServer(Server* s) {
			server = s;
		};
		virtual void onInitialize(string str) = 0;
		/// <summary>
		/// 通过事件来结束LOOP循环 结束监听
		/// </summary>
		/// <returns></returns>
		virtual bool InterruptLoopEvent() = 0;
		/// <summary>
		/// 监听失败
		/// </summary>
		/// <param name="errCode"></param>
		virtual void onListenFailed(int errCode) = 0;
		/// <summary>
		/// 接收到客户端的连接请求触发
		/// </summary>
		/// <param name="client">客户端</param>
		virtual void onAcceptClient(SOCKET client) = 0;
		/// <summary>
		/// 接收连接失败
		/// </summary>
		/// <param name="client"></param>
		virtual void onAcceptClientFailed(SOCKET client,int errCode) = 0;
		/// <summary>
		///  客户端失去响应或者失效
		/// </summary>
		/// <param name="client"></param>
		virtual void onConnectionFailed(SOCKET client) = 0;

		virtual void onReceiveMessage(SOCKET client, string msg) = 0;
	};
	//用于便于响应的处理 与客户端的互动
	Interaction* interaction;
private:
	//Config
	string address;
	u_short port;

	int maxConnections;
	/// <summary>
	/// 1-允许非阻塞模式
	/// 0-禁止非阻塞模式
	/// </summary>
	u_long blockMode;

	timeval loopPeriod;

	//Values
	sockaddr name;
	sockaddr_in addr;

	//SOCKET udpSock;
	SOCKET tcpSock;
	//buffers
	FD_SET rfds;
	FD_SET wfds;
	char* recvBuffer;
	int recvBufferCapacity;

	int socketSignaledNumber;

	list<SOCKET> *conns;
	list<SOCKET> *errs;
	
	map<SOCKET, string>* clientAddrs;
public:
	Server(string address,u_short port,int recvBufferCapacity);
	Server(Configuration& conf);
	~Server();
	void StartUp();

	void Listen();

	void Connect();

	int Send(char* buf,int len);
	int Recv(char* buf,int len);

	int SendTo(const char* buf,int len,const sockaddr *to,int tolen);
	int RevFrom(char* buf,int len,sockaddr *from,int* fromlen);
	
	/// <summary>
	/// 向所有客户端发表数据
	/// </summary>
	void PostMsg(string msg);
	/// <summary>
	/// 向指定客户端发送数据
	/// 只有在发现无法发送数据的时候才连接失效
	/// </summary>
	/// <param name="client"></param>
	/// <param name="s"></param>
	void SendMsg(SOCKET client,string s);

	void SendBuffer(SOCKET client,const char* buf,size_t size);

	void SetInteraction(Interaction* interaction);

	void Loop();

	void CloseSocket(SOCKET client);

	void Close();

	string GetClientAddress(SOCKET s);

	string GetClientAddressOffline(SOCKET s);
private:
	void Socket();

	void Bind();

	void Accept(sockaddr_in& addr, int& nAddrLen);
	/// <summary>
	/// 添加会话到SOCKET列表
	/// </summary>
	void AddSession(SOCKET session);
	/// <summary>
	/// 会话失效，从列表删除
	/// </summary>
	void AddErrSession(SOCKET session);
	/// <summary>
	///  移除失效的SOCKET会话
	/// </summary>
	void RemoveErrSessions();
	/// <summary>
	/// 从客户端接收连接请求
	/// </summary>
	void RevRequest();
	/// <summary>
	/// 从所有的客户端接收信息
	/// </summary>
	void RevMessage();
	/// <summary>
	/// 监听单个客户端的数据
	/// </summary>
	/// <param name="client"></param>
	void RevMessage(SOCKET client);
	/// <summary>
	/// 设置阻塞模式
	/// </summary>
	/// <param name="s"></param>
	void SetBlockMode(SOCKET s);


};

