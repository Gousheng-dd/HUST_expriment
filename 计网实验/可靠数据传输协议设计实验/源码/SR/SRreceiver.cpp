#include "SRreceiver.h"

using namespace std;

SRreceiver::SRreceiver():rcvbase(0)
{
	//初始状态下，上次发送的确认包的确认序号为-1，
	//使得当第一个接受的数据包出错时该确认报文的确认号为-1
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
	//检查校验和是否正确
	int checksum = pUtils->calculateCheckSum(packet);
	//如果校验和正确
	if (checksum == packet.checksum)
	{
		int flagin = 0, flagbe = 0;
		//判断序号在当前滑动窗口[rcvbase,rcvbase+N-1]
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
		//序号在当前滑动窗口[rcvbase,rcvbase+N-1]
		if (flagin)
		{
			pUtils->printPacket("接收方正确收到发送方的报文", packet);
			lastAckPkt.acknum = packet.seqnum; //确认序号等于收到的报文序号
			lastAckPkt.checksum = pUtils->calculateCheckSum(lastAckPkt);
			pUtils->printPacket("接收方发送确认报文", lastAckPkt);
			//调用模拟网络环境的sendToNetworkLayer，通过网络层发送确认报文到对方
			pns->sendToNetworkLayer(SENDER, lastAckPkt);
			win[packet.seqnum] = true;
			buf[packet.seqnum] = packet;
			if (packet.seqnum == rcvbase)
			{
				printf("滑动前：\n");
				printwin();
				for (int i = rcvbase; win[i] == true; i = (i + 1) % MAXNUM)
				{
					//取出Message，向上递交给应用层
					Message msg;
					memcpy(msg.data, buf[i].payload, sizeof(buf[i].payload));
					pns->delivertoAppLayer(RECEIVER, msg);
					//窗口向前滑动
					win[i] = false;
					rcvbase = (rcvbase + 1) % MAXNUM;
				}
				printf("滑动后：\n");
				printwin();
			}
		}
		//序号在[rcvbase-N,rcvbase-1]
		else if (flagbe)
		{
			
			pUtils->printPacket("接收方没有正确收到发送方的报文,报文序号不对", packet);
			lastAckPkt.acknum = packet.seqnum; //确认序号等于收到的报文序号
			lastAckPkt.checksum = pUtils->calculateCheckSum(lastAckPkt);
			pUtils->printPacket("接收方发送确认报文", lastAckPkt);
			//调用模拟网络环境的sendToNetworkLayer，通过网络层发送上次的确认报文
			pns->sendToNetworkLayer(SENDER, lastAckPkt);
		}
	}
	else
	{
		pUtils->printPacket("接收方没有正确收到发送方的报文,数据校验错误", packet);
	}
}

void SRreceiver::printwin()
{
	printf("-----接收方滑动窗口-----\n");
	for (int i = 0; i < RCVWINLEN ; i++)
	{
		int num = (rcvbase + i) % MAXNUM;
		printf("序号:%d\t", num);
		if (win[num])
			pUtils->printPacket("", buf[num]);
		else
			printf("\n");
	}
	printf("------------------------\n");
}