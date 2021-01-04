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
	//�����Ƿ�������Ҫ��֤ѭ��
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
		this->win[nextseqnum].acknum = -1; //���Ը��ֶ�
		this->win[nextseqnum].seqnum = this->nextseqnum;
		this->win[nextseqnum].checksum = 0;
		memcpy(this->win[nextseqnum].payload, message.data, sizeof(message.data));
		this->win[nextseqnum].checksum = pUtils->calculateCheckSum(win[nextseqnum]);
		pUtils->printPacket("���ͷ����ͱ���", this->win[nextseqnum]);

		//����ģ�����绷����sendToNetworkLayer��ͨ������㷢�͵��Է�
		pns->sendToNetworkLayer(RECEIVER, this->win[nextseqnum]);
		if (base == nextseqnum)
		{
			//�������ͷ���ʱ��
			pns->startTimer(SENDER, Configuration::TIME_OUT, this->win[nextseqnum].seqnum);
		}
		nextseqnum = (nextseqnum + 1) % MAXNUM;
		printwin();
	}
	else
	{
		printf("����������\n");
		return false;
	}
	return true;
}

void GBNsender::receive(const Packet &ackPkt)
{
	//���У����Ƿ���ȷ
	int checkSum = pUtils->calculateCheckSum(ackPkt);

	//���У�����ȷ
	if (checkSum == ackPkt.checksum)
	{
		//�жϽ��յ�������Ƿ��ڻ���������
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
		pUtils->printPacket("���ͷ���ȷ�յ�ȷ��", ackPkt);
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
	//����ʱ����base=nextseqnumʱ�᲻ͣ��ʱ
	if (base == nextseqnum)
		return;
	pns->stopTimer(SENDER,seqNum);
	pns->startTimer(SENDER, Configuration::TIME_OUT, seqNum);
	for (int i = base; i != nextseqnum; i = (i + 1) % MAXNUM)
	{
		pns->sendToNetworkLayer(RECEIVER, this->win[i]);
		pUtils->printPacket("��ʱ���ط��ϴη��͵ı���",this->win[i]);
	}
}

void GBNsender::printwin()
{
	printf("-----��������-----\n");
	for (int i = base; i != nextseqnum; i = (i + 1) % MAXNUM)
	{
		printf("���:%d\t", i);
		pUtils->printPacket("", win[i]);
	}
	printf("------------------\n");
}
