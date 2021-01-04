#pragma once
#include "mksendpk.h"
#include <WS2tcpip.h>
#include <cstring>
#include <conio.h>
#include <thread>
using namespace std;

class server {
private:
	SOCKET srvSock;
	sockaddr_in srvAddr, clientAddr;
	string pwd;
	
public:
	server();
	~server();
	int inisrvsock();
	int setsrvsock();/*°ó¶¨²¢¼àÌý*/
	int srvloop();
	void serverth(SOCKET sessionSocket);

#define DATABUF 4096
};