#include "TCPsender.h"

TCPsender::TCPsender():base(0),nextseqnum(0)
{
	for (int i = 0; i < MAXNUM; i++)
		acknum[i] = 0;
}

TCPsender::~TCPsender()
{

}

bool TCPsender::getWaitingState()
{
	//窗口是否已满，要保证循环
	if (nextseqnum % MAXNUM == (base + WINLEN) % MAXNUM)
		return true;
	else
		return false;
}

bool TCPsender::send(const Message &message)
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
		//TCP只使用一个计时器，选择在窗口只有一个分组时对该分组计时
		if (base == nextseqnum)
		{
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

void TCPsender::receive(const Packet &ackPkt)
{
	//检查校验和是否正确
	int checkSum = pUtils->calculateCheckSum(ackPkt);

	//如果校验和正确
	if (checkSum == ackPkt.checksum)
	{
		//判断接收到的序号是否在滑动窗口内(由于为期待序号所以先减一)
		int flag = 0;
		for (int i = base; i != nextseqnum; i = (i + 1) % MAXNUM)
		{
			if (i == (ackPkt.acknum+MAXNUM)%MAXNUM)
			{
				flag = 1;
				break;
			}
		}
		if (flag)
		{
			base = (ackPkt.acknum + 1) % MAXNUM;
			printwin();
			pUtils->printPacket("发送方正确收到确认", ackPkt);
			if (base == nextseqnum)
				pns->stopTimer(SENDER, this->win[nextseqnum].seqnum);
			else
			{
				//窗口非空则对窗口内第一个分组计时
				pns->stopTimer(SENDER, this->win[nextseqnum].seqnum);
				pns->startTimer(SENDER, Configuration::TIME_OUT, this->win[nextseqnum].seqnum);
			}
		}
		else
		{
			acknum[ackPkt.acknum]++;
			//三次冗余ack则重传其期待分组
			if (acknum[ackPkt.acknum] == 3)
			{
				pns->sendToNetworkLayer(RECEIVER, this->win[ackPkt.acknum+1]);
				pUtils->printPacket("三次冗余ACK，重发其期待报文", this->win[ackPkt.acknum+1]);
				for (int i = 0; i < MAXNUM; i++)
					acknum[i] = 0;
			}
		}

	}
}

void TCPsender::timeoutHandler(int seqNum)
{
	//调试时发现base=nextseqnum时会不停超时
	if (base == nextseqnum)
		return;
	pns->stopTimer(SENDER, seqNum);
	pns->startTimer(SENDER, Configuration::TIME_OUT, seqNum);
	pns->sendToNetworkLayer(RECEIVER, this->win[base]);
	pUtils->printPacket("超时，重发第一个报文", this->win[base]);
	for (int i = 0; i < MAXNUM; i++)
		acknum[i] = 0;
}

void TCPsender::printwin()
{
	printf("-----滑动窗口-----\n");
	for (int i = base; i != nextseqnum; i = (i + 1) % MAXNUM)
	{
		printf("序号:%d\t",i);
		pUtils->printPacket("",win[i]);
	}
	printf("------------------\n");
}