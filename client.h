//�ͻ��� 
 #include<winsock2.h>
#include<stdio.h>
#include<windows.h>
#include<time.h>
#pragma comment(lib,"WS2_32.lib")
int main(){
	WSADATA wsaData;
	WORD sockVersion = MAKEWORD(2, 0);

	::WSAStartup(sockVersion, &wsaData);//��һ��������WINSOCK�汾�ţ��ڶ���������ָ��WSADATA��ָ��
	/*�������������׽���*/
	SOCKET s = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);//���������ֱ����ʹ��TCP/IP���������ʹ��TCP����ʹ����������Э��

	if (s == INVALID_SOCKET)
	{
		printf("Failed socket()\n");
		::WSACleanup();
		system("pause");
		return 0;
	}

	/*socket��װ���ַ��Ϣ*/
	sockaddr_in servAddr;

	servAddr.sin_family = AF_INET;//sin_familyָ��Э���壬��socket�����ֻ����AF_INET
	servAddr.sin_port = htons(8888);//��ʾ�����������Ķ˿ں�Ϊ13
	servAddr.sin_addr.S_un.S_addr = inet_addr("192.168.31.220");
	/*�󶨵�ַ���˿ں�*/
	if (::connect(s, (sockaddr*)&servAddr, sizeof(servAddr)) == -1);
	{
		printf("���ӳɹ�,�ȴ���Ϣ...\n\n");

	while(1){
		char buff[256];
	char te[256];
	int nRecv = ::recv(s, buff, 256, 0);
	if (nRecv > 0)
	{
		buff[nRecv] = '\0';
		printf("�Է���%s\n", buff);
		printf("�ң�");
        scanf("%s",&te);
		::send(s, te, strlen(te), 0);
	//	system("pause");
	}}
		printf("Failed connect()\n");
		::WSACleanup();
		system("pause");
	}

	/*�������ݲ���ӡ����Ļ��*/

	return 0;
}

