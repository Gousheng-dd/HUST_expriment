#pragma once
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

class TCPreceiver :public RdtReceiver
{
private:
	int expectSequenceNumberRcvd;
	Packet lastAckPkt;
public:
	TCPreceiver();
	~TCPreceiver();
	void receive(const Packet &packet);
};