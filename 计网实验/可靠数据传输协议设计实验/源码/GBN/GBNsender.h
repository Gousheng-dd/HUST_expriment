#include <stdio.h>
#include <string.h>
#include <iostream>
#include "DataStructure.h"
#include "RdtSender.h"
#include "Tool.h"
#include "Global.h"
#include "RandomEventEnum.h"
#include "NetworkService.h"

#define WINLEN 4
#define MAXNUM 8

class GBNsender :public RdtSender
{
private:
	int base;
	int nextseqnum;
	Packet win[MAXNUM];//»º³åÇø
	bool waitingState;
public:
	GBNsender();
	virtual ~GBNsender();
	bool getWaitingState();
	bool send(const Message &message);
	void receive(const Packet &ackPkt);
	void timeoutHandler(int seqNum);
	void printwin();
};