#include "SettingsReader.h"
#include <QDebug>

SettingsReader::SettingsReader(QObject* parent)
	: QObject(parent)
{
	udp_num = 2;
	onega_ip = "192.168.0.152";
	
	udp_ip = new QString[udp_num];
	udp_ip[0] = "192.168.0.140";
	udp_ip[1] = "192.168.0.141";
	
	//udp_port_rtp = new ushort[udp_num];
	udp_port_rtp = 3010;
	udp_port_rcp = 3005;
	
	max_chan = new int[udp_num];
	max_chan[0] = 3;
	max_chan[1] = 3;
	
	read_server_settings();
	
	for (size_t i = 0; i < server.directions; i++)
	{
		QString s = "settings" + QString::number(i) + ".dat";
		read_radios_settings(s, i);
	}
	
	read_favorite();
}


void SettingsReader::read_server_settings()
{
	QFile file;

	file.setFileName("settings.dat");
	
	bool res = file.open(QIODevice::ReadOnly | QIODevice::Text);

	if (res)
	{
		QString line = file.readLine();

		QStringList list = line.split(",");

		server.ip = onega_ip =  list.at(0);
		server.rcp = udp_port_rcp = list.at(1).toInt();
		server.rtp = udp_port_rtp = list.at(2).toInt();
		server.tcp = list.at(3).toUShort();
		server.udp = list.at(4).toUShort();
		server.directions = list.at(5).toInt();

		file.close();
	}
	else
	{
		qDebug() << file.fileName() << "not found";
		exit(1);
	}
}
	
void SettingsReader::read_radios_settings(QString s, int i)
{
	QFile file;

	file.setFileName(s);
	
	bool res = file.open(QIODevice::ReadOnly | QIODevice::Text);

	if (res)
	{
		QString line = file.readLine();

		QStringList list = line.split(",");

		radio[i].name = list.at(0);
		radio[i].ip = list.at(1);
		radio[i].type = list.at(2).toInt();
		radio[i].an_dig = list.at(3).toInt();
		radio[i].channels = list.at(4).toInt();
		radio[i].num_contacts_gr = list.at(5).toInt();
		radio[i].num_contacts_ab = list.at(6).toInt();

		Contact cont;
		for (int var = 0; var < radio[i].num_contacts_gr; ++var)
		{
			line = file.readLine();
			list = line.split(",");
			cont.id = list.at(0).toInt();
			cont.name = list.at(1);
			cont.channel = list.at(2).toInt();
			radio[i].contact_gr.push_back(cont);
		}

		for (int var = 0; var < radio[i].num_contacts_ab; ++var)
		{
			line = file.readLine();
			list = line.split(",");
			cont.id = list.at(0).toInt();
			cont.name = list.at(1);
			cont.channel = list.at(2).toInt();
			radio[i].contact_ab.push_back(cont);
		}

		file.close();
	}
	else
	{
		qDebug() << s << "not found";
		exit(1);
	}
}


void SettingsReader::read_favorite()
{
	favForAllRadio.resize(server.directions);
	
	for (size_t i = 0; i < server.directions; i++)
	{
		favForAllRadio[i].resize(radio[i].channels);	
	}
	
	
	QFile file;
	
	file.setFileName("favorite.dat");
	
	if (file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QString s;
		s = file.readAll();
		if (!s.isEmpty())
		{
			QStringList sl = s.split('\n');
			for (size_t i = 0; i < sl.length(); i++)
			{
				QStringList sl_in = sl[i].split(',');
				favForAllRadio[sl_in.at(0).toInt()][sl_in.at(1).toInt()].push_back(sl_in.at(2).toInt());
			}
		}
	
		file.close();
	}
}

void SettingsReader::write_favorite()
{
	QFile file;
	
	QTextStream stream;

	file.setFileName("favorite.dat");
	
	if (file.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		for (size_t i = 0; i < server.directions; i++)
		{
			for (size_t j = 0; j < radio[i].channels; j++)
			{
				for (size_t k = 0; k < favForAllRadio[i][j].size(); k++)
				{
					stream << i << "," << j << "," << favForAllRadio[i][j][k] << "\n";
				} 
			}				
		}	
		
		file.close();
	}
}

void SettingsReader::display_favorites()
{
	
}
