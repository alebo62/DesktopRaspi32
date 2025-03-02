#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	tab = new QTabWidget();
	
	// Change the radio signal-slot	
	
	connect(tab, &QTabWidget::tabBarClicked, this, &MainWindow::tabBarClicked_slot);
	
//	int res = hid_init();
//	
//	handle = hid_open(0x1962, 0x1809, NULL);
//	if (!handle)
//		qDebug() << "unable open";
//	else
//		qDebug() << "open";
	
			
	//hid_close(handle);

	//hid_timer->start(200);

	//res = hid_read(handle, buffer, 1);
	//hid_write(handle, buffer, 1);
	
	//pb_add_Timer = new QTimer(); 
		
	interface_init();
	
	palet = pb_add_ch[0]->palette();
	
	new_palet.setColor(pb_add_ch[current_index]->backgroundRole(), QColor(100,200,100,0));	
			
	for (size_t i{ 0 }; i < reader->server.directions; i++)
		load_contacts(i, 1);
		
	sig_slot_init();

	load_favorite();

	write_favorite();
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




