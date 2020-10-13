#include <iostream>
#include "Server.h"
#include "Console.h"
#include "NetInteraction.h"
#include "Configuration.h"
using namespace std;
int main()
{
    try {
        Configuration& conf = *new Configuration("default.cfg");
        console.Log("当前加载的配置:\n"+conf.GetConfigurationInfo());
        Server& s = *new Server(conf);

        delete &conf;

        NetInteraction& ni=*new NetInteraction();
        s.SetInteraction(&ni);

        s.StartUp();
        console.Log("Winsock初始化成功");
        console.Log("服务器TCP socket创建成功");
        console.Log("服务器socket监听地址绑定成功");
        s.Listen();
        console.Log("开始监听外部请求...");
        s.Loop();
        console.Warning("程序正常终止..");
    }
    catch (const char* msg) {
       console.Error(*new string(msg));
       console.Warning("程序遭遇意外退出..");
    }
    
}
