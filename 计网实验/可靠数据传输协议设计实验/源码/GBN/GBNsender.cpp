#include "GBNsender.h"

using namespace std;

GBNsender::GBNsender():base(0),nextseqnum(0),waitingState(false)
{

}

GBNsender::~GBNsender()
{

}

bool GBNsender::getWaitingState()
{
	//窗口是否已满，要保证循环
	if (nextseqnum % MAXNUM == (base + WINLEN)%MAXNUM)
		waitingState = true;
	else
		waitingState = false;
	return waitingState;
}

bool GBNsender::send(const Message &message)
{
	if (!getWaitingState())
	{
		this->win[nextseqnum].acknum = -1; //忽略该字段
		this->win[nextseqnum].seqnum = this->nextseqnum;
		this->win[nextseqnum].checksum = 0;
		memcpy(this->win[nextseqnum].payload, message.data, sizeof(message.data));
		this->win[nextseqnum].checksum = pUtils->calculateCheckSum(win[nextseqnum]);
		pUtils->printPacket("发送方发送报文", this->win[nextseqnum]);

		//调用模拟网络环境的sendToNetworkLayer，通过网络层发送到对方
		pns->sendToNetworkLayer(RECEIVER, this->win[nextseqnum]);
		if (base == nextseqnum)
		{
			//启动发送方定时器
			pns->startTimer(SENDER, Configuration::TIME_OUT, this->win[nextseqnum].seqnum);
		}
		nextseqnum = (nextseqnum + 1) % MAXNUM;
		printwin();
	}
	else
	{
		printf("窗口已满！\n");
		return false;
	}
	return true;
}

void GBNsender::receive(const Packet &ackPkt)
{
	//检查校验和是否正确
	int checkSum = pUtils->calculateCheckSum(ackPkt);

	//如果校验和正确
	if (checkSum == ackPkt.checksum)
	{
		//判断接收到的序号是否在滑动窗口内
		int flag = 0;
		for (int i = base; i != nextseqnum; i = (i + 1) % MAXNUM)
		{
			if (i == ackPkt.acknum)
			{
				flag = 1;
				break;
			}
		}
		if (!flag)
		{
			return;
		}
		base = (ackPkt.acknum + 1) % MAXNUM;
		//printf("\n--------base:%d  nextseqnum:%d--------\n", base, nextseqnum);
		//cout << waitingState << endl;
		pUtils->printPacket("发送方正确收到确认", ackPkt);
		printwin();
		if (base == nextseqnum)
			pns->stopTimer(SENDER, this->win[nextseqnum].seqnum);
		else
		{
			pns->stopTimer(SENDER, this->win[nextseqnum].seqnum);
			pns->startTimer(SENDER, Configuration::TIME_OUT, this->win[nextseqnum].seqnum);
		}
	}
}

void GBNsender::timeoutHandler(int seqNum)
{
	//调试时发现base=nextseqnum时会不停超时
	if (base == nextseqnum)
		return;
	pns->stopTimer(SENDER,seqNum);
	pns->startTimer(SENDER, Configuration::TIME_OUT, seqNum);
	for (int i = base; i != nextseqnum; i = (i + 1) % MAXNUM)
	{
		pns->sendToNetworkLayer(RECEIVER, this->win[i]);
		pUtils->printPacket("超时，重发上次发送的报文",this->win[i]);
	}
}

void GBNsender::printwin()
{
	printf("-----滑动窗口-----\n");
	for (int i = base; i != nextseqnum; i = (i + 1) % MAXNUM)
	{
		printf("序号:%d\t", i);
		pUtils->printPacket("", win[i]);
	}
	printf("------------------\n");
}
