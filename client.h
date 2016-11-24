//客户端 
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
	sockaddr_in servAddr;

	servAddr.sin_family = AF_INET;//sin_family指代协议族，在socket编程中只能是AF_INET
	servAddr.sin_port = htons(8888);//表示服务器监听的端口号为13
	servAddr.sin_addr.S_un.S_addr = inet_addr("192.168.31.220");
	/*绑定地址及端口号*/
	if (::connect(s, (sockaddr*)&servAddr, sizeof(servAddr)) == -1);
	{
		printf("连接成功,等待消息...\n\n");

	while(1){
		char buff[256];
	char te[256];
	int nRecv = ::recv(s, buff, 256, 0);
	if (nRecv > 0)
	{
		buff[nRecv] = '\0';
		printf("对方：%s\n", buff);
		printf("我：");
        scanf("%s",&te);
		::send(s, te, strlen(te), 0);
	//	system("pause");
	}}
		printf("Failed connect()\n");
		::WSACleanup();
		system("pause");
	}

	/*接收数据并打印到屏幕上*/

	return 0;
}

