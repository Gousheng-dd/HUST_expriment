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
	//�����Ƿ�������Ҫ��֤ѭ��
	if (nextseqnum % MAXNUM == (base + WINLEN) % MAXNUM)
		return true;
	else
		return false;
}

bool SRsender::send(const Message &message)
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
		//�������ͷ���ʱ��
		pns->startTimer(SENDER, Configuration::TIME_OUT, this->win[nextseqnum].seqnum);
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

void SRsender::receive(const Packet &ackPkt)
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
		if (flag)
		{
			ack[ackPkt.acknum] = true;
			pUtils->printPacket("���ͷ���ȷ�յ�ȷ��", ackPkt);
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
	//�ط���ʱ�ķ���
	pns->sendToNetworkLayer(RECEIVER, this->win[seqNum]);
	pUtils->printPacket("��ʱ���ط��ϴη��͵ı���", this->win[seqNum]);
}

void SRsender::printwin()
{
	printf("-----���ͷ���������-----\n");
	for (int i = base; i != nextseqnum; i = (i + 1) % MAXNUM)
	{
		printf("���:%d\t", i);
		pUtils->printPacket("", win[i]);
	}
	printf("------------------------\n");
}