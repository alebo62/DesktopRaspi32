#pragma once

#include <QThread>
#include <QObject>
#include <QDebug>
#include "hidapi/hidapi.h"

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