#include "SRreceiver.h"

using namespace std;

SRreceiver::SRreceiver():rcvbase(0)
{
	//��ʼ״̬�£��ϴη��͵�ȷ�ϰ���ȷ�����Ϊ-1��
	//ʹ�õ���һ�����ܵ����ݰ�����ʱ��ȷ�ϱ��ĵ�ȷ�Ϻ�Ϊ-1
	lastAckPkt.acknum = -1;
	lastAckPkt.checksum = 0;
	lastAckPkt.seqnum = -1;
	for (int i = 0; i < Configuration::PAYLOAD_SIZE; i++)
		lastAckPkt.payload[i] = '.';
	lastAckPkt.checksum = pUtils->calculateCheckSum(lastAckPkt);

	for (int i = 0; i < MAXNUM; i++)
		win[i] = false;
}

SRreceiver::~SRreceiver()
{

}

void SRreceiver::receive(const Packet &packet)
{
	//printf("++rcvbase:%d++\n", rcvbase);
	//���У����Ƿ���ȷ
	int checksum = pUtils->calculateCheckSum(packet);
	//���У�����ȷ
	if (checksum == packet.checksum)
	{
		int flagin = 0, flagbe = 0;
		//�ж�����ڵ�ǰ��������[rcvbase,rcvbase+N-1]
		for (int j = rcvbase; j != (rcvbase + RCVWINLEN ) % MAXNUM; j = (j + 1) % MAXNUM)
		{
			if (packet.seqnum == j)
			{
				flagin = 1;
				break;
			}
		}
		if (!flagin)
		{
			for (int j = (rcvbase - 1 + MAXNUM) % MAXNUM; j != (rcvbase - RCVWINLEN - 1 + MAXNUM) % MAXNUM; j = (j - 1 + MAXNUM) % MAXNUM)
			{
				if (packet.seqnum == j)
				{
					flagbe = 1;
					break;
				}
			}
		}
		//����ڵ�ǰ��������[rcvbase,rcvbase+N-1]
		if (flagin)
		{
			pUtils->printPacket("���շ���ȷ�յ����ͷ��ı���", packet);
			lastAckPkt.acknum = packet.seqnum; //ȷ����ŵ����յ��ı������
			lastAckPkt.checksum = pUtils->calculateCheckSum(lastAckPkt);
			pUtils->printPacket("���շ�����ȷ�ϱ���", lastAckPkt);
			//����ģ�����绷����sendToNetworkLayer��ͨ������㷢��ȷ�ϱ��ĵ��Է�
			pns->sendToNetworkLayer(SENDER, lastAckPkt);
			win[packet.seqnum] = true;
			buf[packet.seqnum] = packet;
			if (packet.seqnum == rcvbase)
			{
				printf("����ǰ��\n");
				printwin();
				for (int i = rcvbase; win[i] == true; i = (i + 1) % MAXNUM)
				{
					//ȡ��Message�����ϵݽ���Ӧ�ò�
					Message msg;
					memcpy(msg.data, buf[i].payload, sizeof(buf[i].payload));
					pns->delivertoAppLayer(RECEIVER, msg);
					//������ǰ����
					win[i] = false;
					rcvbase = (rcvbase + 1) % MAXNUM;
				}
				printf("������\n");
				printwin();
			}
		}
		//�����[rcvbase-N,rcvbase-1]
		else if (flagbe)
		{
			
			pUtils->printPacket("���շ�û����ȷ�յ����ͷ��ı���,������Ų���", packet);
			lastAckPkt.acknum = packet.seqnum; //ȷ����ŵ����յ��ı������
			lastAckPkt.checksum = pUtils->calculateCheckSum(lastAckPkt);
			pUtils->printPacket("���շ�����ȷ�ϱ���", lastAckPkt);
			//����ģ�����绷����sendToNetworkLayer��ͨ������㷢���ϴε�ȷ�ϱ���
			pns->sendToNetworkLayer(SENDER, lastAckPkt);
		}
	}
	else
	{
		pUtils->printPacket("���շ�û����ȷ�յ����ͷ��ı���,����У�����", packet);
	}
}

void SRreceiver::printwin()
{
	printf("-----���շ���������-----\n");
	for (int i = 0; i < RCVWINLEN ; i++)
	{
		int num = (rcvbase + i) % MAXNUM;
		printf("���:%d\t", num);
		if (win[num])
			pUtils->printPacket("", buf[num]);
		else
			printf("\n");
	}
	printf("------------------------\n");
}