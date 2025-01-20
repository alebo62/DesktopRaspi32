#include "MainWindow.h"
#include <QApplication>
#include <QObject>
#include <QThread>

#include <QDebug>
#include "hidapi/hidapi.h"
#include "alsa/asoundlib.h" 
#include "Sound.h"
#include "Udp.h"
#include "DataBase.h"
#include "SettingsReader.h"

MainWindow* w;
Sound* sound;
Udp* udp;
DataBase* dbase;
SettingsReader* reader; 

class MyThreadMic : public QThread {
	Q_OBJECT

	public :
	    unsigned char buffer[1];
	void run()
	{
		int res, err;
		
		snd_ctl_t *ctl;
		snd_ctl_event_t * 	event;
		
		const char* name = "hw:2";

		err = snd_ctl_open(&ctl, name, SND_CTL_READONLY);
	
		if (err < 0) {
			qDebug() << "Cannot open ctl " << name;
		}
		else
		{
			qDebug() << "Open ctl " << name;
		}
	
		err = snd_ctl_subscribe_events(ctl, -1);
		if (err < 0)
		{
			qDebug() << "Cannot open subscribe events to ctl " <<  name;
		}
		else
		{
			qDebug() << "Open subscribe events to ctl " <<  name;
		}
		snd_ctl_event_alloca(&event);
		pollfd* fds = new pollfd;
		snd_ctl_poll_descriptors(ctl, fds, 1);
		err = poll(fds, 1, -1);
		if (err <= 0) {
			qDebug() << "poll error!!!";			
		}
		unsigned short revents;
		
		
		while (1)
		{
			//QThread::msleep(100);
			snd_ctl_poll_descriptors_revents(ctl, fds, 1, &revents);
			if (revents & POLLIN) {
				
				//res = snd_ctl_read(ctl, event);	
				//if (res >= 0)
				qDebug() << "Opa!";
			}
			//hid_read(w->handle, buffer, 1);
			//emit ptt(buffer[0]);
			//qDebug() << buffer[0];
		}
	}

signals:
	void pttKey(int);
};
class MyThreadHid : public QThread {
	Q_OBJECT

	public :
	    unsigned char buffer[1];
	void run()
	{

		while (1)
		{
			QThread::msleep(100);
			//hid_read(w->handle, buffer, 1);
			//emit ptt(buffer[0]);
			//qDebug() << buffer[0];
		}
	}

signals:
	void pttKey(int);
};


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	
	reader = new SettingsReader();
	dbase = new DataBase();
	sound = new Sound();
	udp = new Udp();
	w = new MainWindow;
	
	MyThreadHid  thread_hid;
	thread_hid.start();
	
	MyThreadMic  thread_mic;
	thread_mic.start();
	
	w->show();
	
	QObject::connect(&thread_hid, SIGNAL(pttKey(int)),
						   w, SLOT(pttKeySlot(int)));
	
	return a.exec();
}

#include "DesktopRaspi32.moc"

