#pragma once
#include "mksendpk.h"

using namespace std;

bool endwith(const string &a, const string &b)
{
	return a.compare(a.size() - b.size(), a.size(), b) == 0;
}

bool startwith(const string &a, const string &b)
{
	return a.compare(0, b.size(), b) == 0;
}

mksendpk::mksendpk(string fname) :status("200 OK"), filename(fname), leftlen(0), len(0) {
	memset(buffer, '\0', DATABUF);
	callen();
	findtype();
}

mksendpk::mksendpk() : status("200 OK"), leftlen(0), len(0) {
	memset(buffer, '\0', DATABUF);
}

//ȷ���ļ����Ͳ�����content-type
void mksendpk::findtype()
{
	if (endwith(this->filename, ".html") || endwith(this->filename, ".htm"))
		this->type = "text/html";
	else if (endwith(this->filename, ".txt"))
		this->type = "text/plain";
	else if (endwith(this->filename, ".jpg") || endwith(this->filename, ".jpeg") || endwith(this->filename, ".jpe"))
		this->type = "image/jpeg";
	else if (endwith(this->filename, ".gif"))
		this->type = "image/gif";
	else if (endwith(this->filename, ".bmp"))
		this->type = "image/bmp";
	else
		this->type = "application/octet-stream";
	return;
}

//����Ҫ�����ļ��ĳ���
void mksendpk::callen()
{
	this->f.open(this->filename, ios_base::binary | ios_base::in);
	//��ʧ���򷵻�404������
	if (this->f.rdstate() && ios_base::failbit)
	{
		this->status = "404 Not Found";
		this->leftlen = -1;
	}
	istream::pos_type old_pos = this->f.tellg();
	this->f.seekg(0, ios_base::end);
	istream::pos_type size = this->f.tellg();
	this->f.seekg(old_pos);
	this->leftlen = long(size);
	this->len = long(size);
	return;
}

//���첢���ͱ���ͷ
string mksendpk::sendheader()
{
	string t = "HTTP/1.1 ";
	//�������200 OK����404��Ӧ����ͷ
	if (this->status != "200 OK")
	{
		t = t + this->status + "\r\nContent-Length: 0\r\n";
		return t;
	}
	t = t + status + "\r\nServer:Mao\r\nContent-Length:" + to_string(len) + "\r\nContent-Type:" + this->type + "\r\n\r\n";
	return t;
}

//�ֶζ�ȡ������������ļ�����
int mksendpk::sendmsg(SOCKET s)
{
	int nrc;
	//DATABUFΪ��������С
	memset(buffer, '\0', DATABUF);
	if (leftlen == -1)
		return -2;
	//���϶�ȡ��������С�����ݲ�����ֱ��ȫ��������
	while (leftlen > 0)
	{
		if (leftlen >= DATABUF)
		{
			this->f.read(this->buffer, DATABUF);
			this->leftlen -= DATABUF;
			nrc = send(s, this->buffer, DATABUF, 0);
		}
		else
		{
			this->f.read(this->buffer, this->leftlen);
			nrc = send(s, this->buffer, this->leftlen, 0);
			this->leftlen = 0;
		}
		//printf("*****send*****\n%s\n*****end*****%d\n", buffer, nrc);
		if (nrc == SOCKET_ERROR)
		{
			return SOCKET_ERROR;
		}
	}
	return 0;
}