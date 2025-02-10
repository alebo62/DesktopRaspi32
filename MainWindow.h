#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLCDNumber>
#include <QPushButton>
#include <QGroupBox>
#include <QComboBox>
#include <vector>

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
    
	void interface_init();
	void sig_slot_init();
	// Что бы не проводить процедуку инициализации радиост. после перекл.каналов
	qint32 chan_change_state	{-1}	;
	
	QWidget *centralwidget;
	QPushButton *pb_ptt[4];
	QPushButton *pb_ch_dwn[4];
	QPushButton *pb_ch_up[4];
	QLCDNumber *lcdNumber[4];
	QGroupBox *groupBoxAb[4];
	QComboBox *combo_gr[4];
	QPushButton *pb_gr1[4];
	QPushButton *pb_gr2[4];
	QPushButton *pb_gr3[4];
	QPushButton *pb_gr4[4];
	QGroupBox *groupBoxGr[4];
	QComboBox *combo_ab[4];
	QPushButton *pb_ab1[4];
	QPushButton *pb_ab2[4];
	QPushButton *pb_ab3[4];
	QPushButton *pb_ab4[4];
	QPushButton *pb_add_ch[4];

	QWidget* wdg[4];
	QTabWidget* tab;


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
	void gr1_slot();
	void gr2_slot();
	void gr3_slot();
	void gr4_slot();
	void ab1_slot();
	void ab2_slot();
	void ab3_slot();
	void ab4_slot();
	
	
signals :
	void sig_ptt(int);
	
};

#endif // MAINWINDOW_H
