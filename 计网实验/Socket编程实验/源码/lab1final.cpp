// lab1final.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#pragma once
#include "server.h"

using namespace std;

#pragma comment(lib,"ws2_32.lib")

int mux = 0;

void exitth();

int main()
{
	printf("WELCOME! put in \"exit\" to exit\n");
	thread te(exitth);
	WSADATA wsaData;
	int nRC;
	//初始化 winsock
	nRC = WSAStartup(0x0202, &wsaData);
	if (nRC)
	{
		printf("服务器初始化失败!\n");
		return -1;
	}
	if (wsaData.wVersion != 0x0202)
	{
		printf("服务器winsock版本错误!\n");
		WSACleanup();
		return -1;
	}
	printf("服务器winsock初始化!\n");
	server s;
	if (s.inisrvsock() == -1)
		return -1;
	if (s.setsrvsock() == -1)
		return -1;
	if (s.srvloop() == -1)
		return -1;
	WSACleanup();
	return 0;

}

//服务器关闭线程处理函数，等待输入exit
void exitth()
{
	string t;
	cin >> t;
	if (t == "exit")
	{
		system("cls");
		printf("thank you,bye\n");
		exit(0);
	}
}

