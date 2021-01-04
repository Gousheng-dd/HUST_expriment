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
	string type; //mime����
	string filename;//�ļ���
	string status;//�ļ���״̬
	long leftlen;//�ļ�ʣ�೤��
	long len;//�ļ�����
	char buffer[DATABUF];//������
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