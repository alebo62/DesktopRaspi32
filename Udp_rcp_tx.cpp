#include "Udp.h"

void Udp::make_call(qint32 id, qint32 type, qint32 tx_rcp)
{
	messagesHm785->call_req[5] = static_cast<quint8>(type); // call type
	messagesHm785->call_req[6] = static_cast<quint8>(id       & 0xFF);
	messagesHm785->call_req[7] = static_cast<quint8>(id >> 8  & 0xFF);
	messagesHm785->call_req[8] = static_cast<quint8>(id >> 16 & 0xFF);
	messagesHm785->call_req[9] = 0;
	
	checksum(messagesHm785->call_req);
	send_command[4] = send_req_id >> 8;
	send_command[5] = send_req_id & 0xFF;
	memcpy(send_command + 6, messagesHm785->call_req, messagesHm785->call_req[3] + 7);
	udp_sock_rcp->writeDatagram((char*)send_command, messagesHm785->call_req[3] + 7 + 6, QHostAddress(reader->udp_ip[tx_rcp]), reader->udp_port_rcp);
	udp_sock_rcp->flush();
	send_req_id++;
	// and wait 0x4188 ...
}

void Udp::make_stop_call(qint32 tx_rcp)
{
	checksum(messagesHm785->ptt_release_req);
	send_command[4] = send_req_id >> 8;
	send_command[5] = send_req_id & 0xFF;
	memcpy(send_command + 6, messagesHm785->ptt_release_req, messagesHm785->ptt_release_req[3] + 7);
	udp_sock_rcp->writeDatagram((char*)send_command, messagesHm785->ptt_release_req[3] + 7 + 6, QHostAddress(reader->udp_ip[tx_rcp]), reader->udp_port_rcp);
	send_req_id++;
}

void Udp::select_channel(qint32 channel, qint32 radio_number, qint32 zone /* = 1 */)
{
	
	checksum(messagesHm785->zone_ch);
	send_command[4] = send_req_id >> 8;
	send_command[5] = send_req_id & 0xFF;
	memcpy(send_command + 6, messagesHm785->zone_ch, messagesHm785->zone_ch[3] + 7);
	udp_sock_rcp->writeDatagram((char*)send_command, messagesHm785->zone_ch[3] + 7 + 6, QHostAddress(reader->udp_ip[tx_rcp]), reader->udp_port_rcp);
	send_req_id++;
}