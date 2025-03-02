#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLCDNumber>
#include <QPushButton>
#include <QGroupBox>
#include <QComboBox>
#include <vector>
#include <QDateTime>

#include <QTimer>
#include "hidapi/hidapi.h"
#include "SettingsReader.h"
#include "Udp.h"
#include <iostream>

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

struct Record
{
	QDateTime m_date;
	int m_who;
	int m_whoom;
	int m_type;
	QByteArray mic_buf;
};

class MainWindow : public QMainWindow
{
	enum CALL_TYPE
	{
		GROUP,
		PRIVATE
	};

	Q_OBJECT

		void
		load_contacts(int current_radio, int channel);

	int current_index{0};
	int current_channel{0};
	int current_call_type{3};  // 0-group 1-individ

	QPalette palet;
	QPalette new_palet;
	
	QTimer pb_add_Timer;
	public :
	    explicit MainWindow(QWidget *parent = 0);
	~MainWindow();
	QTimer* hid_timer;
	hid_device *handle;
    
	void interface_init();
	void sig_slot_init();

	void load_favorite();

	//void write_favorite();
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
	
	void pb_add_Timer_slot();
	void tabBarClicked_slot(int idx);
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
	void display_favorites(int radio, int channel);
	void write_favorite();
	void add_ch_click_slot();
	void add_ch_release_slot();
	void cb_ab_slot(const QString&);
	void cb_gr_slot(const QString&);
	void update_favorites(int curr_idx, int chan_num, int pb_idx, QString& s);

  signals:
	void sig_ptt(int);
	
};

#endif // MAINWINDOW_H
