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
	
			
	//hid_close(handle);

	//hid_timer->start(200);

	//res = hid_read(handle, buffer, 1);
	//hid_write(handle, buffer, 1);
	
	interface_init();
	
	sig_slot_init();

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




void MainWindow::gr1_slot()
{
	int i = tab->currentIndex();
	
}


void MainWindow::gr2_slot()
{
	int i = tab->currentIndex();
	
}


void MainWindow::gr3_slot()
{
	int i = tab->currentIndex();
	
}

void MainWindow::gr4_slot()
{
	int i = tab->currentIndex();
	
}

void MainWindow::ab1_slot()
{
	int i = tab->currentIndex();
	
}


void MainWindow::ab2_slot()
{
	int i = tab->currentIndex();
	
}


void MainWindow::ab3_slot()
{
	int i = tab->currentIndex();
	
}

void MainWindow::ab4_slot()
{
	int i = tab->currentIndex();
	
}