#include <iostream>
#include "Server.h"
#include "Console.h"
#include "NetInteraction.h"
#include "Configuration.h"
#include "PreDefinations.h"
using namespace std;
int main()
{
    SetConsoleOutputCP(65001);
    Configuration& conf = *new Configuration("default.cfg");
    console.Log("当前加载的配置:\n" + conf.GetConfigurationInfo());
    try {

        Server& s = *new Server(conf);

        NetInteraction& ni=*new NetInteraction(conf);
        s.SetInteraction(&ni);

        s.StartUp();
        console.Log("Winsock初始化成功");
        console.Log("服务器TCP socket创建成功");
        console.Log("服务器socket监听地址绑定成功");
        s.Listen();
        console.Log("开始监听外部请求...");
        s.Loop();
        console.Warning("程序正常终止..");
        delete& conf;
        return 0;
    }
    catch (const char* msg) {
       console.Error(*new string(msg));
       console.Warning("程序意外退出..");
       delete& conf;
       return -1;
    }
}
