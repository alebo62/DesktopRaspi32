#pragma once

#include <QThread>
#include <QObject>
#include <alsa/asoundlib.h>
#include <QDebug>
#include "Sound.h"


extern Sound* sound;

class MyThreadMic : public QThread 
{
	Q_OBJECT

	volatile int flag = 0;
	int result = 0;
	snd_pcm_sframes_t buff_count = 160;
	int avail;

public:
	void run()
	{
		while (true) {
			avail =  snd_pcm_avail(sound->handle_mic);
			if (avail < 0)
				avail = snd_pcm_recover(sound->handle_mic, avail, 0);
			if (flag)
			{
				usleep(100);
				//    avail =  snd_pcm_avail(tcp->handle_mic);
				//qDebug() << avail;
				if (avail >= 160)
				{
					result = snd_pcm_readi(sound->handle_mic, sound->mic_buffer, buff_count);
					//avail =  snd_pcm_avail(tcp->handle_mic);
					//qDebug() << avail;
					emit sig_udp();

				}
			}
			else {

				result = snd_pcm_readi(sound->handle_mic, sound->mic_buffer, buff_count);
				usleep(10000);
			}
		}
	}

signals:
	void sig_udp();

	private slots :
	void slot_ptt(int i) 
	{
		flag = i;
	}

};


/*
 *public :
	    unsigned char buffer[1];
	    
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
 *
 **/