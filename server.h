//服务器
#include<winsock2.h>
#include<stdio.h>
#include<windows.h>
#include<time.h>
#pragma comment(lib,"WS2_32.lib")
int main(){
	WSADATA wsaData;
	WORD sockVersion = MAKEWORD(2, 0);

	::WSAStartup(sockVersion, &wsaData);//第一个参数是WINSOCK版本号，第二个参数是指向WSADATA的指针
	/*创建服务器的套接字*/
	SOCKET s = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);//三个参数分别代表使用TCP/IP，传输过程使用TCP，不使用其他特殊协议

	if (s == INVALID_SOCKET)
	{
		printf("Failed socket()\n");
		::WSACleanup();
		system("pause");
		return 0;
	}

	/*socket中装入地址信息*/
	sockaddr_in sin;

	sin.sin_family = AF_INET;//sin_family指代协议族，在socket编程中只能是AF_INET
	sin.sin_port = htons(8888);//表示服务器监听的端口号为13
	sin.sin_addr.S_un.S_addr = INADDR_ANY;//储存IP地址，INADDR_ANY就是指定地址为0.0.0.0的地址，
	//这个地址事实上表示不确定地址，或“所有地址”、“任意地址”
	/*绑定地址及端口号*/
	if (::bind(s, (LPSOCKADDR)&sin, sizeof(sin)) == SOCKET_ERROR)
	{
		printf("Falied bind()\n");
		::WSACleanup();
		system("pause");
		return 0;
	}
	/*监听客户端的连接请求*/
	if (::listen(s, 2) == SOCKET_ERROR)
	{
		printf("Falied bind()\n");
		::WSACleanup();
		system("pause");
		return 0;
	}
	sockaddr_in remoteAddr;
	int nAddrLen = sizeof(remoteAddr);
	SOCKET client;

	time_t t = time(0);
	char tmp[64];
	char po[256];

//	strftime(tmp, sizeof(tmp), "%Y/%m/%d%X%A\n\t", localtime(&t)); //提取系统时间

	/*循环接受连接请求*/
	while (TRUE)
	{
		client = ::accept(s, (SOCKADDR*)&remoteAddr, &nAddrLen);//accept默认会阻塞进程，知道有一个客户建立连接后返回，
		//它返回的是一个新可用的套接字，这个套接字是连接套接字
		if (client == INVALID_SOCKET)
		{
			printf("Failed accept()\n");
			continue;
		}
		printf("接受到一个客户端的连接\r\n\n" );
		while(1){
			printf("我：");
			scanf("%s",&tmp);
	//		while(strlen(tmp)==0){
			::send(client, tmp, strlen(tmp), 0);
			int nRecv = ::recv(client, po, 256, 0);
	if (nRecv > 0)
	{
		po[nRecv] = '\0';
		printf("%s：%s\n", inet_ntoa(remoteAddr.sin_addr),po);
		//system("pause");
			}//}
	}

		::closesocket(client);/*关闭连接*/
	}
	::closesocket(s);/*关闭套接字*/

	system("pause");
	return 0;
}