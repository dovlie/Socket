//������
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
	sockaddr_in sin;

	sin.sin_family = AF_INET;//sin_familyָ��Э���壬��socket�����ֻ����AF_INET
	sin.sin_port = htons(8888);//��ʾ�����������Ķ˿ں�Ϊ13
	sin.sin_addr.S_un.S_addr = INADDR_ANY;//����IP��ַ��INADDR_ANY����ָ����ַΪ0.0.0.0�ĵ�ַ��
	//�����ַ��ʵ�ϱ�ʾ��ȷ����ַ�������е�ַ�����������ַ��
	/*�󶨵�ַ���˿ں�*/
	if (::bind(s, (LPSOCKADDR)&sin, sizeof(sin)) == SOCKET_ERROR)
	{
		printf("Falied bind()\n");
		::WSACleanup();
		system("pause");
		return 0;
	}
	/*�����ͻ��˵���������*/
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

//	strftime(tmp, sizeof(tmp), "%Y/%m/%d%X%A\n\t", localtime(&t)); //��ȡϵͳʱ��

	/*ѭ��������������*/
	while (TRUE)
	{
		client = ::accept(s, (SOCKADDR*)&remoteAddr, &nAddrLen);//acceptĬ�ϻ��������̣�֪����һ���ͻ��������Ӻ󷵻أ�
		//�����ص���һ���¿��õ��׽��֣�����׽����������׽���
		if (client == INVALID_SOCKET)
		{
			printf("Failed accept()\n");
			continue;
		}
		printf("���ܵ�һ���ͻ��˵�����\r\n\n" );
		while(1){
			printf("�ң�");
			scanf("%s",&tmp);
	//		while(strlen(tmp)==0){
			::send(client, tmp, strlen(tmp), 0);
			int nRecv = ::recv(client, po, 256, 0);
	if (nRecv > 0)
	{
		po[nRecv] = '\0';
		printf("%s��%s\n", inet_ntoa(remoteAddr.sin_addr),po);
		//system("pause");
			}//}
	}

		::closesocket(client);/*�ر�����*/
	}
	::closesocket(s);/*�ر��׽���*/

	system("pause");
	return 0;
}