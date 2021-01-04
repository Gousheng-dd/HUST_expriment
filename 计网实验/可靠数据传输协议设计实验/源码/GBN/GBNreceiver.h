#include <stdio.h>
#include <string.h>
#include <iostream>
#include "DataStructure.h"
#include "RdtReceiver.h"
#include "Tool.h"
#include "Global.h"
#include "RandomEventEnum.h"
#include "NetworkService.h"
//#include "GBNsender.h"

#define MAXNUM 8

class GBNreceiver:public RdtReceiver
{
private:
	int expectSequenceNumberRcvd;
	Packet lastAckPkt;
	
public:
	GBNreceiver();
	virtual ~GBNreceiver();
	void receive(const Packet &packet);
};

