// lab2TCP.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "TCPreceiver.h"
#include "TCPsender.h"
#include "stdafx.h"

int main()
{
	RdtSender *ps = new TCPsender();
	RdtReceiver *pr = new TCPreceiver();
	//pns->setRunMode(0); //VERBOS模式
	pns->setRunMode(1); //安静模式
	pns->init();
	pns->setRtdSender(ps);
	pns->setRtdReceiver(pr);
	pns->setInputFile("F://comnet/input.txt");
	pns->setOutputFile("output.txt");
	pns->start();
	delete ps;
	delete pr;
	//指向唯一的工具类实例，只在main函数结束前delete
	delete pUtils;
	//指向唯一的模拟网络环境类实例，只在main函数结束前delete
	delete pns;
	return 0;
}

