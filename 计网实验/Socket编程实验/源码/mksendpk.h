#pragma once
#include <stdio.h>
#include <winsock2.h>
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

class mksendpk {
#define DATABUF 4096
private:
	ifstream f;
	string type; //mime类型
	string filename;//文件名
	string status;//文件打开状态
	long leftlen;//文件剩余长度
	long len;//文件长度
	char buffer[DATABUF];//缓冲区
public:
	mksendpk(string fname);
	mksendpk();
	//~mksendpk();
	string sendheader();
	int sendmsg(SOCKET s);
	void callen();
	void findtype();
};

bool endwith(const string &a, const string &b);
bool startwith(const string &a, const string &b);