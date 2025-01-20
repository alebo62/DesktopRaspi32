#include "Udp.h"
#include <QDebug>



Udp::Udp(QObject *parent)
	: QObject(parent)
{
	messagesHm785 = new Messages_HM785();
	
	radioConn_tim = new QTimer();
	connect(radioConn_tim, SIGNAL(timeout()), this, SLOT(rad_conn_tim_slot()));
	radioConn_tim->setInterval(1000);
	
	udp_sock_rtp = new QUdpSocket();
	udp_sock_rtp->bind(QHostAddress(reader->onega_ip), reader->udp_port_rtp);
	connect(udp_sock_rtp, SIGNAL(readyRead()), this, SLOT(readPendDgrmRtp()));
	
	udp_sock_rcp = new QUdpSocket();
	udp_sock_rcp->bind(QHostAddress(reader->onega_ip), reader->udp_port_rcp);
	connect(udp_sock_rcp, SIGNAL(readyRead()), this, SLOT(readPendDgrmRcp()));
	
	connection = new u_int32_t [reader->udp_num];
}



void Udp::send_reply(int req_type)
{
//	sCtrlReply.result = ba_3005.at(20);
//	sCtrlReply.radio_id[3] = ba_3005.at(21);
//	sCtrlReply.radio_id[2] = ba_3005.at(22);
//	sCtrlReply.radio_id[1] = ba_3005.at(23);
//	sCtrlReply.req_type = req_type;//
//	if (tcp_srv.state() ==  QAbstractSocket::ConnectedState)
//	{
//		tcp_srv.write(reinterpret_cast<char*>(&sCtrlReply), sizeof(sCtrlReply));
//		tcp_srv.flush();
//	}
}