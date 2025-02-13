#pragma once

#include <QFile>
#include <QObject>
#include <array>


class SettingsReader : public QObject
{
	Q_OBJECT
		
	void read_server_settings();

	void read_radios_settings(QString s, int i);
	
	void read_favorite();
	
	void write_favorite();
	
	void display_favorites();
public: 
	explicit SettingsReader(QObject* parent = nullptr);
	
	int udp_num;
	QString* udp_ip;
	ushort udp_port_rtp;
	ushort udp_port_rcp;
	QString onega_ip;
	int* max_chan;
	
	struct Server
	{
		QString ip;
		ushort rcp;
		ushort rtp;
		ushort tcp;
		ushort udp;		
		int directions;
	};
	
	struct Contact {
		quint32 id;
		QString name;
		qint32 channel;
	};
	
	struct Radio {
		QString name;
		QString ip;
		qint32 type;
		qint32 an_dig;
		qint32 channels;
		qint32 num_contacts_gr;
		qint32 num_contacts_ab;

		std::vector<Contact> contact_gr;
		std::vector<Contact> contact_ab;
	};
	Server server;
	std::array<Radio, 4> radio;
	
	
	// std::vector<int>								избранные для канала до 4-х
	// std::vector<std::vector<int>>				избранные для радиостанции до 4-х
	// std::vector<std::vector<std::vector<int>>>	избранные для всех радиостанций    
	std::vector<std::vector<std::vector<int>>> favForAllRadio;

};