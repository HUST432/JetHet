#pragma once
#include "Server.h"
class NetInteraction:public Server::Interaction
{
public:
	NetInteraction();
	virtual void onInitialize(string str)override;
	virtual bool InterruptLoopEvent()override;
	virtual void onListenFailed(int errCode)override;
	virtual void onAcceptClient(SOCKET client) override;
	virtual void onAcceptClientFailed(SOCKET client,int errCode)override;
	virtual void onConnectionFailed(SOCKET client)override;
	virtual void onReceiveMessage(SOCKET client, string msg)override;
};

