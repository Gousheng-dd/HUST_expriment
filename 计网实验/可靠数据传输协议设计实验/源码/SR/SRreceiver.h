#include <stdio.h>
#include <string.h>
#include <iostream>
#include "DataStructure.h"
#include "RdtReceiver.h"
#include "Tool.h"
#include "Global.h"
#include "RandomEventEnum.h"
#include "NetworkService.h"

#define MAXNUM 8
#define RCVWINLEN 3

class SRreceiver :public RdtReceiver
{
private:
	int rcvbase;
	Packet lastAckPkt;
	bool win[MAXNUM];//»¬¶¯´°¿Ú·¶Î§
	Packet buf[MAXNUM];//»º³åÇø

public:
	SRreceiver();
	virtual ~SRreceiver();
	void receive(const Packet &packet);
	void printwin();
};