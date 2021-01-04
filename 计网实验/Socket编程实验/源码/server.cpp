#pragma once
#include "server.h"

server::server()
{
	
}

server::~server()
{
	if (srvSock != NULL)
		closesocket(srvSock);
}

//��ʼ��������socket
int server::inisrvsock()
{
	//���� TCP socket
	srvSock = socket(AF_INET, SOCK_STREAM, 0);
	if (srvSock == INVALID_SOCKET)
	{
		printf("����������socketʧ��!\n");
		WSACleanup();
		return -1;
	}
	printf("������TCP socket�����ɹ�!\n");
	return 0;
}

//���÷�����socket������ַ���˿ںš��������ļ�Ŀ¼���󶨼���
int server::setsrvsock()
{
	int nRC;
	u_short sport;
	char cp[16];
	//�� socket to Server's IP and port
	srvAddr.sin_family = AF_INET;
	//��ȡ�����ļ�
	ifstream fin;
	fin.open("../../lab1server/init.txt");
	//���ü����˿�
	fin >> sport;
	srvAddr.sin_port = htons(sport);
	cout << "�ɹ����ü����˿�:" << sport << '\n';
	//���ü���IP��ַ
	fin >> cp;
	inet_pton(AF_INET, cp, &srvAddr.sin_addr);
	cout << "�ɹ����ü���IP��ַ��" << cp << '\n';
	//���÷�����Ŀ¼
	fin >> pwd;
	cout << "�ɹ�������Ŀ¼��" << pwd << '\n';
	//�󶨷�����socket
	nRC = ::bind(srvSock, (LPSOCKADDR)&srvAddr, sizeof(srvAddr));
	if (nRC == SOCKET_ERROR)
	{
		printf("������socket��ʧ��!\n");
		closesocket(srvSock);
		WSACleanup();
		return -1;
	}
	printf("������socket�󶨳ɹ�!\n");

	//��ʼ�������̣��ȴ��ͻ�������
	nRC = listen(srvSock, 5);
	if (nRC == SOCKET_ERROR)
	{
		printf("������socket����ʧ��!\n");
		closesocket(srvSock);
		WSACleanup();
		return -1;
	}

	clientAddr.sin_family = AF_INET;
	return 0;
}

//Ϊÿ�����󴴽��̴߳���
int server::srvloop()
{
	SOCKET sessionSocket;
	int addrLen = sizeof(sockaddr);
	while (1)
	{
		//�����ỰSOCKET
		sessionSocket = accept(srvSock, (LPSOCKADDR)&clientAddr, &addrLen);
		if (sessionSocket != INVALID_SOCKET)
			printf("Socket����һ���ͻ�������!\n");
		else
		{
			printf("����ʧ��!\n");
			return -1;
		}
		printf("��IP: %s �յ�����\n", inet_ntoa(clientAddr.sin_addr));
		thread t(&server::serverth,this, sessionSocket);
		t.detach();
	}
	return 0;
}

//�̴߳�����
void server::serverth(SOCKET sessionSocket)
{
	char recvBuf[4096];
	int nRC = 1;

	while (nRC > 0)
	{
		//receiving data from client
		memset(recvBuf, '\0', 4096);
		nRC = recv(sessionSocket, recvBuf, 4096, 0);
		printf("�ӿͻ��� %d �˿�:�յ� %d �ֽ�\n", ntohs(srvAddr.sin_port), nRC);
		printf("*****receive*****\n%s\n*******end*******\n", recvBuf);
		string buft = recvBuf;
		//�ͻ������󷽷���GETֻ����200 OK
		if (!startwith(buft, "GET"))
		{
			string tem = "HTTP/1.1 200 OK";
			const char* t = tem.c_str();
			int tlen = strlen(t);
			nRC = send(sessionSocket, t, tlen, 0);
			//printf("*****send*****\n%s\n*****end*****\n", t);
			if (nRC == SOCKET_ERROR)
			{
				closesocket(sessionSocket);
				return;
			}
			return;
		}
		//�ͻ�������ΪGET����ʱ���챨�Ĳ�����
		int sppos, i;
		for (sppos = 0; recvBuf[sppos] != ' '; sppos++);
		//�����URL
		string url = pwd;
		for (i = 0; recvBuf[sppos + i + 1] != ' '; i++)
			url += recvBuf[sppos + i + 1];
		//cout << "url:" << url << endl;
		//���첢������Ӧ����
		mksendpk m(url);
		//���첢������Ӧ����ͷ
		string tem = m.sendheader();
		const char* t = tem.c_str();
		int tlen = strlen(t);
		nRC = send(sessionSocket, t, tlen, 0);
		//printf("*****send*****\n%s\n*****end*****\n", t);
		if (nRC == SOCKET_ERROR)
		{
			closesocket(sessionSocket);
			return;
		}
		//���첢������Ӧ������������
		nRC = m.sendmsg(sessionSocket);
		if (nRC == SOCKET_ERROR)
		{
			closesocket(sessionSocket);
			return;
		}
		if (!nRC)
			cout << "�ɹ���Ӧ�ͻ��˵�" << url << "����" << endl;
		else if(nRC==-2)
			cout << "�ͻ��������" << url << "������" << endl;
		closesocket(sessionSocket);
	}
	//closesocket(sessionSocket);
	return;
}