#pragma once

#include "alsa/asoundlib.h"
#include  <QObject>

class Sound : public QObject
{
	Q_OBJECT
	public :
    explicit Sound(QObject *parent = nullptr);
	
	snd_pcm_t *handle_mic;
	snd_pcm_t *handle_play;
	snd_pcm_hw_params_t *hwparams;
	snd_pcm_sframes_t frames;
	
	snd_ctl_t *ctl;
	snd_ctl_event_t * 	event;
		
	const char* name = "hw:2";
	snd_async_handler_t * 	handler;
	int private_data;
	//void callback(snd_async_handler_t * h);
	unsigned char play_buffer[960];
	unsigned char *mic_buffer = nullptr;
	
private:
	void sound_mic_init();
	void sound_play_init();
		
};
