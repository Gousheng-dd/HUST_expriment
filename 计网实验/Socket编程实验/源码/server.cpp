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

//初始化服务器socket
int server::inisrvsock()
{
	//创建 TCP socket
	srvSock = socket(AF_INET, SOCK_STREAM, 0);
	if (srvSock == INVALID_SOCKET)
	{
		printf("服务器创建socket失败!\n");
		WSACleanup();
		return -1;
	}
	printf("服务器TCP socket创建成功!\n");
	return 0;
}

//配置服务器socket监听地址、端口号、服务器文件目录并绑定监听
int server::setsrvsock()
{
	int nRC;
	u_short sport;
	char cp[16];
	//绑定 socket to Server's IP and port
	srvAddr.sin_family = AF_INET;
	//读取配置文件
	ifstream fin;
	fin.open("../../lab1server/init.txt");
	//配置监听端口
	fin >> sport;
	srvAddr.sin_port = htons(sport);
	cout << "成功配置监听端口:" << sport << '\n';
	//配置监听IP地址
	fin >> cp;
	inet_pton(AF_INET, cp, &srvAddr.sin_addr);
	cout << "成功配置监听IP地址：" << cp << '\n';
	//配置服务器目录
	fin >> pwd;
	cout << "成功设置主目录：" << pwd << '\n';
	//绑定服务器socket
	nRC = ::bind(srvSock, (LPSOCKADDR)&srvAddr, sizeof(srvAddr));
	if (nRC == SOCKET_ERROR)
	{
		printf("服务器socket绑定失败!\n");
		closesocket(srvSock);
		WSACleanup();
		return -1;
	}
	printf("服务器socket绑定成功!\n");

	//开始监听过程，等待客户的连接
	nRC = listen(srvSock, 5);
	if (nRC == SOCKET_ERROR)
	{
		printf("服务器socket监听失败!\n");
		closesocket(srvSock);
		WSACleanup();
		return -1;
	}

	clientAddr.sin_family = AF_INET;
	return 0;
}

//为每个请求创建线程处理
int server::srvloop()
{
	SOCKET sessionSocket;
	int addrLen = sizeof(sockaddr);
	while (1)
	{
		//产生会话SOCKET
		sessionSocket = accept(srvSock, (LPSOCKADDR)&clientAddr, &addrLen);
		if (sessionSocket != INVALID_SOCKET)
			printf("Socket监听一个客户端请求!\n");
		else
		{
			printf("监听失败!\n");
			return -1;
		}
		printf("从IP: %s 收到请求\n", inet_ntoa(clientAddr.sin_addr));
		thread t(&server::serverth,this, sessionSocket);
		t.detach();
	}
	return 0;
}

//线程处理函数
void server::serverth(SOCKET sessionSocket)
{
	char recvBuf[4096];
	int nRC = 1;

	while (nRC > 0)
	{
		//receiving data from client
		memset(recvBuf, '\0', 4096);
		nRC = recv(sessionSocket, recvBuf, 4096, 0);
		printf("从客户端 %d 端口:收到 %d 字节\n", ntohs(srvAddr.sin_port), nRC);
		printf("*****receive*****\n%s\n*******end*******\n", recvBuf);
		string buft = recvBuf;
		//客户端请求方法非GET只返回200 OK
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
		//客户端请求为GET方法时构造报文并发送
		int sppos, i;
		for (sppos = 0; recvBuf[sppos] != ' '; sppos++);
		//分离出URL
		string url = pwd;
		for (i = 0; recvBuf[sppos + i + 1] != ' '; i++)
			url += recvBuf[sppos + i + 1];
		//cout << "url:" << url << endl;
		//构造并发送响应报文
		mksendpk m(url);
		//构造并发送响应报文头
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
		//构造并发送响应报文数据内容
		nRC = m.sendmsg(sessionSocket);
		if (nRC == SOCKET_ERROR)
		{
			closesocket(sessionSocket);
			return;
		}
		if (!nRC)
			cout << "成功响应客户端的" << url << "请求" << endl;
		else if(nRC==-2)
			cout << "客户端请求的" << url << "不存在" << endl;
		closesocket(sessionSocket);
	}
	//closesocket(sessionSocket);
	return;
}