#include "SRsender.h"

using namespace std;

SRsender::SRsender() :base(0), nextseqnum(0)
{
	for (int i = 0; i < MAXNUM; i++)
		ack[i] = false;
}

SRsender::~SRsender()
{

}

bool SRsender::getWaitingState()
{
	//窗口是否已满，要保证循环
	if (nextseqnum % MAXNUM == (base + WINLEN) % MAXNUM)
		return true;
	else
		return false;
}

bool SRsender::send(const Message &message)
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
		//启动发送方定时器
		pns->startTimer(SENDER, Configuration::TIME_OUT, this->win[nextseqnum].seqnum);
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

void SRsender::receive(const Packet &ackPkt)
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
		if (flag)
		{
			ack[ackPkt.acknum] = true;
			pUtils->printPacket("发送方正确收到确认", ackPkt);
			pns->stopTimer(SENDER, ackPkt.acknum);
			if (ackPkt.acknum == base)
			{
				for (int i = base; ack[i] == true; i = (i + 1) % MAXNUM)
				{
					base = (base + 1) % MAXNUM;
					printwin();
					ack[i] = false;
				}
			}
		}
	}
}

void SRsender::timeoutHandler(int seqNum)
{
	
	pns->stopTimer(SENDER, seqNum);
	pns->startTimer(SENDER, Configuration::TIME_OUT, seqNum);
	//重发超时的分组
	pns->sendToNetworkLayer(RECEIVER, this->win[seqNum]);
	pUtils->printPacket("超时，重发上次发送的报文", this->win[seqNum]);
}

void SRsender::printwin()
{
	printf("-----发送方滑动窗口-----\n");
	for (int i = base; i != nextseqnum; i = (i + 1) % MAXNUM)
	{
		printf("序号:%d\t", i);
		pUtils->printPacket("", win[i]);
	}
	printf("------------------------\n");
}