#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	
	int res = hid_init();
	
	handle = hid_open(0x1962, 0x1809, NULL);
	if (!handle)
		qDebug() << "unable open";
	else
		qDebug() << "open";
	
	
	connect(ui->pushButton_ptt1, SIGNAL(pressed()), this, SLOT(ptt_pressed()));
	connect(ui->pushButton_ptt1, SIGNAL(released()), this, SLOT(ptt_released()));
	
	connect(ui->pushButton_ChUp1,  SIGNAL(clicked()),  this, SLOT(ch_up_slot()));
	connect(ui->pushButton_ChDwn1, SIGNAL(clicked()), this,  SLOT(ch_dwn_slot()));

	//hid_close(handle);

	//hid_timer->start(200);

	//res = hid_read(handle, buffer, 1);
	//hid_write(handle, buffer, 1);

}

MainWindow::~MainWindow()
{
    delete ui;
}

//  Заглушка
void MainWindow::ButtonClicked()
{
	//    QMessageBox msgBox;
	//    msgBox.setText("Hello, World!");
	//    msgBox.setWindowTitle("VisualGDB Qt Demo");
	//    msgBox.exec();
}


