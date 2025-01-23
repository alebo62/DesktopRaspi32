#include "Udp.h"

qint16 pre_mu_buffer[160];
qint8 mu_buffer[160];
char mic_buffer[320];


void Udp::slot_udp()
{
	memcpy((char*)pre_mu_buffer, sound->mic_buffer, 320);
	
	for (int i = 0; i < 160; i++)
		mu_buffer[i] = MuLaw_Encode(pre_mu_buffer[i]);
	
	memmove((char*)messagesHm785->aud_tx + 28, mu_buffer, 160);
	
	messagesHm785->seq_num++;
	messagesHm785->aud_tx[2] = messagesHm785->seq_num >> 8;
	messagesHm785->aud_tx[3] = messagesHm785->seq_num & 0xFF;
	
	messagesHm785->timestamp++;
	messagesHm785->aud_tx[4] = messagesHm785->timestamp >> 24;
	messagesHm785->aud_tx[5] = messagesHm785->timestamp >> 16 & 0xFF;
	messagesHm785->aud_tx[6] = messagesHm785->timestamp >> 8  & 0xFF;
	messagesHm785->aud_tx[7] = messagesHm785->timestamp		  & 0xFF;

	udp_sock_rtp->writeDatagram((char*)messagesHm785->aud_tx, 188, QHostAddress(reader->udp_ip[rcv_rtp]), reader->udp_port_rtp);
	
}