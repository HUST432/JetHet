#pragma once
#include <string>
#include <map>
using namespace std;
class ReqHead
{
private:
	map<string, string> serializeHead;
	string method;
	string file;
	string httpVersion;
	string host;//��ʼURL�е������Ͷ˿�
	//��ʾ�Ƿ���Ҫ�־����ӡ����Servlet���������ֵΪ��Keep - Alive����
	//���߿�������ʹ�õ���HTTP 1.1��HTTP 1.1Ĭ�Ͻ��г־����ӣ���
	//���Ϳ������ó־����ӵ��ŵ㣬��ҳ��������Ԫ��ʱ������Applet��ͼƬ����
	//�����ؼ�����������Ҫ��ʱ�䡣
	//Ҫʵ����һ�㣬Servlet��Ҫ��Ӧ���з���һ��Content - Lengthͷ��
	//��򵥵�ʵ�ַ����ǣ��Ȱ�����д��ByteArrayOutputStream��Ȼ������ʽд������֮ǰ�������Ĵ�С��
	string connection;
	string upgradeInsecureRequests;//����������Ϣ
	string userAgent;//��������ͣ����Servlet���ص�����������������й����ֵ�ǳ����á�
	string secFetchUser;//����������Ϣ
	string accept;// ������ɽ��ܵ�MIME����
	string secFetchSite;
	string secFetchMode;
	string refer;//����������Ϣ   ����һ��URL���û��Ӹ�URL�����ҳ��������ʵ�ǰ�����ҳ�档
	//������ܹ����н�������ݱ��뷽ʽ������gzip��
	//Servlet�ܹ���֧��gzip����������ؾ�gzip�����HTMLҳ�档
	//�������������Լ���5��10��������ʱ�䡣
	string acceptEncoding;
	string acceptLanguage;//�������ϣ�����������࣬���������ܹ��ṩһ�����ϵ����԰汾ʱҪ�õ���


	string acceptCharset;//������ɽ��ܵ��ַ���
	string authorization;//��Ȩ��Ϣ��ͨ�������ڶԷ��������͵�WWW-Authenticateͷ��Ӧ���С�
	string contentLength;//��ʾ������Ϣ���ĵĳ���
	string cookie;//��������Ҫ������ͷ��Ϣ֮һ
	string from;//�������ߵ�email��ַ����һЩ�����Web�ͻ�����ʹ�ã�����������õ�����
	string ifModifiedSince;//ֻ�е��������������ָ��������֮���־����޸Ĳŷ����������򷵻�304��Not Modified��Ӧ��
	string pragma;//ָ����no-cache��ֵ��ʾ���������뷵��һ��ˢ�º���ĵ�����ʹ���Ǵ�������������Ѿ�����ҳ��ı��ؿ�����
	//��ĳЩ�汾��IE����������͵ķǱ�׼������ͷ����ʾ��Ļ��С����ɫ��ȡ�����ϵͳ��CPU���͡�
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

