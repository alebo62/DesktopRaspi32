#include "Udp.h"
#include  <QDebug>

QByteArray ba_udp_tst = { "hello" };
void Udp::readPendDgrmRcp()
{
	
	QHostAddress ha;
	ushort port;
	
	ba_udp_rcp.resize((int)udp_sock_rcp->pendingDatagramSize());
	udp_sock_rcp->readDatagram(ba_udp_rcp.data(), ba_udp_rcp.size(), &ha, &port);
	
	for (rcv_rcp = 0; rcv_rcp < reader->udp_num; rcv_rcp++)
		if (QHostAddress(reader->udp_ip[rcv_rcp]) == ha)
			break;
	
	if (ba_udp_rcp.at(3) == 0x02) // heatbeat
	{
		if (connection[rcv_rcp] == 2)
		{
			udp_sock_rcp->writeDatagram((char*) messagesHm785->ack_heatbeat, 6, QHostAddress(reader->udp_ip[rcv_rcp]), reader->udp_port_rcp);
			//radioConn_tim->start();
			//qDebug() << "heartbeat";
		}
		else if (connection[rcv_rcp] == 1)
		{
			connection[rcv_rcp] = 2;
			checksum(messagesHm785->zone_ch);
			send_command[4] = send_req_id >> 8;
			send_command[5] = send_req_id & 0xFF;
			memcpy(send_command + 6, messagesHm785->zone_ch, messagesHm785->zone_ch[3] + 7);
			udp_sock_rcp->writeDatagram((char*)send_command, messagesHm785->zone_ch[3] + 7 + 6, QHostAddress(reader->udp_ip[rcv_rcp]), reader->udp_port_rcp);
			send_req_id++;
		}
		else if (connection[rcv_rcp] == 0)
		{
			udp_sock_rcp->writeDatagram((char*)messagesHm785->disconn, 6, QHostAddress(reader->udp_ip[rcv_rcp]), reader->udp_port_rcp);
		}
	}
	else if (ba_udp_rcp.at(3) & 0x01)// its ack
	{
		rcp_req_id = ((quint16)ba_udp_rcp.at(4) << 8) + (quint16)ba_udp_rcp.at(5);
	}
	else if (ba_udp_rcp.at(3) == 0x20 || ba_udp_rcp.at(3) == 0x00)
	{
		if (ba_udp_rcp.at(3) == 0x20)
		{
			if (ba_udp_rcp.at(6) == (char)0x83 && ba_udp_rcp.at(7) == 0x04 && ba_udp_rcp.at(12) == 0x04 && ba_udp_rcp.at(13) == 0x01)
			{
				memcpy((char*)messagesHm785->ack, ba_udp_rcp.data(), 15);
				messagesHm785->ack[3] = 0x21;
				udp_sock_rcp->writeDatagram((char*)messagesHm785->ack, 15, QHostAddress(reader->udp_ip[rcv_rcp]), reader->udp_port_rcp);
				// receive
				if (ba_udp_rcp.at(16) == 0x44 && ba_udp_rcp.at(17) == (char)0xB8) {
					//                    checksum(dig_audio_rx);
					//                    send_command[4] = send_req_id >> 8;
					//                    send_command[5] = send_req_id & 0xFF;
					//                    memcpy(send_command + 6, dig_audio_rx, dig_audio_rx[3] + 7);
					//                    udp_sock_rcp->writeDatagram((char*)send_command, dig_audio_rx[3] + 7 + 6, QHostAddress(radio_ip), RCP);
					//                    udp_sock_rcp->flush();
					//                    send_req_id++;
					call_decoding();
				}
				// server initiated call
				else if ((ba_udp_rcp.at(16) == 0x41) && (ba_udp_rcp.at(17) == (char)0x88))
					press_ptt();
				else if ((ba_udp_rcp.at(16) == 0x41) && (ba_udp_rcp.at(17) == (char)0x80))
					send_call_report();
				else if ((ba_udp_rcp.at(16) == 0x43) && (ba_udp_rcp.at(17) == (char)0xB8))
				{
					if (ba_udp_rcp.at(20) == 2)
					{
						//qDebug() << "ptt reply";
//						sCallReport.callType = CallsDecoder[static_cast<uint>(ba_udp_rcp.at(24))];
//						sCallReport.callState = eCallHandTime;
//						memcpy(&sCallReport.calledId, &sRegMsgReport.radio_id, 4);
//						sCallReport.receivedId[3] = ba_udp_rcp.at(26);
//						sCallReport.receivedId[2] = ba_udp_rcp.at(27);
//						sCallReport.receivedId[1] = ba_udp_rcp.at(28);
//						if (tcp_srv.state() ==  QAbstractSocket::ConnectedState)
//						{
//							tcp_srv.write(reinterpret_cast<char*>(&sCallReport), sizeof(sCallReport));
//							tcp_srv.flush();
//						}
						//Radio_Reg_State = WAIT_STOP_CALL_ENDED;
//#ifdef DBG
//						qDebug() << "WAIT_STOP_CALL_HANGIN";
//#endif
					}
					else if (ba_udp_rcp.at(20) == 3)
					{
						//						sCallReport.callType = CallsDecoder[static_cast<uint>(ba_udp_rcp.at(24))];
						//						sCallReport.callState = eCallEnded;
						//						memcpy(sCallReport.calledId, sRegMsgReport.radio_id, 4);
						//						sCallReport.receivedId[3] = ba_udp_rcp.at(26);
						//						sCallReport.receivedId[2] = ba_udp_rcp.at(27);
						//						sCallReport.receivedId[1] = ba_udp_rcp.at(28);
						//						if (tcp_srv.state() ==  QAbstractSocket::ConnectedState)
						//						{
						//							tcp_srv.write(reinterpret_cast<char*>(&sCallReport), sizeof(sCallReport));
						//							tcp_srv.flush();
						//						}
												//Radio_Reg_State = READY;
#ifdef DBG
						qDebug() << "WAIT_STOP_CALL_ENDED";
#endif
					}
				}
				else if ((ba_udp_rcp.at(16) == 0x49) && (ba_udp_rcp.at(17) == (char)0x88)) // replay radio disable
				{
					// result [20]          // ip[24-21]
					send_reply(1);
				}
				else if ((ba_udp_rcp.at(16) == 0x4A) && (ba_udp_rcp.at(17) == (char)0x88)) // replay radio enblbe
				{
					// result [20]                    // ip[24-21]
					send_reply(2);
				}
				else if ((ba_udp_rcp.at(16) == 0x33) && (ba_udp_rcp.at(17) == (char)0x88)) // replay check radio
				{
					// result [20]                    // ip[24-21]
					send_reply(0);

				}
				else if ((ba_udp_rcp.at(16) == 0x34) && (ba_udp_rcp.at(17) == (char)0x88)) // replay monitor
				{
					// result [20]                    // ip[24-21]
					send_reply(3);
				}
				else
				{
					radio_init();
				}
			}
			else 
			{
				qDebug() << "Length wrong!!!! " << ba_udp_rcp.toHex();
			}
		}
		else 
		{
			memcpy((char*)messagesHm785->ack, ba_udp_rcp.data(), 6);
			messagesHm785->ack[3] |= 0x01;
			udp_sock_rcp->writeDatagram((char*) messagesHm785->ack, 6, QHostAddress(reader->udp_ip[rcv_rcp]), reader->udp_port_rcp);
			udp_sock_rcp->flush();
		}		
	}
	else if (ba_udp_rcp.at(3) ==  0x24) // connect request
	{
		qDebug() << "rcp conn req";
		memcpy((char*)messagesHm785->ack_connect + 4, ba_udp_rcp.data() + 4, 11);
		udp_sock_rcp->writeDatagram((char*) messagesHm785->ack_connect, 15, QHostAddress(reader->udp_ip[rcv_rcp]), reader->udp_port_rcp);
		connection[rcv_rcp] = 1;
	}
	else if (ba_udp_rcp.at(3) ==  0x28) // disconnect request
	{
		memcpy((char*)messagesHm785->ack_connect + 4, ba_udp_rcp.data() + 4, 11);
		udp_sock_rcp->writeDatagram((char*) messagesHm785->ack_connect, 15, QHostAddress(reader->udp_ip[rcv_rcp]), reader->udp_port_rcp);
		connection = 0;
	}
	//qDebug() << "udp rx: " << rcv << ba_udp_rcp.size();
}
