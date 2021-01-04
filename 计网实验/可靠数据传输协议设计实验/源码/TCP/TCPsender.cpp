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
	//�����Ƿ�������Ҫ��֤ѭ��
	if (nextseqnum % MAXNUM == (base + WINLEN) % MAXNUM)
		return true;
	else
		return false;
}

bool TCPsender::send(const Message &message)
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
		//TCPֻʹ��һ����ʱ����ѡ���ڴ���ֻ��һ������ʱ�Ը÷����ʱ
		if (base == nextseqnum)
		{
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

void TCPsender::receive(const Packet &ackPkt)
{
	//���У����Ƿ���ȷ
	int checkSum = pUtils->calculateCheckSum(ackPkt);

	//���У�����ȷ
	if (checkSum == ackPkt.checksum)
	{
		//�жϽ��յ�������Ƿ��ڻ���������(����Ϊ�ڴ���������ȼ�һ)
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
			pUtils->printPacket("���ͷ���ȷ�յ�ȷ��", ackPkt);
			if (base == nextseqnum)
				pns->stopTimer(SENDER, this->win[nextseqnum].seqnum);
			else
			{
				//���ڷǿ���Դ����ڵ�һ�������ʱ
				pns->stopTimer(SENDER, this->win[nextseqnum].seqnum);
				pns->startTimer(SENDER, Configuration::TIME_OUT, this->win[nextseqnum].seqnum);
			}
		}
		else
		{
			acknum[ackPkt.acknum]++;
			//��������ack���ش����ڴ�����
			if (acknum[ackPkt.acknum] == 3)
			{
				pns->sendToNetworkLayer(RECEIVER, this->win[ackPkt.acknum+1]);
				pUtils->printPacket("��������ACK���ط����ڴ�����", this->win[ackPkt.acknum+1]);
				for (int i = 0; i < MAXNUM; i++)
					acknum[i] = 0;
			}
		}

	}
}

void TCPsender::timeoutHandler(int seqNum)
{
	//����ʱ����base=nextseqnumʱ�᲻ͣ��ʱ
	if (base == nextseqnum)
		return;
	pns->stopTimer(SENDER, seqNum);
	pns->startTimer(SENDER, Configuration::TIME_OUT, seqNum);
	pns->sendToNetworkLayer(RECEIVER, this->win[base]);
	pUtils->printPacket("��ʱ���ط���һ������", this->win[base]);
	for (int i = 0; i < MAXNUM; i++)
		acknum[i] = 0;
}

void TCPsender::printwin()
{
	printf("-----��������-----\n");
	for (int i = base; i != nextseqnum; i = (i + 1) % MAXNUM)
	{
		printf("���:%d\t",i);
		pUtils->printPacket("",win[i]);
	}
	printf("------------------\n");
}