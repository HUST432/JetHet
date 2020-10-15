# JetHet
### ※ 请不要在main分支提交代码更改
---
## 版本更新说明 1.0
- 增加了对中文路径的支持
- 支持转换URL至字符
- 允许传输大型文件
- 可以自由更改Http的版本
---
## default.cfg 配置文件使用手册
```
# Address为绑定监听的地址
Address		:	127.0.0.1
# 监听端口
Port		:	8888

# 阻塞模式 0为阻塞模式 1为非阻塞模式
BlockMode	:	1
# 非阻塞模式的情况下 在循环体内阻塞运行的时间 单位:秒
LoopPeriod	:	0.5
# 能接受的最大连接数
MaxConnections	:	2147483647
# 接收请求的最大缓存字节
ReceiveBuffer	:	65536

# 服务器名字
Server		:	HeJiahuiWebServer/100.0
# HTTP版本设置
HttpVersion	:	HTTP/2.0
# 网站所在根目录
HomeDir		:	html/432-chasers/
# 首页位置
HomePage	:	/index.html
# 如果找不到资源 输出的404页面
NotFoundPage	:	/404.html

# 总体的编码
Encoding		:	utf-8
# 对于特殊网页的编码 使用;符号分隔 使用=符号赋值
Encodings	:	/404.html=gbk;/

# 对于Connection通常设置 采用Close传输以后就断开 Keep-Alive将保持传输
Connection	:	Close
# 对于特殊网页的连接设置 使用;符号分隔 使用=符号赋值
Connections	:	/index.html=Keep-Alive;
```
