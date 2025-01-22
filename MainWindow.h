#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "hidapi/hidapi.h"
#include "SettingsReader.h"
#include "Udp.h"

extern SettingsReader* reader;
extern Udp* udp;

namespace Ui {
	class MainWindow;
}

enum CallTypes {
	eGroupCall     = 1,
	eEmrgGroupCall = 2,
	ePrivCall      = 3,
	eEmergPrivCall = 4,
	eAllCall       = 5,
	eEmergAllCall  = 6,
};

class MainWindow : public QMainWindow
{
	Q_OBJECT
    
	public :
	    explicit MainWindow(QWidget *parent = 0);
	~MainWindow();
	QTimer* hid_timer;
	hid_device *handle;


	protected slots :
	    void ButtonClicked();

private:
	Ui::MainWindow *ui;
	
public slots :
		void slot_ptt(int);
	void ptt_pressed();
	void ptt_released();
	void ch_up_slot();
	void ch_dwn_slot();
	
signals :
	void sig_ptt(int);
	
};

#endif // MAINWINDOW_H
