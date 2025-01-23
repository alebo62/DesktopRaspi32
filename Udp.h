#pragma once

#include <QObject>
#include <QUdpSocket>
#include <QTimer>
#include "messages_hm785.h"
#include "SettingsReader.h"
#include  <Sound.h>
#include "alsa/asoundlib.h"


//extern MainWindow* w;
extern SettingsReader* reader;
extern Sound* sound;
class Udp : public QObject
{
	Q_OBJECT
	
	Messages_HM785* messagesHm785;

	quint8 send_command[256] = { 0x32, 0x42, 0, 0, 0, 0 };	
	quint8 conn[12] { 0x7e, 4, 0, 0xfe, 0x20, 0x10, 0, 0, 0, 0x0c, 0x60, 0xe1 };
	QTimer* radioConn_tim;
	quint32 rcv_rcp;
	quint32 rcv_rtp;
	quint32 tx_rcp;
	quint32 tx_rtp;
	QByteArray ba_udp_rtp;
	QByteArray ba_udp_rcp;
	uint16_t send_req_id = 0;
	uint16_t rcp_req_id = 0;
	uint32_t connection[4] {0};
	bool isRadioInit[4] {0};
	void checksum(unsigned char *ip);
	void crc(quint8* p, int len);
	void radio_init();	
	void send_reply(int req_type);
	void press_ptt();
	void call_decoding();	
	void send_call_report();
	qint16 MuLaw_Decode(qint8 number);
	qint16 ALaw_Decode(qint8 number);
	qint8 MuLaw_Encode(qint16 number);
	qint8 ALaw_Encode(qint16 number);
	
public:
	explicit Udp(QObject *parent = nullptr);
	
	//  До четырех направлений
	//QUdpSocket* udp_sock[4];
	QUdpSocket* udp_sock_rtp;
	QUdpSocket* udp_sock_rcp;
	
	void make_call(qint32 id, qint32 type, qint32 tx_rcp);
	void make_stop_call(qint32 radio_number);
	void select_channel(qint32 channel, qint32 tx_rcp, qint32 zone = 1);
	
	private slots :
		void readPendDgrmRtp();
	void readPendDgrmRcp();
	void rad_conn_tim_slot();	
	void slot_udp();
	
	
};