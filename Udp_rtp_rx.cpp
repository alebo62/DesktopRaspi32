#include "Udp.h"
#include  <QDebug>

QByteArray ba_udp_test = { "hello" };
void Udp::readPendDgrmRtp()
{
	int rcv_rtp;
	QHostAddress ha;
	ushort port;
	
	ba_udp_rtp.resize((int)udp_sock_rtp->pendingDatagramSize());
	udp_sock_rtp->readDatagram(ba_udp_rtp.data(), ba_udp_rtp.size(), &ha, &port);
	
	for (rcv_rtp = 0; rcv_rtp < reader->udp_num; rcv_rtp++)
		if (QHostAddress(reader->udp_ip[rcv_rtp]) == ha)
			break;
	
	
	if (ba_udp_rtp.at(3) ==  0x24) // connect request
	{
		qDebug() << "rtp connect";
		memcpy((char*)messagesHm785->ack_connect + 4, ba_udp_rtp.data() + 4, 13);
		messagesHm785->ack_connect[12] = 0x04;
		udp_sock_rtp->writeDatagram((char*) messagesHm785->ack_connect_rtp, 15, QHostAddress(reader->udp_ip[rcv_rtp]), reader->udp_port_rtp);
		udp_sock_rtp->flush();
	}
	else if (ba_udp_rtp.at(3) == 0x02) // heatbeat
	{
		qDebug() << "rtp heatbeat" << rcv_rtp;
		udp_sock_rtp->writeDatagram((char*) messagesHm785->ack_heatbeat, 6, QHostAddress(reader->udp_ip[rcv_rtp]), reader->udp_port_rtp);
		udp_sock_rtp->flush();
	}
	else 
	{
		qDebug() << rcv_rtp << ba_udp_rtp.length();
		if (rcv_rtp == 0)
		{
			
			uint16_t temp_16[480];
			for (int i = 0; i < 480; i++)
				temp_16[i] = static_cast<quint16>(MuLaw_Decode(static_cast<qint8>(ba_udp_rtp.at(i + 40))));
			
			sound->frames = snd_pcm_writei(sound->handle_play, temp_16, 480);
			
			if (sound->frames < 0)
				sound->frames = snd_pcm_recover(sound->handle_play, sound->frames, 0);
		}
	}

	//qDebug() << "udp rtp rx: " << rcv << ba_udp_rtp.size();
}