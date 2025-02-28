#include "MainWindow.h"
#include <QApplication>
#include <QObject>
#include <QThread>

#include <QDebug>
#include "hidapi/hidapi.h"
#include "alsa/asoundlib.h" 
#include "Sound.h"
#include "Udp.h"
#include "databasewriter.h"
#include "SettingsReader.h"
#include "MyThreadMic.h"
#include "MyThreadHid.h"


MainWindow* w;
Sound* sound;
Udp* udp;
DataBaseWriter* dbWriter;
SettingsReader* reader; 

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	
	reader = new SettingsReader();
//	if (DataBaseWriter::createConnection())
//		qDebug() << "Connect to DB";
//	else
//	{
//		qDebug() << "No conn to DB";
//		return -1;
//	}
		
//	dbWriter = new DataBaseWriter();
//	sound = new Sound();
//	udp = new Udp();
	w = new MainWindow();
	
	//MyThreadHid  thread_hid;
	//thread_hid.start();
	
	//MyThreadMic thread_mic;
	//thread_mic.start();
	
	w->show();
	
	
	//QObject::connect(&thread_hid, SIGNAL(pttKey(int)),	w, SLOT(slot_ptt(int)));
	
	//QObject::connect(&thread_hid, SIGNAL(pttKey(int)),	&thread_mic, SLOT(slot_ptt(int)));
	
	//QObject::connect(w, SIGNAL(sig_ptt(int)), &thread_mic, SLOT(slot_ptt(int)));
	
	//QObject::connect(&thread_mic, SIGNAL(sig_udp()), udp, SLOT(slot_udp()));

	
	return a.exec();
}

#include "DesktopRaspi32.moc"

